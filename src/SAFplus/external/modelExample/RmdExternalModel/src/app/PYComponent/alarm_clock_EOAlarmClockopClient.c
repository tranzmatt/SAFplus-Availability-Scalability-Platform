
/*********************************************************************
* ModuleName  : idl
*********************************************************************/
/*********************************************************************
* Description :ClientSide Stub routines
*
* THIS FILE IS AUTO-GENERATED BY OPENCLOVIS IDE. EDIT THIS FILE AT
* YOUR OWN RISK. ANY CHANGE TO THIS FILE WILL BE OVERWRITTEN ON
* RE-GENERATION.
*
*********************************************************************/

#include <netinet/in.h>
#include <string.h>
#include <clBufferApi.h>
#include <clRmdApi.h>
#include <clIdlApi.h>
#include <clEoApi.h>
#include <clLogApi.h>
#include <clLogApi.h>
#include <clXdrApi.h>
#include <clHandleApi.h>
#include "alarm_clock_EOAlarmClockopClient.h"
#define clprintf(severity, ...)   clAppLog(CL_LOG_HANDLE_APP, severity, 10, "MAI", CL_LOG_CONTEXT_UNSPECIFIED,__VA_ARGS__)

extern ClIdlClntT gIdlClnt;


ClRcT GetTimeClientSync_4_0_0(CL_IN ClIdlHandleT handle, CL_OUT acTimeT_4_0_0* current)
{
    ClRcT rc = CL_OK;
    ClVersionT funcVer = {4, 0, 0};
    ClUint32T funcNo = CL_EO_GET_FULL_FN_NUM(CL_EO_NATIVE_COMPONENT_TABLE_ID, 0);
    ClBufferHandleT inMsgHdl = 0;
    ClBufferHandleT outMsgHdl = 0;
    ClIocAddressT address = {{0}};
    ClIdlHandleObjT* pHandleObj = NULL;
    ClUint32T tempFlags = 0;

    rc = clHandleCheckout(gIdlClnt.idlDbHdl,handle,(void **)&pHandleObj);
    if( rc != CL_OK )
    {
        return rc ;
    }
    if (CL_IDL_ADDRESSTYPE_IOC == pHandleObj->address.addressType)
    {
        address = pHandleObj->address.address.iocAddress;
    }
    else if (CL_IDL_ADDRESSTYPE_NAME == pHandleObj->address.addressType)
    {
        rc = clNameToObjectReferenceGet(&(pHandleObj->address.address.nameAddress.name),
                                        pHandleObj->address.address.nameAddress.attrCount,
                                        pHandleObj->address.address.nameAddress.attr,
                                        pHandleObj->address.address.nameAddress.contextCookie,
                                        (ClUint64T*)&address);
        if (CL_OK != rc)
        {
            return rc;
        }
    }
    else
    {
        return CL_IDL_RC(CL_ERR_INVALID_PARAMETER);
    }


    rc = clBufferCreate(&outMsgHdl);
    if (CL_OK != rc)
    {
        return rc;
    }

    tempFlags |= pHandleObj->flags |
                 (CL_RMD_CALL_NON_PERSISTENT | CL_RMD_CALL_NEED_REPLY);
    tempFlags &= ~CL_RMD_CALL_ASYNC;
    rc = clRmdWithMsgVer(address, &funcVer, funcNo, inMsgHdl, outMsgHdl, tempFlags, &(pHandleObj->options), NULL);
    //clprintf(CL_LOG_SEV_INFO, "Enter GetTimeClientSync_4_0_0 : %d ",(int)address.iocLogicalAddress);
    if(CL_OK != rc)
    {
        clBufferDelete(&outMsgHdl);
    return rc;
    }


    rc = clXdrUnmarshallacTimeT_4_0_0( outMsgHdl, current);
    if (CL_OK != rc)
    {
        return rc;
    }

    clBufferDelete(&outMsgHdl);
    
    rc = clHandleCheckin(gIdlClnt.idlDbHdl,handle);
    return rc;
}

void printTime()
{
	clprintf(CL_LOG_SEV_INFO, "............................................");
}


