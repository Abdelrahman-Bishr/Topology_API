#ifndef API_H
#define API_H


#include <fstream>
#include <jsoncpp/json/reader.h>
#include <jsoncpp/json/writer.h>
#include "Topology.h"


class JSONTopologyParser{

public:
    JSONTopologyParser();
    ~JSONTopologyParser();

    Topology * readJSON(string filename);
    bool writeJSON(string topologyID,string filename);
    std::vector<Topology*> & queryTopologies();
    bool deleteTopology(string topologyID);
    vector<Device*> &queryDevices(string TopologyID);
    vector<Device*> queryDevicesWithNetlistNode(string TopologyID,string NetlistNodeID);


private: 

    map<string,vector<Device*> > devices;
    std::vector<Topology*> topologies;
    Topology * getTopology(string topologyID);
    Json::Value packages_topology_in_JSON_value(Topology * alias);
    bool list_of_topologies(Json::Value & value);
    void deleteDevices(string topologyID);
};


#endif // API_H