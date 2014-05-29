/* 
 * File EscalationPolicy.cxx
 * This file has been auto-generated by Y2CPP, the
 * plug-in of pyang.
 */ 
#include "SAFplusAmfCommon.hxx"

#include <vector>
#include "clTransaction.hxx"
#include "clMgtContainer.hxx"
#include "clMgtProv.hxx"
#include "EscalationPolicy.hxx"


namespace SAFplusAmf
  {

    EscalationPolicy::EscalationPolicy(): SAFplus::MgtContainer("EscalationPolicy"), maximum("maximum"), duration("duration")
    {
        this->addChildObject(&maximum, "maximum");
        this->addChildObject(&duration, "duration");
    };

    void EscalationPolicy::toString(std::stringstream &xmlString)
    {
        /* TODO:  */
    };

    std::vector<std::string>* EscalationPolicy::getChildNames()
    {
        std::string childNames[] = { "maximum", "duration" };
        return new std::vector<std::string> (childNames, childNames + sizeof(childNames) / sizeof(childNames[0]));
    };

    /*
     * XPATH: /SAFplusAmf/EscalationPolicy/maximum
     */
    unsigned long int EscalationPolicy::getMaximum()
    {
        return this->maximum.value;
    };

    /*
     * XPATH: /SAFplusAmf/EscalationPolicy/maximum
     */
    void EscalationPolicy::setMaximum(unsigned long int maximumValue, SAFplus::Transaction &txn)
    {
        this->maximum.set(maximumValue,txn);
    };

    /*
     * XPATH: /SAFplusAmf/EscalationPolicy/duration
     */
    SaTimeT EscalationPolicy::getDuration()
    {
        return this->duration.value;
    };

    /*
     * XPATH: /SAFplusAmf/EscalationPolicy/duration
     */
    void EscalationPolicy::setDuration(SaTimeT durationValue, SAFplus::Transaction &txn)
    {
        this->duration.set(durationValue,txn);
    };

    EscalationPolicy::~EscalationPolicy()
    {
    };

}
/* namespace SAFplusAmf */
