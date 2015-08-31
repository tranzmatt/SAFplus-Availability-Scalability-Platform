#include <reliableSocket.hxx>
#include "clLogApi.hxx"
#include <stdio.h>

#define MIN(a,b) ( (a) < (b) ? (a) : (b) )

namespace SAFplus
{
  // Callback function for Null Fragment Timer
  static void * nullFragmentTimerFunc(void* arg)
  {
    MsgSocketReliable* tempMsgSocket = (MsgSocketReliable*)arg;
    while(tempMsgSocket->nullFragmentTimer.isStop)
    {
      sleep(tempMsgSocket->nullFragmentTimer.interval);
      if(tempMsgSocket->nullFragmentTimer.status==TIMER_RUN)
      {
        tempMsgSocket->nullFragmentTimer.timerLock.lock();
        tempMsgSocket->handleNullFragmentTimerFunc();
        tempMsgSocket->nullFragmentTimer.timerLock.unlock();
      }
    }
    return NULL;
  }

  // Callback function for retransmission Timer
  static void* retransmissionTimerFunc(void* arg)
  {
    MsgSocketReliable* tempMsgSocket = (MsgSocketReliable*)arg;
    while(tempMsgSocket->retransmissionTimer.isStop)
    {
      sleep(tempMsgSocket->retransmissionTimer.interval);
      if(tempMsgSocket->retransmissionTimer.status==TIMER_RUN)
      {
        tempMsgSocket->retransmissionTimer.timerLock.lock();
        tempMsgSocket->handleRetransmissionTimerFunc();
        tempMsgSocket->retransmissionTimer.timerLock.unlock();
      }
      //call function
    }
    return NULL;
  }

  // Callback function for cumulative Ack Timer
  static void* cumulativeAckTimerFunc(void* arg)
  {
    MsgSocketReliable* tempMsgSocket = (MsgSocketReliable*)arg;
    while(tempMsgSocket->cumulativeAckTimer.isStop)
    {
      sleep(tempMsgSocket->cumulativeAckTimer.interval);
      if(tempMsgSocket->cumulativeAckTimer.status==TIMER_RUN)
      {
        tempMsgSocket->cumulativeAckTimer.timerLock.lock();
        tempMsgSocket->handleCumulativeAckTimerFunc();
        tempMsgSocket->cumulativeAckTimer.timerLock.unlock();
      }
    }
    return NULL;
  }



  // Callback function for Keep alive Timer
  static void* keepAliveTimerFunc(void* arg)
  {
    MsgSocketReliable* tempMsgSocket = (MsgSocketReliable*)arg;
    while(tempMsgSocket->keepAliveTimer.isStop)
    {
      sleep(tempMsgSocket->keepAliveTimer.interval);
      if(tempMsgSocket->keepAliveTimer.status==TIMER_RUN)
      {
        tempMsgSocket->keepAliveTimer.timerLock.lock();
        tempMsgSocket->handleKeepAliveTimerFunc();
        tempMsgSocket->keepAliveTimer.timerLock.unlock();
      }
    }
    return NULL;
  }


  // Handle Retransmission function
  void MsgSocketReliable::handleRetransmissionTimerFunc(void)
  {
    unackedSentQueueLock.lock();
    for(ReliableFragmentList::iterator iter = unackedSentQueue.begin();
        iter != unackedSentQueue.end();
        iter++)
    {
      ReliableFragment &frag = *iter;
      try
      {
        retransmitFragment(&frag);
      }
      catch(...)
      {
        // Handle Exception
      }
    }
    unackedSentQueueLock.unlock();

  }

  // Handle Null Fragment function
  void MsgSocketReliable::handleNullFragmentTimerFunc(void)
  {
      if (unackedSentQueue.empty())
      {
        try
        {
          // Send a new NULL segment if there is nothing to be retransmitted.
          queueAndSendReliableFragment(new NULLFragment(queueInfo.nextSequenceNumber()));
        }
        catch (...)
        {
          // Hanlde Exception
        }
      }
  }

  // Handle Cumulative Ack function
  void MsgSocketReliable::handleCumulativeAckTimerFunc(void)
  {
    this->sendACK();
  }

  // Handle Cumulative keep alive function
  void MsgSocketReliable::handleKeepAliveTimerFunc(void)
  {
    this->setconnection(connectionNotification::FAILURE);
  }

  // Compare two fragment
  int compareFragment(int frag1, int frag2)
  {
    if (frag1 == frag2)
    {
      return 0;
    }
    else if (((frag1 < frag2) && ((frag2 - frag1) > MAX_FRAGMENT_NUMBER/2)) ||
        ((frag1 > frag2) && ((frag1 - frag2) < MAX_FRAGMENT_NUMBER/2)))
    {
      return 1;
    }
    else
    {
      return -1;
    }
  }

