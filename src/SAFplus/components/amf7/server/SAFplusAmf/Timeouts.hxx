/* 
 * File Timeouts.hxx
 * This file has been auto-generated by Y2CPP, the
 * plug-in of pyang.
 */ 

#pragma once
#ifndef TIMEOUTS_HXX_
#define TIMEOUTS_HXX_
#include "SAFplusAmfCommon.hxx"

#include "clTransaction.hxx"
#include "clMgtProv.hxx"
#include <vector>
#include "MgtFactory.hxx"
#include "clMgtContainer.hxx"

namespace SAFplusAmf
  {

    class Timeouts : public SAFplus::MgtContainer {

        /* Apply MGT object factory */
        MGT_REGISTER(Timeouts);

    public:

        /*
         * How much time to give a component to gracefully finish handling its work before faulting it, in milliseconds.
         */
        SAFplus::MgtProv<SaTimeT> quiescingComplete;

        /*
         * How much time to give a component to executes its work (component service instance) removal callback before faulting the component.  Specified in milliseconds.
         */
        SAFplus::MgtProv<SaTimeT> workRemoval;

        /*
         * How much time to give a component to executes its work (component service instance) removal callback before faulting the component.  Specified in milliseconds.
         */
        SAFplus::MgtProv<SaTimeT> workAssignment;

    public:
        Timeouts();
        void toString(std::stringstream &xmlString);
        std::vector<std::string>* getChildNames();

        /*
         * XPATH: /SAFplusAmf/Component/timeouts/quiescingComplete
         */
        SaTimeT getQuiescingComplete();

        /*
         * XPATH: /SAFplusAmf/Component/timeouts/quiescingComplete
         */
        void setQuiescingComplete(SaTimeT quiescingCompleteValue, SAFplus::Transaction &txn=SAFplus::NO_TXN);

        /*
         * XPATH: /SAFplusAmf/Component/timeouts/workRemoval
         */
        SaTimeT getWorkRemoval();

        /*
         * XPATH: /SAFplusAmf/Component/timeouts/workRemoval
         */
        void setWorkRemoval(SaTimeT workRemovalValue, SAFplus::Transaction &txn=SAFplus::NO_TXN);

        /*
         * XPATH: /SAFplusAmf/Component/timeouts/workAssignment
         */
        SaTimeT getWorkAssignment();

        /*
         * XPATH: /SAFplusAmf/Component/timeouts/workAssignment
         */
        void setWorkAssignment(SaTimeT workAssignmentValue, SAFplus::Transaction &txn=SAFplus::NO_TXN);
        ~Timeouts();

    };
}
/* namespace SAFplusAmf */
#endif /* TIMEOUTS_HXX_ */