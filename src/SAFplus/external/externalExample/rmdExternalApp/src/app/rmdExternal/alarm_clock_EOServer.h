/*********************************************************************
* File: 
*********************************************************************/
/*********************************************************************
* Description : This file contains the declartions for server stub
*               routines
*     
* THIS FILE IS AUTO-GENERATED BY OPENCLOVIS IDE. EDIT THIS FILE AT
* YOUR OWN RISK. ANY CHANGE TO THIS FILE WILL BE OVERWRITTEN ON
* RE-GENERATION.
*     
*********************************************************************/

#ifndef _ALARM_CLOCK_EO_SERVER_H_
#define _ALARM_CLOCK_EO_SERVER_H_
#ifdef __cplusplus
extern "C" {
#endif
#include <clXdrApi.h>
#include <clIdlApi.h>
#include <ipi/clRmdIpi.h>
#include "../common/clientIDDefinitions.h"
#include "xdrAlarmReactionT.h"
#include "xdrAcTimeT.h"
#include "rmdServer.h"

ClRcT clAlarm_clock_EOIdlSyncDefer(ClIdlHandleT *pIdlHdl);
ClRcT clAlarm_clock_EOClientInstall(void);
ClRcT clAlarm_clock_EOClientUninstall(void);
extern ClRcT GetTimeServer_4_0_0(ClEoDataT eoData, ClBufferHandleT inmSgHdl , ClBufferHandleT outMsgHdl);
extern ClRcT SetTimeServer_4_0_0(ClEoDataT eoData, ClBufferHandleT inmSgHdl , ClBufferHandleT outMsgHdl);
extern ClRcT SetAlarmServer_4_0_0(ClEoDataT eoData, ClBufferHandleT inmSgHdl , ClBufferHandleT outMsgHdl);


#ifdef __cplusplus
}

#endif
#endif /*_ALARM_CLOCK_EO_SERVER_H_*/