  void MsgSocketReliable::handleReliableFragment(ReliableFragment *frag)
  {
    fragmentType fragType = frag->getType();
    if(fragType == fragmentType::FRAG_RST)
    {
      resetMutex.lock();
      isReset = true;
      resetMutex.unlock();
      setconnection(connectionNotification::RESET);
    }

    /*
     * When a FIN segment is received, no more packets
     * are expected to arrive after this segment.
     */
    if(fragType == fragmentType::FRAG_FIN)
    {
      switch(state)
      {
        case connectionState::CONN_SYN_SENT:
        {
          thisCond.notify_one();
          break;
        }
        case connectionState::CONN_CLOSED:
        {
          break;
        }
        default:
        {
          state = connectionState::CONN_CLOSE_WAIT;
          break;
        }
      }
    }
    bool bIsInSequence = false;
    recvQueueLock.lock();
    if(compareFragment(frag->seq(), queueInfo.getLastInSequence() ) <= 0 )
    {
      /* Drop packet: duplicate. */
    }
    else if(compareFragment(frag->seq(), nextSequenceNumber(queueInfo.getLastInSequence()) ) == 0 )
    {
      //fragment is the next fragment in queue. Add to in-seq queue
      bIsInSequence = true;
      if (inSeqQueue.size() == 0 || (inSeqQueue.size() + outOfSeqQueue.size() < recvQueueSize))
      {
        /* Insert in-sequence segment */
        queueInfo.setLastInSequence(frag->seq());
        if ( fragType == fragmentType::FRAG_DATA ||
            fragType ==  fragmentType::FRAG_RST ||
            fragType == fragmentType::FRAG_FIN)
        {
          inSeqQueue.push_back(*frag);
          //todo
//          if(frag->isLast())
//          {
//            recvQueueCond.notify_one();
//          }
        }
        checkRecvQueues();
      }
      else
      {
        /* Drop packet: queue is full. */
      }
    }
    else if(inSeqQueue.size() + outOfSeqQueue.size() < recvQueueSize)
    {
      //Fragment is not the next fragment in queue. Add it to out of seq queue
      bool added = false;
      for (ReliableFragmentList::iterator iter = outOfSeqQueue.begin();
          iter != outOfSeqQueue.end() && !added;
          iter ++)
      {
        ReliableFragment &s = *iter;
        int cmp = compareFragment(frag->seq(), s.seq());
        if (cmp == 0)
        {
          /* Ignore duplicate packet */
          added = true;
        }
        else if (cmp < 0)
        {
          outOfSeqQueue.insert(iter, *frag);
          added = true;
        }
      }

      if (!added)
      {
        outOfSeqQueue.push_back(*frag);
      }
      //inscreate out of sequence fragment
      queueInfo.increaseOutOfSequenceCounter();
      if (fragType == fragmentType::FRAG_DATA)
      {

      }
    }

    if (bIsInSequence &&
        ( fragType == fragmentType::FRAG_RST ||
            fragType == fragmentType::FRAG_NUL||
            fragType == fragmentType::FRAG_FIN))
    {
      sendACK();
    }
    else if ( (queueInfo.getOutOfSequenceCounter() > 0) &&
        (profile->maxOutOfSequence() == 0 || queueInfo.getOutOfSequenceCounter() > profile->maxOutOfSequence()) )
    {
      sendNAK();
    }
    else if ((queueInfo.getCumulativeAckCounter() > 0) &&
        (profile->maxCumulativeAcks() == 0 || queueInfo.getCumulativeAckCounter() > profile->maxCumulativeAcks()))
    {
      sendSingleAck();
    }
    else
    {
      cumulativeAckTimer.timerLock.lock();
      {
        if (cumulativeAckTimer.status==TIMER_PAUSE)
        {
          cumulativeAckTimer.interval=profile->cumulativeAckTimeout();
          cumulativeAckTimer.status=TIMER_RUN;
        }
      }
      cumulativeAckTimer.timerLock.unlock();
      boost::thread(cumulativeAckTimerFunc,this);

    }
    recvQueueLock.unlock();
  }

