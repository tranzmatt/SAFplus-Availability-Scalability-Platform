/* 
 * File ObjectIdentifier128.hxx
 * This file has been auto-generated by Y2CPP, the
 * plug-in of pyang.
 */ 

#pragma once
#ifndef OBJECTIDENTIFIER128_HXX_
#define OBJECTIDENTIFIER128_HXX_
#include "ietfYangTypesCommon.hxx"

#include <string>
#include "clTransaction.hxx"
#include <iostream>

namespace ietfYangTypes
  {

    class ObjectIdentifier128 {
    public:
        std::string Value;

    public:
        ObjectIdentifier128();
        std::string getValue();
        void setValue(std::string value, SAFplus::Transaction &t=SAFplus::NO_TXN);
        ietfYangTypes::ObjectIdentifier128& operator=(const ietfYangTypes::ObjectIdentifier128 &objectIdentifier128);
        friend std::ostream& operator<<(std::ostream &os, const ietfYangTypes::ObjectIdentifier128 &objectIdentifier128);
        friend std::istream& operator>>(std::istream &is, ietfYangTypes::ObjectIdentifier128 &objectIdentifier128);
        ~ObjectIdentifier128();

    };
}
/* namespace ietfYangTypes */
#endif /* OBJECTIDENTIFIER128_HXX_ */
