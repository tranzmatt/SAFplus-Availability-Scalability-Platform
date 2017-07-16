// /*
//  * Copyright (C) 2002-2014 OpenClovis Solutions Inc.  All Rights Reserved.
//  *
//  * This file is available  under  a  commercial  license  from  the
//  * copyright  holder or the GNU General Public License Version 2.0.
//  *
//  * The source code for  this program is not published  or otherwise
//  * divested of  its trade secrets, irrespective  of  what  has been
//  * deposited with the U.S. Copyright office.
//  *
//  * This program is distributed in the  hope that it will be useful,
//  * but WITHOUT ANY WARRANTY; without even the implied  warranty  of
//  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
//  * General Public License for more details.
//  *
//  * For more  information, see  the file  COPYING provided with this
//  * material.
//  */

#ifndef STORAGE_ALARM_DATA_HXX_HEADER_INCLUDED
#define STORAGE_ALARM_DATA_HXX_HEADER_INCLUDED
#include <string>
#include <sstream>
#include <clCustomization.hxx>
#include <AlarmUtils.hxx>
#include <thread>
#include <mutex>

using namespace SAFplusAlarm;

namespace SAFplus
{
// this class to contain data on AlarmClient server side
class StorageAlarmData
{
public:
  StorageAlarmData();
  void initialize();
  bool findAlarmInfo(const AlarmKey& key, AlarmInfo& alarmInfo);
  std::vector<AlarmKey> getKeysAlarmInfo(const std::string& resourceId);
  void updateAlarmInfo(AlarmInfo& alarmInfo);
  void removeAlarmInfo(const AlarmKey& key);
  bool findAlarmProfileData(const AlarmKey& key, AlarmProfileData& alarmProfileData);
  void updateAlarmProfileData(const AlarmProfileData& alarmProfileData);
  void removeAlarmProfileData(const AlarmKey& key);
  void loadAlarmProfile();
  void loadAlarmData();
  void accumulateSummary(const AlarmSeverity& severity,const AlarmState& state,const bool& isIncrease = true);
  void changeSummary(const AlarmSeverity& fromSeverity, const AlarmSeverity& toSeverity);
  void printSummary();
  void printProfile();
  void printAlarm();
  bool isUpdate;
  // list of summary
  std::vector<Summary> vectSummary;
private:
  std::mutex mtxAlarmData;
  std::mutex mtxProfileData;
  MAPALARMPROFILEINFO m_ProfileInfoData;
  MAPMAPALARMINFO m_mapAlarmInfoData;
  SAFplus::Checkpoint m_checkpointProfile;
  SAFplus::Checkpoint m_checkpointAlarm;
  //last update time
  boost::posix_time::ptime lastUpdateAlarmData;
  boost::posix_time::ptime lastUpdateSummary;
};
}

#endif /* STORAGE_ALARM_DATA_HXX_HEADER_INCLUDED */
