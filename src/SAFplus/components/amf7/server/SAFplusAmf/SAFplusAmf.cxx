/* 
 * File SAFplusAmf.cxx
 * This file has been auto-generated by Y2CPP, the
 * plug-in of pyang.
 */ 
#include "SAFplusAmfCommon.hxx"

#include "clMgtList.hxx"
#include <vector>
#include "MgtFactory.hxx"
#include "clMgtContainer.hxx"
#include "clTransaction.hxx"
#include "clMgtProv.hxx"
#include "SAFplusAmf.hxx"


namespace SAFplusAmf
  {

    /* Apply MGT object factory */
    MGT_REGISTER_IMPL(SAFplusAmfRoot, /SAFplusAmf)

    SAFplusAmfRoot::SAFplusAmfRoot(): SAFplus::MgtContainer("SAFplusAmf"), healthCheckPeriod("healthCheckPeriod"), healthCheckMaxSilence("healthCheckMaxSilence"), clusterList("Cluster"), nodeList("Node"), serviceGroupList("ServiceGroup"), componentList("Component"), componentServiceInstanceList("ComponentServiceInstance"), serviceInstanceList("ServiceInstance"), serviceUnitList("ServiceUnit"), applicationList("Application"), entityByNameList("EntityByName"), entityByIdList("EntityById")
    {
        this->addChildObject(&healthCheckPeriod, "healthCheckPeriod");
        this->addChildObject(&healthCheckMaxSilence, "healthCheckMaxSilence");
        this->addChildObject(&clusterList, "Cluster");
        this->addChildObject(&nodeList, "Node");
        this->addChildObject(&serviceGroupList, "ServiceGroup");
        this->addChildObject(&componentList, "Component");
        this->addChildObject(&componentServiceInstanceList, "ComponentServiceInstance");
        this->addChildObject(&serviceInstanceList, "ServiceInstance");
        this->addChildObject(&serviceUnitList, "ServiceUnit");
        this->addChildObject(&applicationList, "Application");
        this->addChildObject(&entityByNameList, "EntityByName");
        this->addChildObject(&entityByIdList, "EntityById");
    };

    void SAFplusAmfRoot::toString(std::stringstream &xmlString)
    {
        /* TODO:  */
    };

    std::vector<std::string>* SAFplusAmfRoot::getChildNames()
    {
        std::string childNames[] = { "Cluster", "Node", "ServiceGroup", "Component", "ComponentServiceInstance", "ServiceInstance", "ServiceUnit", "Application", "EntityByName", "EntityById", "healthCheckPeriod", "healthCheckMaxSilence" };
        return new std::vector<std::string> (childNames, childNames + sizeof(childNames) / sizeof(childNames[0]));
    };

    /*
     * XPATH: /SAFplusAmf/healthCheckPeriod
     */
    SaTimeT SAFplusAmfRoot::getHealthCheckPeriod()
    {
        return this->healthCheckPeriod.value;
    };

    /*
     * XPATH: /SAFplusAmf/healthCheckPeriod
     */
    void SAFplusAmfRoot::setHealthCheckPeriod(SaTimeT healthCheckPeriodValue, SAFplus::Transaction &txn)
    {
        this->healthCheckPeriod.set(healthCheckPeriodValue,txn);
    };

    /*
     * XPATH: /SAFplusAmf/healthCheckMaxSilence
     */
    SaTimeT SAFplusAmfRoot::getHealthCheckMaxSilence()
    {
        return this->healthCheckMaxSilence.value;
    };

    /*
     * XPATH: /SAFplusAmf/healthCheckMaxSilence
     */
    void SAFplusAmfRoot::setHealthCheckMaxSilence(SaTimeT healthCheckMaxSilenceValue, SAFplus::Transaction &txn)
    {
        this->healthCheckMaxSilence.set(healthCheckMaxSilenceValue,txn);
    };

    SAFplusAmfRoot::~SAFplusAmfRoot()
    {
    };

}
/* namespace SAFplusAmf */
