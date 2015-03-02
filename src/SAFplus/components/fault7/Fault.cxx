/* Standard headers */
#include <string>
/* SAFplus headers */

#include <clCommon.hxx>
#include <clIocPortList.hxx>
#include <clFaultIpi.hxx>
#include <clHandleApi.hxx>
#include <boost/functional/hash.hpp>
#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/allocators/allocator.hpp>
#include <boost/interprocess/errors.hpp>
#include <boost/foreach.hpp>
#include <boost/unordered_map.hpp>
#include <functional>
#include <boost/functional/hash.hpp>
#include <boost/thread.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/asio/ip/address.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/foreach.hpp>
#include <boost/unordered_map.hpp>
#include <clCommon.hxx>
#include <clCustomization.hxx>
#include <clNameApi.hxx>
#include <clIocPortList.hxx>
#include <clHandleApi.hxx>
#include <clFaultPolicyPlugin.hxx>
#include <FaultStatistic.hxx>
#include <FaultHistoryEntity.hxx>
#include <clObjectMessager.hxx>
#include <time.h>

using namespace SAFplus;
using namespace SAFplusI;
using namespace std;
#define FAULT "FLT"
#define FAULT_ENTITY "ENT"
#define FAULT_SERVER "SVR"
namespace SAFplus
{
	FaultSharedMem fsm;
	static unsigned int MAX_MSGS=25;
	static unsigned int MAX_HANDLER_THREADS=10;
    typedef boost::unordered_map<SAFplus::FaultPolicy,ClPluginHandle*> FaultPolicyMap;
    FaultPolicyMap faultPolicies;


    // Register a Fault Entity to Fault Server
    void Fault::sendFaultAnnounceMessage(SAFplus::Handle other, SAFplus::FaultState state)
    {
    	FaultMessageProtocol sndMessage;
        sndMessage.reporter = reporter;
        sndMessage.messageType = FaultMessageTypeT::MSG_ENTITY_JOIN;
        sndMessage.state = state;
        sndMessage.faultEntity=other;
        sndMessage.data.init(SAFplusI::AlarmStateT::ALARM_STATE_INVALID,SAFplusI::AlarmCategoryTypeT::ALARM_CATEGORY_INVALID,SAFplusI::AlarmSeverityTypeT::ALARM_SEVERITY_INVALID,SAFplusI::AlarmProbableCauseT::ALARM_ID_INVALID);
        sndMessage.pluginId=SAFplus::FaultPolicy::Undefined;
        sndMessage.syncData[0]=0;
        if (other == INVALID_HDL)
        {
        	logDebug(FAULT,FAULT_ENTITY,"Sending Fault Announce Message : Node [%d], Process Id [%d], Message Type [%d]", reporter.getNode(), reporter.getProcess(),sndMessage.messageType);
        }
        else
        {
        	logDebug(FAULT,FAULT_ENTITY,"Sending Fault Announce Message : Node [%d], Process Id [%d], Message Type [%d]", other.getNode(), other.getProcess(),sndMessage.messageType);
        }

        sendFaultNotification((void *)&sndMessage,sizeof(FaultMessageProtocol),FaultMessageSendMode::SEND_TO_LOCAL_SERVER);
    }
    //deregister Fault Entity
    void Fault::deRegister()
    {
    	deRegister(INVALID_HDL);
    }
    //deregister Fault Entity by Entity Handle
    void Fault::deRegister(SAFplus::Handle faultEntity)
    {
    	FaultMessageProtocol sndMessage;
        sndMessage.reporter = reporter;    typedef boost::unordered_map<SAFplus::FaultPolicy,ClPluginHandle*> FaultPolicyMap;
        FaultPolicyMap faultPolicies;
        sndMessage.messageType = FaultMessageTypeT::MSG_ENTITY_LEAVE;
        sndMessage.state = FaultState::STATE_UP;
        sndMessage.faultEntity=faultEntity;
        sndMessage.data.init(SAFplusI::AlarmStateT::ALARM_STATE_INVALID,SAFplusI::AlarmCategoryTypeT::ALARM_CATEGORY_INVALID,SAFplusI::AlarmSeverityTypeT::ALARM_SEVERITY_INVALID,SAFplusI::AlarmProbableCauseT::ALARM_ID_INVALID);
        sndMessage.pluginId=SAFplus::FaultPolicy::Undefined;
        sndMessage.syncData[0]=0;
        logDebug(FAULT,FAULT_ENTITY,"Deregister fault entity : Node [%d], Process [%d] , Message Type [%d]", reporter.getNode(), reporter.getProcess(),sndMessage.messageType);
        sendFaultNotification((void *)&sndMessage,sizeof(FaultMessageProtocol),FaultMessageSendMode::SEND_TO_LOCAL_SERVER);
    }

