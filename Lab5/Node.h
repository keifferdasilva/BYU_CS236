#pragma once
#include <set>
#include <sstream>
using namespace std;

class Node{

private:
    set<int> adjacentNodeIDs;
    bool visited;
    int postOrderNum;

public:

    void addEdge(int adjacentNodeID){
        adjacentNodeIDs.insert(adjacentNodeID);
    }

    string toString() const{
        ostringstream os;
        string output;
        for(auto& nodeID : adjacentNodeIDs){
            os << "R" << nodeID << ",";
        }

        output = os.str();
        if(output.length() > 0){
            output.erase(output.length()-1, 1);
        }
        return output;
    }

};