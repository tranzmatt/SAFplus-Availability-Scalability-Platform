/*
 * Copyright (C) 2002-2012 OpenClovis Solutions Inc.  All Rights Reserved.
 *
 * This file is available  under  a  commercial  license  from  the
 * copyright  holder or the GNU General Public License Version 2.0.
 *
 * The source code for  this program is not published  or otherwise
 * divested of  its trade secrets, irrespective  of  what  has been
 * deposited with the U.S. Copyright office.
 *
 * This program is distributed in the  hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied  warranty  of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 *
 * For more  information, see  the file  COPYING provided with this
 * material.
 *
 */
#include <algorithm>
#include <set>
#include <clSafplusMsgServer.hxx>
#include <clMsgPortsAndTypes.hxx>
#include <MgtMsg.pb.hxx>

//TODO Temporary using clCommonErrors6.h
#include <clCommonErrors6.h>
#include <clMgtBaseCommon.hxx>
#include <clMgtFunction.hxx>
#include <clMgtRoot.hxx>

using namespace Mgt::Msg;

namespace SAFplus
{
// Mgt Checkpoint
  Checkpoint* mgtCheckpoint = 0;

  Checkpoint* getMgtCheckpoint()
  {
    assert(mgtCheckpoint);  // You should have called mgtAccessInitialize
    return mgtCheckpoint;
  }

  void mgtAccessInitialize(void)
  {
    if (!mgtCheckpoint)
    {
      mgtCheckpoint = new Checkpoint(MGT_CKPT, Checkpoint::SHARED | Checkpoint::REPLICATED, SAFplusI::CkptRetentionDurationDefault, 1024 * 1024, SAFplusI::CkptDefaultRows);
      mgtCheckpoint->name = "safplusMgt";
    }
  }


  SAFplus::Handle getMgtHandle(const std::string& pathSpec, ClRcT &errCode)
  {
    std::string xpath = pathSpec;  // I need to make a copy so I can modify it
    if (pathSpec[0] == '{')
      {
        xpath = pathSpec.substr(pathSpec.find('}')+1);
      }

    size_t lastSlash = std::string::npos;
    while(1)
      {
        try
          {
            logDebug("MGT", "LKP", "Trying [%s]", xpath.c_str());
            const SAFplus::Buffer& b = mgtCheckpoint->read(xpath);
            if (&b)
              {
                assert(b.len() == sizeof(SAFplus::Handle));
                SAFplus::Handle hdl = *((const SAFplus::Handle*) b.data);
                logDebug("MGT", "LKP", "Resolved [%s] to [%" PRIx64 ",%" PRIx64 "]", xpath.c_str(),hdl.id[0],hdl.id[1]);
                //std::string strRout = pathSpec.substr(lastSlash+1);  // request the "rest" of the string (everything that did not match the binding)
                return hdl;
              }
          }
        catch (SAFplus::Error& e)
          {
          }
        lastSlash = xpath.find_last_of("/[");
        if (lastSlash == std::string::npos) break;
        xpath = xpath.substr(0,lastSlash);
      }
    return INVALID_HDL;
  }

  void lookupObjects(const std::string& pathSpec, std::vector<MgtObject*>* matches)
  {
    MgtRoot *mgtRoot = MgtRoot::getInstance();

    // If there are non xpath directives preceding the XPATH then strip and process them
    // TODO: add directives
    std::string xpath;
    if (pathSpec[0] == '{')
      {
        xpath = pathSpec.substr(pathSpec.find('}')+1);
      }
    else
      {
        xpath = pathSpec;
      }

    mgtRoot->resolvePath(xpath.c_str()+1,matches);  // +1 to drop the preceding /

  }