    void Fault::sendFaultEventMessage(SAFplus::Handle faultEntity,SAFplusI::FaultMessageSendMode messageMode,SAFplusI::FaultMessageTypeT msgType,SAFplus::FaultPolicy pluginId,SAFplus::FaultEventData faultData)
    {
    	logDebug(FAULT,FAULT_ENTITY,"Sending Fault Event message ... ");
        FaultMessageProtocol sndMessage;
        sndMessage.reporter = reporter;
        sndMessage.messageType = msgType;
        sndMessage.data.alarmState= faultData.alarmState;
        sndMessage.data.category=faultData.category;
        sndMessage.data.cause=faultData.cause;
        sndMessage.data.severity=faultData.severity;
        sndMessage.faultEntity=faultEntity;
        sndMessage.pluginId=pluginId;
        sndMessage.syncData[0]=0;
        sendFaultNotification((void *)&sndMessage,sizeof(FaultMessageProtocol),FaultMessageSendMode::SEND_TO_LOCAL_SERVER);
    }
    void Fault::sendFaultEventMessage(SAFplus::Handle faultEntity,SAFplusI::FaultMessageSendMode messageMode,SAFplusI::FaultMessageTypeT msgType,SAFplusI::AlarmStateT alarmState,SAFplusI::AlarmCategoryTypeT category,SAFplusI::AlarmSeverityTypeT severity,SAFplusI::AlarmProbableCauseT cause,SAFplus::FaultPolicy pluginId)
    {
    	logDebug(FAULT,FAULT_ENTITY,"Sending Fault Event message ...");
        FaultMessageProtocol sndMessage;
        sndMessage.reporter = reporter;
        sndMessage.messageType = msgType;
        sndMessage.data.alarmState= alarmState;
        sndMessage.data.category=category;
        sndMessage.data.cause=cause;
        sndMessage.data.severity=severity;
        sndMessage.faultEntity=faultEntity;
        sndMessage.pluginId=pluginId;
        sndMessage.syncData[0]=0;
        sendFaultNotification((void *)&sndMessage,sizeof(FaultMessageProtocol),messageMode);
    }
    void Fault::notify(SAFplus::Handle faultEntity,SAFplusI::AlarmStateT alarmState,SAFplusI::AlarmCategoryTypeT category,SAFplusI::AlarmSeverityTypeT severity,SAFplusI::AlarmProbableCauseT cause,SAFplus::FaultPolicy pluginId)
    {
    	sendFaultEventMessage(faultEntity,FaultMessageSendMode::SEND_TO_LOCAL_SERVER,SAFplusI::FaultMessageTypeT::MSG_ENTITY_FAULT,alarmState,category,severity,cause,pluginId);
    }
    void Fault::notifytoActive(SAFplus::Handle faultEntity,SAFplusI::AlarmStateT alarmState,SAFplusI::AlarmCategoryTypeT category,SAFplusI::AlarmSeverityTypeT severity,SAFplusI::AlarmProbableCauseT cause,SAFplus::FaultPolicy pluginId)
    {
    	sendFaultEventMessage(faultEntity,FaultMessageSendMode::SEND_TO_ACTIVE_SERVER,SAFplusI::FaultMessageTypeT::MSG_ENTITY_FAULT,alarmState,category,severity,cause,pluginId);
    }
    void Fault::notify(SAFplus::Handle faultEntity,SAFplus::FaultEventData faultData,SAFplus::FaultPolicy pluginId)
    {
       	sendFaultEventMessage(faultEntity,FaultMessageSendMode::SEND_TO_LOCAL_SERVER,SAFplusI::FaultMessageTypeT::MSG_ENTITY_FAULT,pluginId,faultData);
    }
    void Fault::notifytoActive(SAFplus::Handle faultEntity,SAFplus::FaultEventData faultData,SAFplus::FaultPolicy pluginId)
    {
    	sendFaultEventMessage(faultEntity,FaultMessageSendMode::SEND_TO_ACTIVE_SERVER,SAFplusI::FaultMessageTypeT::MSG_ENTITY_FAULT,pluginId,faultData);
    }
    void Fault::notify(SAFplus::FaultEventData faultData,SAFplus::FaultPolicy pluginId)
    {
      	sendFaultEventMessage(reporter,FaultMessageSendMode::SEND_TO_LOCAL_SERVER,SAFplusI::FaultMessageTypeT::MSG_ENTITY_FAULT,pluginId,faultData);
    }
    void Fault::notifytoActive(SAFplus::FaultEventData faultData,SAFplus::FaultPolicy pluginId)
    {
      	sendFaultEventMessage(reporter,FaultMessageSendMode::SEND_TO_ACTIVE_SERVER,SAFplusI::FaultMessageTypeT::MSG_ENTITY_FAULT,pluginId,faultData);
    }
    //Sending a fault notification to fault server
    void Fault::sendFaultNotification(void* data, int dataLength, SAFplusI::FaultMessageSendMode messageMode)
    {
    	logDebug(FAULT,FAULT_ENTITY,"sendFaultNotification");
        switch(messageMode)
        {
            case SAFplusI::FaultMessageSendMode::SEND_TO_LOCAL_SERVER:
            {
            	logDebug(FAULT,FAULT_ENTITY,"Send Fault Notification to local Fault server");
                try
                {
                    faultMsgServer->SendMsg(iocFaultLocalServer, (void *)data, dataLength, SAFplusI::FAULT_MSG_TYPE);
                }
                catch (...) // SAFplus::Error &e)
                {
                    logDebug(FAULT,FAULT_ENTITY,"Failed to send.");
                }
                break;
            }
            case SAFplusI::FaultMessageSendMode::SEND_TO_ACTIVE_SERVER:
            {
                // get active server address
            	ClIocAddressT iocFaultActiveServer=getActiveServerAddress();
                logDebug(FAULT,FAULT_ENTITY,"Send Fault Notification to active Fault Server  : node Id [%d]",iocFaultActiveServer.iocPhyAddress.nodeAddress);
                try
                {
                	faultMsgServer->SendMsg(iocFaultLocalServer, (void *)data, dataLength, SAFplusI::FAULT_MSG_TYPE);
                }
                catch (...)
                {
                     logDebug(FAULT,"MSG","Failed to send.");
                }
                break;
            }
            default:
            {
                logError(FAULT,"MSG","Unknown message sending mode");
                break;
            }
        }
    }

    void Fault::init(SAFplus::Handle faultHandle,ClIocAddressT faultServer, int comPort,SAFplus::Wakeable& execSemantics)
    {
    	logDebug(FAULT,FAULT,"Initial Fault Entity");
        reporter = faultHandle;
        faultCommunicationPort = comPort;
        logDebug(FAULT,FAULT,"Initial Fault Entity MsgServer");
        if(!faultMsgServer)
        {
            faultMsgServer = &safplusMsgServer;
        }
        iocFaultLocalServer.iocPhyAddress.nodeAddress = faultServer.iocPhyAddress.nodeAddress;
        iocFaultLocalServer.iocPhyAddress.portId      = faultServer.iocPhyAddress.portId;
    }

