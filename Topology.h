#ifndef TOPOLOGY_H
#define TOPOLOGY_H

#include "device.h"


class Topology
{
public:
    Topology(Json::Value* id=nullptr);
    ~Topology();

    Json::Value * get_id();
    Json::Value & get_values();
    void add_value(Json::Value key , Json::Value new_value);
    void set_id(Json::Value new_id);
    vector<Device*> &get_devices();
    void write();
    void print_devices();
    void print();

private:
    Json::Value * id;
    Json::Value values;
    vector<Device*> devices;
    bool visited = false;    
    string dev_key;


    void PrintJSONValue(const Json::Value &val ,int depth);

    // 

};




#endif // TOPOLOGY_H