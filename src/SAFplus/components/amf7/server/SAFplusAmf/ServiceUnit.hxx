/* 
 * File ServiceUnit.hxx
 * This file has been auto-generated by Y2CPP, the
 * plug-in of pyang.
 */ 

#pragma once
#ifndef SERVICEUNIT_HXX_
#define SERVICEUNIT_HXX_
#include "SAFplusAmfCommon.hxx"

#include "RestartCount.hxx"
#include "Node.hxx"
#include <string>
#include "clTransaction.hxx"
#include "NumActiveServiceInstances.hxx"
#include "RestartCount.hxx"
#include "Component.hxx"
#include "MgtFactory.hxx"
#include "AdministrativeState.hxx"
#include "NumStandbyServiceInstances.hxx"
#include "clMgtIdentifier.hxx"
#include "ReadinessState.hxx"
#include "NumActiveServiceInstances.hxx"
#include "clMgtProv.hxx"
#include "ServiceInstance.hxx"
#include "HighAvailabilityReadinessState.hxx"
#include "ServiceGroup.hxx"
#include <vector>
#include "clMgtIdentifierList.hxx"
#include "PresenceState.hxx"
#include "EntityId.hxx"
#include "NumStandbyServiceInstances.hxx"
#include "HighAvailabilityState.hxx"