    ClIocAddressT Fault::getActiveServerAddress()
    {
    	ClIocAddressT masterAddress;
    	masterAddress.iocPhyAddress.nodeAddress= fsm.faultHdr->iocFaultServer.iocPhyAddress.nodeAddress;
    	masterAddress.iocPhyAddress.portId= fsm.faultHdr->iocFaultServer.iocPhyAddress.portId;
    	return masterAddress;
    }
    void Fault::setName(const char* entityName)
    {
    	logDebug(FAULT,FAULT_ENTITY,"Set Fault Entity name");
        strncpy(name,entityName,FAULT_NAME_LEN);
    }

    Fault::Fault(SAFplus::Handle faultHandle,const char* name,ClIocAddressT iocServerAddress)
    {
    	wakeable = NULL;
        faultMsgServer = NULL;
        reporter =INVALID_HDL;
        this->init(faultHandle,iocServerAddress,SAFplusI::FLT_IOC_PORT,BLOCK);
        if (name && name[0] != 0)
        {
            setName(name);
        }
    }
    SAFplus::FaultState Fault::getFaultState(SAFplus::Handle faultHandle)
    {
        FaultShmHashMap::iterator entryPtr;
        entryPtr = fsm.faultMap->find(faultHandle);
        if (entryPtr == fsm.faultMap->end())
        {
        	logError(FAULT,FAULT_ENTITY,"Fault Entity not available in shared memory");
            return SAFplus::FaultState::STATE_UNDEFINED;
        }
        FaultShmEntry *fse = &entryPtr->second;
        logDebug(FAULT,FAULT_ENTITY,"Fault state of Fault Entity [%lx:%lx] is [%s]",faultHandle.id[0],faultHandle.id[1],strFaultEntityState[int(fse->state)]);
        return fse->state;
    }

    void Fault::registerFault()
    {
    	sendFaultAnnounceMessage(INVALID_HDL,FaultState::STATE_UP);
    }
    void Fault::registerFault(SAFplus::Handle other,FaultState state)
    {
    	sendFaultAnnounceMessage(other,state);
    }

    static ClRcT faultServerIocNotificationCallback(ClIocNotificationT *notification, ClPtrT cookie)
    {
    	logDebug(FAULT,"IOC","Recv notification");
    	FaultServer* svr = (FaultServer*) cookie;
    	ClRcT rc = CL_OK;
    	ClIocAddressT address;
    	ClIocNotificationIdT eventId = (ClIocNotificationIdT) ntohl(notification->id);
    	ClIocNodeAddressT nodeAddress = ntohl(notification->nodeAddress.iocPhyAddress.nodeAddress);
    	ClIocPortT portId = ntohl(notification->nodeAddress.iocPhyAddress.portId);
    	logDebug(FAULT,"IOC","Recv notification [%d] for [%d.%d]", eventId, nodeAddress,portId);
    	switch(eventId)
    	{
      		case CL_IOC_COMP_DEATH_NOTIFICATION:
      		{
      			logDebug(FAULT,"IOC","Received component leave notification for [%d.%d]", nodeAddress,portId);
      			//ScopedLock<ProcSem> lock(svr->fsmServer.mutex);
      			FaultShmHashMap::iterator i;
      			for (i=svr->fsmServer.faultMap->begin(); i!=svr->fsmServer.faultMap->end();i++)
      			{
      				FaultShmEntry& ge = i->second;
      				Handle handle = i->first;
      				logDebug("GMS","IOC","  Checking fault [%lx:%lx]", handle.id[0],handle.id[1]);
      				//deregister Fault entry in shared memory.
      			}

      		} break;
      		case CL_IOC_NODE_LEAVE_NOTIFICATION:
      		case CL_IOC_NODE_LINK_DOWN_NOTIFICATION:
      		{
      			logDebug("GMS","IOC","Received node leave notification for node id [%d]", nodeAddress);
      			//ScopedLock<ProcSem> lock(svr->fsmServer.mutex);
      			FaultShmHashMap::iterator i;

      			for (i=svr->fsmServer.faultMap->begin(); i!=svr->fsmServer.faultMap->end();i++)
      			{
      				FaultShmEntry& ge = i->second;
      				//deregister all fault entity in this node.
      			}
      		} break;
      		default:
      		{
      			logDebug("GMS","IOC","Received event [%d] from IOC notification",eventId);
      			break;
      		}
        }
    	// there are no faultPolisy plugin Id from ioc notification, using AMF for default :  Fix it
      	svr->processIocNotification(FaultPolicy::AMF,eventId,nodeAddress,portId);
      	return rc;
    }

