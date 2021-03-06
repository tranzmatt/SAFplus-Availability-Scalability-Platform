/* 
 * File EscalationPolicy.hxx
 * This file has been auto-generated by Y2CPP, the
 * plug-in of pyang.
 */ 

#pragma once
#ifndef ESCALATIONPOLICY_HXX_
#define ESCALATIONPOLICY_HXX_

#include "clMgtContainer.hxx"
#include "clTransaction.hxx"
#include "clMgtProv.hxx"
#include "SAFplusAmfCommon.hxx"
#include <cstdint>
#include <vector>

namespace SAFplusAmf
  {

    class EscalationPolicy : public SAFplus::MgtContainer {
    public:

        /*
         * The maximum number of events that can occur within that time period before escalation occurs.  A value of 0 will escalate the event right away.
         */
        SAFplus::MgtProv<::uint64_t> maximum;

        /*
         * The time period (in milliseconds) involved.
         */
        SAFplus::MgtProv<SaTimeT> duration;

    public:
        EscalationPolicy();
        std::vector<std::string>* getChildNames();

        /*
         * XPATH: /SAFplusAmf/EscalationPolicy/maximum
         */
        ::uint64_t getMaximum();

        /*
         * XPATH: /SAFplusAmf/EscalationPolicy/maximum
         */
        void setMaximum(::uint64_t maximumValue, SAFplus::Transaction &txn=SAFplus::NO_TXN);

        /*
         * XPATH: /SAFplusAmf/EscalationPolicy/duration
         */
        SaTimeT getDuration();

        /*
         * XPATH: /SAFplusAmf/EscalationPolicy/duration
         */
        void setDuration(SaTimeT &durationValue, SAFplus::Transaction &txn=SAFplus::NO_TXN);
        ~EscalationPolicy();

    };
}
/* namespace ::SAFplusAmf */
#endif /* ESCALATIONPOLICY_HXX_ */
