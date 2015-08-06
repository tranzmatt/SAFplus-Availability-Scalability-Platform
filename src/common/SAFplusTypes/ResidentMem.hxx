/* 
 * File ResidentMem.hxx
 * This file has been auto-generated by Y2CPP, the
 * plug-in of pyang.
 */ 

#pragma once
#ifndef RESIDENTMEM_HXX_
#define RESIDENTMEM_HXX_
#include "SAFplusTypesCommon.hxx"

#include <vector>
#include "MgtFactory.hxx"
#include "IntStatistic.hxx"

namespace SAFplusTypes
  {

    class ResidentMem : public IntStatistic {

        /* Apply MGT object factory */
        MGT_REGISTER(ResidentMem);

    public:
        ResidentMem();
        std::vector<std::string>* getChildNames();
        ~ResidentMem();

    };
}
/* namespace SAFplusTypes */
#endif /* RESIDENTMEM_HXX_ */