    void loadFaultPlugins()
    {
        // pick the SAFplus directory or the current directory if it is not defined.
    	const char * soPath = (SAFplus::ASP_APP_BINDIR[0] == 0) ? ".":SAFplus::ASP_APP_BINDIR;
    	logDebug(FAULT,"POL","loadFaultPlugins policy: %s", soPath);
        boost::filesystem::path p(soPath);
        boost::filesystem::directory_iterator it(p),eod;
        BOOST_FOREACH(boost::filesystem::path const &p, std::make_pair(it, eod))
        {
            if (p.extension()==".so")
            {
                if (p.string().find("Fault") != std::string::npos)
                {
                    if(is_regular_file(p))
                    {
                        const char *s = p.c_str();
                        logDebug(FAULT,"POL","Loading policy: %s", s);
                        ClPluginHandle* plug = clLoadPlugin(FAULT_POLICY_PLUGIN_ID,FAULT_POLICY_PLUGIN_VER,s);
                        if (plug)
                        {
                            FaultPolicyPlugin* pp = dynamic_cast<FaultPolicyPlugin*> (plug->pluginApi);
                            if (pp)
                            {
                                faultPolicies[pp->policyId] = plug;
                                logDebug(FAULT,"POL","AMF Policy [%d] plugin load succeeded.", int(pp->pluginId));
                            }
                        }
                        else clLogError(FAULT,"POL","AMF Policy plugin load failed.  Incorrect plugin type");
                    }
                    else clLogError(FAULT,"POL","Policy load failed.  Incorrect plugin Identifier or version.");
                }
            }
        }
    }
    void FaultServer::writeToSharedMemoryAllEntity()
    {
        for (Checkpoint::Iterator i=faultCheckpoint.begin();i!=faultCheckpoint.end();i++)
        {
            SAFplus::Checkpoint::KeyValuePair& item = *i;
            Handle tmpHandle = *((Handle*) (*item.first).data);
            FaultShmEntry* tmpShmEntry = ((FaultShmEntry*) (*item.first).data);
        	logDebug(FAULT,FAULT_SERVER,"Fault server sync : Fault Entity with Node Id [%d] and Process Id [%d]",tmpHandle.getNode(),tmpHandle.getProcess());
            registerFaultEntity(tmpShmEntry,tmpHandle,false);
        }
    }
    void FaultServer::init()
    {

        faultServerHandle = Handle::create();
        logDebug(FAULT,FAULT_SERVER,"Register IOC notification");
        clIocNotificationRegister(faultServerIocNotificationCallback,this);
        logDebug(FAULT,FAULT_SERVER,"Initial Fault Server Group");
        group=Group(FAULT_GROUP);
        group.setNotification(*this);
        SAFplus::objectMessager.insert(faultServerHandle,this);
        faultInfo.iocFaultServer.iocPhyAddress.nodeAddress=SAFplus::ASP_NODEADDR;
        faultInfo.iocFaultServer.iocPhyAddress.portId=SAFplusI::FLT_IOC_PORT;
        group.registerEntity(faultServerHandle, SAFplus::ASP_NODEADDR,NULL,0,Group::ACCEPT_STANDBY | Group::ACCEPT_ACTIVE | Group::STICKY);
        SAFplus::Handle activeMember = INVALID_HDL;
        activeMember = group.getActive();
        ClIocAddress activeAddress = getAddress(activeMember);
        logDebug(FAULT,FAULT_SERVER,"Fault Server active address : nodeAddress [%d] - port [%d]",activeAddress.iocPhyAddress.nodeAddress,activeAddress.iocPhyAddress.portId);
        logDebug(FAULT,FAULT_SERVER,"Initialize shared memory");
        fsmServer.init(activeAddress);
        fsmServer.clear();  // I am the node representative just starting up, so members may have fallen out while I was gone.  So I must delete everything I knew.
        logDebug(FAULT,FAULT_SERVER,"Loading Fault Policy");
        loadFaultPlugins();
        logDebug(FAULT,FAULT_SERVER,"Register fault message server");
        faultMsgServer = &safplusMsgServer;
        if (1)
        {
        	faultMsgServer->RegisterHandler(SAFplusI::FAULT_MSG_TYPE, this, NULL);  //  Register the main message handler (no-op if already registered)
        }
        //Fault server include fault client
        if(activeAddress.iocPhyAddress.nodeAddress != clIocLocalAddressGet())
        {
        	logDebug(FAULT,FAULT_SERVER,"Standby fault server . Get fault information from active fault server");
        	faultCheckpoint.name = "safplusFault";
        	faultCheckpoint.init(FAULT_CKPT,Checkpoint::SHARED | Checkpoint::REPLICATED , 1024*1024, CkptDefaultRows);
        	logDebug(FAULT,FAULT_SERVER,"Get all checkpoint data");
        	sleep(10);
        	writeToSharedMemoryAllEntity();
        }
        else
        {

        	logDebug(FAULT,FAULT_SERVER,"Active fault server.");
        	faultCheckpoint.name = "safplusFault";
        	faultCheckpoint.init(FAULT_CKPT,Checkpoint::SHARED | Checkpoint::REPLICATED , 1024*1024, CkptDefaultRows);
        	sleep(10);
        }
        faultClient = Fault();
        ClIocAddress server;
        server.iocPhyAddress.nodeAddress= SAFplus::ASP_NODEADDR;
        server.iocPhyAddress.portId=  SAFplusI::FLT_IOC_PORT;
        logInfo(FAULT,"CLT","********************Initial fault client*********************");
        faultClient.init(faultServerHandle,server,SAFplusI::FLT_IOC_PORT,BLOCK);
        sleep(2);
        faultClient.registerFault();
    }
    void FaultServer::msgHandler(ClIocAddressT from, SAFplus::MsgServer* svr, ClPtrT msg, ClWordT msglen, ClPtrT cookie)
    {
        const SAFplus::FaultMessageProtocol *rxMsg = (SAFplus::FaultMessageProtocol *)msg;
        SAFplusI::FaultMessageTypeT msgType=  rxMsg->messageType;
        SAFplus::Handle reporterHandle = rxMsg->reporter;
        SAFplus::FaultState faultState = rxMsg->state;
        SAFplus::FaultPolicy pluginId = rxMsg->pluginId;
        FaultEventData eventData= rxMsg->data;
        SAFplus::Handle faultEntity=rxMsg->faultEntity;
        //logDebug(FAULT,"MSG","Received message [%s] from node [%d] and state [%s]",strFaultMsgType[int(msgType)-1],from.iocPhyAddress.nodeAddress,strFaultEntityState[int(faultState)]);
        FaultShmHashMap::iterator entryPtr;
        if(msgType==SAFplusI::FaultMessageTypeT::MSG_FAULT_SYNC_REQUEST)
        {
        	sendFaultSyncReply(from);
        	return;
        }
        else if(msgType==SAFplusI::FaultMessageTypeT::MSG_FAULT_SYNC_REPLY)
        {
        	ClWordT len = msglen - sizeof(FaultMessageProtocol) - 1;
        	fsmServer.applyFaultSync((char *)(rxMsg->syncData),len);
        }
        if(faultEntity==INVALID_HDL)
        {
        	logDebug(FAULT,"MSG","Receive Fault message with process id [%d]",reporterHandle.getProcess());
        	entryPtr = fsmServer.faultMap->find(reporterHandle);
        }
        else
        {
        	logDebug(FAULT,"MSG","Receive Fault message with process id [%d]",faultEntity.getProcess());
        	entryPtr = fsmServer.faultMap->find(faultEntity);
        }
        FaultShmEntry *fe=new FaultShmEntry();
        //check point data
        char handleData[sizeof(Buffer)-1+sizeof(Handle)];
        Buffer* key = new(handleData) Buffer(sizeof(Handle));
        Handle* tmp = (Handle*)key->data;
    	logDebug(FAULT,"MSG","Size of Handle [%d]",sizeof(Handle));
    	logDebug(FAULT,"MSG","Size of share entry [%d]",sizeof(FaultEntryData));
        char vdata[sizeof(Buffer)-1+sizeof(FaultEntryData)];
        Buffer* val = new(vdata) Buffer(sizeof(FaultEntryData));
        FaultEntryData* tmpShrEntity = (FaultEntryData*)val->data;
        for(int i=0;i<MAX_FAULT_DEPENDENCIES;i++)
        {
            tmpShrEntity->depends[i]=INVALID_HDL;
        }

        if (entryPtr == fsmServer.faultMap->end())  // We don't know about the fault entity, so create it;
        {

        	if(msgType!=SAFplusI::FaultMessageTypeT::MSG_ENTITY_JOIN && msgType!=SAFplusI::FaultMessageTypeT::MSG_ENTITY_JOIN_BROADCAST)
        	{
        		logDebug(FAULT,"MSG","Fault entity not available in shared memory. Ignore this message");
        		return;
        	}
        	logDebug(FAULT,"MSG","Fault entity not available in shared memory. Initial new fault entity");
        	if(faultEntity==INVALID_HDL)
        	{
        		logDebug(FAULT,"MSG","Init reporter handle");
        		fe->init(reporterHandle);
        		*tmp=reporterHandle;
                tmpShrEntity->faultHdl=reporterHandle;

        	}
        	else
        	{
        		logDebug(FAULT,"MSG","Init fault entity handle");
        		fe->init(faultEntity);
        		*tmp=faultEntity;
        		tmpShrEntity->faultHdl=faultEntity;
        	}
        	tmpShrEntity->dependecyNum=0;
            for(int i=0;i<MAX_FAULT_DEPENDENCIES;i++)
            {
            	tmpShrEntity->depends[i]=INVALID_HDL;
            }

        }
        else
        {
        	logDebug(FAULT,"MSG","Fault entity available in shared memory. process fault message");
            fe = &entryPtr->second; // &(gsm.groupMap->find(grpHandle)->second);
            tmpShrEntity->dependecyNum= fe->dependecyNum;
            tmpShrEntity->faultHdl= fe->faultHdl;
            tmpShrEntity->state= fe->state;
            for(int i=0;i<MAX_FAULT_DEPENDENCIES;i++)
            {
            	tmpShrEntity->depends[i]=fe->depends[i];
            }
        	if(faultEntity==INVALID_HDL)
        	{
        		*tmp=reporterHandle;
        	}
        	else
        	{
        		*tmp=faultEntity;
        	}
        }

        if(rxMsg == NULL)
        {
          logError(FAULT,"MSG","Received NULL message. Ignored fault message");
          return;
        }

        switch(msgType)
        {
            case SAFplusI::FaultMessageTypeT::MSG_ENTITY_JOIN:
                if(1)
                {
                	fe->state=faultState;
                	fe->dependecyNum=0;
                	tmpShrEntity->state=faultState;
                	tmpShrEntity->dependecyNum=0;
                    logDebug(FAULT,"MSG","Entity JOIN message with fault state [%d]",fe->state);
         			logDebug(FAULT,"MSG","Entity Fault message from local node. Register new fault entity");
         			if(faultEntity==INVALID_HDL)
         			{
         				registerFaultEntity(fe,reporterHandle,true);
                        logDebug(FAULT,"MSG","write to checkpoint");
                        faultCheckpoint.write(*key,*val);

         			}
         			else
         			{
         				registerFaultEntity(fe,faultEntity,true);
         				logDebug(FAULT,"MSG","write to checkpoint");
                        faultCheckpoint.write(*key,*val);
         				//write to checkpoint
         			}
                }break;
            case SAFplusI::FaultMessageTypeT::MSG_ENTITY_LEAVE:
            	if(1)
            	{
              		logDebug(FAULT,"MSG","Entity Fault message from local node . Deregister fault entity.");
              		if(faultEntity==INVALID_HDL)
              		{
              			removeFaultEntity(reporterHandle,true);
              			//remove entity in checkpoint
                        faultCheckpoint.remove(*key);
              		}
              		else
              		{
              			removeFaultEntity(faultEntity,true);
              			//remove entity in checkpoint
              			faultCheckpoint.remove(*key);
              		}
            	}break;
            case SAFplusI::FaultMessageTypeT::MSG_ENTITY_FAULT:
            	if(1)
            	{
                    logDebug(FAULT,"MSG","Process fault event message");
                    processFaultEvent(pluginId,eventData,faultEntity,reporterHandle);
                    logDebug("POL","AMF","Fault event data severity [%s] , cause [%s] , catagory [%s] , state [%d] ", SAFplus::strFaultSeverity[int(eventData.severity)],SAFplus::strFaultProbableCause[int(eventData.cause)],SAFplus::strFaultCategory[int(eventData.category)],eventData.alarmState);
                    FaultHistoryEntity faultHistoryEntry;
                    time_t now;
                    time(&now);
                    if (1)
                    {
                    	ScopedLock<Mutex> lock(faultServerMutex);
                    	faultHistoryEntry.setValue(eventData,faultEntity,reporterHandle,now,NO_TXN);
                    	faultHistory.setCurrent(faultHistoryEntry,NO_TXN);
                    	faultHistory.setHistory10min(faultHistoryEntry,NO_TXN);
                    }
                    logDebug(FAULT,"MSG","Send fault event message to all fault server");
                    if(reporterHandle.getNode()==clIocLocalAddressGet())
                    {
                    	FaultMessageProtocol sndMessage;
                    	sndMessage.reporter = reporterHandle;
                    	sndMessage.messageType = SAFplusI::FaultMessageTypeT::MSG_ENTITY_FAULT_BROADCAST;
                    	sndMessage.data.alarmState= eventData.alarmState;
                    	sndMessage.data.category=eventData.category;
                    	sndMessage.data.cause=eventData.cause;
                    	sndMessage.data.severity=eventData.severity;
                    	sndMessage.faultEntity=faultEntity;
                    	sndMessage.pluginId=pluginId;
                    	sndMessage.syncData[0]=0;
                    	sendFaultNotificationToGroup((void *)&sndMessage,sizeof(FaultMessageProtocol));
                        int i;
                        for(i=0;i<faultHistory.history10min.value.size();i++)
                        {
                        	char todStr[128]="";
                        	struct tm tmStruct;
                        	localtime_r(&faultHistory.history10min.value[i].time, &tmStruct);
                        	strftime(todStr, 128, "[%b %e %T]", &tmStruct);
                        	logDebug(FAULT,"HIS","*** Fault event [%d] : time [%s] node [%d] with processId [%d]",i,todStr,faultHistory.history10min.value[i].faultHdl.getNode(),faultHistory.history10min.value[i].faultHdl.getProcess());
                        }
                    }
            	}
            	break;
            case SAFplusI::FaultMessageTypeT::MSG_ENTITY_JOIN_BROADCAST:
            	if(1)
            	{
            		if(from.iocPhyAddress.nodeAddress==clIocLocalAddressGet())
            		{
            			logDebug(FAULT,"MSG","Fault entity join message broadcast from local . Ignore this message");
            		}
            		else
            		{
            			logDebug(FAULT,"MSG","Fault event message broadcast from external.");
            			//TODO Process this event
                    	fe->state=faultState;
                    	fe->dependecyNum=0;
                        logDebug(FAULT,"MSG","Entity JOIN message with fault state [%d]",fe->state);
             			logDebug(FAULT,"MSG","Entity Fault message from local node. Register new fault entity");
             			if(faultEntity==INVALID_HDL)
             			{
             				registerFaultEntity(fe,reporterHandle,false);
             			}
             			else
             			{
             				registerFaultEntity(fe,faultEntity,false);
             			}
            		}
            	}
             break;
             case SAFplusI::FaultMessageTypeT::MSG_ENTITY_LEAVE_BROADCAST:
            	if(1)
            	{
            		if(from.iocPhyAddress.nodeAddress==clIocLocalAddressGet())
            		{
            			logDebug(FAULT,"MSG","Fault entity leave message broadcast from local . Ignore this message");
            		}
            		else
            		{
            			logDebug(FAULT,"MSG","Fault event message broadcast from external.");
            			//TODO process this event
            			logDebug(FAULT,"MSG","Entity Fault message from local node . Deregister fault entity.");
            			if(faultEntity==INVALID_HDL)
            			{
            				removeFaultEntity(reporterHandle,false);
            			}
            			else
            			{
            				removeFaultEntity(faultEntity,false);
            			}
            		}
            	}
             break;
             case SAFplusI::FaultMessageTypeT::MSG_ENTITY_FAULT_BROADCAST:
             if(1)
             {
         		if(from.iocPhyAddress.nodeAddress==clIocLocalAddressGet())
         		{
         			logDebug(FAULT,"MSG","Fault event message broadcast from local . Ignore this message");
         		}
         		else
         		{
         			logDebug(FAULT,"MSG","Fault event message broadcast from external.");
         			//TODO
         		}
             }
             break;
          default:
            logDebug(FAULT,"MSG","Unknown message type [%d] from %d",rxMsg->messageType,from.iocPhyAddress.nodeAddress);
            break;
        }
    }

