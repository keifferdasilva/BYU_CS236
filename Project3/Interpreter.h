#include "Database.h"
#include "Datalog.h"

class Interpreter{
private:
    Datalog program;
    Database database;
    vector<Scheme> relationSchemes;

public:
    Interpreter(Datalog program) : program(program){}

    void run(){
        evalSchemes();
        evalFacts();
        evalQueries();
    }

    void evalSchemes(){
        vector<Predicate> sch = program.getSchemesVector();
        for(size_t i = 0; i < sch.size(); i++){
            Scheme scheme(sch.at(i).getParams(),sch.at(i).getId());
            Relation newRelation(scheme.name, scheme);
            database.insert(newRelation);
        }
    }

    //convert schemes from predicates to Scheme class
    void convertSchemes(){
        
    }

    void evalFacts(){
        for(Predicate fact : program.getFactsVector()){
            Relation& r = database.getRelationReference(fact.getId());
            Tuple tuple(fact.getParams());
            r.addTuple(tuple);
        }
    }

    void evalQueries(){
        for(Predicate query : program.getQueriesVector()){
            Relation r = evaluatePredicate(query);
            cout << query << "?";
            if(r.size() > 0){
                cout << " Yes(" << r.size() << ")" << endl;
                cout << r.toString();
            }
            else{
                cout << " No" << endl;
            }
            //cout << r.toString();
        }

    }

    Relation evaluatePredicate(Predicate pred){
        Relation currRel = database.getRelationCopy(pred.getId());
        vector<unsigned int> colsToKeep;
        vector<string> names;

        for(size_t i = 0; i < pred.getParams().size(); i++){
            Parameter currParam = pred.getParams().at(i);
            if(currParam.isConst()){
                currRel = currRel.select(i, currParam.toString()); //If the parameter is a constant, select all from the relation with the same constant value at the pos
            }
            else{
                bool seenBefore = false;
                unsigned int j = 0;
                //loop that checks through names if currParam is found, set seenBefore to true
                for(j = 0; j < names.size(); j++){
                    if(currParam.toString() == names.at(j)){
                        seenBefore = true;
                        break;
                    }
                }
                
                //if seen before is true, do a type 2 select
                if(seenBefore){
                    currRel = currRel.select(i, colsToKeep.at(j)); 
                }
                //if not, add the current param in cols to keep and names.
                else{
                    colsToKeep.push_back(i);
                    names.push_back(currParam.toString());
                }
            }
        }

        currRel = currRel.project(colsToKeep);
        currRel = currRel.rename(names);
        return currRel;
    }

};