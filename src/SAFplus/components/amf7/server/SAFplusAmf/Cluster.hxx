/* 
 * File Cluster.hxx
 * This file has been auto-generated by Y2CPP, the
 * plug-in of pyang.
 */ 

#pragma once
#ifndef CLUSTER_HXX_
#define CLUSTER_HXX_
#include "SAFplusAmfCommon.hxx"

#include <string>
#include "clMgtProv.hxx"
#include <vector>
#include "MgtFactory.hxx"
#include "AdministrativeState.hxx"
#include "EntityId.hxx"

namespace SAFplusAmf
  {

    class Cluster : public EntityId {

        /* Apply MGT object factory */
        MGT_REGISTER(Cluster);

    public:

        /*
         * Does the operator want this entity to be off, idle, or in service?
         */
        SAFplus::MgtProv<SAFplusAmf::AdministrativeState> adminState;

        /*
         * When the cluster is first started, no work will be assigned until either ALL configured service units are instantiated or this time duration elapses.  By giving every node a chance to come up fully, this ensures that initial work assignments are as close as possible to preferred work assignments.
         */
        SAFplus::MgtProv<SaTimeT> startupAssignmentDelay;

    public:
        Cluster();
        Cluster(std::string myNameValue);
        void toString(std::stringstream &xmlString);
        std::vector<std::string> getKeys();
        std::vector<std::string>* getChildNames();

        /*
         * XPATH: /SAFplusAmf/Cluster/adminState
         */
        SAFplusAmf::AdministrativeState getAdminState();

        /*
         * XPATH: /SAFplusAmf/Cluster/adminState
         */
        void setAdminState(SAFplusAmf::AdministrativeState adminStateValue);

        /*
         * XPATH: /SAFplusAmf/Cluster/startupAssignmentDelay
         */
        SaTimeT getStartupAssignmentDelay();

        /*
         * XPATH: /SAFplusAmf/Cluster/startupAssignmentDelay
         */
        void setStartupAssignmentDelay(SaTimeT startupAssignmentDelayValue);
        ~Cluster();

    };
}
/* namespace SAFplusAmf */
#endif /* CLUSTER_HXX_ */