	void FaultServer::sendFaultSyncRequest(ClIocAddress activeAddress)
	{
		// send sync request to master fault server
    	logDebug(FAULT,FAULT,"Sending sync requst message to server");
        FaultMessageProtocol sndMessage;
        sndMessage.reporter = INVALID_HDL;
        sndMessage.messageType = FaultMessageTypeT::MSG_FAULT_SYNC_REQUEST;
        sndMessage.state = FaultState::STATE_UNDEFINED;
        sndMessage.faultEntity=INVALID_HDL;
        sndMessage.data.init(SAFplusI::AlarmStateT::ALARM_STATE_INVALID,SAFplusI::AlarmCategoryTypeT::ALARM_CATEGORY_INVALID,SAFplusI::AlarmSeverityTypeT::ALARM_SEVERITY_INVALID,SAFplusI::AlarmProbableCauseT::ALARM_ID_INVALID);
        sndMessage.pluginId=SAFplus::FaultPolicy::Undefined;
        sndMessage.syncData[0]=0;
        sendFaultNotificationToGroup((void *)&sndMessage,sizeof(FaultMessageProtocol));
	}

	void FaultServer::sendFaultSyncReply(ClIocAddress address)
	{
		// send sync reply  to standby fault server
		long bufferSize=0;
		char* buf = new char[MAX_FAULT_BUFFER_SIZE];
		fsmServer.getAllFaultClient(buf,bufferSize);
		char msgPayload[sizeof(FaultMessageProtocol)-1 + bufferSize];
		FaultMessageProtocol *sndMessage = (FaultMessageProtocol *)&msgPayload;
		sndMessage->reporter = INVALID_HDL;
		sndMessage->messageType = FaultMessageTypeT::MSG_FAULT_SYNC_REPLY;
		sndMessage->state = FaultState::STATE_UNDEFINED;
		sndMessage->faultEntity=INVALID_HDL;
		sndMessage->data.init(SAFplusI::AlarmStateT::ALARM_STATE_INVALID,SAFplusI::AlarmCategoryTypeT::ALARM_CATEGORY_INVALID,SAFplusI::AlarmSeverityTypeT::ALARM_SEVERITY_INVALID,SAFplusI::AlarmProbableCauseT::ALARM_ID_INVALID);
		sndMessage->pluginId=SAFplus::FaultPolicy::Undefined;
  	    memcpy(sndMessage->syncData,(const void*) &buf,sizeof(GroupIdentity));
  	    faultMsgServer->SendMsg(address, (void *)msgPayload, sizeof(msgPayload), SAFplusI::FAULT_MSG_TYPE);
	}

