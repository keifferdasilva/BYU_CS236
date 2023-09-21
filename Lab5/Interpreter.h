#include "Database.h"
#include "Datalog.h"
#include "Graph.h"

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
        evalRules();
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
        cout << "Query Evaluation" << endl;
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

    void evalRules(){
        cout << "Rule Evaluation" << endl;
        unsigned int sizeBefore = 0;
        unsigned int sizeAfter = 0;
        int numPasses = 0;
        do{
            numPasses++;
            sizeBefore = database.size();
            singlePass(program.getRulesVector());
            sizeAfter = database.size();
        }while(sizeBefore != sizeAfter);
        
        cout << endl << "Schemes populated after " << numPasses << " passes through the Rules." << endl << endl;
    }

    void singlePass(vector<Rule> rules){
        for(Rule r : rules){
            cout << r.toString() << endl;
            vector<Relation> bodyRelations;
            for(Predicate p : r.getBody()){ //convert all the rules into relations
                Relation currRelation = evaluatePredicate(p);
                bodyRelations.push_back(currRelation);
            }

            Relation result = bodyRelations.at(0);
            for(unsigned int i = 1; i < bodyRelations.size(); i++){ //combine all the relations into one
                result = result.natJoin(result, bodyRelations.at(i));
            }
            vector<unsigned int> ruleCols;
            for(unsigned int i = 0; i < r.getHead().getParams().size(); i++){
                for(unsigned int j = 0; j < result.getScheme().size(); j++){
                    if(r.getHead().getParams().at(i) == result.getScheme().at(j)){
                        ruleCols.push_back(j);
                    } 
                }
            }

            result = result.project(ruleCols);

            string name = r.getHead().getId();
            result = result.rename(database.getRelationReference(name).getScheme());

            database.getRelationReference(name).unionize(result);
            //join all the body predicates of the rule into one Rule
                //for each body predicate call evaluatePredicate
                //join all those into relation currRelation
            //project cols that are in head 
                //scan through head parameters and match them up with body  relation
            //rename cols
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


    static Graph makeGraph(const vector<Rule>& rules){
        Graph graph(rules.size());
        for(unsigned int fromID = 0; fromID < rules.size(); fromID++){
            const Rule& fromRule = rules.at(fromID);
            //cout << "from rule R" << fromID << ": " << fromRule.toString() << endl;
            for(unsigned int pred = 0; pred < fromRule.size(); pred++){
                const Predicate& bodyPred = fromRule.getBodyPredicate(pred);
                //cout << "from body predicate: " << bodyPred.toString() << endl;
                for(unsigned int toID = 0; toID < rules.size(); toID++){
                    const Rule& toRule = rules.at(toID);
                    //cout << "to rule R" << toID << ": " << toRule.toString() << endl;
                    if(fromRule.getBodyPredicate(pred).getId() == toRule.getHead().getId()){
                        //cout << "dependency found: (R" << fromID << ",R" << toID << ")" << endl;
                        graph.addEdge(fromID, toID);
                    }
                }
            }
        }
        return graph;
    }
};