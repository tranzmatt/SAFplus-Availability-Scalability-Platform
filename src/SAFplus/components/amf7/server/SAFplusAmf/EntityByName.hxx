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
#include "clMgtProv.hxx"
#include "clMgtList.hxx"
#include <vector>
#include "MgtFactory.hxx"

namespace SAFplusAmf
  {

    class EntityByName : public SAFplus::MgtList {

        /* Apply MGT object factory */
        MGT_REGISTER(EntityByName);

    public:
        SAFplus::MgtProv<std::string> myName;
        SAFplus::MgtProv<std::string> entity;

    public:
        EntityByName();
        void toString(std::stringstream &xmlString);
        std::vector<std::string>* getChildNames();

        /*
         * XPATH: /SAFplusAmf/EntityByName/myName
         */
        std::string getMyName();

        /*
         * XPATH: /SAFplusAmf/EntityByName/myName
         */
        void setMyName(std::string myNameValue);

        /*
         * XPATH: /SAFplusAmf/EntityByName/entity
         */
        std::string getEntity();

        /*
         * XPATH: /SAFplusAmf/EntityByName/entity
         */
        void setEntity(std::string entityValue);
        ~EntityByName();

    };
}
/* namespace SAFplusAmf */
#endif /* ENTITYBYNAME_HXX_ */