  SAFplus::MsgReply *mgtRpcRequest(SAFplus::Handle src, MsgMgt_MgtMsgType reqType, const std::string& pathSpec, const std::string& value = "", Mgt::Msg::MsgRpc::MgtRpcType rpcType=Mgt::Msg::MsgRpc::CL_MGT_RPC_VALIDATE)
  {
    SAFplus::MsgReply *msgReply = NULL;
    uint retryDuration = SAFplusI::MsgSafplusSendReplyRetryInterval;
    std::string request;
    if (pathSpec[0]=='{')
      {
        if ((pathSpec[1] == 'b')||(pathSpec[1] == 'p')) // Commands a break (to gdb) or pause on the server side processing this RPC, so we'll wait forever before retrying
          {
            retryDuration = 1000*1000*1000;
          }
      }
    MsgMgt mgtMsgReq;
    MsgRpc rpcMsgReq;
    if(reqType==Mgt::Msg::MsgMgt::CL_MGT_MSG_RPC)
    {
        std::string data = value;
        rpcMsgReq.set_rpctype(rpcType);
        rpcMsgReq.set_data(data);
        rpcMsgReq.set_bind(pathSpec);
        rpcMsgReq.SerializeToString(&request);
    }
    else
    {
        mgtMsgReq.set_type(reqType);
        mgtMsgReq.set_bind(pathSpec);
        mgtMsgReq.add_data(value);
        mgtMsgReq.SerializeToString(&request);
        logError("MGT", "REV", "send MGT [%d] [%s] [%s]",reqType,pathSpec.c_str(),value.c_str());
    }
    SAFplus::SafplusMsgServer* mgtIocInstance = &SAFplus::safplusMsgServer;
    try
      {
        msgReply = mgtIocInstance->sendReply(src, (void *) request.c_str(), request.size(), SAFplusI::CL_MGT_MSG_TYPE, NULL, retryDuration);
        if (!msgReply)
        {
            logError("MGT", "REV", "No REPLY");
        }
      }
    catch (SAFplus::Error &ex)
      {
        logError("MGT", "REQ", "RPC [%d] failure for xpath [%s]", reqType, pathSpec.c_str());
      }
    return msgReply;
  }

  SAFplus::MsgReply *mgtRestRpcRequest(SAFplus::Handle src, MsgMgt_MgtMsgType reqType, const std::string& pathSpec, const std::string& value = "", Mgt::Msg::MsgRpc::MgtRpcType rpcType=Mgt::Msg::MsgRpc::CL_MGT_RPC_VALIDATE)
  {
	SAFplus::MsgReply *msgReply = NULL;
	uint retryDuration = SAFplusI::MsgSafplusSendReplyRetryInterval;
	std::string request;
	if (pathSpec[0]=='{')
	{
		if ((pathSpec[1] == 'b')||(pathSpec[1] == 'p')) // Commands a break (to gdb) or pause on the server side processing this RPC, so we'll wait forever before retrying
		{
		retryDuration = 1000*1000*1000;
		}
	}
	MsgMgt mgtMsgReq;
	MsgRpc rpcMsgReq;
	if(reqType == Mgt::Msg::MsgMgt::CL_MGT_MSG_REST_RPC)
	{
		std::string data = value;
		rpcMsgReq.set_rpctype(rpcType);
		rpcMsgReq.set_data(data);
		rpcMsgReq.set_bind(pathSpec);
		rpcMsgReq.SerializeToString(&request);
	}
	else
	{
		mgtMsgReq.set_type(reqType);
		mgtMsgReq.set_bind(pathSpec);
		mgtMsgReq.add_data(value);
		mgtMsgReq.SerializeToString(&request);
		logError("MGT", "REV", "send MGT [%d] [%s] [%s]",reqType,pathSpec.c_str(),value.c_str());
	}
	SAFplus::SafplusMsgServer* mgtIocInstance = &SAFplus::safplusMsgServer;
	try
	{
		msgReply = mgtIocInstance->sendReply(src, (void *) request.c_str(), request.size(), SAFplusI::CL_MGT_MSG_TYPE, NULL, retryDuration);
		if (!msgReply)
		{
			logError("MGT", "REV", "No REPLY");
		}
	}
	catch (SAFplus::Error &ex)
	{
		logError("MGT", "REQ", "RPC [%d] failure for xpath [%s]", reqType, pathSpec.c_str());
	}
	return msgReply;
  }

  std::string mgtGet(SAFplus::Handle src, const std::string& pathSpec)
  {
    std::string output = "";
    MsgGeneral rxMsg;
    logError("MGT", "REV", "mgtget call");
    SAFplus::MsgReply *msgReply = mgtRpcRequest(src, Mgt::Msg::MsgMgt::CL_MGT_MSG_XGET, pathSpec);
    if (msgReply != NULL)
    {
      rxMsg.ParseFromArray(msgReply->buffer, strlen(msgReply->buffer));
      if (rxMsg.data_size() == 1) //Received data
        {
          output.assign(rxMsg.data(0));
        }
      else
        {
          logError("MGT", "REV", "Invalid message with data size %d", rxMsg.data_size());
        }
    }
    return output;
  }