  void MsgSocketReliable::checkRecvQueues()
  {
    ReliableFragmentList::iterator it = outOfSeqQueue.begin();
    while (it != outOfSeqQueue.end() )
    {
      ReliableFragment &s = *it;
      if (compareFragment(s.seq(), nextSequenceNumber(queueInfo.getLastInSequence())) == 0)
      {
        queueInfo.setLastInSequence(s.seq());
        if (s.getType() == fragmentType::FRAG_DATA ||
            s.getType() == fragmentType::FRAG_RST ||
            s.getType() == fragmentType::FRAG_FIN)
        {
          inSeqQueue.push_back(s);
        }
        it = outOfSeqQueue.erase(it);
      }
      else
      {
        it++;
      }
    }
  }
  void MsgSocketReliable::handleSYNReliableFragment(SYNFragment *frag)
  {
    try
    {
      logDebug("MSG", "REL","Handle SYNC fragment [%d]",frag->seq());
      switch (state)
      {
        case connectionState::CONN_CLOSED:
        {
          queueInfo.setLastInSequence(frag->seq());
          state = connectionState::CONN_SYN_RCVD;
          logDebug("MSG", "REL","Socket([%d]-[%d]) : State CONN_CLOSED. set state to CONN_SYN_RCVD. Send sync frag to [%d] - [%d]",sock->handle().getNode(),sock->handle().getPort(), destination.getNode(),destination.getPort());
          ReliableSocketProfile* _profile = new ReliableSocketProfile(
              sendQueueSize,
              recvQueueSize,
              frag->getMaxFragmentSize(),
              frag->getMaxOutstandingFragments(),
              frag->getMaxRetransmissions(),
              frag->getMaxCumulativeAcks(),
              frag->getMaxOutOfSequence(),
              frag->getMaxAutoReset(),
              frag->getNulFragmentTimeout(),
              frag->getRetransmissionTimeout(),
              frag->getCummulativeAckTimeout());
          profile = _profile;
          SYNFragment* synFrag = new SYNFragment(
              queueInfo.setSequenceNumber(0),
              _profile->maxOutstandingSegs(),
              _profile->maxFragmentSize(),
              _profile->retransmissionTimeout(),
              _profile->cumulativeAckTimeout(),
              _profile->nullFragmentTimeout(),
              _profile->maxRetrans(),
              _profile->maxCumulativeAcks(),
              _profile->maxOutOfSequence(),
              _profile->maxAutoReset());
          synFrag->setAck(frag->seq());
          queueAndSendReliableFragment(synFrag);
          break;
        }
        case connectionState::CONN_SYN_SENT:
        {
          logDebug("MSG", "REL","current connection([%d]-[%d]) state : CONN_CLOSED. Set connection to established",sock->handle().getNode(),sock->handle().getPort());
          queueInfo.setLastInSequence(frag->seq());
          state = connectionState::CONN_ESTABLISHED;
          /*
           * Here the client accepts or rejects the parameters sent by the
           * server. For now we will accept them.
           */
          this->sendACK();
          this->setconnection(connectionNotification::OPENED);
          break;
        }
        default:
        {
          logDebug("MSG", "REL","Connection state : Error");
          break;
        }
      }
    }
    catch (...)
    {
      // TO DO EXCEPTION
    }
  }
  void MsgSocketReliable::handleACKReliableFragment(ReliableFragment *frag)
  {

  }
  void MsgSocketReliable::handleNAKReliableFragment(NAKFragment *frag)
  {
    logDebug("MSG", "REL","Handle NAK fragment [%d]",frag->seq());
    int length = 0;
    bool bFound = false;
    Byte* acks = frag->getACKs(&length);
    int lastInSequence = frag->getAck();
    int lastOutSequence = acks[length -1];
    unackedSentQueueLock.lock();
    /* Removed acknowledged fragments from unackedSent queue */
    ReliableFragmentList::iterator it = unackedSentQueue.begin();
    while(it != unackedSentQueue.end())
    {
      ReliableFragment& s = *it;
      if ((compareFragment(s.seq(), lastInSequence) <= 0))
      {
        it = unackedSentQueue.erase_and_dispose(it, delete_disposer());
        continue;
      }
      bFound = false;
      for (int i = 0; i < length; i++)
      {
        if ((compareFragment(s.seq(), acks[i]) == 0))
        {
          it = unackedSentQueue.erase_and_dispose(it, delete_disposer());
          bFound = true;
          break;
        }
      }
      if(bFound == false)
      {
        it++;
      }
    }
    /* Retransmit segments */
    for(ReliableFragmentList::iterator iter = unackedSentQueue.begin();
        iter != unackedSentQueue.end();
        iter++ )
    {
      ReliableFragment& s = *iter;
      if ((compareFragment(lastInSequence, s.seq()) < 0) &&
          (compareFragment(lastOutSequence, s.seq()) > 0))
      {
        try
        {
          retransmitFragment(&s);
        }
        catch (...)
        {
          // xcp.printStackTrace();
          // Handle Exception
        }
      }
    }
    unackedSentQueueCond.notify_all();
    unackedSentQueueLock.unlock();
  }

  void MsgSocketReliable::sendACK()
  {
    if (!outOfSeqQueue.empty() )
    {
      sendNAK();
    }
    else
    {
      sendSingleAck();
    }
  }
  void MsgSocketReliable::sendNAK()
  {
    logDebug("MSG", "REL","Send NAK fragment to Node [%d]",destination.getNode());
    if (outOfSeqQueue.empty())
    {
      return;
    }
    queueInfo.getAndResetCumulativeAckCounter();
    queueInfo.getAndResetOutOfSequenceCounter();

    /* Compose list of out-of-sequence sequence numbers */
    int size = outOfSeqQueue.size();
    int* acks = new int[size];
    int nIdx = 0;
    for (ReliableFragmentList::iterator it = outOfSeqQueue.begin();
        it != outOfSeqQueue.end();
        it++)
    {
      ReliableFragment& s = *it;
      acks[nIdx++] = s.seq();
    }
    try
    {
      int lastInSequence = queueInfo.getLastInSequence();
      this->sendReliableFragment(new NAKFragment(nextSequenceNumber(lastInSequence), lastInSequence, acks, size));
    }
    catch (...)
    {
      // Handle Exception
    }
  }

  void MsgSocketReliable::sendSingleAck()
  {
    if (queueInfo.getAndResetCumulativeAckCounter() == 0)
    {
      return;
    }
    try
    {
      int lastInSequence = queueInfo.getLastInSequence();
      logDebug("MSG", "REL","Socket([%d - %d]) : Send single ACK [%d] to Node [%d] port [%d]",sock->handle().getNode(),sock->handle().getPort(),lastInSequence,destination.getNode(),destination.getPort());
      this->sendReliableFragment(new ACKFragment(nextSequenceNumber(lastInSequence), lastInSequence));
    }
    catch (...)
    {
      // Handle Exception
    }
  }

  int MsgSocketReliable::nextSequenceNumber(int seqn)
  {
    return (seqn + 1) % MAX_FRAGMENT_NUMBER;
  }

  void MsgSocketReliable::sendSYN()
  {
    //Todo
  }
  void MsgSocketReliable::setACK(ReliableFragment *frag)
  {
    if (queueInfo.getAndResetCumulativeAckCounter() == 0)
    {
      return;
    }
    frag->setAck(queueInfo.getLastInSequence());
  }

