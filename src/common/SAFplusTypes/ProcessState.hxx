/* 
 * File ProcessState.hxx
 * This file has been auto-generated by Y2CPP, the
 * plug-in of pyang.
 */ 

#pragma once
#ifndef PROCESSSTATE_HXX_
#define PROCESSSTATE_HXX_
#include "SAFplusTypesCommon.hxx"

#include "MgtEnumType.hxx"
#include <iostream>

namespace SAFplusTypes
  {

    enum class ProcessState
      {
        Running=0, Sleeping=1, WaitingForDisk=2, Zombie=3, Stopped=4, TracingStop=5
      };
    std::ostream& operator<<(std::ostream& os, const ProcessState& e);
    std::istream& operator>>(std::istream& is, ProcessState& e);
    const char* c_str(const ProcessState& e);

    /*
     * This is the class that will handle the conversion for us.
     */
    class ProcessStateManager : public SAFplus::MgtEnumType<ProcessStateManager, ProcessState> {
        ProcessStateManager();  // private to prevent instantiation
    public:
        static const map_t en2str_map;  // This is the lookup table.
    };
}
/* namespace SAFplusTypes */
#endif /* PROCESSSTATE_HXX_ */