  std::string mgtGet(const std::string& pathSpec)
  {
    std::string output = "";
    std::vector<MgtObject*> matches;

    std::string suffixLoc = pathSpec.substr(pathSpec.find('/') + 1);
    if (suffixLoc.empty())
      {
        MgtRoot *mgtRoot = MgtRoot::getInstance();

        // 1. 'get' all children of root
        for (MgtObject::Iterator it = mgtRoot->begin(); it != mgtRoot->end(); it++)
        {
            std::string objxml;
            it->second->get(&objxml);
            output.append(objxml);
        }

        // 2. Forward to retrieve from handle
        // 2.1 Collect handle from checkpoint
        std::set<SAFplus::Handle> processHdl;
        for (Checkpoint::Iterator it = mgtCheckpoint->begin(); it != mgtCheckpoint->end(); ++it)
          {
            SAFplus::Buffer *b = (*it).second.get();
            if (b)
              {
                assert(b->len() == sizeof(SAFplus::Handle));
                SAFplus::Handle hdl = *((const SAFplus::Handle*) b->data);
                processHdl.insert(getProcessHandle(hdl));  // Only care about the process because the RPC ends up at the MGT request handler anyway.  And by using the process handle, duplicates are removed.
              }
          }

        // 2.2 Issue 'get' all children for each handle (also ignore duplicate handle)
        std::set<SAFplus::Handle>::iterator it;
        for (it = processHdl.begin(); it != processHdl.end(); ++it)
          {
            std::string objxml;
            SAFplus::Handle hdl = *it;
            objxml = mgtGet(hdl, pathSpec);
            output.append(objxml);
          }

        return output;
      }

    lookupObjects(pathSpec, &matches);

    if (matches.size())
      {
        for(std::vector<MgtObject*>::iterator i = matches.begin(); i != matches.end(); i++)
          {
            std::string objxml;
            (*i)->get(&objxml);
            output.append(objxml);
          }
      }
    else  // Object Implementer not found. Broadcast message to get data
      {
        ClRcT errCode = CL_OK;
        Handle hdl = getMgtHandle(pathSpec, errCode);
        if (INVALID_HDL != hdl)
        {
          output = mgtGet(hdl, pathSpec);  // Pass the {} directives through to the server side
        }
        else
          {
            logError("MGT", "REV", "Route [%s] has no implementer", pathSpec.c_str());
            throw Error(Error::SAFPLUS_ERROR,Error::DOES_NOT_EXIST,"Route has no implementer",__FILE__,__LINE__);
          }
      }
    return output;
  }

  ClRcT mgtSet(SAFplus::Handle src, const std::string& pathSpec, const std::string& value)
  {
    ClRcT rcRet = CL_OK;

    SAFplus::MsgReply *msgReply = mgtRpcRequest(src, Mgt::Msg::MsgMgt::CL_MGT_MSG_XSET, pathSpec, value);

    if (msgReply == NULL)
      {
    	rcRet = CL_ERR_IGNORE_REQUEST;
      }
    else
      {
        memcpy(&rcRet, msgReply->buffer, sizeof(ClRcT));
      }
    return rcRet;
  }

  ClRcT mgtSet(const std::string& pathSpec, const std::string& value)
  {
    ClRcT rcRet = CL_OK;
    std::vector<MgtObject*> matches;

    lookupObjects(pathSpec, &matches);

    if (matches.size())
      {
        for(std::vector<MgtObject*>::iterator i = matches.begin(); i != matches.end(); i++)
          {
        	rcRet = (*i)->setObj(value);
          }
      }
    else  // Object Implementer not found. Broadcast message to get data
      {
        Handle hdl = getMgtHandle(pathSpec, rcRet);
        if (rcRet == CL_OK && INVALID_HDL != hdl)
        {
        	rcRet = mgtSet(hdl, pathSpec, value);
        }
        else
          {
            logError("MGT", "REV", "Route [%s] has no implementer", pathSpec.c_str());
            throw Error(Error::SAFPLUS_ERROR,Error::DOES_NOT_EXIST,"Route has no implementer",__FILE__,__LINE__);
          }
      }

    return rcRet;
  }


  ClRcT mgtRpc(SAFplus::Handle src,Mgt::Msg::MsgRpc::MgtRpcType mgtRpcType,const std::string& pathSpec,const std::string& request)
  {
    ClRcT rcRet = CL_OK;
    SAFplus::MsgReply *msgReply = mgtRpcRequest(src, Mgt::Msg::MsgMgt::CL_MGT_MSG_REST_RPC, pathSpec, request,mgtRpcType);
    if (msgReply == NULL)
      {
    	rcRet = CL_ERR_IGNORE_REQUEST;
      }
    else
      {
        memcpy(&rcRet, msgReply->buffer, sizeof(ClRcT));
      }
    return rcRet;
  }