    //count fault event of fault entity in latest time second
    int FaultServer::countFaultEvent(SAFplus::Handle reporter,SAFplus::Handle faultEntity,long timeInterval)
    {
    	int i;
    	int count =0;
    	for(i = faultHistory.history10min.value.size()-1;i>=0;i--)
    	{
    		time_t now;
    		time(&now);
    		if(((now - faultHistory.history10min.value[i].time) <=timeInterval))
    		{
    			if(faultHistory.history10min.value[i].faultHdl == faultEntity)// && faultHistory.history10min.value[i].reporter != reporter)
    			{
    				count++;
    			}
    		}
    		else
    		{
    			return count;
    		}
    	}
    	return count;
    }
    //register a fault client entity
    void FaultServer::registerFaultEntity(FaultShmEntry* frp, SAFplus::Handle faultClient,bool needNotify )
    {
    	logDebug(FAULT,"MSG","Register fault entity :  node id [%d] and process Id [%d]",faultClient.getNode(),faultClient.getProcess());
        fsmServer.createFault(frp,faultClient);
        if(needNotify)
        {
        	logDebug(FAULT,"MSG","Send broadcast fault entity join message :  node id [%d] and process Id [%d]",faultClient.getNode(),faultClient.getProcess());
            sendFaultAnnounceMessage(faultClient);
        }
    }   
    //Deregister a fault client entity

