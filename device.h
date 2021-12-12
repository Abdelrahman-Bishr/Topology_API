#ifndef DEVICE_H
#define DEVICE_

#include <jsoncpp/json/value.h>
#include <bits/stdc++.h>
using namespace std;

typedef vector<map<string, map<string,pair<string,double> > > > specs_vec;
typedef map<string,pair<string,double> >  specs_map;
typedef vector<map<string,string> > attributes_vec; 

class Device
{
public:
    Device(Json::Value &component);
    ~Device();

    string get_id();
    vector<map<string,string> > * get_main_attributes();
    vector<map<string, map<string,pair<string,double> > > > * get_specs(); 
    
    friend ostream& operator<<(ostream& os, Device & dev);

private:
    string id;
    vector<map<string,string> > * main_attributes;
    vector<map<string, map<string,pair<string,double> > > > * specs; 

};




#endif  // DEVICE_H