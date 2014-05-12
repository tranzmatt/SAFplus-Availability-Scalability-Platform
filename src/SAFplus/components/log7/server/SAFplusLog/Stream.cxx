/* 
 * File Stream.cxx
 * This file has been auto-generated by Y2CPP, the
 * plug-in of pyang.
 */ 
#include "SAFplusLogCommon.hxx"

#include <vector>
#include "MgtFactory.hxx"
#include <string>
#include "StreamStatistics.hxx"
#include "StreamAttributes.hxx"
#include "Stream.hxx"


namespace SAFplusLog
  {

    /* Apply MGT object factory */
    MGT_REGISTER_IMPL(Stream, /SAFplusLog/StreamConfig/stream)

    Stream::Stream()
      :fileBuffer(SAFplusI::LogDefaultFileBufferSize),msgBuffer(SAFplusI::LogDefaultMessageBufferSize),fp(NULL)  // additions 
    {
        this->name.assign("stream");
    };

    Stream::Stream(std::string myNameValue)
      :fileBuffer(SAFplusI::LogDefaultFileBufferSize),msgBuffer(SAFplusI::LogDefaultMessageBufferSize),fp(NULL)  // additions 
    {
        this->myName.value =  myNameValue;
        this->name.assign("stream");
    };

    void Stream::toString(std::stringstream &xmlString)
    {
        /* TODO:  */
    };

    std::vector<std::string> Stream::getKeys()
    {
        std::string keyNames[] = { "myName" };
        return std::vector<std::string> (keyNames, keyNames + sizeof(keyNames) / sizeof(keyNames[0]));
    };

    std::vector<std::string>* Stream::getChildNames()
    {
        std::string childNames[] = { "myName", "fileName", "fileLocation", "fileUnitSize", "recordSize", "fileFullAction", "maximumFilesRotated", "flushFreq", "flushInterval", "syslog", "streamScope", "numLogs" };
        return new std::vector<std::string> (childNames, childNames + sizeof(childNames) / sizeof(childNames[0]));
    };

    Stream::~Stream()
    {
    };

}
/* namespace SAFplusLog */