  void MsgSocketReliable::getACK(ReliableFragment *frag)
  {
    int ackn = frag->getAck();
    logDebug("REL","MSL","Socket([%d - %d]) : ack : [%d]",sock->handle().getNode(),sock->handle().getPort(),ackn);
    if (ackn < 0)
    {
      logDebug("REL","MSL","Ack < 0. Return ");
      return;
    }
    queueInfo.getAndResetOutstandingFragmentsCounter();
    if (state == connectionState::CONN_SYN_RCVD)
    {
      logDebug("REL","MSL","Socket([%d - %d]) : Current state CONN_SYN_RCVD. set to CONN_ESTABLISHED",sock->handle().getNode(),sock->handle().getPort());
      state = connectionState::CONN_ESTABLISHED;
      setconnection(connectionNotification::OPENED);
    }
    unackedSentQueueLock.lock();
    for(ReliableFragmentList::iterator iter = unackedSentQueue.begin();
        iter != unackedSentQueue.end();
    )
    {
      ReliableFragment &fragment = *iter;
      if(compareFragment(fragment.seq(), ackn) <= 0)
      {
        logDebug("REL","MSL","Socket([%d - %d]) : UnackedSentQueue delete Fragment [%d]",sock->handle().getNode(),sock->handle().getPort(),fragment.seq());
        iter = unackedSentQueue.erase_and_dispose(iter, delete_disposer());
      }
      else
      {
        iter++;
      }
    }
    if(unackedSentQueue.empty())
    {
      // Cancel Retransmisstion Timer
      retransmissionTimer.status==TIMER_PAUSE;
    }
    unackedSentQueueCond.notify_all();
    unackedSentQueueLock.unlock();
  }

  //send a reliable fragment
  void MsgSocketReliable::sendReliableFragment(ReliableFragment *frag)
  {
    /* Piggyback any pending acknowledgments */
    if (frag->getType()==fragmentType::FRAG_DATA || frag->getType()==fragmentType::FRAG_RST || frag->getType()==fragmentType::FRAG_FIN || frag->getType()==fragmentType::FRAG_NUL)
    {
      //TODO checkAndSetAck(s);
      setACK(frag);
    }
    /* Reset null segment timer */
    if (frag->getType()==fragmentType::FRAG_DATA || frag->getType()==fragmentType::FRAG_RST || frag->getType()==fragmentType::FRAG_FIN)
    {
      nullFragmentTimer.status=TimerStatus::TIMER_PAUSE;
      nullFragmentTimer.status=TimerStatus::TIMER_RUN;
    }
    //send reliable fragment
    if(sock==NULL)
    {
      return;
    }
    if(sock->msgPool==NULL)
    {
      return;
    }
    Message* reliableFragment;
    reliableFragment=sock->msgPool->allocMsg();
    assert(reliableFragment);
    reliableFragment->setAddress(destination);
    MsgFragment* fragment = reliableFragment->append(0);
    fragment->set((Byte*)frag->getBytes(),frag->length());
    logDebug("REL","MSL","Send Fragment to node [%d] port [%d] ",reliableFragment->getAddress().getNode(),reliableFragment->getAddress().getPort());
    sock->send(reliableFragment);
  }

  // send fragment and store it in uncheck ack
  void MsgSocketReliable::queueAndSendReliableFragment(ReliableFragment* frag)
  {
    unackedSentQueueLock.lock();
    while ((unackedSentQueue.size() >= sendQueueSize) ||
        ( queueInfo.getOutstandingFragmentsCounter() > profile->maxOutstandingSegs()))
    {
      try
      {
        unackedSentQueueCond.wait(unackedSentQueueLock);
      }
      catch (...)
      {
        // Hanlde Exception
      }
    }
    queueInfo.incOutstandingFragmentsCounter();
    logDebug("REL","MSL","Socket([%d - %d]) : Store Fragment [%d] to unackedSent Queue",sock->handle().getNode(),sock->handle().getPort(),frag->seq());
    unackedSentQueue.push_back(*frag);
    unackedSentQueueLock.unlock();
    if (isClosed)
    {
      // Hanlde Exception
      //print log and exit
      return;
    }
    /* Re-start retransmission timer */
    if (!(frag->getType() == fragmentType::FRAG_NAK) && !(frag->getType() == fragmentType::FRAG_ACK))
    {
      if (retransmissionTimer.status==TIMER_PAUSE)
      {
        //retransmissionTimer.interval=profile->retransmissionTimeout();
        retransmissionTimer.status==TIMER_RUN;
        boost::thread(retransmissionTimerFunc,this);
      }
    }
    sendReliableFragment(frag);
  }

  Message* MsgSocketReliable::receive(uint_t maxMsgs,int maxDelay)
  {
    return sock->receive(maxMsgs,maxDelay);
  }

  ReliableFragment* MsgSocketReliable::receiveReliableFragment(Handle &handle)
  {
    ReliableFragment* p_Fragment;
    Message* p_Msg = nullptr;
    MsgFragment* p_NextFrag = nullptr;
    int iMaxMsg = 1;
    int iDelay = 1;

    p_Msg = this->sock->receive( iMaxMsg, iDelay);
    if(p_Msg == nullptr)
    {
      return nullptr;

    }
    handle = p_Msg->getAddress();
    p_NextFrag = p_Msg->firstFragment;
    if(p_NextFrag == nullptr)
    {
      p_Fragment= nullptr;      return nullptr;
    }
    p_Fragment = ReliableFragment::parse((Byte*)p_NextFrag->read(0), 0, p_NextFrag->len);
    p_Fragment->address=p_Msg->getAddress();
    fragmentType fragType = p_Fragment->getType();
    if(fragType == fragmentType::FRAG_DATA ||
        fragType == fragmentType::FRAG_NUL ||
        fragType == fragmentType::FRAG_RST ||
        fragType == fragmentType::FRAG_FIN ||
        fragType == fragmentType::FRAG_SYN)
    {
      queueInfo.increaseCumulativeAckCounter();
    }

    if(iskeepAlive)
    {
      // Reset keepAliveTimer
      // keepAliveTimer
    }
    return p_Fragment;
  }

