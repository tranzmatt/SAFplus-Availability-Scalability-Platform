/* 
 * File Capacity.hxx
 * This file has been auto-generated by Y2CPP, the
 * plug-in of pyang.
 */ 

#pragma once
#ifndef CAPACITY_HXX_
#define CAPACITY_HXX_
#include "SAFplusAmfCommon.hxx"

#include <string>
#include "clTransaction.hxx"
#include "clMgtProv.hxx"
#include <vector>
#include "MgtFactory.hxx"
#include "clMgtContainer.hxx"

namespace SAFplusAmf
  {

    class Capacity : public SAFplus::MgtContainer {

        /* Apply MGT object factory */
        MGT_REGISTER(Capacity);

    public:
        SAFplus::MgtProv<std::string> resource;
        SAFplus::MgtProv<long int> value;

    public:
        Capacity();
        Capacity(std::string resourceValue);
        std::vector<std::string> getKeys();
        std::vector<std::string>* getChildNames();

        /*
         * XPATH: /SAFplusAmf/Node/capacity/resource
         */
        std::string getResource();

        /*
         * XPATH: /SAFplusAmf/Node/capacity/resource
         */
        void setResource(std::string resourceValue, SAFplus::Transaction &t=SAFplus::NO_TXN);

        /*
         * XPATH: /SAFplusAmf/Node/capacity/value
         */
        long int getValue();

        /*
         * XPATH: /SAFplusAmf/Node/capacity/value
         */
        void setValue(long int valueValue, SAFplus::Transaction &t=SAFplus::NO_TXN);
        ~Capacity();

    };
}
/* namespace SAFplusAmf */
#endif /* CAPACITY_HXX_ */
