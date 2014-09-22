/* 
 * File AdministrativeState.cxx
 * This file has been auto-generated by Y2CPP, the
 * plug-in of pyang.
 */ 
#include "SAFplusAmfCommon.hxx"

#include "MgtEnumType.hxx"
#include <iostream>
#include "AdministrativeState.hxx"


namespace SAFplusAmf
  {

    /*
     * Provide an implementation of the en2str_map lookup table.
     */
    const AdministrativeStateManager::map_t AdministrativeStateManager::en2str_map = {
            pair_t(AdministrativeState::off, "off"),
            pair_t(AdministrativeState::idle, "idle"),
            pair_t(AdministrativeState::on, "on")
    }; // uses c++11 initializer lists 

    const char* c_str(const SAFplusAmf::AdministrativeState &administrativeState)
    {
        return AdministrativeStateManager::c_str(administrativeState);
    };

    std::ostream& operator<<(std::ostream &os, const SAFplusAmf::AdministrativeState &administrativeState)
    {
        return os << AdministrativeStateManager::toString(administrativeState);
    };

    std::istream& operator>>(std::istream &is, SAFplusAmf::AdministrativeState &administrativeState)
    {
        std::string buf;
        is >> buf;
        administrativeState = AdministrativeStateManager::toEnum(buf);
        return is;
    };

}
/* namespace SAFplusAmf */
