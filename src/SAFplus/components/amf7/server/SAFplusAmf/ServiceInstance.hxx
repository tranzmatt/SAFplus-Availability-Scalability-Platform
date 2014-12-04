/* 
 * File ServiceInstance.hxx
 * This file has been auto-generated by Y2CPP, the
 * plug-in of pyang.
 */ 

#pragma once
#ifndef SERVICEINSTANCE_HXX_
#define SERVICEINSTANCE_HXX_
#include "SAFplusAmfCommon.hxx"

#include "AssignmentState.hxx"
#include "clMgtIdentifier.hxx"
#include "clTransaction.hxx"
#include "StandbyAssignments.hxx"
#include "ComponentServiceInstance.hxx"
#include "ServiceGroup.hxx"
#include "clMgtList.hxx"
#include "MgtFactory.hxx"
#include "ActiveAssignments.hxx"
#include "AdministrativeState.hxx"
#include <string>
#include "clMgtProv.hxx"
#include "StandbyAssignments.hxx"
#include "clMgtIdentifierList.hxx"
#include <vector>
#include "ActiveAssignments.hxx"
#include "EntityId.hxx"

namespace SAFplusAmf
  {

    class ServiceInstance : public EntityId {

        /* Apply MGT object factory */
        MGT_REGISTER(ServiceInstance);

    public:

        /*
         * Does the operator want this entity to be off, idle, or in service?
         */
        SAFplus::MgtProv<SAFplusAmf::AdministrativeState> adminState;

        /*
         * The assignment state of a service instance indicates whether the service represented by this service instance is being provided or not by some service unit.
         */
        SAFplus::MgtProv<SAFplusAmf::AssignmentState> assignmentState;

        /*
         * What is the optimal number of Service Units that should be given an active assignment for this work?
         */
        SAFplus::MgtProv<unsigned int> preferredActiveAssignments;

        /*
         * What is the optimal number of Service Units that should be given a standby assignment for this work?
         */
        SAFplus::MgtProv<unsigned int> preferredStandbyAssignments;

        /*
         * Lower rank is instantiated before higher; but rank 0 means 'don't care'.
         */
        SAFplus::MgtProv<unsigned int> rank;

        /*
         * Component Service Instances in this Service group
         */
        SAFplus::MgtIdentifierList<SAFplusAmf::ComponentServiceInstance*> componentServiceInstances;
        SAFplus::MgtIdentifier<SAFplusAmf::ServiceGroup*> serviceGroup;

        /*
         * An abstract definition of the amount of work this node can handle.  Nodes can be assigned capacities for arbitrarily chosen strings (MEM or CPU, for example).  Service Instances can be assigned 'weights' and the sum of the weights of service instances assigned active or standby on this node cannot exceed these values.
         */
        SAFplus::MgtList<std::string> activeWeightList;

        /*
         * An abstract definition of the amount of work this node can handle.  Nodes can be assigned capacities for arbitrarily chosen strings (MEM or CPU, for example).  Service Instances can be assigned 'weights' and the sum of the weights of service instances assigned active or standby on this node cannot exceed these values.
         */
        SAFplus::MgtList<std::string> standbyWeightList;

    public:
        ServiceInstance();
        ServiceInstance(std::string nameValue);
        std::vector<std::string> getKeys();
        std::vector<std::string>* getChildNames();

        /*
         * XPATH: /SAFplusAmf/ServiceInstance/adminState
         */
        SAFplusAmf::AdministrativeState getAdminState();

        /*
         * XPATH: /SAFplusAmf/ServiceInstance/adminState
         */
        void setAdminState(SAFplusAmf::AdministrativeState adminStateValue, SAFplus::Transaction &t=SAFplus::NO_TXN);

        /*
         * XPATH: /SAFplusAmf/ServiceInstance/assignmentState
         */
        SAFplusAmf::AssignmentState getAssignmentState();

        /*
         * XPATH: /SAFplusAmf/ServiceInstance/assignmentState
         */
        void setAssignmentState(SAFplusAmf::AssignmentState assignmentStateValue, SAFplus::Transaction &t=SAFplus::NO_TXN);

        /*
         * XPATH: /SAFplusAmf/ServiceInstance/preferredActiveAssignments
         */
        unsigned int getPreferredActiveAssignments();

        /*
         * XPATH: /SAFplusAmf/ServiceInstance/preferredActiveAssignments
         */
        void setPreferredActiveAssignments(unsigned int preferredActiveAssignmentsValue, SAFplus::Transaction &t=SAFplus::NO_TXN);

        /*
         * XPATH: /SAFplusAmf/ServiceInstance/preferredStandbyAssignments
         */
        unsigned int getPreferredStandbyAssignments();

        /*
         * XPATH: /SAFplusAmf/ServiceInstance/preferredStandbyAssignments
         */
        void setPreferredStandbyAssignments(unsigned int preferredStandbyAssignmentsValue, SAFplus::Transaction &t=SAFplus::NO_TXN);

        /*
         * XPATH: /SAFplusAmf/ServiceInstance/rank
         */
        unsigned int getRank();

        /*
         * XPATH: /SAFplusAmf/ServiceInstance/rank
         */
        void setRank(unsigned int rankValue, SAFplus::Transaction &t=SAFplus::NO_TXN);

        /*
         * XPATH: /SAFplusAmf/ServiceInstance/componentServiceInstances
         */
        std::vector<SAFplusAmf::ComponentServiceInstance*> getComponentServiceInstances();

        /*
         * XPATH: /SAFplusAmf/ServiceInstance/componentServiceInstances
         */
        void setComponentServiceInstances(SAFplusAmf::ComponentServiceInstance* componentServiceInstancesValue);

        /*
         * XPATH: /SAFplusAmf/ServiceInstance/serviceGroup
         */
        SAFplusAmf::ServiceGroup* getServiceGroup();

        /*
         * XPATH: /SAFplusAmf/ServiceInstance/serviceGroup
         */
        void setServiceGroup(SAFplusAmf::ServiceGroup* serviceGroupValue, SAFplus::Transaction &t=SAFplus::NO_TXN);

        /*
         * XPATH: /SAFplusAmf/ServiceInstance/activeAssignments
         */
        SAFplusAmf::ActiveAssignments* getActiveAssignments();

        /*
         * XPATH: /SAFplusAmf/ServiceInstance/activeAssignments
         */
        void addActiveAssignments(SAFplusAmf::ActiveAssignments *activeAssignmentsValue);

        /*
         * XPATH: /SAFplusAmf/ServiceInstance/standbyAssignments
         */
        SAFplusAmf::StandbyAssignments* getStandbyAssignments();

        /*
         * XPATH: /SAFplusAmf/ServiceInstance/standbyAssignments
         */
        void addStandbyAssignments(SAFplusAmf::StandbyAssignments *standbyAssignmentsValue);
        ~ServiceInstance();

    };
}
/* namespace SAFplusAmf */
#endif /* SERVICEINSTANCE_HXX_ */
