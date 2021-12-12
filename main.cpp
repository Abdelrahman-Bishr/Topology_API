#include "API.h"
#include<unistd.h>



int main(){

    
    JSONTopologyParser parser;
    char temp[256];
    getcwd(temp,256);
    string path = (string) temp;

    Topology* topology = parser.readJSON(path+"/x.json");
    if (topology==nullptr){
        return 0;
    }

    parser.writeJSON(topology->get_id()->asString(),path+"/new_file.json");

    for (vector<Topology*>::iterator it = parser.queryTopologies().begin();
                it!=parser.queryTopologies().end();it++){
        for(vector<Device*>::iterator in_it= parser.queryDevices((*it)->get_id()->asString()).begin();
                in_it!=parser.queryDevices((*it)->get_id()->asString()).end();in_it++){

                        cout<<(*(*in_it))<<"=======================================\n";
        }
        
        vector<Device*> devs = parser.queryDevicesWithNetlistNode((*it)->get_id()->asString(),"vss"); 
        cout<<"------------------------------------------------------------------\n\n";        
        for(vector<Device*>::iterator in_it= devs.begin();
                in_it!=devs.end();in_it++){
                        cout<<(*(*in_it))<<"=======================================\n";
        }
    }
    cout<<"topologies size before delete is "<<parser.queryTopologies().size()<<endl;
    parser.deleteTopology(parser.queryTopologies()[0]->get_id()->asString());
    cout<<"topologies size after delete becomes "<<parser.queryTopologies().size()<<endl;

    return 0;
}
