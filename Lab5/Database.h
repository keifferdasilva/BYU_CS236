#pragma once
#include "Parser.h"
#include "Relation.h"
#include <map>


class Database{
private:
    map<string, Relation> relations;
public:
    Database() {}
    
    

    void insert(Relation r){
        relations.insert({r.getName(),r});
    }

    Relation getRelationCopy(string name){
        return relations.at(name);
    }

    Relation& getRelationReference(string name){
        return relations.at(name);
    }

    unsigned int size(){
        unsigned int count = 0;
        for(auto pairP : relations){
            count += pairP.second.size();
        }
        return count;
    }

    string toString(){
        ostringstream os;
        for(auto pairP : relations){
            os << pairP.first << endl;
            os << pairP.second.toString() << endl;
        }
        return os.str();
    }

    
    
};