/* 
 * File CapabilityModel.hxx
 * This file has been auto-generated by Y2CPP, the
 * plug-in of pyang.
 */ 

#pragma once
#ifndef CAPABILITYMODEL_HXX_
#define CAPABILITYMODEL_HXX_
#include "SAFplusAmfCommon.hxx"

#include "MgtEnumType.hxx"
#include <iostream>

namespace SAFplusAmf
  {

    enum class CapabilityModel
      {
        x_active_and_y_standby, x_active_or_y_standby, one_active_or_y_standby, one_active_or_one_standby, x_active, one_active, nonPreInstantiable
      };
    std::ostream& operator<<(std::ostream& os, const CapabilityModel& e);
    std::istream& operator>>(std::istream& is, CapabilityModel& e);
    const char* c_str(const CapabilityModel& e);

    /*
     * This is the class that will handle the conversion for us.
     */
    class CapabilityModelManager : public SAFplus::MgtEnumType<CapabilityModelManager, CapabilityModel> {
        CapabilityModelManager();  // private to prevent instantiation
    public:
        static const map_t en2str_map;  // This is the lookup table.
    };
}
/* namespace SAFplusAmf */
#endif /* CAPABILITYMODEL_HXX_ */
