#pragma once

#include <boost/interprocess/managed_shared_memory.hpp>

namespace SAFplus
{
  class ClusterNodeArray;

  //? Simple status variable indicating whether this node is reachable
  enum class NodeStatus
    {
    NonExistent = 0,
      Dead        = 1,
      Unknown     = 2,
      Alive       = 3
      };

  //? Convert the node status to a printable string
  const char* nodeStatus2CString(NodeStatus s)
  {
    if (s == NodeStatus::NonExistent) return "non-existent";
    if (s == NodeStatus::Dead) return "dead";
    if (s == NodeStatus::Unknown) return "unknown";
    if (s == NodeStatus::Alive) return "alive";
  }

  // Client side of the cloud discovery system.  But still intended for internal use.
  // Applications should use the cluster group (reports the AMF using nodes)
  class ClusterNodes
  {
  public:
    ClusterNodes(bool writable=false);

    // returns the node's generation...
    //uint32_t numNodes();
    uint32_t    maxNodeId();

    //? Return the node's status
    NodeStatus  status(int nodeId);
    //? Return the node's generation
    uint64_t    generation(int nodeId);

    const char* transportAddress(int nodeId);

    // There should be only one writer of this shared memory in the node.


    //? Add a node into the cloud.  Overwrites Nonexistent, Dead or Unknown nodes with "Alive" state.
    // If node is already marked as alive but address is different, returns false.
    // If address is the same, returns true if this generation >= existing one, else false.
    // returns the nodeId.
    uint add(const std::string& address,uint64_t generation,uint preferredNodeId=0);
 
    //? Force add a node into the cloud.  
    void set(uint nodeId,const std::string& address,uint64_t generation,NodeStatus status);

    //? Mark a particular node as dead.  Cloud Discovery algorithms handle every other state internally, but need your help (fault manager linkage filtering transport layer keep-alives or hardware assist) on death detection so as to not have redundant death detection mechanisms.
    void mark(int nodeId,NodeStatus status);


    //? typically you'd never call this...
    static void deleteSharedMemory();

  protected:
    boost::interprocess::shared_memory_object mem;
    boost::interprocess::mapped_region        memRegion;
    ClusterNodeArray* data;

  public:

    class Iterator
    {
    protected:
      ClusterNodes* clusterNodes;
      int curIdx;
    public:
      Iterator(ClusterNodes* cn,int start=1)
      {
        clusterNodes = cn;
        curIdx = start;
      }
      int nodeId() { return curIdx; }
      SAFplus::NodeStatus status() { return clusterNodes->status(curIdx); }
      const char* transportAddress() { return clusterNodes->transportAddress(curIdx); }

      //? Go to the next member in this group
      Iterator& operator++();
      Iterator& operator++(int);

      bool operator == (const Iterator& b) { return ((clusterNodes == b.clusterNodes) && (curIdx == b.curIdx)); }
      bool operator != (const Iterator& b) { return !((clusterNodes == b.clusterNodes) && (curIdx == b.curIdx)); }
    };

    Iterator  begin(uint start=1) { return Iterator(this,start); }
    Iterator& end() const { return endSentinel; }

    static Iterator endSentinel;
  };
}
