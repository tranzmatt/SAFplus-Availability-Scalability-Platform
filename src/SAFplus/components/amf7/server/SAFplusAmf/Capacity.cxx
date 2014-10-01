/* 
 * File Capacity.cxx
 * This file has been auto-generated by Y2CPP, the
 * plug-in of pyang.
 */ 
#include "SAFplusAmfCommon.hxx"

#include <string>
#include "clTransaction.hxx"
#include "clMgtProv.hxx"
#include <vector>
#include "MgtFactory.hxx"
#include "clMgtContainer.hxx"
#include "Capacity.hxx"


namespace SAFplusAmf
  {

    /* Apply MGT object factory */
    MGT_REGISTER_IMPL(Capacity, /SAFplusAmf/Node/capacity)

    Capacity::Capacity(): SAFplus::MgtContainer("capacity"), resource("resource"), value("value")
    {
        this->addChildObject(&resource, "resource");
        this->addChildObject(&value, "value");
    };

    Capacity::Capacity(std::string resourceValue): SAFplus::MgtContainer("capacity"), resource("resource"), value("value")
    {
        this->resource.value =  resourceValue;
        this->addChildObject(&resource, "resource");
        this->addChildObject(&value, "value");
    };

    std::vector<std::string> Capacity::getKeys()
    {
        std::string keyNames[] = { "resource" };
        return std::vector<std::string> (keyNames, keyNames + sizeof(keyNames) / sizeof(keyNames[0]));
    };

    std::vector<std::string>* Capacity::getChildNames()
    {
        std::string childNames[] = { "resource", "value" };
        return new std::vector<std::string> (childNames, childNames + sizeof(childNames) / sizeof(childNames[0]));
    };

    /*
     * XPATH: /SAFplusAmf/Node/capacity/resource
     */
    std::string Capacity::getResource()
    {
        return this->resource.value;
    };

    /*
     * XPATH: /SAFplusAmf/Node/capacity/resource
     */
    void Capacity::setResource(std::string resourceValue, SAFplus::Transaction &t)
    {
        if(&t == &SAFplus::NO_TXN) this->resource.value = resourceValue;
        else
        {
            SAFplus::SimpleTxnOperation<std::string> *opt = new SAFplus::SimpleTxnOperation<std::string>(&(resource.value),resourceValue);
            t.addOperation(opt);
        }
    };

    /*
     * XPATH: /SAFplusAmf/Node/capacity/value
     */
    long int Capacity::getValue()
    {
        return this->value.value;
    };

    /*
     * XPATH: /SAFplusAmf/Node/capacity/value
     */
    void Capacity::setValue(long int valueValue, SAFplus::Transaction &t)
    {
        if(&t == &SAFplus::NO_TXN) this->value.value = valueValue;
        else
        {
            SAFplus::SimpleTxnOperation<long int> *opt = new SAFplus::SimpleTxnOperation<long int>(&(value.value),valueValue);
            t.addOperation(opt);
        }
    };

    Capacity::~Capacity()
    {
    };

}
/* namespace SAFplusAmf */