  void MsgSocketReliable::retransmitFragment(ReliableFragment *frag)
  {
    logDebug("MSG", "REL","Socket([%d - %d]) : Retransmit Fragment fradId [%d] to node [%d]",sock->handle().getNode(),sock->handle().getPort(), frag->seq(),destination.getNode());
    if (profile->maxRetrans() > 0)
    {
      frag->setRetxCounter(frag->getRetxCounter()+1);
    }
    if (profile->maxRetrans() != 0 && frag->getRetxCounter() > profile->maxRetrans())
    {
      setconnection(connectionNotification::FAILURE);
      return ;
    }
    assert(sock);
    Message* reliableReliableFragment =sock->msgPool->allocMsg();
    assert(reliableReliableFragment);
    reliableReliableFragment->setAddress(destination);
    MsgFragment* pfx  = reliableReliableFragment->append(1);
    * ((unsigned char*)pfx->data()) = messageType;
    pfx->len = 1;
    MsgFragment* fragment = reliableReliableFragment->append(0);
    fragment->set((char*)frag,frag->length());
    sock->send(reliableReliableFragment);
  }


  void MsgSocketReliable::connectionFailure()
  {
    logDebug("MSG", "REL","Socket([%d - %d]) : set connection to Failure",sock->handle().getNode(),sock->handle().getPort());
    closeMutex.lock();
    {
      if (isClosed)
      {
        closeMutex.unlock();
        return;
      }
      switch (state)
      {
        case connectionState::CONN_SYN_SENT:
        {
          thisMutex.lock();
          {
            thisCond.notify_one();
          }
          thisMutex.unlock();
          break;
        }
        case connectionState::CONN_CLOSE_WAIT :
        case connectionState::CONN_SYN_RCVD :
        case connectionState::CONN_ESTABLISHED :
        {
          isConnected = false;
          unackedSentQueueLock.lock();
          {
            unackedSentQueueCond.notify_all();
          }
          unackedSentQueueLock.unlock();
          recvQueueLock.lock();
          {
            recvQueueCond.notify_one();
          }
          recvQueueLock.unlock();
          closeImpl();
          break;
        }
      }
      state = connectionState::CONN_CLOSED;
      isClosed = true;
    }
    closeMutex.unlock();
  }


  void MsgSocketReliable::closeImplThread(void* arg)
  {
    MsgSocketReliable* p_this = (MsgSocketReliable*) arg;
    p_this->handleCloseImpl();
  }

  void MsgSocketReliable::handleCloseImpl(void)
  {
    //keepAliveTimer->destroy();
    keepAliveTimer.isStop=true;
    nullFragmentTimer.isStop=true;
    try
    {
      boost::this_thread::sleep_for(boost::chrono::seconds{profile->nullFragmentTimeout() * 2});
    }
    catch (...)
    {
      // Hanlde Exception
    }
    retransmissionTimer.isStop=true;
    cumulativeAckTimer.isStop=true;
    // Close UDP socket.
    // TO DO

    setconnection(connectionNotification::CLOSE);
  }

  void MsgSocketReliable::closeImpl()
  {
    nullFragmentTimer.status=TIMER_PAUSE;
    keepAliveTimer.status=TIMER_PAUSE;
    state = connectionState::CONN_CLOSE_WAIT;
    boost::thread closeThread = boost::thread(MsgSocketReliable::closeImplThread, this);
  }
  void MsgSocketReliable::setconnection(connectionNotification state)
  {
    switch(state)
    {
      case connectionNotification::CLOSE :
        break;
      case connectionNotification::FAILURE :
      {
        connectionFailure();
        break;
      }
      case connectionNotification::OPENED :
      {
        connectionOpened();
        break;
      }
      case connectionNotification::REFUSED :
        break;
      case connectionNotification::RESET :
        break;
    }
  }

  void MsgSocketReliable::connectionOpened(void)
  {
    logDebug("MSG", "REL","Socket([%d - %d]) : set connection to Opened",sock->handle().getNode(),sock->handle().getPort());
    if(isConnected)
    {
      nullFragmentTimer.status = TIMER_RUN;
      boost::thread(nullFragmentTimerFunc,this);
      if(iskeepAlive)
      {
        keepAliveTimer.status = TIMER_RUN;
        boost::thread(keepAliveTimerFunc,this);
      }
      resetMutex.lock();
      {
        isReset = false;
        resetCond.notify_one();
      }
      resetMutex.unlock();
    }
    else
    {
      thisMutex.lock();
      {
        isConnected = true;
        state = connectionState::CONN_ESTABLISHED;
      }
      thisCond.notify_one();
      thisMutex.unlock();
      connectionClientOpen();

    }
  }
  static void ReliableSocketThread(void * arg)
  {
    MsgSocketReliable* p_this = (MsgSocketReliable*)arg;
    p_this->handleReliableSocketThread();
  }

