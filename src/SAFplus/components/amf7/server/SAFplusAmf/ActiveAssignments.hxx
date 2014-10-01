/* 
 * File ActiveAssignments.hxx
 * This file has been auto-generated by Y2CPP, the
 * plug-in of pyang.
 */ 

#pragma once
#ifndef ACTIVEASSIGNMENTS_HXX_
#define ACTIVEASSIGNMENTS_HXX_
#include "SAFplusAmfCommon.hxx"

#include <vector>
#include "MgtFactory.hxx"
#include "IntStatistic.hxx"

namespace SAFplusAmf
  {

    class ActiveAssignments : public SAFplusTypes::IntStatistic {

        /* Apply MGT object factory */
        MGT_REGISTER(ActiveAssignments);

    public:
        ActiveAssignments();
        std::vector<std::string>* getChildNames();
        ~ActiveAssignments();

    };
}
/* namespace SAFplusAmf */
#endif /* ACTIVEASSIGNMENTS_HXX_ */
