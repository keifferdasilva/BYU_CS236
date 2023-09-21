#pragma once
#include "Node.h"
#include <map>
#include <vector>
#include <stack>

class Graph{
private:
    map<int,Node> nodes;
    map<int,Node> reverseNodes;
    stack<int> workingStack;
    set<int> workingSet;

public:
    Graph(int size){
        for(int nodeID = 0; nodeID < size; nodeID++){
            nodes[nodeID] = Node();
            reverseNodes[nodeID] = Node();
        }
    }

    Node getNode(int index){
        return nodes[index];
    }

    void addEdge(int fromNodeID, int toNodeID){
        nodes[fromNodeID].addEdge(toNodeID);
    }

    void makeReverseGraph(){
        for(auto node: nodes){
            for(auto adjacentNode : node.second.getChildren()){
                reverseNodes[adjacentNode].addEdge(node.first);
            }
        }
    }

    stack<int> DFS(int startNode){
        stack<int> emptyStack;
        if(reverseNodes[startNode].getVisited()){
            return emptyStack;
        }

        reverseNodes[startNode].setVisited(true);
        for(auto childID : reverseNodes[startNode].getChildren()){
            if(!reverseNodes[childID].getVisited()){
                DFS(childID);
            }
        }
        workingStack.push(startNode);
        return workingStack;
    }

    stack<int> DFSForest(){
        for(unsigned int i = 0; i < nodes.size(); i++){
            if(!reverseNodes[i].getVisited()){
                DFS(i);
            }
        }
        return workingStack;
    }

    set<int> DFS_SCC(int startNode){
        set<int> emptySet;
        if(nodes[startNode].getVisited()){
            return emptySet;
        }
        set<int> result;

        nodes[startNode].setVisited(true);
        for(auto& childID : nodes[startNode].getChildren()){
            if(!nodes[childID].getVisited()){
                set<int> tempResult = DFS_SCC(childID);
                for(int item : tempResult){
                    result.insert(item);
                }
            }
        }
        result.insert(startNode);
        return result;
    }

    vector<set<int>> DFSForest_SCC(stack<int> priorQueue){
        vector<set<int>> SCCs;
        for(auto& node : nodes){
            node.second.setVisited(false);
        }
        while(!priorQueue.empty()){
            int i = priorQueue.top();
            priorQueue.pop();
            if(!nodes[i].getVisited()){
                SCCs.push_back(DFS_SCC(i));
            }
        }
        return SCCs;
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

    string reverseToString() const{
        ostringstream os;
        for(auto& pair: reverseNodes){
            int nodeID = pair.first;
            const Node& node = pair.second;

            os << "R" << nodeID << ":" << node.toString() << endl;
        }

        return os.str();
    }

    string postOrderNums(){
        std::ostringstream os;
        while(!workingStack.empty()){
            os << "R" << workingStack.top() << endl;
            workingStack.pop();
        }
        return os.str();
    }
};