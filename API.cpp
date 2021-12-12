#include "API.h"




JSONTopologyParser::JSONTopologyParser(){


}


JSONTopologyParser::~JSONTopologyParser(){
    for (vector<Topology*>::iterator it = topologies.begin();it!=topologies.end();it++){
        delete (*it);
        (*it) = nullptr;
    }
}




Topology * JSONTopologyParser::readJSON(string filename){
    // get file pointer


    fstream fileptr(filename);
    Json::Reader reader;
    Topology *top = new Topology(nullptr);
    Json::Value value;

    reader.parse(fileptr,value);
    // empty file
    if (value==Json::nullValue){
        delete top;
        top=nullptr;
        return top;
    }
    
    for (Json::Value::iterator it=value.begin();it!=value.end();it++){
        if (it.key()=="id")
            top->set_id(*it);
        else{
            top->add_value(it.key(),(*it));
        }
    }
    topologies.push_back(top);

    return top;

};



bool JSONTopologyParser::writeJSON(string topologyID,string filename){
    Json::Value given_topology;
    // Json::Value given_topology;
    // Topology to_write(val);
    Topology * alias_top = getTopology(topologyID);
    if(alias_top==nullptr){
        cout<<"Entered topology id doesn't exist\n";
        return false;
    }

    given_topology = packages_topology_in_JSON_value(alias_top);

    Topology * found_in_given_file = readJSON(filename);
    Json::Value value_to_be_written;
    
    if(found_in_given_file!=nullptr){
        cout<<"Entered file already has content , erase it and try again"<<endl;
        return false;

        // till now , support is for one topology per single json file
        // // check if what is read is a single topology or a dict of topologies
        // if(list_of_topologies(found_in_given_file)){
        //     // continue;
        // }
        // else{
        //     value_to_be_written["topology_1"] = found_in_given_file;
        //     value_to_be_written["topology_2"] = given_topology;
        // }
    }
    else{
            value_to_be_written = given_topology;
        }


    Json::StreamWriterBuilder builder;

    std::unique_ptr<Json::StreamWriter> writer(builder.newStreamWriter());
    std::ofstream outputfile(filename);
    writer->write(value_to_be_written,&outputfile);
    
    return true;
}


std::vector<Topology*> & JSONTopologyParser::queryTopologies(){
    return topologies;
}



bool JSONTopologyParser::deleteTopology(string topologyID){

    Topology * top_to_remove = getTopology(topologyID);
    if (top_to_remove==nullptr){
        cout<<"Entered topology id doesn't exist\n";
        return false;
    }
    topologies.erase(find(topologies.begin(),topologies.end(),top_to_remove));
    delete top_to_remove; 
    top_to_remove = nullptr;
    return true;

}


vector<Device*> JSONTopologyParser::queryDevices(string TopologyID){
    Topology * top = getTopology(TopologyID);
    if (top==nullptr){
        cout<<"Entered topology id doesn't exist\n";
        vector <Device*> devices;
        return devices;
    }
    vector <Device*> devices = top->get_devices(); 

    return devices;
}


vector<Device*> JSONTopologyParser::queryDevicesWithNetlistNode(string TopologyID,string NetlistNodeID){
    vector <Device*> tot_devices = queryDevices(TopologyID);
    vector <Device*> devices;
    int dev_size = 0;
    for(vector<Device*>::iterator dev=tot_devices.begin();dev!=tot_devices.end();dev++){
        // *dev is a device pointer
        for (specs_vec::iterator it= (*dev)->get_specs()->begin();it!= (*dev)->get_specs()->end();it++){
            for (specs_map::iterator in_it=(*it)["netlist"].begin();in_it!=(*it)["netlist"].end();in_it++){
                if(in_it->second.first==NetlistNodeID){
                    devices.push_back((*dev));
                    break;
                }
            }
            if(devices.size()>dev_size){
                dev_size++;
                break;
            }
        }
    }
    return devices;
}









Json::Value JSONTopologyParser::packages_topology_in_JSON_value(Topology * alias){
    Json::Value topology_to_be_written;

    // vector of topology values , each value is a key value pair , 
    // i.e temp_val[0] is "components" : [list of components]

    Json::Value temp_vals = alias->get_values();
    for (Json::Value::iterator it = temp_vals.begin();it!=temp_vals.end();it++){
        topology_to_be_written[it.key().asString()] = (*it);
    }


    topology_to_be_written["id"] = *(alias->get_id());


    return topology_to_be_written;
}


bool JSONTopologyParser::list_of_topologies(Json::Value & value){
    for (Json::Value::iterator it=value.begin();it!=value.end();it++){
        if(it.key()=="id")
            return true;
    }
    return false;

}


Topology * JSONTopologyParser::getTopology(string topologyID){
     for (int i=0;i<topologies.size();i++){
        Topology* &alias = topologies[i];
        if(alias->get_id()->asString()==topologyID && alias!=nullptr){
            alias->write();
            return alias;
        }
    }
    return nullptr;
}