  MsgSocketReliable::MsgSocketReliable(uint_t port,MsgTransportPlugin_1* transport)
  {
    sock=transport->createSocket(port);
    profile = new ReliableSocketProfile();
    queueInfo.fragNumber =0;
    queueInfo.lastFrag=0;
    queueInfo.numberOfCumAck=0;
    queueInfo.numberOfOutOfSeq=0;
    queueInfo.numberOfNakFrag=0; /* Outstanding segments counter */
    rcvThread = boost::thread(ReliableSocketThread, this);
  }
  MsgSocketReliable::MsgSocketReliable(uint_t port,MsgTransportPlugin_1* transport,Handle destination)
  {
    sock=transport->createSocket(port);
    rcvThread = boost::thread(ReliableSocketThread, this);
    profile = new ReliableSocketProfile();
    connect(destination,0);
  }
  MsgSocketReliable::MsgSocketReliable(MsgSocket* socket)
  {
    sock=socket;
    rcvThread = boost::thread(ReliableSocketThread, this);
  }


  void MsgSocketReliable::init()
  {
    //start receiver thread.
    rcvThread.start_thread();
  }

  void MsgSocketReliable::handleReliableSocketThread(void)
  {
    fragmentType fragType = fragmentType::FRAG_UDE;
    Handle handle;
    logDebug("REL","INI"," Socket([%d - %d]) : start thread to receive and handle fragment from [%d] [%d].",sock->handle().getNode(),sock->handle().getPort(),destination.getNode(),destination.getPort());
    while (1)
    {
      ReliableFragment* pFrag =receiveReliableFragment(handle);
      if(pFrag==nullptr)
      {
        logDebug("REL","INI","Receive NULL fragment . Exit thread");
        return;
      }
      fragType = pFrag->getType();
      logDebug("MSG", "REL","Socket([%d - %d]) : Receive reliable fragment Id [%d] fragment type [%d] from node [%d] port [%d]",sock->handle().getNode(),sock->handle().getPort(),pFrag->seq(),fragType,handle.getNode(),handle.getPort());

      if (fragType == fragmentType::FRAG_SYN)
      {
        this->destination = handle;
        handleSYNReliableFragment((SYNFragment*)pFrag);
      }
      else if (fragType == fragmentType::FRAG_NAK)
      {
        handleNAKReliableFragment((NAKFragment*)pFrag);
      }
      else if (fragType == fragmentType::FRAG_ACK)
      {
        // do nothing.
      }
      else
      {
        handleReliableFragment(pFrag);
      }
      getACK(pFrag);
    }
    logDebug("REL","INI","Receive NULL fragment . Exit thread");
  }

  MsgSocketReliable::~MsgSocketReliable()
  {
    //TODO
  }

  void MsgSocketReliable::send(Message* msg)
  {

  }
  void MsgSocketReliable::writeReliable(Byte* buffer, int offset, int len)
  {
    //MsgFragment* p_Frag = nullptr;
    logDebug("MSG", "REL","send buffer to  node [%d] in reliable mode ",destination.getNode());
    if (isClosed)
    {
      throw new Error("Socket is closed");
    }

    if (!isConnected)
    {
      throw new Error("Connection reset");
    }

    int totalBytes = 0;
    resetMutex.lock();
    {
      while (isReset)
      {
        try
        {
          resetCond.wait(resetMutex);
        }
        catch (...)
        {
          // Handle Exception
        }
      }
      int off = 0;
      int writeBytes = 0;
      while(totalBytes<len)
      {
        writeBytes = MIN(profile->maxFragmentSize() - RUDP_HEADER_LEN,len - totalBytes);
        if(totalBytes+writeBytes<len)
        {
          queueAndSendReliableFragment(new DATFragment(queueInfo.nextSequenceNumber(),
              queueInfo.getLastInSequence(), buffer, off + totalBytes, writeBytes));
          totalBytes += writeBytes;
        }
        else
        {
          logDebug("MSG", "REL","send last fragment to  node [%d] in reliable mode ",destination.getNode());
          queueAndSendReliableFragment(new DATFragment(queueInfo.nextSequenceNumber(),
              queueInfo.getLastInSequence(), buffer, off + totalBytes, writeBytes,1));
          totalBytes += writeBytes;
        }
      }
    }
  }

  void MsgSocketReliable::send(SAFplus::Handle destination, void* buffer, uint_t length,uint_t msgtype)
  {
    // TODO
  }

  int MsgSocketReliable::readReliable(Byte* buffer, int offset, int len)
  {
    logDebug("MSG", "REL","receive buffer from node [%d] in reliable mode ",destination.getNode());
    int totalBytes = 0;
    recvQueueLock.lock();
    {
      while (true)
      {
        while (inSeqQueue.empty())
        {
          if (isClosed)
          {
            throw Error("Socket is closed");
          }
          if (!isConnected)
          {
            throw Error("Connection reset");
          }
          try
          {
            if (timeout == 0)
            {
              recvQueueCond.wait(recvQueueLock);
            }
            else
            {
              recvQueueCond.timed_wait(recvQueueLock, timeout);
            }
          }
          catch (...)
          {
            // Handle Exception.
          }
        }
        for (ReliableFragmentList::iterator it = inSeqQueue.begin();
            it != inSeqQueue.end();)
        {
          ReliableFragment &s = *it;
          ReliableFragment * p_frag = &s;
          if (s.getType() == fragmentType::FRAG_RST)
          {
            inSeqQueue.erase_and_dispose(it, delete_disposer());
            break;
          }
          else if (s.getType() == fragmentType::FRAG_FIN)
          {
            if (totalBytes <= 0)
            {
              inSeqQueue.erase_and_dispose(it, delete_disposer());
              recvQueueLock.unlock();
              return -1; /* EOF */
            }
            break;
          }
          else if (s.getType() == fragmentType::FRAG_DATA)
          {

            int length = 0;
            Byte* data = ((DATFragment*) &s)->getData();
            length = ((DATFragment*) &s)->length() - RUDP_HEADER_LEN ;
            if(totalBytes + length > len)
            {
              if (totalBytes <= 0)
              {
                throw new Error("insufficient buffer space");
              }
              break;
            }
            memcpy(buffer + (offset+totalBytes), (void*)data , length);
            inSeqQueue.erase_and_dispose(it, delete_disposer());
            totalBytes += length;
//            if(((DATFragment*) &s)->isLast())
//            {
//              //check out of sequence queue
//              if()
//              break;
//
//              //exist while loop
//            }
          }
          it++;
        }
        if(totalBytes > 0)
        {
          recvQueueLock.unlock();
          return totalBytes;
        }
      }
    }
    recvQueueLock.unlock();
    return totalBytes;
  }

