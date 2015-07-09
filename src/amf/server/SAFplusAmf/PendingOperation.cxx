/* 
 * File PendingOperation.cxx
 * This file has been auto-generated by Y2CPP, the
 * plug-in of pyang.
 */ 
#include "SAFplusAmfCommon.hxx"

#include "MgtEnumType.hxx"
#include <iostream>
#include "PendingOperation.hxx"


namespace SAFplusAmf
  {

    /*
     * Provide an implementation of the en2str_map lookup table.
     */
    const PendingOperationManager::map_t PendingOperationManager::en2str_map = {
            pair_t(PendingOperation::none, "none"),
            pair_t(PendingOperation::instantiation, "instantiation"),
            pair_t(PendingOperation::shutdown, "shutdown"),
            pair_t(PendingOperation::workAssignment, "workAssignment"),
            pair_t(PendingOperation::workRemoval, "workRemoval")
    }; // uses c++11 initializer lists 

    const char* c_str(const SAFplusAmf::PendingOperation &pendingOperation)
    {
        return PendingOperationManager::c_str(pendingOperation);
    };

    std::ostream& operator<<(std::ostream &os, const SAFplusAmf::PendingOperation &pendingOperation)
    {
        return os << PendingOperationManager::toString(pendingOperation);
    };

    std::istream& operator>>(std::istream &is, SAFplusAmf::PendingOperation &pendingOperation)
    {
        std::string buf;
        is >> buf;
        pendingOperation = PendingOperationManager::toEnum(buf);
        return is;
    };

}
/* namespace SAFplusAmf */