  ClRcT mgtRpc(Mgt::Msg::MsgRpc::MgtRpcType mgtRpcType,const std::string& pathSpec, const std::string& request)
  {
    ClRcT rcRet = CL_OK;
    ClBoolT rc = CL_TRUE;
    std::vector<MgtObject*> matches;

    lookupObjects(pathSpec, &matches);

    if (matches.size())
      {
        for(std::vector<MgtObject*>::iterator i = matches.begin(); i != matches.end(); i++)
          {
            MgtRpc *rpc = dynamic_cast<MgtRpc*> (*i);
            if(request!="")
            {
              logDebug("MGT","RPC","set rpc input parameter");
              rpc->setInParams((void*)request.c_str(),request.length());
            }
            switch (mgtRpcType)
            {
              case Mgt::Msg::MsgRpc::CL_MGT_RPC_VALIDATE:
                rc = rpc->validate();
                break;
              case Mgt::Msg::MsgRpc::CL_MGT_RPC_INVOKE:
                rc = rpc->invoke();
                break;
              case Mgt::Msg::MsgRpc::CL_MGT_RPC_POSTREPLY:
                rc = rpc->postReply();
                break;
              default:
                break;
            }
          }
      }
    else  // Object Implementer not found. Broadcast message to get data
      {
        Handle hdl = getMgtHandle(pathSpec, rcRet);
        if (rcRet == CL_OK && INVALID_HDL != hdl)
        {
          rcRet = mgtRpc(hdl,mgtRpcType, pathSpec, request);
        }
        else
          {
            rcRet = CL_OK;
            logError("MGT", "REV", "Route [%s] has no implementer", pathSpec.c_str());
            throw Error(Error::SAFPLUS_ERROR,Error::DOES_NOT_EXIST,"Route has no implementer",__FILE__,__LINE__);
          }
      }
    if(CL_FALSE == rc) rcRet = CL_ERR_NOT_EXIST;
    return rcRet;
  }


  ClRcT mgtCreate(SAFplus::Handle src, const std::string& pathSpec)
  {
    ClRcT rcRet = CL_OK;

    SAFplus::MsgReply *msgReply = mgtRpcRequest(src, Mgt::Msg::MsgMgt::CL_MGT_MSG_CREATE, pathSpec);

    if (msgReply == NULL)
      {
    	rcRet = CL_ERR_IGNORE_REQUEST;
      }
    else
      {
        memcpy(&rcRet, msgReply->buffer, sizeof(ClRcT));
      }
    return rcRet;
  }

  ClRcT mgtCreate(const std::string& pathSpec)
  {
      ClRcT rcRet = CL_OK;
      std::vector<MgtObject*> matches;

      std::size_t idx = pathSpec.find_last_of("/");

      if (idx == std::string::npos)
        {
          // Invalid xpath
          return CL_ERR_INVALID_PARAMETER;
        }

      std::string path = pathSpec.substr(0, idx);
      std::string value = pathSpec.substr(idx + 1);

      lookupObjects(path, &matches);

      if (matches.size())
        {
          for(std::vector<MgtObject*>::iterator i = matches.begin(); i != matches.end(); i++)
            {
        	  rcRet = (*i)->createObj(value);
            }
        }
      else  // Object Implementer not found. Broadcast message to get data
        {
          Handle hdl = getMgtHandle(pathSpec, rcRet);
          if (rcRet == CL_OK && INVALID_HDL != hdl)
          {
        	  rcRet = mgtCreate(hdl, pathSpec);
          }
          else
            {
        	  rcRet = CL_OK;
              logError("MGT", "REV", "Route [%s] has no implementer", pathSpec.c_str());
              throw Error(Error::SAFPLUS_ERROR,Error::DOES_NOT_EXIST,"Route has no implementer",__FILE__,__LINE__);
            }
        }
    return rcRet;
  }

  ClRcT mgtDelete(SAFplus::Handle src, const std::string& pathSpec)
  {
    ClRcT rcRet = CL_OK;

    SAFplus::MsgReply *msgReply = mgtRpcRequest(src, Mgt::Msg::MsgMgt::CL_MGT_MSG_DELETE, pathSpec);

    if (msgReply == NULL)
      {
    	rcRet = Error::DOES_NOT_EXIST;
      }
    else
      {
        memcpy(&rcRet, msgReply->buffer, sizeof(ClRcT));
      }
    return rcRet;
  }