  void MsgSocketReliable::connect(Handle destination, int timeout)
  {
    logDebug("REL","MSR","Connect to log server");
    if (timeout < 0)
    {
      throw Error("connect: timeout can't be negative");
    }
    if (isClosed)
    {
      throw Error("Socket is closed");
    }
    if (isConnected)
    {
      throw new Error("already connected");
    }
    this->destination = destination;
    // Synchronize sequence numbers
    state = connectionState::CONN_SYN_SENT;
    int sequenceNum=queueInfo.setSequenceNumber(0);
    ReliableFragment *frag = new SYNFragment(sequenceNum,
        profile->maxOutstandingSegs(), profile->maxFragmentSize(),
        profile->retransmissionTimeout(), profile->cumulativeAckTimeout(),
        profile->nullFragmentTimeout(), profile->maxRetrans(),
        profile->maxCumulativeAcks(), profile->maxOutOfSequence(),
        profile->maxAutoReset());

    logDebug("REL","MSR","Socket([%d - %d]) : Create syn fragment with folow parameter [%d] [%d] [%d] [%d] [%d] [%d] [%d] [%d] [%d] [%d].",sock->handle().getNode(),sock->handle().getPort(),sequenceNum,
        profile->maxOutstandingSegs(), profile->maxFragmentSize(),
        profile->retransmissionTimeout(), profile->cumulativeAckTimeout(),
        profile->nullFragmentTimeout(), profile->maxRetrans(),
        profile->maxCumulativeAcks(), profile->maxOutOfSequence(),
        profile->maxAutoReset());

    queueAndSendReliableFragment(frag);

    // Wait for connection establishment (or timeout)
    bool timedout = false;
    thisMutex.lock();
    if (!isConnected)
    {
      try
      {
        if (timeout == 0)
        {
          thisCond.wait(thisMutex);
        }
      }
      catch (...)
      {
        // Hanle Exception
      }
    }
    thisMutex.unlock();
    if (state == connectionState::CONN_ESTABLISHED)
    {
      return;
    }

    unackedSentQueueLock.lock();
    {
      unackedSentQueue.clear();
      unackedSentQueueCond.notify_all();
    }
    unackedSentQueueLock.unlock();

    queueInfo.reset();
    retransmissionTimer.status = TIMER_PAUSE;
    switch (state)
    {
      case connectionState::CONN_SYN_SENT:
      {
        setconnection(connectionNotification::REFUSED);
        state = connectionState::CONN_CLOSED;
        if (timedout)
        {
          throw new Error("SocketTimeoutException");
        }
        throw new Error("Connection refused");

      }
      case connectionState::CONN_CLOSED:
      case connectionState::CONN_CLOSE_WAIT:
      {
        state = connectionState::CONN_CLOSED;
        throw Error("Socket closed");
      }
    }
  }

  void MsgSocketReliable::close()
  {
    closeMutex.lock();
    {
      if (isClosed)
      {
        closeMutex.unlock();
        return;
      }
      try
      {
        // Runtime.getRuntime().removeShutdownHook(_shutdownHook);
      }
      catch (...)
      {
        // Handle Exception
      }
      switch (state)
      {
        case connectionState::CONN_SYN_SENT:
        {
          thisMutex.lock();
          {
            thisCond.notify_one();
          }
          thisMutex.unlock();
          break;
        }
        case connectionState::CONN_CLOSE_WAIT:
        case connectionState::CONN_SYN_RCVD:
        case connectionState::CONN_ESTABLISHED:
        {
          sendReliableFragment(new FINFragment(queueInfo.nextSequenceNumber()));
          closeImpl();
          break;
        }
        case connectionState::CONN_CLOSED:
        {
          retransmissionTimer.isStop = true;
          cumulativeAckTimer.isStop = true;
          keepAliveTimer.isStop = true;
          nullFragmentTimer.isStop = true;
          break;
        }
      }
      isClosed = true;
      state = connectionState::CONN_CLOSED;

      unackedSentQueueLock.lock();
      {
        unackedSentQueueCond.notify_one();
      }
      unackedSentQueueLock.unlock();
    }
    closeMutex.unlock();
  }
  void MsgSocketReliable::flush()
  {
   sock->flush();
  }
  void MsgSocketReliable::connectionClientOpen()
  {
  };

