/* 
 * File Ut.hxx
 * This file has been auto-generated by Y2CPP, the
 * plug-in of pyang.
 */ 

#pragma once
#ifndef UNITTESTROOT_HXX_
#define UNITTESTROOT_HXX_
#include "unitTestCommon.hxx"

#include "ComponentKey.hxx"
#include "clMgtList.hxx"
#include <vector>
#include "MgtFactory.hxx"
#include "clMgtContainer.hxx"

namespace unitTest
  {

    class UnitTestRoot : public SAFplus::MgtContainer {

        /* Apply MGT object factory */
        MGT_REGISTER(UnitTestRoot);

    public:
        SAFplus::MgtList<unitTest::ComponentKey> componentList;

    public:
        UnitTestRoot();
        std::vector<std::string>* getChildNames();
        ~UnitTestRoot();

    };
}
/* namespace unitTest */
#endif /* UNITTESTROOT_HXX_ */