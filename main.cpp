#include "API.h"

string path="/home/abdelrahman/career/projects/master_micro/topologies_api/";
string existing_file = "topology.json";
string new_file = "made.json";


int main(){

    JSONTopologyParser parser;
    Topology * temp = parser.readJSON(path+existing_file);
    
    return 0;
}
