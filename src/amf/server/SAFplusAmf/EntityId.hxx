/* 
 * File EntityId.hxx
 * This file has been auto-generated by Y2CPP, the
 * plug-in of pyang.
 */ 

#pragma once
#ifndef ENTITYID_HXX_
#define ENTITYID_HXX_

#include "clMgtContainer.hxx"
#include "clTransaction.hxx"
#include <string>
#include "clMgtProv.hxx"
#include "SAFplusAmfCommon.hxx"
#include <cstdint>
#include <vector>

namespace SAFplusAmf
  {

    class EntityId : public SAFplus::MgtContainer {
    public:

        /*
         * Unique name of this entity
         */
        SAFplus::MgtProv<std::string> name;

        /*
         * Each SAFplus AMF entity gets a unique numerical identifier
         */
        SAFplus::MgtProv<::uint16_t> id;

    public:
        EntityId();
        std::vector<std::string>* getChildNames();

        /*
         * XPATH: /SAFplusAmf/EntityId/name
         */
        std::string getName();

        /*
         * XPATH: /SAFplusAmf/EntityId/name
         */
        void setName(std::string nameValue, SAFplus::Transaction &txn=SAFplus::NO_TXN);

        /*
         * XPATH: /SAFplusAmf/EntityId/id
         */
        ::uint16_t getId();

        /*
         * XPATH: /SAFplusAmf/EntityId/id
         */
        void setId(::uint16_t idValue, SAFplus::Transaction &txn=SAFplus::NO_TXN);
        ~EntityId();

    };
}
/* namespace ::SAFplusAmf */
#endif /* ENTITYID_HXX_ */
