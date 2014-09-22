/* 
 * File Application.hxx
 * This file has been auto-generated by Y2CPP, the
 * plug-in of pyang.
 */ 

#pragma once
#ifndef APPLICATION_HXX_
#define APPLICATION_HXX_
#include "SAFplusAmfCommon.hxx"

#include "NumServiceGroups.hxx"
#include <string>
#include "clTransaction.hxx"
#include "clMgtProv.hxx"
#include "ServiceGroup.hxx"
#include <vector>
#include "MgtFactory.hxx"
#include "NumServiceGroups.hxx"
#include "AdministrativeState.hxx"
#include "EntityId.hxx"
#include "clMgtProvList.hxx"

namespace SAFplusAmf
  {

    class Application : public EntityId {

        /* Apply MGT object factory */
        MGT_REGISTER(Application);

    public:

        /*
         * Does the operator want this entity to be off, idle, or in service?
         */
        SAFplus::MgtProv<SAFplusAmf::AdministrativeState> adminState;

        /*
         * Service Groups in this Application
         */
        SAFplus::MgtProvList<SAFplusAmf::ServiceGroup*> serviceGroups;

        /*
         * SAFplus Extension: To the greatest extent possible, all Service Groups in this application will be Active (or standby) on the same node.  This will only be not true if service groups are not configured to run on the same nodes.
         */
        SAFplus::MgtProv<bool> keepTogether;

    public:
        Application();
        Application(std::string myNameValue);
        void toString(std::stringstream &xmlString);
        std::vector<std::string> getKeys();
        std::vector<std::string>* getChildNames();

        /*
         * XPATH: /SAFplusAmf/Application/adminState
         */
        SAFplusAmf::AdministrativeState getAdminState();

        /*
         * XPATH: /SAFplusAmf/Application/adminState
         */
        void setAdminState(SAFplusAmf::AdministrativeState adminStateValue, SAFplus::Transaction &t=SAFplus::NO_TXN);

        /*
         * XPATH: /SAFplusAmf/Application/serviceGroups
         */
        std::vector<SAFplusAmf::ServiceGroup*> getServiceGroups();

        /*
         * XPATH: /SAFplusAmf/Application/serviceGroups
         */
        void setServiceGroups(SAFplusAmf::ServiceGroup* serviceGroupsValue);

        /*
         * XPATH: /SAFplusAmf/Application/keepTogether
         */
        bool getKeepTogether();

        /*
         * XPATH: /SAFplusAmf/Application/keepTogether
         */
        void setKeepTogether(bool keepTogetherValue, SAFplus::Transaction &t=SAFplus::NO_TXN);

        /*
         * XPATH: /SAFplusAmf/Application/numServiceGroups
         */
        SAFplusAmf::NumServiceGroups* getNumServiceGroups();

        /*
         * XPATH: /SAFplusAmf/Application/numServiceGroups
         */
        void addNumServiceGroups(SAFplusAmf::NumServiceGroups *numServiceGroupsValue);
        ~Application();

    };
}
/* namespace SAFplusAmf */
#endif /* APPLICATION_HXX_ */
