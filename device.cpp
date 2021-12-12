#include "device.h"

Device::Device(Json::Value &component){
    main_attributes = new vector<map<string,string> >;
    specs = new vector<map<string, map<string,pair<string,double> > > >; 
    
    for (Json::Value::iterator it=component.begin();it!=component.end();it++){

        if(it.key().asString()=="id")
            id = (*it).asString();
        else if ((*it).isObject()){
            map<string,map<string,pair<string,double> > > temp;    
            for (Json::Value::iterator inside_it = (*it).begin();inside_it!=(*it).end();inside_it++){
                pair <string,double > temp_pair;
                if((*inside_it).isString()){
                    temp_pair = {(*inside_it).asString() , 0 };
                }
                else if ((*inside_it).isDouble() || (*inside_it).isInt()){
                    temp_pair = {"",(*inside_it).asDouble()};
                }
                    temp[it.key().asString()][inside_it.key().asString()] = temp_pair;
            }
            specs->push_back(temp);
        }
        else{
            map<string,string> temp;
            temp[it.key().asString()] = (*it).asString();
            main_attributes->push_back(temp);
        }
    }

}

Device::~Device(){
    delete main_attributes;
    main_attributes = nullptr;
    delete specs;
    specs=nullptr;
}

string Device::get_id(){
    return id;
}


vector<map<string,string> > * Device::get_main_attributes(){
    return main_attributes;
}

vector<map<string, map<string,pair<string,double> > > > * Device::get_specs(){
    return specs;
} 



 
ostream& operator<<(ostream& os, Device & dev){
    os<<"id = "<<dev.get_id()<<endl;
    for (vector<map<string,string> >::iterator it=dev.get_main_attributes()->begin();
         it!=dev.get_main_attributes()->end(); it++ ){
        
        for(map<string,string>::iterator in_it=it->begin();in_it!=it->end();in_it++){
            os <<"\""<< in_it->first <<"\" = \""
            <<in_it->second<<"\"\n";
        } 
    }

    for (vector<map<string,map<string,pair<string,double> > > >::iterator 
                    i =dev.get_specs()->begin();i!=dev.get_specs()->end();i++){
        
        for (map<string,map<string,pair<string,double> > >::iterator it=i->begin();it!=i->end();it++){
            if (it->second.size()>0)
                os<<it->first<<" = {\n";
            for (map<string,pair<string,double> >::iterator in_it=it->second.begin();in_it!=it->second.end();in_it++){
                os<<"\t\""<<in_it->first<<"\" = \"";
                if (in_it->second.first=="")
                    os<<in_it->second.second;
                else
                    os<<in_it->second.first;
                os<<"\"\n";
            }
            if (it->second.size()>0)
                os<<"\t}\n";            
        }
    }


    return os;
}
