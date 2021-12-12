# Topology_API
An API for reading and writing JSON files of electronic devices' topologies

It helps :

  -Read a topology from a given JSON file and store it in the memory.
  
  -Write a given topology from the memory to a JSON file.
  
  -Query about which topologies are currently in the memory.
  
  -Delete a given topology from memory.
  
  -Query about which devices are in a given topology.
  
  -Query about which devices are connected to a given netlist node in a given topology.
  
# Linux Installing
  
    git clone https://github.com/Abdelrahman-Bishr/Topology_API/new/main

    sudo apt-get install libjsoncpp-dev
    
    
# Compiling

      g++ main.cpp Topology.cpp API.cpp device.cpp -ljsoncpp -o main
      

# API Public Functions
  
###      Topology * readJSON(string filename) 
        Loads a topology from a json file into memory
  #####      Arguments:
            filename : an std::string describing full path to json file containing the required topology
  #####      Returns:
            A pointer to the loaded topology in memory
  
###      bool writeJSON(string topologyID,string filename)
        Writes a topology from memory into a json file
  #####      Arguments:
            topologyID : an std::string specifying the ID of the topology to be saved 
            filename : an std::string describing full path to json file where the topology is to be saved
  #####      Returns:
            A bool indicating save success or failure
    
###      std::vector<Topology*> & queryTopologies()
        returns a vector of the topologies that are currently in  memory
  #####      Returns:
            An std::vector of pointers to the topologies in memory 
        
###      bool deleteTopology(string topologyID)
        deletes a specified topology from memory
  #####      Arguments:
to          pologyID : an std::string specifying the ID of the topology to be deleted
  #####      Returns:
            A bool indicating delete success or failure
        
###      vector<Device*> &queryDevices(string TopologyID)
        Returns a vector of the devices of the specified topology that resides in memory 
  #####      Arguments:
            topologyID : an std::string specifying the ID of the topology whose devices are to be returned 
  #####      Returns:
            An std::vector of pointers to the devices in memory.
    
###      vector<Device*> queryDevicesWithNetlistNode(string TopologyID,string NetlistNodeID)
        Returns a vector of the devices of the specified topology that are connected to the specified netlistNode 
  #####      Arguments:
            topologyID : an std::string specifying the ID of the topology whose devices are to be returned 
            NetlisNodeID : an std::string specifying the ID of the node that the devices are connected by. 
  #####      Returns:
            A copy of an std::vector of pointers to the devices in memory.
              

  