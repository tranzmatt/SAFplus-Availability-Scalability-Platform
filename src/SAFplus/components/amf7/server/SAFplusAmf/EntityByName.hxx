/* 
 * File EntityByName.hxx
 * This file has been auto-generated by Y2CPP, the
 * plug-in of pyang.
 */ 

#pragma once
#ifndef ENTITYBYNAME_HXX_
#define ENTITYBYNAME_HXX_
#include "SAFplusAmfCommon.hxx"

#include <string>
#include "clTransaction.hxx"
#include "clMgtProv.hxx"
#include <vector>
#include "MgtFactory.hxx"
#include "clMgtContainer.hxx"

namespace SAFplusAmf
  {

    class EntityByName : public SAFplus::MgtContainer {

        /* Apply MGT object factory */
        MGT_REGISTER(EntityByName);

    public:
        SAFplus::MgtProv<std::string> myName;
        SAFplus::MgtProv<std::string> entity;

    public:
        EntityByName();
        EntityByName(std::string myNameValue);
        std::vector<std::string> getKeys();
        std::vector<std::string>* getChildNames();

        /*
         * XPATH: /SAFplusAmf/EntityByName/myName
         */
        std::string getMyName();

        /*
         * XPATH: /SAFplusAmf/EntityByName/myName
         */
        void setMyName(std::string myNameValue, SAFplus::Transaction &t=SAFplus::NO_TXN);

        /*
         * XPATH: /SAFplusAmf/EntityByName/entity
         */
        std::string getEntity();

        /*
         * XPATH: /SAFplusAmf/EntityByName/entity
         */
        void setEntity(std::string entityValue, SAFplus::Transaction &t=SAFplus::NO_TXN);
        ~EntityByName();

    };
}
/* namespace SAFplusAmf */
#endif /* ENTITYBYNAME_HXX_ */
