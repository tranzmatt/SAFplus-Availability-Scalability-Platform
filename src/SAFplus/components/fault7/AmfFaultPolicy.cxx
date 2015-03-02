#include <clFaultPolicyPlugin.hxx>
#include <clLogApi.hxx>
#include <vector>
#include <clFaultIpi.hxx>

using namespace std;
using namespace SAFplus;

namespace SAFplus
{
    class AmfFaultPolicy:public FaultPolicyPlugin
    {
      public:
    	AmfFaultPolicy();
        ~AmfFaultPolicy();
        virtual FaultAction processFaultEvent(SAFplus::FaultEventData fault,SAFplus::Handle faultReporter,SAFplus::Handle faultEntity,int countFaultEvent);
        virtual FaultAction processIocNotification(ClIocNotificationIdT eventId, ClIocNodeAddressT nodeAddress, ClIocPortT portId);

    };
    AmfFaultPolicy::AmfFaultPolicy()
    {

    }

    AmfFaultPolicy::~AmfFaultPolicy()
    {

    }

    FaultAction AmfFaultPolicy::processFaultEvent(SAFplus::FaultEventData fault,SAFplus::Handle faultReporter,SAFplus::Handle faultEntity,int countFaultEvent)
    {
        logInfo("POL","AMF","Received fault event : Process Id [%d], Node Id [%d], Fault Count [%d] ", faultEntity.getProcess(),faultEntity.getNode(),countFaultEvent);
        logInfo("POL","AMF","Process fault event : Default");
        if (countFaultEvent>=2)
        {
          	return FaultAction::ACTION_STOP;
        }
        return FaultAction::ACTION_IGNORE;
    }
    FaultAction AmfFaultPolicy::processIocNotification(ClIocNotificationIdT eventId, ClIocNodeAddressT nodeAddress, ClIocPortT portId)
    {
        logInfo("POL","AMF","Process ioc notification");
        //TODO :
        return FaultAction::ACTION_STOP;
    }
    static AmfFaultPolicy api;
}

extern "C" ClPlugin* clPluginInitialize(ClWordT preferredPluginVersion)
{
  // We can only provide a single version, so don't bother with the 'preferredPluginVersion' variable.

  // Initialize the pluginData structure
  SAFplus::api.pluginId         = FAULT_POLICY_PLUGIN_ID;
  SAFplus::api.pluginVersion    = FAULT_POLICY_PLUGIN_VER;
  SAFplus::api.policyId = SAFplus::FaultPolicy::Custom;
  // return it
  return (ClPlugin*) &SAFplus::api;
}