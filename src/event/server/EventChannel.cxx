/*
 * EventChannel.cxx
 *
 *  Created on: Apr 13, 2017
 *      Author: minhgiang
 */

#include "EventChannel.hxx"

using namespace SAFplusI;
using namespace SAFplus;
#include <clLogApi.hxx>

EventChannel::EventChannel() {
	// TODO Auto-generated constructor stub

}

EventChannel::~EventChannel() {
	// TODO Auto-generated destructor stub
}

void EventChannel::addChannelSub(EventSubscriber& sub)
{
	if(this->eventSubs.empty())
	{
		logInfo("EVT","SUB","add event client handle [%d,%d] to subscriber list",sub.usr.evtHandle.getNode(),sub.usr.evtHandle.getPort());
		this->eventSubs.push_back(sub);
	}
	else
	{
		for (EventSubscriberList::iterator iter = eventSubs.begin(); iter != eventSubs.end(); iter++)
		{
			EventSubscriber &s = *iter;
			if(s.usr.evtHandle==sub.usr.evtHandle)
			{
				logInfo("EVT","SUB","add event client handle [%d,%d] is already exist in subscriber list",sub.usr.evtHandle.getNode(),sub.usr.evtHandle.getPort());				return;
			}
		}
		logInfo("EVT","SUB","add event client handle [%d,%d] to subscriber list",sub.usr.evtHandle.getNode(),sub.usr.evtHandle.getPort());
		this->eventSubs.push_back(sub);
	}
}

void EventChannel::addChannelPub(EventPublisher& pub)
{
	if(this->eventPubs.empty())
	{
		logInfo("EVT","SUB","add event client handle [%d,%d] to publisher list",pub.usr.evtHandle.getNode(),pub.usr.evtHandle.getPort());
		this->eventPubs.push_back(pub);
	}
	else
	{
		for (EventPublisherList::iterator iter = eventPubs.begin(); iter != eventPubs.end(); iter++)
		{
			EventPublisher &s = *iter;
			if(s.usr.evtHandle==pub.usr.evtHandle)
			{
				logInfo("EVT","SUB","add event client handle [%d,%d] is already exist in publisher list",pub.usr.evtHandle.getNode(),pub.usr.evtHandle.getPort());
				return;
			}
		}
		logInfo("EVT","SUB","add event client handle [%d,%d] to subscriber list",pub.usr.evtHandle.getNode(),pub.usr.evtHandle.getPort());
		this->eventPubs.push_back(pub);
	}
}



struct eventSub_delete_disposer
{
  void operator()(EventSubscriber *delete_this)
  {
    delete delete_this;
  }
};

struct eventPub_delete_disposer
{
  void operator()(EventPublisher *delete_this)
  {
    delete delete_this;
  }
};

void EventChannel::deleteChannelSub(SAFplus::Handle subHandle)
{
    //TODO delete all sub with sub handle
    if(eventSubs.empty())
    {
        return;
    }
    for (EventSubscriberList::iterator iter = eventSubs.begin(); iter != eventSubs.end(); iter++)
    {
        EventSubscriber &evtSub = *iter;
        if(evtSub.usr.evtHandle==subHandle)
        {
            eventSubs.erase_and_dispose(iter, eventSub_delete_disposer());
        }
    }

}

void EventChannel::deleteChannelPub(SAFplus::Handle pubHandle)
{
    //TODO delete all sub with sub handle
    if(eventPubs.empty())
    {
        return;
    }
    for (EventPublisherList::iterator iter = eventPubs.begin(); iter != eventPubs.end(); iter++)
    {
        EventPublisher &evtPub = *iter;
        if(evtPub.usr.evtHandle==pubHandle)
        {
            eventPubs.erase_and_dispose(iter, eventPub_delete_disposer());
        }
    }

}