    void FaultServer::removeFaultEntity(SAFplus::Handle faultClient,bool needNotify)
    {
        //TODO
        logDebug(FAULT,FAULT_SERVER,"De-register fault entity: node id [%d] and process Id [%d]",faultClient.getNode(),faultClient.getProcess());
    	fsmServer.faultMap->erase(faultClient);
    	if(needNotify)
    	{
    		logDebug(FAULT,FAULT_SERVER,"Broadcast leave message:  node id [%d] and process Id [%d]",faultClient.getNode(),faultClient.getProcess());
    		sendFaultLeaveMessage(faultClient);
    	}
    }
    //Remove dependency
    bool FaultServer::removeDependency(SAFplus::Handle dependencyHandle, SAFplus::Handle faultHandle)
    {
        //TODO
        FaultShmHashMap::iterator entryPtr;
        entryPtr = fsmServer.faultMap->find(faultHandle);
        if (entryPtr == fsmServer.faultMap->end())
        {
        	return false;
        }
        FaultShmEntry *fse = &entryPtr->second;
        assert(fse);
        if (fse)
        {
            if(fse->dependecyNum==0) return false;
            for(int i=0;i<fse->dependecyNum;i++)
            {
                if(fse->depends[i]==dependencyHandle)
                {
                    for (int j=i;j<fse->dependecyNum-1;j++)
                    {
                        fse->depends[j]=fse->depends[j+1];
                        return false;
                    }
                    fse->dependecyNum--;
                    return true;
                }
            }
            return false;
        }
        else
        {
            //TODO return
            return false;
        }
}
    //Add dependency
    bool FaultServer::setDependency(SAFplus::Handle dependencyHandle,SAFplus::Handle faultHandle)
    {
        FaultShmHashMap::iterator entryPtr;
        entryPtr = fsmServer.faultMap->find(faultHandle);
        if (entryPtr == fsmServer.faultMap->end()) return false; // TODO: raise exception
        FaultShmEntry *fse = &entryPtr->second;
        assert(fse);  // If this fails, something very wrong with the group data structure in shared memory.  TODO, should probably delete it and fail the node
        if (fse)
        {
          fse->depends[fse->dependecyNum]=dependencyHandle;
          fse->dependecyNum++;
          return true;
        }
        else
        {
            //TODO return
            return false;
        }
    }   
//    // set name for fault client entity
//    void FaultServer::setName(SAFplus::Handle faultHandle, const char* name)
//    {
//        FaultShmHashMap::iterator entryPtr;
//        entryPtr = fsmServer.faultMap->find(faultHandle);
//        if (entryPtr == fsmServer.faultMap->end()) return; // TODO: raise exception
//        SAFplus::FaultShmEntry *fse = &entryPtr->second;
//        assert(fse);  // If this fails, something very wrong with the group data structure in shared memory.  TODO, should probably delete it and fail the node
//        if (fse) // Name is not meant to change, and not used except for display purposes.  So just change both of them
//        {
//          strncpy(fse->name,name,FAULT_NAME_LEN);
//        }
//        else
//        {
//            //TODO
//        }
//    }
    //process a fault event
    void FaultServer::processFaultEvent(SAFplus::FaultPolicy pluginId, FaultEventData fault , SAFplus::Handle faultEntity, SAFplus::Handle faultReporter)
    {
        FaultPolicyMap::iterator it;
        for (it = faultPolicies.begin(); it != faultPolicies.end();it++)
        {
              if(it->first==pluginId || pluginId==FaultPolicy::Undefined)
              {
                  //call Fault plugin to proces fault event
                  FaultPolicyPlugin* pp = dynamic_cast<FaultPolicyPlugin*>(it->second->pluginApi);
                  int count = countFaultEvent(faultReporter,faultEntity,5);
                  FaultAction result = pp->processFaultEvent(fault,faultReporter,faultEntity,count);
                  switch (result)
                  {
					case FaultAction::ACTION_STOP:
					{
						logDebug(FAULT,FAULT_SERVER,"Process fault event return ACTION_STOP.");
						logDebug(FAULT,FAULT_SERVER,"Try to stop process.");
						//TODO stop fault process
						break;
					}
					case FaultAction::ACTION_RESTART:
					{
						logDebug(FAULT,FAULT_SERVER,"Process fault event return ACTION_RESTART.");
						logDebug(FAULT,FAULT_SERVER,"Try to restart process.");
						//TODO stop fault process
						break;
					}
					case FaultAction::ACTION_IGNORE:
					{
						logDebug(FAULT,FAULT_SERVER,"Process fault event return ACTION_IGNORE");
						logDebug(FAULT,FAULT_SERVER,"Ignore this fault event.");
						break;
					}
					default:
						logDebug(FAULT,"MSG","Un-define return value. Exit");
						break;
				}
              }
        }

    }
	void FaultServer::processIocNotification(SAFplus::FaultPolicy pluginId,ClIocNotificationIdT eventId, ClIocNodeAddressT nodeAddress, ClIocPortT portId)
	{
        FaultPolicyMap::iterator it;
        for (it = faultPolicies.begin(); it != faultPolicies.end();it++)
          {
              if(it->first==pluginId)
              {
                  //call Fault plugin to proces fault event
                  FaultPolicyPlugin* pp = dynamic_cast<FaultPolicyPlugin*>(it->second->pluginApi);
                  pp->processIocNotification(eventId,nodeAddress,portId);
              }
          }
  	}

