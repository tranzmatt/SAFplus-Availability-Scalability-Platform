/* 
 * File Node.cxx
 * This file has been auto-generated by Y2CPP, the
 * plug-in of pyang.
 */ 
#include "SAFplusAmfCommon.hxx"

#include <vector>
#include "Capacity.hxx"
#include <string>
#include "clMgtProv.hxx"
#include "Capacity.hxx"
#include "clMgtList.hxx"
#include "ServiceUnitFailureEscalationPolicy.hxx"
#include "MgtFactory.hxx"
#include "AdministrativeState.hxx"
#include "clMgtProvList.hxx"
#include "ServiceUnitFailureEscalationPolicy.hxx"
#include "EntityId.hxx"
#include "ServiceUnit.hxx"
#include "Node.hxx"


namespace SAFplusAmf
  {

    /* Apply MGT object factory */
    MGT_REGISTER_IMPL(Node, /SAFplusAmf/Node)

    Node::Node(): adminState("adminState"), operState("operState"), autoRepair("autoRepair"), failFastOnInstantiationFailure("failFastOnInstantiationFailure"), failFastOnCleanupFailure("failFastOnCleanupFailure"), serviceUnits("serviceUnits"), capacityList("capacity")
    {
        this->addChildObject(&adminState, "adminState");
        this->addChildObject(&operState, "operState");
        this->addChildObject(&autoRepair, "autoRepair");
        this->addChildObject(&failFastOnInstantiationFailure, "failFastOnInstantiationFailure");
        this->addChildObject(&failFastOnCleanupFailure, "failFastOnCleanupFailure");
        this->addChildObject(&serviceUnits, "serviceUnits");
        this->addChildObject(&capacityList, "capacity");
        this->addKey("myName");
        this->name.assign("Node");
    };

    Node::Node(std::string myNameValue): adminState("adminState"), operState("operState"), autoRepair("autoRepair"), failFastOnInstantiationFailure("failFastOnInstantiationFailure"), failFastOnCleanupFailure("failFastOnCleanupFailure"), serviceUnits("serviceUnits"), capacityList("capacity")
    {
        this->myName.value =  myNameValue;
        this->addKey("myName");
        this->addChildObject(&adminState, "adminState");
        this->addChildObject(&operState, "operState");
        this->addChildObject(&autoRepair, "autoRepair");
        this->addChildObject(&failFastOnInstantiationFailure, "failFastOnInstantiationFailure");
        this->addChildObject(&failFastOnCleanupFailure, "failFastOnCleanupFailure");
        this->addChildObject(&serviceUnits, "serviceUnits");
        this->addChildObject(&capacityList, "capacity");
        this->name.assign("Node");
    };

    std::vector<std::string> Node::getKeys()
    {
        std::string keyNames[] = { "myName" };
        return std::vector<std::string> (keyNames, keyNames + sizeof(keyNames) / sizeof(keyNames[0]));
    };

    std::vector<std::string>* Node::getChildNames()
    {
        std::string childNames[] = { "myName", "id", "adminState", "operState", "capacity", "serviceUnitFailureEscalationPolicy", "autoRepair", "failFastOnInstantiationFailure", "failFastOnCleanupFailure", "serviceUnits" };
        return new std::vector<std::string> (childNames, childNames + sizeof(childNames) / sizeof(childNames[0]));
    };

    /*
     * XPATH: /SAFplusAmf/Node/adminState
     */
    SAFplusAmf::AdministrativeState Node::getAdminState()
    {
        return this->adminState.value;
    };

    /*
     * XPATH: /SAFplusAmf/Node/adminState
     */
    void Node::setAdminState(SAFplusAmf::AdministrativeState adminStateValue)
    {
        this->adminState.value = adminStateValue;
    };

    /*
     * XPATH: /SAFplusAmf/Node/operState
     */
    bool Node::getOperState()
    {
        return this->operState.value;
    };

    /*
     * XPATH: /SAFplusAmf/Node/operState
     */
    void Node::setOperState(bool operStateValue)
    {
        this->operState.value = operStateValue;
    };

    /*
     * XPATH: /SAFplusAmf/Node/autoRepair
     */
    bool Node::getAutoRepair()
    {
        return this->autoRepair.value;
    };

    /*
     * XPATH: /SAFplusAmf/Node/autoRepair
     */
    void Node::setAutoRepair(bool autoRepairValue)
    {
        this->autoRepair.value = autoRepairValue;
    };

    /*
     * XPATH: /SAFplusAmf/Node/failFastOnInstantiationFailure
     */
    bool Node::getFailFastOnInstantiationFailure()
    {
        return this->failFastOnInstantiationFailure.value;
    };

    /*
     * XPATH: /SAFplusAmf/Node/failFastOnInstantiationFailure
     */
    void Node::setFailFastOnInstantiationFailure(bool failFastOnInstantiationFailureValue)
    {
        this->failFastOnInstantiationFailure.value = failFastOnInstantiationFailureValue;
    };

    /*
     * XPATH: /SAFplusAmf/Node/failFastOnCleanupFailure
     */
    bool Node::getFailFastOnCleanupFailure()
    {
        return this->failFastOnCleanupFailure.value;
    };

    /*
     * XPATH: /SAFplusAmf/Node/failFastOnCleanupFailure
     */
    void Node::setFailFastOnCleanupFailure(bool failFastOnCleanupFailureValue)
    {
        this->failFastOnCleanupFailure.value = failFastOnCleanupFailureValue;
    };

    /*
     * XPATH: /SAFplusAmf/Node/serviceUnits
     */
    std::vector<SAFplusAmf::ServiceUnit*> Node::getServiceUnits()
    {
        return this->serviceUnits.value;
    };

    /*
     * XPATH: /SAFplusAmf/Node/serviceUnits
     */
    void Node::setServiceUnits(SAFplusAmf::ServiceUnit* serviceUnitsValue)
    {
        this->serviceUnits.value.push_back(serviceUnitsValue);
    };

    /*
     * XPATH: /SAFplusAmf/Node/capacity
     */
    SAFplusAmf::Capacity* Node::getCapacity(std::string resourceValue)
    {
        for (unsigned int i = 0; i < this->capacityList.getEntrySize(); i++)
        {
            Capacity* childObject = (Capacity*)this->capacityList.getEntry(i);
            if (childObject->getResource() == resourceValue)
            {
                return childObject;
            }
        }
        return NULL;
    };

    /*
     * XPATH: /SAFplusAmf/Node/capacity
     */
    void Node::addCapacity(SAFplusAmf::Capacity *capacityValue)
    {
        this->capacityList.addChildObject(capacityValue);
    };

    /*
     * XPATH: /SAFplusAmf/Node/serviceUnitFailureEscalationPolicy
     */
    SAFplusAmf::ServiceUnitFailureEscalationPolicy* Node::getServiceUnitFailureEscalationPolicy()
    {
        return (ServiceUnitFailureEscalationPolicy*)this->getChildObject("serviceUnitFailureEscalationPolicy");
    };

    /*
     * XPATH: /SAFplusAmf/Node/serviceUnitFailureEscalationPolicy
     */
    void Node::addServiceUnitFailureEscalationPolicy(SAFplusAmf::ServiceUnitFailureEscalationPolicy *serviceUnitFailureEscalationPolicyValue)
    {
        this->addChildObject(serviceUnitFailureEscalationPolicyValue, "serviceUnitFailureEscalationPolicy");
    };

    Node::~Node()
    {
    };

}
/* namespace SAFplusAmf */