  ClRcT mgtDelete(const std::string& pathSpec)
  {
    ClRcT rcRet = CL_OK;
    std::vector<MgtObject*> matches;
    std::size_t idx = pathSpec.find_last_of("/");

    assert(idx != std::string::npos);  // All the xpaths should have at least one / (they should BEGIN with a /)

    std::string path = pathSpec.substr(0, idx);
    std::string value = pathSpec.substr(idx + 1);

    lookupObjects(path, &matches);

    if (matches.size())
      {
        for(std::vector<MgtObject*>::iterator i = matches.begin(); i != matches.end(); i++)
          {
        	rcRet = (*i)->deleteObj(value);
          }
      }
    else  // Object Implementer not found. Broadcast message to get data
      {
        Handle hdl = getMgtHandle(pathSpec, rcRet);
        if (rcRet == CL_OK && INVALID_HDL != hdl)
        {
        	rcRet = mgtDelete(hdl, pathSpec);
        }
        else
          {
            logError("MGT", "REV", "Route [%s] has no implementer", pathSpec.c_str());
            throw Error(Error::SAFPLUS_ERROR,Error::DOES_NOT_EXIST,"Route has no implementer",__FILE__,__LINE__);
          }
      }
    return rcRet;
  }

     //? Get information from the management subsystem -- removes the XML and casts
  uint64_t mgtGetUint(const std::string& pathSpec)
     {
       std::string result = mgtGet(pathSpec);
       if (result.size() == 0)
         {
            throw Error(Error::SAFPLUS_ERROR,Error::DOES_NOT_EXIST,"Path does not exist",__FILE__,__LINE__);
         }
       int start = result.find('>');
       start++;
       int end = result.find('<',start);
       std::string val = result.substr(start,end-start);
       return boost::lexical_cast<uint64_t>(val);

     }