    //broadcast fault state to all other node

    void FaultServer::sendFaultAnnounceMessage(SAFplus::Handle handle)
    {
    	logDebug(FAULT,FAULT_SERVER,"Sending announce message to server with node[%d] , process [%d]", handle.getNode(), handle.getProcess());
        FaultMessageProtocol sndMessage;
        sndMessage.reporter = handle;
        sndMessage.messageType = FaultMessageTypeT::MSG_ENTITY_JOIN_BROADCAST;
        sndMessage.state = FaultState::STATE_UP;
        sndMessage.faultEntity=INVALID_HDL;
        sndMessage.data.init(SAFplusI::AlarmStateT::ALARM_STATE_INVALID,SAFplusI::AlarmCategoryTypeT::ALARM_CATEGORY_INVALID,SAFplusI::AlarmSeverityTypeT::ALARM_SEVERITY_INVALID,SAFplusI::AlarmProbableCauseT::ALARM_ID_INVALID);
        sndMessage.pluginId=SAFplus::FaultPolicy::Undefined;
        sndMessage.syncData[0]=0;
        sendFaultNotificationToGroup((void *)&sndMessage,sizeof(FaultMessageProtocol));

    }

    void FaultServer::sendFaultLeaveMessage(SAFplus::Handle handle)
    {
    	logDebug(FAULT,FAULT_SERVER,"Sending announce message to server with node[%d] , process [%d]", handle.getNode(), handle.getProcess());
        FaultMessageProtocol sndMessage;
        sndMessage.reporter = handle;
        sndMessage.messageType = FaultMessageTypeT::MSG_ENTITY_LEAVE_BROADCAST;
        sndMessage.state = FaultState::STATE_UP;
        sndMessage.faultEntity=INVALID_HDL;
        sndMessage.data.init(SAFplusI::AlarmStateT::ALARM_STATE_INVALID,SAFplusI::AlarmCategoryTypeT::ALARM_CATEGORY_INVALID,SAFplusI::AlarmSeverityTypeT::ALARM_SEVERITY_INVALID,SAFplusI::AlarmProbableCauseT::ALARM_ID_INVALID);
        sndMessage.pluginId=SAFplus::FaultPolicy::Undefined;
        sndMessage.syncData[0]=0;
        sendFaultNotificationToGroup((void *)&sndMessage,sizeof(FaultMessageProtocol));
    }

    void FaultServer::sendFaultNotification(void* data, int dataLength, SAFplusI::FaultMessageSendMode messageMode)
    {
        switch(messageMode)
        {
            case SAFplusI::FaultMessageSendMode::SEND_BROADCAST:
            {
                /* Destination is broadcast address */
                ClIocAddressT iocDest;
                iocDest.iocPhyAddress.nodeAddress = CL_IOC_BROADCAST_ADDRESS;
                iocDest.iocPhyAddress.portId      = faultCommunicationPort;
                //logDebug("GMS","MSG","Sending broadcast message");
                try
                {
                    faultMsgServer->SendMsg(iocDest, (void *)data, dataLength, SAFplusI::FAULT_MSG_TYPE);
                }
                catch (...)
                {
                    //logDebug("GMS","MSG","Failed to send. Error %x",e.rc);
                    logDebug("GMS","MSG","Failed to send.");
                }
                break;
            }
            default:
            {
                logError("GMS","MSG","Unknown message sending mode");
                break;
            }
        }
    }
    void FaultServer::sendFaultNotificationToGroup(void* data, int dataLength)
    {
    	group.send(data,dataLength,GroupMessageSendMode::SEND_BROADCAST);
    }
    FaultServer::FaultServer()
    {

    }
    SAFplus::FaultState FaultServer::getFaultState(SAFplus::Handle faultHandle)
    {
        FaultShmHashMap::iterator entryPtr;
        entryPtr = fsmServer.faultMap->find(faultHandle);
        if (entryPtr == fsmServer.faultMap->end())
        {
        	logError(FAULT,FAULT,"not available in shared memory");
            return SAFplus::FaultState::STATE_UNDEFINED;
        }
        FaultShmEntry *fse = &entryPtr->second;
    	logError(FAULT,FAULT_SERVER,"Fault Entity [%d] State  [%d]",faultHandle,fse->state);
        return fse->state;
    }
    void faultInitialize(void)
      {
    	ClIocAddress localAddress;
    	localAddress.iocPhyAddress.nodeAddress=0;
    	localAddress.iocPhyAddress.portId=0;
    	SAFplus::fsm.init(localAddress);
      }
    void FaultServer::wake(int amt,void* cookie)
         {
        	 changeCount++;
        	 Group* g = (Group*) cookie;
        	 logInfo(FAULT,FAULT_SERVER, "Group [%lx:%lx] changed", g->handle.id[0],g->handle.id[1]);
        	 Group::Iterator i;
        	 char buf[100];
        	 for (i=g->begin(); i != g->end(); i++)
        	 {
        		 const GroupIdentity& gid = i->second;
        		 logInfo(FAULT,FAULT_SERVER, " Entity [%lx:%lx] on node [%d] credentials [%ld] capabilities [%d] %s", gid.id.id[0],gid.id.id[1],gid.id.getNode(),gid.credentials, gid.capabilities, Group::capStr(gid.capabilities,buf));
        	 }
          }
};