static void GetTimeAsyncCallback_4_0_0(ClRcT rc, void *pIdlCookie, ClBufferHandleT inMsgHdl, ClBufferHandleT outMsgHdl)
{
    ClIdlCookieT* pCookie = (ClIdlCookieT*)pIdlCookie;
    ClRcT retVal = CL_OK;
    acTimeT_4_0_0  current;

    memset(&(current), 0, sizeof(acTimeT_4_0_0));


    if (CL_OK == rc)
    {
        retVal = clXdrUnmarshallacTimeT_4_0_0(outMsgHdl, &(current));
        if (CL_OK != retVal)
        {
            goto L0;
        }
    }

    if (rc != CL_OK)
    {
        retVal = rc;
    }
    clprintf(CL_LOG_SEV_INFO,"Get Time RPC Async [ From External App]: [%02d:%02d:%02d]",current.hour,current.minute,current.second);
    ((Alarm_clock_EOGetTimeAsyncCallbackT_4_0_0)(pCookie->actualCallback))(pCookie->handle, &(current), retVal, pCookie->pCookie);
    goto L1;

L1:

L0:  clHeapFree(pCookie);
     clBufferDelete(&outMsgHdl);
     return;
}


ClRcT GetTimeClientAsync_4_0_0(CL_IN ClIdlHandleT handle, CL_OUT acTimeT_4_0_0* current,CL_IN Alarm_clock_EOGetTimeAsyncCallbackT_4_0_0 fpAsyncCallback, CL_IN void *cookie)
{
    ClRcT rc = CL_OK;
    ClVersionT funcVer = {4, 0, 0};
    ClUint32T funcNo = CL_EO_GET_FULL_FN_NUM(CL_EO_NATIVE_COMPONENT_TABLE_ID, 0);
    ClBufferHandleT inMsgHdl = 0;
    ClBufferHandleT outMsgHdl = 0;
    ClIocAddressT address = {{0}};
    ClIdlHandleObjT* pHandleObj = NULL;
    ClRmdAsyncOptionsT asyncOptions;
    ClUint32T tempFlags = 0;
    ClIdlCookieT* pCookie = NULL;

    rc = clHandleCheckout(gIdlClnt.idlDbHdl,handle,(void **)&pHandleObj);
    if(rc != CL_OK)
    {
        return rc;
    }
    if (CL_IDL_ADDRESSTYPE_IOC == pHandleObj->address.addressType)
    {
        address = pHandleObj->address.address.iocAddress;
    }
    else if (CL_IDL_ADDRESSTYPE_NAME == pHandleObj->address.addressType)
    {
        rc = clNameToObjectReferenceGet(&(pHandleObj->address.address.nameAddress.name),
                                        pHandleObj->address.address.nameAddress.attrCount,
                                        pHandleObj->address.address.nameAddress.attr,
                                        pHandleObj->address.address.nameAddress.contextCookie,
                                        (ClUint64T*)&address);
        if (CL_OK != rc)
        {
            goto L;
        }
    }
    else
    {
        rc = CL_IDL_RC(CL_ERR_INVALID_PARAMETER);
        goto L;
    }

    if(fpAsyncCallback != NULL)
    {
        pCookie = (ClIdlCookieT*)clHeapAllocate(sizeof(ClIdlCookieT));
        if (NULL == pCookie)
        {
            return CL_IDL_RC(CL_ERR_NO_MEMORY);
        }
        
        asyncOptions.pCookie = NULL;
        asyncOptions.fpCallback = NULL;
        rc = clBufferCreate(&outMsgHdl);
        if (CL_OK != rc)
        {
            goto L2;
        }

        tempFlags |= pHandleObj->flags |
                     (CL_RMD_CALL_ASYNC | CL_RMD_CALL_NON_PERSISTENT | CL_RMD_CALL_NEED_REPLY);
        
        pCookie->pCookie = cookie;
        pCookie->actualCallback = (void(*)())fpAsyncCallback;
        pCookie->handle = handle;
        asyncOptions.pCookie = pCookie;
        asyncOptions.fpCallback = GetTimeAsyncCallback_4_0_0;
        rc = clRmdWithMsgVer(address, &funcVer, funcNo, inMsgHdl, outMsgHdl, tempFlags, &(pHandleObj->options), &asyncOptions);
        if (CL_OK != rc)
        {
            goto LL;
         }

    }
    else
    {
        tempFlags |= pHandleObj->flags |
                         (CL_RMD_CALL_ASYNC | CL_RMD_CALL_NON_PERSISTENT);
        rc = clRmdWithMsgVer(address, &funcVer, funcNo, inMsgHdl, 0, tempFlags, &(pHandleObj->options),NULL);
        if(CL_OK != rc)
        {
               goto L;
        }
    }
    
    
    clHandleCheckin(gIdlClnt.idlDbHdl,handle);
    return rc;

LL: clBufferDelete(&outMsgHdl);
L2:  clHeapFree(pCookie);
L:
     clHandleCheckin(gIdlClnt.idlDbHdl,handle);
    return rc;
}

