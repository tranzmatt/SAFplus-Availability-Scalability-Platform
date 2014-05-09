/* 
 * File ServiceInstance.cxx
 * This file has been auto-generated by Y2CPP, the
 * plug-in of pyang.
 */ 
#include "SAFplusAmfCommon.hxx"

#include "AssignmentState.hxx"
#include <string>
#include "StandbyWeight.hxx"
#include "StandbyAssignments.hxx"
#include "ComponentServiceInstance.hxx"
#include "clMgtList.hxx"
#include "MgtFactory.hxx"
#include "ActiveAssignments.hxx"
#include "ActiveWeight.hxx"
#include "AdministrativeState.hxx"
#include "StandbyWeight.hxx"
#include "ActiveWeight.hxx"
#include "clMgtProv.hxx"
#include "StandbyAssignments.hxx"
#include "ServiceGroup.hxx"
#include <vector>
#include "ActiveAssignments.hxx"
#include "EntityId.hxx"
#include "clMgtProvList.hxx"
#include "ServiceInstance.hxx"


namespace SAFplusAmf
  {

    /* Apply MGT object factory */
    MGT_REGISTER_IMPL(ServiceInstance, /SAFplusAmf/ServiceInstance)

    ServiceInstance::ServiceInstance(): adminState("adminState"), assignmentState("assignmentState"), rank("rank"), componentServiceInstances("componentServiceInstances"), serviceGroup("serviceGroup"), activeWeightList("activeWeight"), standbyWeightList("standbyWeight")
    {
        this->addChildObject(&adminState, "adminState");
        this->addChildObject(&assignmentState, "assignmentState");
        this->addChildObject(&rank, "rank");
        this->addChildObject(&componentServiceInstances, "componentServiceInstances");
        this->addChildObject(&serviceGroup, "serviceGroup");
        this->addChildObject(&activeWeightList, "activeWeight");
        this->addChildObject(&standbyWeightList, "standbyWeight");
        this->addKey("myName");
        this->name.assign("ServiceInstance");
    };

    ServiceInstance::ServiceInstance(std::string myNameValue): adminState("adminState"), assignmentState("assignmentState"), rank("rank"), componentServiceInstances("componentServiceInstances"), serviceGroup("serviceGroup"), activeWeightList("activeWeight"), standbyWeightList("standbyWeight")
    {
        this->myName.value =  myNameValue;
        this->addKey("myName");
        this->addChildObject(&adminState, "adminState");
        this->addChildObject(&assignmentState, "assignmentState");
        this->addChildObject(&rank, "rank");
        this->addChildObject(&componentServiceInstances, "componentServiceInstances");
        this->addChildObject(&serviceGroup, "serviceGroup");
        this->addChildObject(&activeWeightList, "activeWeight");
        this->addChildObject(&standbyWeightList, "standbyWeight");
        this->name.assign("ServiceInstance");
    };

    std::vector<std::string> ServiceInstance::getKeys()
    {
        std::string keyNames[] = { "myName" };
        return std::vector<std::string> (keyNames, keyNames + sizeof(keyNames) / sizeof(keyNames[0]));
    };

    std::vector<std::string>* ServiceInstance::getChildNames()
    {
        std::string childNames[] = { "myName", "id", "adminState", "assignmentState", "rank", "activeWeight", "standbyWeight", "activeAssignments", "standbyAssignments", "componentServiceInstances", "serviceGroup" };
        return new std::vector<std::string> (childNames, childNames + sizeof(childNames) / sizeof(childNames[0]));
    };

    /*
     * XPATH: /SAFplusAmf/ServiceInstance/adminState
     */
    SAFplusAmf::AdministrativeState ServiceInstance::getAdminState()
    {
        return this->adminState.value;
    };

    /*
     * XPATH: /SAFplusAmf/ServiceInstance/adminState
     */
    void ServiceInstance::setAdminState(SAFplusAmf::AdministrativeState adminStateValue)
    {
        this->adminState.value = adminStateValue;
    };

    /*
     * XPATH: /SAFplusAmf/ServiceInstance/assignmentState
     */
    SAFplusAmf::AssignmentState ServiceInstance::getAssignmentState()
    {
        return this->assignmentState.value;
    };

    /*
     * XPATH: /SAFplusAmf/ServiceInstance/assignmentState
     */
    void ServiceInstance::setAssignmentState(SAFplusAmf::AssignmentState assignmentStateValue)
    {
        this->assignmentState.value = assignmentStateValue;
    };

    /*
     * XPATH: /SAFplusAmf/ServiceInstance/rank
     */
    unsigned int ServiceInstance::getRank()
    {
        return this->rank.value;
    };

    /*
     * XPATH: /SAFplusAmf/ServiceInstance/rank
     */
    void ServiceInstance::setRank(unsigned int rankValue)
    {
        this->rank.value = rankValue;
    };

    /*
     * XPATH: /SAFplusAmf/ServiceInstance/componentServiceInstances
     */
    std::vector<SAFplusAmf::ComponentServiceInstance*> ServiceInstance::getComponentServiceInstances()
    {
        return this->componentServiceInstances.value;
    };

    /*
     * XPATH: /SAFplusAmf/ServiceInstance/componentServiceInstances
     */
    void ServiceInstance::setComponentServiceInstances(SAFplusAmf::ComponentServiceInstance* componentServiceInstancesValue)
    {
        this->componentServiceInstances.value.push_back(componentServiceInstancesValue);
    };

    /*
     * XPATH: /SAFplusAmf/ServiceInstance/serviceGroup
     */
    SAFplusAmf::ServiceGroup* ServiceInstance::getServiceGroup()
    {
        return this->serviceGroup.value;
    };

    /*
     * XPATH: /SAFplusAmf/ServiceInstance/serviceGroup
     */
    void ServiceInstance::setServiceGroup(SAFplusAmf::ServiceGroup* serviceGroupValue)
    {
        this->serviceGroup.value = serviceGroupValue;
    };

    /*
     * XPATH: /SAFplusAmf/ServiceInstance/activeWeight
     */
    SAFplusAmf::ActiveWeight* ServiceInstance::getActiveWeight(std::string resourceValue)
    {
        for (unsigned int i = 0; i < this->activeWeightList.getEntrySize(); i++)
        {
            ActiveWeight* childObject = (ActiveWeight*)this->activeWeightList.getEntry(i);
            if (childObject->getResource() == resourceValue)
            {
                return childObject;
            }
        }
        return NULL;
    };

    /*
     * XPATH: /SAFplusAmf/ServiceInstance/activeWeight
     */
    void ServiceInstance::addActiveWeight(SAFplusAmf::ActiveWeight *activeWeightValue)
    {
        this->activeWeightList.addChildObject(activeWeightValue);
    };

    /*
     * XPATH: /SAFplusAmf/ServiceInstance/standbyWeight
     */
    SAFplusAmf::StandbyWeight* ServiceInstance::getStandbyWeight(std::string resourceValue)
    {
        for (unsigned int i = 0; i < this->standbyWeightList.getEntrySize(); i++)
        {
            StandbyWeight* childObject = (StandbyWeight*)this->standbyWeightList.getEntry(i);
            if (childObject->getResource() == resourceValue)
            {
                return childObject;
            }
        }
        return NULL;
    };

    /*
     * XPATH: /SAFplusAmf/ServiceInstance/standbyWeight
     */
    void ServiceInstance::addStandbyWeight(SAFplusAmf::StandbyWeight *standbyWeightValue)
    {
        this->standbyWeightList.addChildObject(standbyWeightValue);
    };

    /*
     * XPATH: /SAFplusAmf/ServiceInstance/activeAssignments
     */
    SAFplusAmf::ActiveAssignments* ServiceInstance::getActiveAssignments()
    {
        return (ActiveAssignments*)this->getChildObject("activeAssignments");
    };

    /*
     * XPATH: /SAFplusAmf/ServiceInstance/activeAssignments
     */
    void ServiceInstance::addActiveAssignments(SAFplusAmf::ActiveAssignments *activeAssignmentsValue)
    {
        this->addChildObject(activeAssignmentsValue, "activeAssignments");
    };

    /*
     * XPATH: /SAFplusAmf/ServiceInstance/standbyAssignments
     */
    SAFplusAmf::StandbyAssignments* ServiceInstance::getStandbyAssignments()
    {
        return (StandbyAssignments*)this->getChildObject("standbyAssignments");
    };

    /*
     * XPATH: /SAFplusAmf/ServiceInstance/standbyAssignments
     */
    void ServiceInstance::addStandbyAssignments(SAFplusAmf::StandbyAssignments *standbyAssignmentsValue)
    {
        this->addChildObject(standbyAssignmentsValue, "standbyAssignments");
    };

    ServiceInstance::~ServiceInstance()
    {
    };

}
/* namespace SAFplusAmf */