  void MsgSocketServerReliable::addClientSocket(Handle destAddress)
  {
    if (clientSockTable[destAddress] == nullptr)
    {
      try
      {
        MsgSocketClientReliable *sockClient = new MsgSocketClientReliable(sock,destAddress);
        sockClient->sockServer=this;
        clientSockTable[destAddress]=sockClient;
      }
      catch (...)
      {
        // Handle Exception
        throw Error("add client socket error");
      }
    }
  }

  void MsgSocketServerReliable::removeClientSocket(Handle destAddress)
  {
    clientSockTable.erase(destAddress);
    if (clientSockTable.empty())
    {
      if (isClosed==true)
      {
        delete sock;
      }
    }
  }

  void MsgSocketServerReliable::handleRcvThread()
  {
    Message* p_Msg = nullptr;
    int iMaxMsg = 1;
    int iDelay = 1;
    Handle destinationAddress;
    MsgFragment* p_NextFrag = nullptr;
    logDebug("REL","MSS","Socket server ([%d - %d]) : Start server receive thread.",sock->handle().getNode(),sock->handle().getPort());
    while (true)
    {
      try
      {
        p_Msg=this->sock->receive(iMaxMsg,iDelay);
        destinationAddress = p_Msg->getAddress();
        logDebug("REL","MSS","Socket server ([%d - %d]) : Receive fragment from [%d] - [%d]....",sock->handle().getNode(),sock->handle().getPort(),destinationAddress.getNode(),destinationAddress.getPort());
        ReliableFragment* p_Fragment = nullptr;
        p_NextFrag = p_Msg->firstFragment;
        if(p_NextFrag == nullptr)
        {
          logError("REL","MSS","Socket server ([%d - %d]) : Receive fragment null. Return",sock->handle().getNode(),sock->handle().getPort());
          return;
        }
        p_Fragment = ReliableFragment::parse((Byte*)p_NextFrag->read(0), 0, p_NextFrag->len);
        p_Fragment->address=p_Msg->getAddress();
        logDebug("REL","MSS","Fragment type : [%d] Fragment sequence [%d] ",p_Fragment->getType(),p_Fragment->seq());
        if(!isClosed)
        {
          if (p_Fragment->getType()==FRAG_SYN)
          {
            logDebug("REL","INI","Socket server : Receive SYN fragment from [%d] - [%d] .",destinationAddress.getNode(),destinationAddress.getPort());
            if(clientSockTable[destinationAddress]==nullptr)
            {
              logDebug("REL","INI","Socket server Create socket client and add to client Table");
              addClientSocket(destinationAddress);
            }
          }
        }
        if(clientSockTable[destinationAddress]!=nullptr)
        {
          MsgSocketClientReliable *socket = clientSockTable[destinationAddress];
          socket->receiverFragment(p_Fragment);
        }
      }catch (...)
      {

      }
    }
  }
  void MsgSocketServerReliable::rcvThread(void * arg)
  {
    MsgSocketServerReliable* p_this = (MsgSocketServerReliable*)arg;
    p_this->handleRcvThread();
  }
  MsgSocketServerReliable::MsgSocketServerReliable(uint_t port,MsgTransportPlugin_1* transport)
  {
    logError("REL","INI","Init sock server. ");
    sock=transport->createSocket(port);
    ServerRcvThread = boost::thread(rcvThread, this);
  }
  MsgSocketServerReliable::MsgSocketServerReliable(MsgSocket* socket)
  {
    sock=socket;
    ServerRcvThread = boost::thread(rcvThread, this);
  }
  void MsgSocketServerReliable::init()
  {
    ServerRcvThread.start_thread();
  }

  MsgSocketClientReliable* MsgSocketServerReliable::accept()
  {
    listenSockMutex.lock();
    while (listenSock.empty())
    {
      try
      {
        logDebug("REL","INI", "Socket server : ListenSock list is empty. Waiting for socket client.");
        listenSockCond.wait(listenSockMutex);
      }
      catch (...)
      {
        //handle exception
      }
    }
    listenSockMutex.unlock();
    MsgSocketClientReliable* sock = (MsgSocketClientReliable*)&(listenSock.front());
    logDebug("REL","INI", "Get Socket from listenSock list.");
    listenSock.pop_front();
    return sock;
  }

  ReliableFragment* MsgSocketClientReliable::receiveReliableFragment(Handle &handle)
  {
    this->sockServer->fragmentQueueLock.lock();
    while (sockServer->fragmentQueue.empty())
    {
      try
      {
        sockServer->fragmentQueueCond.wait(sockServer->fragmentQueueLock);
      }
      catch(...)
      {
        // Handle Exception
      }
    }

    ReliableFragment* p_Fragment=&sockServer->fragmentQueue.front();
    handle=p_Fragment->address;
    sockServer->fragmentQueue.pop_front();
    sockServer->fragmentQueueLock.unlock();
    return p_Fragment;
  }

  void MsgSocketClientReliable::receiverFragment(ReliableFragment* frag)
  {
    sockServer->fragmentQueueLock.lock();
    sockServer->fragmentQueue.push_back(*frag);
    sockServer->fragmentQueueCond.notify_one();
    sockServer->fragmentQueueLock.unlock();
  }
  void MsgSocketClientReliable::connectionClientOpen()
  {
    logDebug("MSG", "REL","Socket client :  Add socket to listenList");
    sockServer->listenSockMutex.lock();
    sockServer->listenSock.push_back(*(MsgSocketReliable*)sock);
    sockServer->listenSockCond.notify_one();
    sockServer->listenSockMutex.unlock();
  }
};
