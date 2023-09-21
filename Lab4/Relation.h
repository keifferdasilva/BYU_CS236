#pragma once
#include "Tuple.h"
#include <set>
#include <iostream>

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

    static bool joinable(const Scheme& leftScheme, const Scheme& rightScheme,
	const Tuple& leftTuple, const Tuple& rightTuple) {
        for (unsigned leftIndex = 0; leftIndex < leftScheme.size(); leftIndex++) {
            const string& leftName = leftScheme.at(leftIndex);
            const string& leftValue = leftTuple.at(leftIndex);
            std::cout << "left name: " << leftName << " value: " << leftValue << endl;
            for (unsigned rightIndex = 0; rightIndex < rightScheme.size(); rightIndex++) {
                bool schemeOverlap = false;
                const string& rightName = rightScheme.at(rightIndex);
                const string& rightValue = rightTuple.at(rightIndex);
                cout << "right name: " << rightName << " value: " << rightValue << endl;
                if(leftName == rightName){
                    schemeOverlap = true;
                }
                if(schemeOverlap && (rightValue != leftValue)){
                    return false;
                }
            }
        }

        return true;
        
    }

    Relation join(const Relation& r){
        const Scheme& leftScheme = scheme;
        const Scheme& rightScheme = r.scheme;
        for (const Tuple& leftTuple : tuples){
            cout << "left tuple: " << leftTuple.toString(leftScheme) << endl;
            for (const Tuple& rightTuple : r.tuples){
                cout << "right tuple: " << rightTuple.toString(rightScheme) << endl;
            }
        }
        
        return Relation();
    }
};