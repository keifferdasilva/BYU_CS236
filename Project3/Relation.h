#pragma once
#include "Tuple.h"
#include <set>

class Relation{

private:
    string name;
    Scheme scheme;
    set<Tuple> tuples;

public:
    Relation(const string& name, const Scheme& scheme) 
    : name(name), scheme(scheme) {}
    Relation() : name(""), scheme(){}

    void addTuple(const Tuple& tuple){
        tuples.insert(tuple);
    }

    string getName() const{
        return name;
    }

    string toString() const{
        std::ostringstream os;
        for(auto& tuple : tuples){
            if(tuple.size() == 0){
                os << "";
            }
            else{
                os << "  " << tuple.toString(scheme) << endl;
            }
        }
        return os.str();
    }

    Relation select(int index, const string& value) const{
        Relation result(name, scheme);
        for(auto& tuple : tuples){
            if(tuple.at(index) == value){
                result.addTuple(tuple);
            }
        }
        return result;
    }

    //select all tuples whose values are equal at the two columns, e.g. a(X,X)
    Relation select(int index1, int index2){ 
        Relation result(name, scheme);
        for(auto& tuple : tuples){
            if(tuple.at(index1) == tuple.at(index2)){
                result.addTuple(tuple);
            }
        }
        return result;
    }

    //create a new relation with new scheme names but with the same name and tuples
    Relation rename(vector<string> newNames){ 
        Relation result(name, Scheme(newNames,name));
        for(auto& tuple : tuples){
            result.addTuple(tuple);
        }      
        return result;
    }

    unsigned int size(){
        return tuples.size();
    }

    /*create a new relation with the columns we want to keep from
    the original relation */
    Relation project(vector<unsigned int> colsToKeep){ 
        //create a relation with the new scheme
        vector<string> namesToKeep;
        for(size_t i = 0; i < colsToKeep.size(); i++){
            namesToKeep.push_back(scheme.at(colsToKeep.at(i)));
        }
        Relation result(name,Scheme(namesToKeep, name));
        
        //create new tuples based on the new scheme and add to result
        for(auto& tuple : tuples){
            vector<string> valsToKeep;
            for(size_t i = 0; i < colsToKeep.size(); i++){
                valsToKeep.push_back(tuple.at(colsToKeep.at(i)));
            }
            Tuple newTuple(valsToKeep);
            result.addTuple(newTuple);
        }
        return result;
    }
};