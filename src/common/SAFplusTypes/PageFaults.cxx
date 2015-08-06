/* 
 * File PageFaults.cxx
 * This file has been auto-generated by Y2CPP, the
 * plug-in of pyang.
 */ 
#include "SAFplusTypesCommon.hxx"

#include <vector>
#include "MgtFactory.hxx"
#include "IntStatistic.hxx"
#include "PageFaults.hxx"


namespace SAFplusTypes
  {

    /* Apply MGT object factory */
    MGT_REGISTER_IMPL(PageFaults, /SAFplusTypes/processStats/pageFaults)

    PageFaults::PageFaults()
    {
        this->tag.assign("pageFaults");
    };

    std::vector<std::string>* PageFaults::getChildNames()
    {
        std::string childNames[] = { "current", "history10sec", "history1min", "history10min", "history1hour", "history12hour", "history1day", "history1week", "history1month" };
        return new std::vector<std::string> (childNames, childNames + sizeof(childNames) / sizeof(childNames[0]));
    };

    PageFaults::~PageFaults()
    {
    };

}
/* namespace SAFplusTypes */
