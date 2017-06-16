/* 
 * File AlarmSeverity.cxx
 * This file has been auto-generated by Y2CPP, the
 * plug-in of pyang.
 */ 

#include "MgtEnumType.hxx"
#include "SAFplusAlarmCommon.hxx"
#include <iostream>
#include "AlarmSeverity.hxx"


namespace SAFplusAlarm
  {

    /*
     * Provide an implementation of the en2str_map lookup table.
     */
    const AlarmSeverityManager::map_t AlarmSeverityManager::en2str_map = {
            pair_t(AlarmSeverity::INVALID, "INVALID"),
            pair_t(AlarmSeverity::CLEAR, "CLEAR"),
            pair_t(AlarmSeverity::WARNING, "WARNING"),
            pair_t(AlarmSeverity::MINOR, "MINOR"),
            pair_t(AlarmSeverity::MAJOR, "MAJOR"),
            pair_t(AlarmSeverity::CRITICAL, "CRITICAL")
    }; // uses c++11 initializer lists 

    const char* c_str(const ::SAFplusAlarm::AlarmSeverity &alarmSeverity)
    {
        return AlarmSeverityManager::c_str(alarmSeverity);
    };

    std::ostream& operator<<(std::ostream &os, const ::SAFplusAlarm::AlarmSeverity &alarmSeverity)
    {
        return os << AlarmSeverityManager::toString(alarmSeverity);
    };

    std::istream& operator>>(std::istream &is, ::SAFplusAlarm::AlarmSeverity &alarmSeverity)
    {
        std::string buf;
        is >> buf;
        alarmSeverity = AlarmSeverityManager::toEnum(buf);
        return is;
    };

}
/* namespace ::SAFplusAlarm */
