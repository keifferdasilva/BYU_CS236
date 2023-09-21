#pragma once
#include <string>
#include <vector>
#include <sstream>
#include "Parameter.h"
using std::string;

class Predicate{
private:
    string id;
    std::vector<Parameter> parameters;

public:
    Predicate(string s) : id(s){}
    void addValue(string val){
        parameters.push_back(Parameter(val));
    }

    string toString() const{
        std::ostringstream os;
        os << id << "(";
        for(size_t i = 0; i < parameters.size(); i++){
            if(i == 0){
                os << parameters.at(i).toString();
            }
            else{
                os << "," << parameters.at(i).toString();
            }
        }
        os << ")";
        return os.str();
    }

    friend ostream& operator<<(ostream& os, const Predicate& p){
        os << p.toString();
        return os;
    }

};