namespace SAFplusAmf
  {

    class ServiceUnit : public EntityId {

        /* Apply MGT object factory */
        MGT_REGISTER(ServiceUnit);

    public:

        /*
         * Does the operator want this entity to be off, idle, or in service?
         */
        SAFplus::MgtProv<SAFplusAmf::AdministrativeState> adminState;

        /*
         * Lower rank is instantiated before higher; but rank 0 means 'don't care'.
         */
        SAFplus::MgtProv<unsigned int> rank;

        /*
         * TODO
         */
        SAFplus::MgtProv<bool> failover;

        /*
         * Can this service unit be instantiated before being assigned active?  True if ALL components are preinstantiable.
         */
        SAFplus::MgtProv<bool> preinstantiable;

        /*
         * The service unit can only be instantiated on the node (if a node is specified) or on one of the nodes of the node group (if a node group is configured).
         */
        SAFplus::MgtProv<std::string> saAmfSUHostNodeOrNodeGroup;
        SAFplus::MgtProv<SAFplusAmf::PresenceState> presenceState;
        SAFplus::MgtProv<SAFplusAmf::ReadinessState> readinessState;

        /*
         * This state field covers ALL work assignments...
         */
        SAFplus::MgtProv<SAFplusAmf::HighAvailabilityReadinessState> haReadinessState;
        SAFplus::MgtProv<SAFplusAmf::HighAvailabilityState> haState;

        /*
         * True is enabled, False is disabled.  To move from False to True a 'repair' action must occur.
         */
        SAFplus::MgtProv<bool> operState;
        SAFplus::MgtIdentifierList<SAFplusAmf::ServiceInstance*> assignedServiceInstances;
        SAFplus::MgtIdentifierList<SAFplusAmf::Component*> components;
        SAFplus::MgtIdentifier<SAFplusAmf::Node*> node;
        SAFplus::MgtIdentifier<SAFplusAmf::ServiceGroup*> serviceGroup;

        /*
         * Once this Service Unit is instantiated, how long should I wait before assigning it?
         */
        SAFplus::MgtProv<unsigned int> probationTime;

    public:
        ServiceUnit();
        ServiceUnit(std::string nameValue);
        std::vector<std::string> getKeys();
        std::vector<std::string>* getChildNames();

        /*
         * XPATH: /SAFplusAmf/ServiceUnit/adminState
         */
        SAFplusAmf::AdministrativeState getAdminState();

        /*
         * XPATH: /SAFplusAmf/ServiceUnit/adminState
         */
        void setAdminState(SAFplusAmf::AdministrativeState adminStateValue, SAFplus::Transaction &t=SAFplus::NO_TXN);

        /*
         * XPATH: /SAFplusAmf/ServiceUnit/rank
         */
        unsigned int getRank();

        /*
         * XPATH: /SAFplusAmf/ServiceUnit/rank
         */
        void setRank(unsigned int rankValue, SAFplus::Transaction &t=SAFplus::NO_TXN);

        /*
         * XPATH: /SAFplusAmf/ServiceUnit/failover
         */
        bool getFailover();

        /*
         * XPATH: /SAFplusAmf/ServiceUnit/failover
         */
        void setFailover(bool failoverValue, SAFplus::Transaction &t=SAFplus::NO_TXN);

        /*
         * XPATH: /SAFplusAmf/ServiceUnit/preinstantiable
         */
        bool getPreinstantiable();

        /*
         * XPATH: /SAFplusAmf/ServiceUnit/preinstantiable
         */
        void setPreinstantiable(bool preinstantiableValue, SAFplus::Transaction &t=SAFplus::NO_TXN);

        /*
         * XPATH: /SAFplusAmf/ServiceUnit/saAmfSUHostNodeOrNodeGroup
         */
        std::string getSaAmfSUHostNodeOrNodeGroup();

        /*
         * XPATH: /SAFplusAmf/ServiceUnit/saAmfSUHostNodeOrNodeGroup
         */
        void setSaAmfSUHostNodeOrNodeGroup(std::string saAmfSUHostNodeOrNodeGroupValue, SAFplus::Transaction &t=SAFplus::NO_TXN);

        /*
         * XPATH: /SAFplusAmf/ServiceUnit/presenceState
         */
        SAFplusAmf::PresenceState getPresenceState();

        /*
         * XPATH: /SAFplusAmf/ServiceUnit/presenceState
         */
        void setPresenceState(SAFplusAmf::PresenceState presenceStateValue, SAFplus::Transaction &t=SAFplus::NO_TXN);

        /*
         * XPATH: /SAFplusAmf/ServiceUnit/readinessState
         */
        SAFplusAmf::ReadinessState getReadinessState();

        /*
         * XPATH: /SAFplusAmf/ServiceUnit/readinessState
         */
        void setReadinessState(SAFplusAmf::ReadinessState readinessStateValue, SAFplus::Transaction &t=SAFplus::NO_TXN);

        /*
         * XPATH: /SAFplusAmf/ServiceUnit/haReadinessState
         */
        SAFplusAmf::HighAvailabilityReadinessState getHaReadinessState();

        /*
         * XPATH: /SAFplusAmf/ServiceUnit/haReadinessState
         */
        void setHaReadinessState(SAFplusAmf::HighAvailabilityReadinessState haReadinessStateValue, SAFplus::Transaction &t=SAFplus::NO_TXN);

        /*
         * XPATH: /SAFplusAmf/ServiceUnit/haState
         */
        SAFplusAmf::HighAvailabilityState getHaState();

        /*
         * XPATH: /SAFplusAmf/ServiceUnit/haState
         */
        void setHaState(SAFplusAmf::HighAvailabilityState haStateValue, SAFplus::Transaction &t=SAFplus::NO_TXN);

        /*
         * XPATH: /SAFplusAmf/ServiceUnit/operState
         */
        bool getOperState();

        /*
         * XPATH: /SAFplusAmf/ServiceUnit/operState
         */
        void setOperState(bool operStateValue, SAFplus::Transaction &t=SAFplus::NO_TXN);

        /*
         * XPATH: /SAFplusAmf/ServiceUnit/assignedServiceInstances
         */
        std::vector<SAFplusAmf::ServiceInstance*> getAssignedServiceInstances();

        /*
         * XPATH: /SAFplusAmf/ServiceUnit/assignedServiceInstances
         */
        void setAssignedServiceInstances(SAFplusAmf::ServiceInstance* assignedServiceInstancesValue);

        /*
         * XPATH: /SAFplusAmf/ServiceUnit/components
         */
        std::vector<SAFplusAmf::Component*> getComponents();

        /*
         * XPATH: /SAFplusAmf/ServiceUnit/components
         */
        void setComponents(SAFplusAmf::Component* componentsValue);

        /*
         * XPATH: /SAFplusAmf/ServiceUnit/node
         */
        SAFplusAmf::Node* getNode();

        /*
         * XPATH: /SAFplusAmf/ServiceUnit/node
         */
        void setNode(SAFplusAmf::Node* nodeValue, SAFplus::Transaction &t=SAFplus::NO_TXN);

        /*
         * XPATH: /SAFplusAmf/ServiceUnit/serviceGroup
         */
        SAFplusAmf::ServiceGroup* getServiceGroup();

        /*
         * XPATH: /SAFplusAmf/ServiceUnit/serviceGroup
         */
        void setServiceGroup(SAFplusAmf::ServiceGroup* serviceGroupValue, SAFplus::Transaction &t=SAFplus::NO_TXN);

        /*
         * XPATH: /SAFplusAmf/ServiceUnit/probationTime
         */
        unsigned int getProbationTime();

        /*
         * XPATH: /SAFplusAmf/ServiceUnit/probationTime
         */
        void setProbationTime(unsigned int probationTimeValue, SAFplus::Transaction &t=SAFplus::NO_TXN);

        /*
         * XPATH: /SAFplusAmf/ServiceUnit/numActiveServiceInstances
         */
        SAFplusAmf::NumActiveServiceInstances* getNumActiveServiceInstances();

        /*
         * XPATH: /SAFplusAmf/ServiceUnit/numActiveServiceInstances
         */
        void addNumActiveServiceInstances(SAFplusAmf::NumActiveServiceInstances *numActiveServiceInstancesValue);

        /*
         * XPATH: /SAFplusAmf/ServiceUnit/numStandbyServiceInstances
         */
        SAFplusAmf::NumStandbyServiceInstances* getNumStandbyServiceInstances();

        /*
         * XPATH: /SAFplusAmf/ServiceUnit/numStandbyServiceInstances
         */
        void addNumStandbyServiceInstances(SAFplusAmf::NumStandbyServiceInstances *numStandbyServiceInstancesValue);

        /*
         * XPATH: /SAFplusAmf/ServiceUnit/restartCount
         */
        SAFplusAmf::RestartCount* getRestartCount();

        /*
         * XPATH: /SAFplusAmf/ServiceUnit/restartCount
         */
        void addRestartCount(SAFplusAmf::RestartCount *restartCountValue);
        ~ServiceUnit();

    };
}
/* namespace SAFplusAmf */
#endif /* SERVICEUNIT_HXX_ */
