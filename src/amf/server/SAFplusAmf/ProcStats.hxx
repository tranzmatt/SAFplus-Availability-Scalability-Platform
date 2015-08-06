/* 
 * File ProcStats.hxx
 * This file has been auto-generated by Y2CPP, the
 * plug-in of pyang.
 */ 

#pragma once
#ifndef PROCSTATS_HXX_
#define PROCSTATS_HXX_
#include "SAFplusAmfCommon.hxx"

#include "ResidentMem.hxx"
#include "ProcessStats.hxx"
#include "PageFaults.hxx"
#include "NumThreads.hxx"
#include "MemUtilization.hxx"
#include <vector>
#include "MgtFactory.hxx"
#include "Failures.hxx"
#include "CpuUtilization.hxx"

namespace SAFplusAmf
  {

    class ProcStats : public SAFplusTypes::ProcessStats {

        /* Apply MGT object factory */
        MGT_REGISTER(ProcStats);

    public:
        SAFplusTypes::Failures failures;
        SAFplusTypes::CpuUtilization cpuUtilization;
        SAFplusTypes::MemUtilization memUtilization;
        SAFplusTypes::PageFaults pageFaults;
        SAFplusTypes::NumThreads numThreads;
        SAFplusTypes::ResidentMem residentMem;

    public:
        ProcStats();
        std::vector<std::string>* getChildNames();
        ~ProcStats();

    };
}
/* namespace SAFplusAmf */
#endif /* PROCSTATS_HXX_ */