     //? Get information from the management subsystem -- removes the XML and casts
     int64_t mgtGetInt(const std::string& pathSpec)
     {
       std::string result = mgtGet(pathSpec);
       if (result.size() == 0)
         {
            throw Error(Error::SAFPLUS_ERROR,Error::DOES_NOT_EXIST,"Path does not exist",__FILE__,__LINE__);
         }
       int start = result.find('>');
       start++;
       int end = result.find('<',start);
       std::string val = result.substr(start,end-start);
       return boost::lexical_cast<int64_t>(val);

 
     }
     //? Get information from the management subsystem -- removes the XML and casts
     double   mgtGetNum(const std::string& pathSpec)
     {
       std::string result = mgtGet(pathSpec);
       if (result.size() == 0)
         {
            throw Error(Error::SAFPLUS_ERROR,Error::DOES_NOT_EXIST,"Path does not exist",__FILE__,__LINE__);
         }
       int start = result.find('>');
       start++;
       int end = result.find('<',start);
       std::string val = result.substr(start,end-start);
       return boost::lexical_cast<double>(val);

      }
     //? Get information from the management subsystem -- removes the XML and casts	
     std::string mgtGetString(const std::string& pathSpec)
     {
       std::string result = mgtGet(pathSpec);
       if (result.size() == 0)
         {
            throw Error(Error::SAFPLUS_ERROR,Error::DOES_NOT_EXIST,"Path does not exist",__FILE__,__LINE__);
         }
       int start = result.find('>');
       start++;
       int end = result.find('<',start);
       std::string val = result.substr(start,end-start);
       return val;

      }


ClRcT mgtRestRpc(SAFplus::Handle src, const std::string& pathSpec, const std::string& value)
{
  ClRcT rcRet = CL_OK;
  SAFplus::MsgReply *msgReply = mgtRestRpcRequest(src, Mgt::Msg::MsgMgt::CL_MGT_MSG_REST_RPC, pathSpec, value);
  if (msgReply == NULL)
    {
	  rcRet = CL_ERR_IGNORE_REQUEST;
    }
  else
    {
      memcpy(&rcRet, msgReply->buffer, sizeof(ClRcT));
    }
  return rcRet;
}

ClRcT mgtRestRpc(const std::string& pathSpec, const std::string& value)
{
  ClRcT rcRet = CL_OK;
  ClBoolT rc = CL_FALSE;
  std::vector<MgtObject*> matches;
  lookupObjects(pathSpec, &matches);

  if (matches.size())
    {
      for(std::vector<MgtObject*>::iterator i = matches.begin(); i != matches.end(); i++)
        {
          MgtRpc *rpc = dynamic_cast<MgtRpc*> (*i);
          if(value.length() > 0)
          {
            logDebug("MGT","RPC","set mgtRestRpc input parameter");
            rpc->setInParams((void*)value.c_str(),value.length());
          }
		  rc = rpc->validate();
		  if(CL_TRUE == rc) rc = rpc->invoke();
		  if(CL_TRUE == rc) rc = rpc->postReply();
		  if(CL_FALSE == rc) rcRet = CL_ERR_NOT_EXIST;
        }
    }
  else  // Object Implementer not found. Broadcast message to get data
    {
      Handle hdl = getMgtHandle(pathSpec, rcRet);
      if (rcRet == CL_OK && INVALID_HDL != hdl)
      {
    	  rcRet = mgtRestRpc(hdl, pathSpec, value);
      }
      else
        {
    	  rcRet = CL_OK;
          logError("MGT", "REV", "Route [%s] has no implementer", pathSpec.c_str());
          throw Error(Error::SAFPLUS_ERROR,Error::DOES_NOT_EXIST,"Route has no implementer",__FILE__,__LINE__);
        }
    }
  return rcRet;
}

std::string mgtRestGet(SAFplus::Handle src, const std::string& pathSpec, const std::string& value)
{
  std::string output = "";
  MsgGeneral rxMsg;
  logDebug("MGT", "REV", "mgtRestGet call");
  SAFplus::MsgReply *msgReply = mgtRestRpcRequest(src, Mgt::Msg::MsgMgt::CL_MGT_MSG_REST_GET, pathSpec);
  if (msgReply != NULL)
  {
    rxMsg.ParseFromArray(msgReply->buffer, strlen(msgReply->buffer));
    if (rxMsg.data_size() == 1) //Received data
      {
        output.assign(rxMsg.data(0));
      }
    else
      {
        logError("MGT", "REV", "Invalid message with data size %d", rxMsg.data_size());
      }
  }
  return output;
}

std::string mgtRestGet(const std::string& pathSpec, const std::string& value)
{
  std::string output = "";
  std::vector<MgtObject*> matches;

  std::string suffixLoc = pathSpec.substr(pathSpec.find('/') + 1);
  if (suffixLoc.empty())
    {
      MgtRoot *mgtRoot = MgtRoot::getInstance();

      // 1. 'get' all children of root
      for (MgtObject::Iterator it = mgtRoot->begin(); it != mgtRoot->end(); it++)
      {
          std::string objxml;
          it->second->get(&objxml);
          output.append(objxml);
      }

      // 2. Forward to retrieve from handle
      // 2.1 Collect handle from checkpoint
      std::set<SAFplus::Handle> processHdl;
      for (Checkpoint::Iterator it = mgtCheckpoint->begin(); it != mgtCheckpoint->end(); ++it)
        {
          SAFplus::Buffer *b = (*it).second.get();
          if (b)
            {
              assert(b->len() == sizeof(SAFplus::Handle));
              SAFplus::Handle hdl = *((const SAFplus::Handle*) b->data);
              processHdl.insert(getProcessHandle(hdl));  // Only care about the process because the RPC ends up at the MGT request handler anyway.  And by using the process handle, duplicates are removed.
            }
        }

      // 2.2 Issue 'get' all children for each handle (also ignore duplicate handle)
      std::set<SAFplus::Handle>::iterator it;
      for (it = processHdl.begin(); it != processHdl.end(); ++it)
        {
          std::string objxml;
          SAFplus::Handle hdl = *it;
          objxml = mgtRestGet(hdl, pathSpec);
          output.append(objxml);
        }

      return output;
    }

  lookupObjects(pathSpec, &matches);

  if (matches.size())
    {
      for(std::vector<MgtObject*>::iterator i = matches.begin(); i != matches.end(); i++)
        {
          std::string objxml;
          (*i)->get(&objxml);
          output.append(objxml);
        }
    }
  else  // Object Implementer not found. Broadcast message to get data
    {
      ClRcT errCode = CL_OK;
      Handle hdl = getMgtHandle(pathSpec, errCode);
      if (INVALID_HDL != hdl)
      {
        output = mgtRestGet(hdl, pathSpec);  // Pass the {} directives through to the server side
      }
      else
        {
          logError("MGT", "REV", "Route [%s] has no implementer", pathSpec.c_str());
          throw Error(Error::SAFPLUS_ERROR,Error::DOES_NOT_EXIST,"Route has no implementer",__FILE__,__LINE__);
        }
    }
  return output;
}

ClRcT mgtRestPut(SAFplus::Handle src, const std::string& pathSpec, const std::string& value)
{
  ClRcT rcRet = CL_OK;

  SAFplus::MsgReply *msgReply = mgtRestRpcRequest(src, Mgt::Msg::MsgMgt::CL_MGT_MSG_REST_PUT, pathSpec, value);

  if (msgReply == NULL)
    {
	  rcRet = CL_ERR_IGNORE_REQUEST;
    }
  else
    {
      memcpy(&rcRet, msgReply->buffer, sizeof(ClRcT));
    }
  return rcRet;
}

ClRcT mgtRestPut(const std::string& pathSpec, const std::string& value)
{
  ClRcT rcRet = CL_OK;
  std::vector<MgtObject*> matches;
  std::size_t idx = pathSpec.find_last_of("/");
  assert(idx != std::string::npos);  // All the xpaths should have at least one / (they should BEGIN with a /)
  std::string path = pathSpec.substr(0, idx);//get parent

  lookupObjects(path, &matches);
  if (matches.size())
    {
      for(std::vector<MgtObject*>::iterator i = matches.begin(); i != matches.end(); i++)
        {
    	  rcRet = (*i)->createObj(value,false);
        }
    }else  // Object Implementer not found. Broadcast message to get data
    {
		  Handle hdl = getMgtHandle(pathSpec, rcRet);
		  if (rcRet == CL_OK && INVALID_HDL != hdl)
		  {
			  rcRet = mgtRestPut(hdl, pathSpec, value);
		  }
		  else
			{
			  logError("MGT", "REV", "Route [%s] has no implementer", pathSpec.c_str());
			  throw Error(Error::SAFPLUS_ERROR,Error::DOES_NOT_EXIST,"Route has no implementer",__FILE__,__LINE__);
			}

    }

  return rcRet;
}

ClRcT mgtRestPatch(SAFplus::Handle src, const std::string& pathSpec, const std::string& value)
{
  ClRcT rcRet = CL_OK;

  SAFplus::MsgReply *msgReply = mgtRestRpcRequest(src, Mgt::Msg::MsgMgt::CL_MGT_MSG_REST_PATCH, pathSpec, value);

  if (msgReply == NULL)
    {
	  rcRet = CL_ERR_IGNORE_REQUEST;
    }
  else
    {
      memcpy(&rcRet, msgReply->buffer, sizeof(ClRcT));
    }
  return rcRet;
}

ClRcT mgtRestPatch(const std::string& pathSpec, const std::string& value)
{
  ClRcT rcRet = CL_OK;
  std::vector<MgtObject*> matches;
  std::size_t idx = pathSpec.find_last_of("/");
  assert(idx != std::string::npos);  // All the xpaths should have at least one / (they should BEGIN with a /)
  std::string path = pathSpec.substr(0, idx);//get parent
  lookupObjects( pathSpec, &matches);
  if (matches.size())
  {
  //get bulk data path
  xmlParser xmlObj(value);
  std::map<std::string, std::string> mapPath = xmlObj.getChildPathValues("data",path);

  for (std::map<std::string, std::string>::iterator it = mapPath.begin(); it != mapPath.end(); ++it)
	{
		try{
			matches.clear();
			lookupObjects((*it).first, &matches);
			if (matches.size())
			{
				for(std::vector<MgtObject*>::iterator i = matches.begin(); i != matches.end(); i++)
				{
					rcRet = (*i)->setObj((*it).second);
				}
			}
		}catch(...)
		{
			rcRet = CL_ERR_NOT_EXIST;
		break;
		}
	}//for
  }else  // Object Implementer not found. Broadcast message to get data
	{
		Handle hdl = getMgtHandle(pathSpec, rcRet);
		if (rcRet == CL_OK && INVALID_HDL != hdl)
		{
			rcRet = mgtRestPatch(hdl, pathSpec, value);
		}
		else
		{
			logError("MGT", "REV", "Route [%s] has no implementer", pathSpec.c_str());
			throw Error(Error::SAFPLUS_ERROR,Error::DOES_NOT_EXIST,"Route has no implementer",__FILE__,__LINE__);
		}
	}

  return rcRet;
}

ClRcT mgtRestPost(SAFplus::Handle src, const std::string& pathSpec, const std::string& value)
{
  ClRcT rcRet = CL_OK;

  SAFplus::MsgReply *msgReply = mgtRestRpcRequest(src, Mgt::Msg::MsgMgt::CL_MGT_MSG_REST_POST, pathSpec, value);

  if (msgReply == NULL)
    {
	  rcRet = CL_ERR_IGNORE_REQUEST;
    }
  else
    {
      memcpy(&rcRet, msgReply->buffer, sizeof(ClRcT));
    }
  return rcRet;
}

ClRcT mgtRestPost(const std::string& pathSpec, const std::string& value)
{
  ClRcT rcRet = CL_OK;
  std::vector<MgtObject*> matches;

  lookupObjects(pathSpec, &matches);
  std::cout<<"pathSpec:"<<pathSpec<<",value:"<<value<<","<<__FUNCTION__<<","<<__FILE__<<__LINE__<<std::endl;
  if (matches.size())
    {
      for(std::vector<MgtObject*>::iterator i = matches.begin(); i != matches.end(); i++)
        {
    	  try{
    		  rcRet = (*i)->createObj(value);
    	  }catch(...)
    	  {
    		  logError("MGT","SET","Exception object not support xml value[%s]", value.c_str());
    		  rcRet = CL_ERR_NOT_EXIST;
    	  }
        }//for
    }//if
  else  // Object Implementer not found. Broadcast message to get data
    {
      Handle hdl = getMgtHandle(pathSpec, rcRet);
      if (rcRet == CL_OK && INVALID_HDL != hdl)
      {
    	  rcRet = mgtRestPost(hdl, pathSpec, value);
      }
      else
        {
          logError("MGT", "REV", "Route [%s] has no implementer", pathSpec.c_str());
          throw Error(Error::SAFPLUS_ERROR,Error::DOES_NOT_EXIST,"Route has no implementer",__FILE__,__LINE__);
        }
    }
  return rcRet;
}
ClRcT mgtRestDelete(SAFplus::Handle src, const std::string& pathSpec, const std::string& value)
{
  ClRcT rcRet = CL_OK;

  SAFplus::MsgReply *msgReply = mgtRestRpcRequest(src, Mgt::Msg::MsgMgt::CL_MGT_MSG_REST_DELETE, pathSpec, value);

  if (msgReply == NULL)
    {
	  rcRet = Error::DOES_NOT_EXIST;
    }
  else
    {
      memcpy(&rcRet, msgReply->buffer, sizeof(ClRcT));
    }
  return rcRet;
}

ClRcT mgtRestDelete(const std::string& pathSpec, const std::string& value)
{
  ClRcT rcRet = CL_OK;
  std::vector<MgtObject*> matches;
  std::size_t idx = pathSpec.find_last_of("/");

  assert(idx != std::string::npos);  // All the xpaths should have at least one / (they should BEGIN with a /)

  std::string path = pathSpec.substr(0, idx);
  std::string lvalue = pathSpec.substr(idx + 1);

  lookupObjects(path, &matches);
  if (matches.size())
    {
      for(std::vector<MgtObject*>::iterator i = matches.begin(); i != matches.end(); i++)
        {
    	  rcRet = (*i)->deleteObj(lvalue);
        }
    }
  else  // Object Implementer not found. Broadcast message to get data
    {
      Handle hdl = getMgtHandle(pathSpec, rcRet);
      if (rcRet == CL_OK && INVALID_HDL != hdl)
      {
    	  rcRet = mgtRestDelete(hdl, pathSpec, value);
      }
      else
        {
          logError("MGT", "REV", "Route [%s] has no implementer", pathSpec.c_str());
          throw Error(Error::SAFPLUS_ERROR,Error::DOES_NOT_EXIST,"Route has no implementer",__FILE__,__LINE__);
        }
    }
  return rcRet;
}

}

extern "C" void dbgDumpMgtBindings()
{
  // 2. Forward to retrieve from handle
  // 2.1 Collect handle from checkpoint
  std::vector<SAFplus::Handle> processHdl;
  for (SAFplus::Checkpoint::Iterator it = SAFplus::mgtCheckpoint->begin(); it != SAFplus::mgtCheckpoint->end(); ++it)
    {
      SAFplus::Buffer *b = (*it).second.get();

      if (b)
	{
	  assert(b->len() == sizeof(SAFplus::Handle));
	  SAFplus::Handle hdl = *((const SAFplus::Handle*) b->data);
	  printf("%s -> [%" PRIx64 ":%" PRIx64 "] node: %d, port: %d\n",((char*) (*it).first->data),hdl.id[0],hdl.id[1],hdl.getNode(),hdl.getPort());
	}
    }
}


