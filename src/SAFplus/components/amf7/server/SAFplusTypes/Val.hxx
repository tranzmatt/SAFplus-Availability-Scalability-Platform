/* 
 * File Val.hxx
 * This file has been auto-generated by Y2CPP, the
 * plug-in of pyang.
 */ 

#pragma once
#ifndef VAL_HXX_
#define VAL_HXX_
#include "SAFplusTypesCommon.hxx"

#include <vector>
#include "MgtFactory.hxx"
#include "IntStatistic.hxx"

namespace SAFplusTypes
  {

    class Val : public IntStatistic {

        /* Apply MGT object factory */
        MGT_REGISTER(Val);

    public:
        Val();
        void toString(std::stringstream &xmlString);
        std::vector<std::string>* getChildNames();
        ~Val();

    };
}
/* namespace SAFplusTypes */
#endif /* VAL_HXX_ */
