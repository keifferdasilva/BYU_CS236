#pragma once
#include <set>
#include <sstream>
using namespace std;

class Node{

private:
    set<int> adjacentNodeIDs;
    bool visited;
    int nodeID;

public:
    Node(int id) : nodeID(id){
        visited = false;
    }

    Node(){
        visited = false;
    }

    void addEdge(int adjacentNodeID){
        adjacentNodeIDs.insert(adjacentNodeID);
    }

    bool getVisited() const{
        return visited;
    }

    void setVisited(bool val){
        visited = val;
    }

    set<int> getChildren() const{
        return adjacentNodeIDs;
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