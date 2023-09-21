#pragma once
#include "Predicate.h"
#include <vector>
using std::vector;

class Rule{
private:
    Predicate headPredicate;
    vector<Predicate> bodyPredicates;
public:
    Rule(Predicate head) : headPredicate(head){}

    void addValue(Predicate p){
        bodyPredicates.push_back(p);
    }

    vector<Predicate> getBody(){
        return bodyPredicates;
    }

    Predicate getHead(){
        return headPredicate;
    }

    std::string toString() const{
        std::ostringstream os;
        os << headPredicate << " :- ";
        for(size_t i = 0; i < bodyPredicates.size(); i++){
            if(i == 0){
                os << bodyPredicates.at(i);
            }
            else{
                os << "," << bodyPredicates.at(i);
            }
        }
        os << ".";
        return os.str();
    }

    friend ostream& operator<<(ostream& os, const Rule& r){
        os << r.toString();
        return os;
    }

};