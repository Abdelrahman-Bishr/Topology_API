#include "Topology.h"



Topology::Topology(Json::Value * id){
    this->id = id;
}

Topology::~Topology(){
    delete id;
    id = nullptr;
}

Json::Value* Topology::get_id(){
    return id;
}

Json::Value& Topology::get_values(){
    return values;
}

void Topology::add_value(Json::Value key , Json::Value new_value){    
    visited=true;
    values[key.asString()] = new_value;
    if (key.asString()=="components" || key.asString()=="devices"){
        dev_key = key.asString();
        for (vector<Device*>::iterator it = devices.begin();it!=devices.end();it++){
            delete (*it);
            devices[(int)(it-devices.begin())] = nullptr;
            devices.erase(it);
        }
        for(Json::Value::iterator it = values[dev_key].begin();it!=values[dev_key].end(); it++){
            devices.push_back(new Device((*it)));
        }    
    }

}

void Topology::set_id(Json::Value new_id){
    delete id;
    id = new Json::Value(new_id);
    values["id"] = new_id;
}

vector<Device*> &Topology::get_devices(){
    return devices;
}

void Topology::write(){
    // when called , shall update values , to write any changes that have happened to devices
    for (vector<Device*>::iterator it=devices.begin();it!=devices.end();it++){
        for(Json::Value::iterator vals_it=values[dev_key].begin();vals_it!=values[dev_key].end();vals_it++){
            if((*vals_it)["id"].asString()==(*it)->get_id()){
                // copy main attributes back at value
                for (attributes_vec::iterator in_it=(*it)->get_main_attributes()->begin();
                     in_it!=(*it)->get_main_attributes()->end(); in_it++){

                    for (map<string,string>::iterator inner_it=in_it->begin();inner_it!=in_it->end();inner_it++){
                        (*vals_it)[inner_it->first] = inner_it->second;
                    }
                }
                // copy specs too back at value
                for (specs_vec::iterator in_it=(*it)->get_specs()->begin();
                     in_it!=(*it)->get_specs()->end(); in_it++){

                    for (map<string,specs_map>::iterator inner_it=in_it->begin();inner_it!=in_it->end();inner_it++){
                        for (specs_map::iterator inner_most_it=inner_it->second.begin();
                                inner_most_it!=inner_it->second.end();inner_most_it++)

                            if (inner_most_it->second.first==""){
                                (*vals_it)[inner_it->first][inner_most_it->first] = inner_most_it->second.second; 
                            }                            
                            else{
                                (*vals_it)[inner_it->first][inner_most_it->first] = inner_most_it->second.first; 
                            }
                    }                    
                }
            }
        }
    }    
}



void Topology::print_devices(){
    
    for(int i=0;i<devices.size();i++){
        cout<<(*devices[i])<<endl;
    }
}


void Topology::print(){
    if(id!=nullptr){
        Json::Value temp = (*id);
        cout<<"id = ";
        PrintJSONValue((*id),0);
        cout<<endl;
    }else
        return;
    cout<<"values.size = "<<values.size()<<endl;
    for (int i=0;i<values.size();i++){
        PrintJSONValue(values[i],0);
        cout<<"================================================\n";
    }
}


void Topology::PrintJSONValue(const Json::Value &val ,int depth)
{
    if( val.isString() ) {
        cout<< string(depth,' ');
        printf( "%s", val.asString().c_str() ); 
    } else if( val.isBool() ) {
        cout<< string(depth,' ');
        printf( "%d", val.asBool() ); 
    } else if( val.isInt() ) {
        cout<< string(depth,' ');
        printf( "%d", val.asInt() ); 
    } else if( val.isUInt() ) {
        cout<< string(depth,' ');
        printf( "%u", val.asUInt() ); 
    } else if( val.isDouble() ) {
        cout<< string(depth,' ');
        printf( "%f", val.asDouble() ); 
    }
    else if(val.isArray()){
        cout<<"[ ";
        for (Json::Value::const_iterator it=val.begin();it!=val.end();it++){
            PrintJSONValue((*it),depth+1);
            cout<<endl;
            }
        cout<<"]\n";
    }
    else if(val.isObject()){
        cout<<"{\n\" ";
        for (Json::Value::const_iterator it=val.begin();it!=val.end();it++){
            cout<<"\" ";
            PrintJSONValue(it.key(),depth+1);
            cout<<" \" : \" ";
            PrintJSONValue((*it),0);
            cout<<" \"\n";
        }
        cout<<"}\n";
    }
    else 
    {
        printf( "unknown type=[%d]", val.type() ); 
    }
}
