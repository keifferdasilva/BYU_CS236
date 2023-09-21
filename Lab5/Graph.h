#pragma once
#include "Node.h"
#include <map>

class Graph{
private:
    map<int,Node> nodes;

public:
    Graph(int size){
        for(int nodeID = 0; nodeID < size; nodeID++){
            nodes[nodeID] = Node();
        }
    }

    void addEdge(int fromNodeID, int toNodeID){
        nodes[fromNodeID].addEdge(toNodeID);
    }

    string toString() const{
        ostringstream os;
        for(auto& pair: nodes){
            int nodeID = pair.first;
            const Node& node = pair.second;

            os << "R" << nodeID << ":" << node.toString() << endl;
        }

        return os.str();
    }
};