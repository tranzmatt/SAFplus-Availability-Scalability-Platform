/* 
 * File ServiceStats.cxx
 * This file has been auto-generated by Y2CPP, the
 * plug-in of pyang.
 */ 

#include "myServiceCommon.hxx"
#include <vector>
#include "MgtFactory.hxx"
#include "clMgtContainer.hxx"
#include "ServiceStats.hxx"


namespace myService
  {

    /* Apply MGT object factory */
    MGT_REGISTER_IMPL(ServiceStats, /myService/serviceStats)

    ServiceStats::ServiceStats(): SAFplus::MgtContainer("serviceStats")
    {
        this->addChildObject(&accessCounts, "accessCounts");
        accessCounts.config = false;
    };

    std::vector<std::string>* ServiceStats::getChildNames()
    {
        std::string childNames[] = { "accessCounts" };
        return new std::vector<std::string> (childNames, childNames + sizeof(childNames) / sizeof(childNames[0]));
    };

    /*
     * XPATH: /myService/serviceStats/accessCounts
     */
    SAFplus::MgtHistoryStat<int>* ServiceStats::getAccessCounts()
    {
        return dynamic_cast<SAFplus::MgtHistoryStat<int>*>(this->getChildObject("accessCounts"));
    };

    /*
     * XPATH: /myService/serviceStats/accessCounts
     */
    void ServiceStats::addAccessCounts(SAFplus::MgtHistoryStat<int> *accessCountsValue)
    {
        this->addChildObject(accessCountsValue, "accessCounts");
    };

    ServiceStats::~ServiceStats()
    {
    };

}
/* namespace ::myService */
