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

    bool addTuple(const Tuple& tuple){
        return tuples.insert(tuple).second;
    }

    Scheme getScheme(){
        return scheme;
    }

    string getName() const{
        return name;
    }

    set<Tuple> getTuples(){
        return tuples;
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

    /*static bool joinable(const Scheme& leftScheme, const Scheme& rightScheme,
	const Tuple& leftTuple, const Tuple& rightTuple) {
        return true;
        
    }*/

    Scheme combineSchemes(Scheme& s1, Scheme& s2, vector<unsigned int> uniqueColumns){
        Scheme output;
        for(unsigned int i = 0; i < s1.size(); i++){
            output.push_back(s1.at(i));
        }
        
        for(unsigned int i = 0; i < uniqueColumns.size(); i++){
            output.push_back(s2.at(uniqueColumns.at(i)));
        }

        return output;
    }

    static bool joinable(Tuple t1, Tuple t2, vector<pair<unsigned int, unsigned int>> overlap){
        for(pair<unsigned int, unsigned int> p : overlap){
            if(t1.at(p.first) != t2.at(p.second)){
                return false;
            }
        }
        return true;
    }

    Tuple combineTuples(Tuple t1, Tuple t2, vector<unsigned int> uniqueColumns){
        vector<string> newVals;
        for(unsigned int i = 0; i < t1.size(); i++){
            newVals.push_back(t1.at(i));
        }

        for(unsigned int j = 0; j < t2.size(); j++){
            for(unsigned int k = 0; k < uniqueColumns.size(); k++){
                if(j == uniqueColumns.at(k)){
                    newVals.push_back(t2.at(j));
                }
            }
        }

        Tuple result(newVals);
        return result;

    }

    Relation natJoin(Relation r1, Relation r2){
        Relation result;
        result.name = (r1.getName() + r2.getName());
        //indentify overlap in the schemes
        vector<pair<unsigned int, unsigned int>> overlap; //first int is index and second int is relation
        //e.g.
        //A B C D
        //D C B A F
        //{(0,3), (1,2), (2,1), (3,0)}
        vector<unsigned int> uniqueCols;
        //Unique cols is {0}

        for(unsigned int i = 0; i < r2.scheme.size(); i++){
            bool isUnique = true;
            for(unsigned int j = 0; j < r1.scheme.size(); j++){
                if(r1.scheme.at(j) == r2.scheme.at(i)){
                    overlap.push_back({j,i});
                    isUnique = false;
                }
            }
            if(isUnique){
                uniqueCols.push_back(i);
            }
        }
        //combine schemes
        result.scheme = combineSchemes(r1.scheme, r2.scheme, uniqueCols);
        
        
        //for each tuple combine them if they are combinable
        for(Tuple tuple1 : r1.tuples){
            for(Tuple tuple2 : r2.tuples){
                if(joinable(tuple1, tuple2, overlap)){
                    Tuple newTuple = combineTuples(tuple1, tuple2, uniqueCols); //insert combined tuples into result relation.
                    result.addTuple(newTuple);
                }
            }
        }
        
        return result;
    }

    void unionize(Relation toAdd){
        if(this->scheme != toAdd.getScheme()){
            throw "Cannot combine because the schemes are different";
        }

        for(Tuple tuple : toAdd.getTuples()){
            if(addTuple(tuple)){
                if(tuple.size() > 0){
                    cout << "  " << tuple.toString(scheme) << endl;
                }
            }
        }
    }
};