/* 
 * File PageFaults.hxx
 * This file has been auto-generated by Y2CPP, the
 * plug-in of pyang.
 */ 

#pragma once
#ifndef PAGEFAULTS_HXX_
#define PAGEFAULTS_HXX_
#include "SAFplusTypesCommon.hxx"

#include <vector>
#include "MgtFactory.hxx"
#include "IntStatistic.hxx"

namespace SAFplusTypes
  {

    class PageFaults : public IntStatistic {

        /* Apply MGT object factory */
        MGT_REGISTER(PageFaults);

    public:
        PageFaults();
        std::vector<std::string>* getChildNames();
        ~PageFaults();

    };
}
/* namespace SAFplusTypes */
#endif /* PAGEFAULTS_HXX_ */
