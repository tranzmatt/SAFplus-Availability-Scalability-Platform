/* 
 * File ServerConfig.cxx
 * This file has been auto-generated by Y2CPP, the
 * plug-in of pyang.
 */ 

#include <vector>
#include "MgtFactory.hxx"
#include "clMgtObject.hxx"
#include "clMgtProv.hxx"
#include "ServerConfig.hxx"

using namespace std;

namespace SAFplusLog {

    /* Apply MGT object factory */
    REGISTERIMPL(ServerConfig, /SAFplusLog/ServerConfig)

    ServerConfig::ServerConfig(): ClMgtObject("ServerConfig"), maximumStreams("maximumStreams"), maximumComponents("maximumComponents"), maximumSharedMemoryPages("maximumSharedMemoryPages"), maximumRecordsInPacket("maximumRecordsInPacket"), processingInterval("processingInterval") {
        this->addChildObject(&maximumStreams, "maximumStreams");
        this->addChildObject(&maximumComponents, "maximumComponents");
        this->addChildObject(&maximumSharedMemoryPages, "maximumSharedMemoryPages");
        this->addChildObject(&maximumRecordsInPacket, "maximumRecordsInPacket");
        this->addChildObject(&processingInterval, "processingInterval");
    };

    vector<string> *ServerConfig::getChildNames() {
        string childNames[] = { "maximumStreams", "maximumComponents", "maximumSharedMemoryPages", "maximumRecordsInPacket", "processingInterval" };
        return new vector<string> (childNames, childNames + sizeof(childNames) / sizeof(childNames[0]));
    };

    /*
     * XPATH: /SAFplusLog/ServerConfig/maximumStreams
     */
    unsigned int ServerConfig::getMaximumStreamsValue() {
        return this->maximumStreams.Value;
    };

    /*
     * XPATH: /SAFplusLog/ServerConfig/maximumStreams
     */
    void ServerConfig::setMaximumStreamsValue(unsigned int maximumStreamsValue) {
        this->maximumStreams.Value = maximumStreamsValue;
    };

    /*
     * XPATH: /SAFplusLog/ServerConfig/maximumComponents
     */
    unsigned int ServerConfig::getMaximumComponentsValue() {
        return this->maximumComponents.Value;
    };

    /*
     * XPATH: /SAFplusLog/ServerConfig/maximumComponents
     */
    void ServerConfig::setMaximumComponentsValue(unsigned int maximumComponentsValue) {
        this->maximumComponents.Value = maximumComponentsValue;
    };

    /*
     * XPATH: /SAFplusLog/ServerConfig/maximumSharedMemoryPages
     */
    unsigned int ServerConfig::getMaximumSharedMemoryPagesValue() {
        return this->maximumSharedMemoryPages.Value;
    };

    /*
     * XPATH: /SAFplusLog/ServerConfig/maximumSharedMemoryPages
     */
    void ServerConfig::setMaximumSharedMemoryPagesValue(unsigned int maximumSharedMemoryPagesValue) {
        this->maximumSharedMemoryPages.Value = maximumSharedMemoryPagesValue;
    };

    /*
     * XPATH: /SAFplusLog/ServerConfig/maximumRecordsInPacket
     */
    unsigned int ServerConfig::getMaximumRecordsInPacketValue() {
        return this->maximumRecordsInPacket.Value;
    };

    /*
     * XPATH: /SAFplusLog/ServerConfig/maximumRecordsInPacket
     */
    void ServerConfig::setMaximumRecordsInPacketValue(unsigned int maximumRecordsInPacketValue) {
        this->maximumRecordsInPacket.Value = maximumRecordsInPacketValue;
    };

    /*
     * XPATH: /SAFplusLog/ServerConfig/processingInterval
     */
    unsigned long int ServerConfig::getProcessingIntervalValue() {
        return this->processingInterval.Value;
    };

    /*
     * XPATH: /SAFplusLog/ServerConfig/processingInterval
     */
    void ServerConfig::setProcessingIntervalValue(unsigned long int processingIntervalValue) {
        this->processingInterval.Value = processingIntervalValue;
    };

    ServerConfig::~ServerConfig() {
    };

}
/* namespace SAFplusLog */
