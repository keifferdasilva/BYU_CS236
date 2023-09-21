#pragma once
#include "Rule.h"

class Datalog{
private:
    vector<Rule> rules;
    vector<Predicate> facts;
    vector<Predicate> schemes;
    vector<Predicate> queries;

public:
    Datalog(){}

    void addRules(const Rule& r){
        rules.push_back(r);
    }

    void addFacts(const Predicate& f){
        facts.push_back(f);
    }

    void addSchemes(const Predicate& s){
        schemes.push_back(s);
    }

    void addQueries(const Predicate& q){
        queries.push_back(q);
    }

    std::string getRules() const{
        std::ostringstream os;
        for(size_t i = 0; i < rules.size(); i++){
            os << "  " << rules.at(i) << endl;
        }
        return os.str();
    }

    std::string getFacts() const{
        std::ostringstream os;
        for(size_t i = 0; i < facts.size(); i++){
            os << "  " << facts.at(i) << "." << endl;
        }
        return os.str();
    }

    std::string getSchemes() const{
        std::ostringstream os;
        for(size_t i = 0; i < schemes.size(); i++){
            os << "  " << schemes.at(i) << endl;
        }
        return os.str();
    }

    std::string getQueries() const{
        std::ostringstream os;
        for(size_t i = 0; i < queries.size(); i++){
            os << "  " << queries.at(i) << "?" << endl;
        }
        return os.str();
    }

    std::string toString() const{
        std::ostringstream os;
        std::string schemesString = getSchemes();
        std::string factsString = getFacts();
        std::string rulesString = getRules();
        std::string queriesString = getQueries();
        os << "Schemes(" << schemes.size() << "):" << endl << schemesString;
        os << "Facts(" << facts.size() << "):" << endl << factsString;
        os << "Rules(" << rules.size() << "):" << endl << rulesString;
        os << "Queries(" << queries.size() << "):" << endl << queriesString;
        return os.str();
    }

    friend ostream& operator<<(ostream& os, const Datalog& d){
        os << d.toString();
        return os;
    }

};