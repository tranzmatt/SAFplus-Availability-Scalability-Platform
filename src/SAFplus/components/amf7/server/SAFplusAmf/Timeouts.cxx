/* 
 * File Timeouts.cxx
 * This file has been auto-generated by Y2CPP, the
 * plug-in of pyang.
 */ 
#include "SAFplusAmfCommon.hxx"

#include "clTransaction.hxx"
#include "clMgtProv.hxx"
#include <vector>
#include "MgtFactory.hxx"
#include "clMgtContainer.hxx"
#include "Timeouts.hxx"


namespace SAFplusAmf
  {

    /* Apply MGT object factory */
    MGT_REGISTER_IMPL(Timeouts, /SAFplusAmf/Component/timeouts)

    Timeouts::Timeouts(): SAFplus::MgtContainer("timeouts"), quiescingComplete("quiescingComplete"), workRemoval("workRemoval"), workAssignment("workAssignment")
    {
        this->addChildObject(&quiescingComplete, "quiescingComplete");
        this->addChildObject(&workRemoval, "workRemoval");
        this->addChildObject(&workAssignment, "workAssignment");
    };

    std::vector<std::string>* Timeouts::getChildNames()
    {
        std::string childNames[] = { "quiescingComplete", "workRemoval", "workAssignment" };
        return new std::vector<std::string> (childNames, childNames + sizeof(childNames) / sizeof(childNames[0]));
    };

    /*
     * XPATH: /SAFplusAmf/Component/timeouts/quiescingComplete
     */
    SaTimeT Timeouts::getQuiescingComplete()
    {
        return this->quiescingComplete.value;
    };

    /*
     * XPATH: /SAFplusAmf/Component/timeouts/quiescingComplete
     */
    void Timeouts::setQuiescingComplete(SaTimeT quiescingCompleteValue, SAFplus::Transaction &txn)
    {
        this->quiescingComplete.set(quiescingCompleteValue,txn);
    };

    /*
     * XPATH: /SAFplusAmf/Component/timeouts/workRemoval
     */
    SaTimeT Timeouts::getWorkRemoval()
    {
        return this->workRemoval.value;
    };

    /*
     * XPATH: /SAFplusAmf/Component/timeouts/workRemoval
     */
    void Timeouts::setWorkRemoval(SaTimeT workRemovalValue, SAFplus::Transaction &txn)
    {
        this->workRemoval.set(workRemovalValue,txn);
    };

    /*
     * XPATH: /SAFplusAmf/Component/timeouts/workAssignment
     */
    SaTimeT Timeouts::getWorkAssignment()
    {
        return this->workAssignment.value;
    };

    /*
     * XPATH: /SAFplusAmf/Component/timeouts/workAssignment
     */
    void Timeouts::setWorkAssignment(SaTimeT workAssignmentValue, SAFplus::Transaction &txn)
    {
        this->workAssignment.set(workAssignmentValue,txn);
    };

    Timeouts::~Timeouts()
    {
    };

}
/* namespace SAFplusAmf */
