#pragma once
#include <vector>
#include "Token.h"
#include "Datalog.h"
#include "Predicate.h"
#include "Parameter.h"
#include "Rule.h"
#include <iostream>
#include <set>
using std::cout;

class Parser{
private:
    std::vector<Token> tokens;
    Datalog dataProgram;
    std::vector<Predicate> facts;
    std::vector<Predicate> schemes;
    std::vector<Predicate> queries;
    std::vector<Predicate> preds;
    std::set<std::string> strings;
    std::vector<Rule> rules;

public:
    Parser(const std::vector<Token>& vt): tokens(vt){}
    
    TokenType tokenType() const{
        if(tokens.size() <= 0){
            throw string("There are no more tokens and we did not reach EOF");
        }
        return tokens.at(0).getType();
    }

    void advanceToken(){
        tokens.erase(tokens.begin());
    }

    void throwError(){
        throw(tokens.at(0));
    }


    std::string match(TokenType t) {
        //cout << "match: " << t << endl;
        if (tokenType() == t){
            std::string returnVal = tokens.at(0).getValue();
            advanceToken();
            return returnVal;
        }
        else{
            throwError();
            return "";
        }
    }

    /* datalogProgram	->	SCHEMES COLON scheme schemeList
		                    FACTS COLON factList
		                    RULES COLON ruleList
		                    QUERIES COLON query queryList
			                EOF
    */
    //TODO: add all predicates/rules to a datalog object
    void parse(){
        if(tokenType() == SCHEMES){
            match(SCHEMES);
            match(COLON);
            scheme();
            schemeList();
            
            match(FACTS);
            match(COLON);
            factList();

            match(RULES);
            match(COLON);
            ruleList();

            match(QUERIES);
            match(COLON);
            query();
            queryList();
            match(ENDOFFILE);
            //test toString of preds
            /*for(size_t i = 0; i < preds.size(); i++){
                cout << preds.at(i).toString() << endl;
            }*/
            //test strings
            cout << "Success!" << endl;
            //cout << dataProgram.getRules();
            cout << dataProgram.toString();
            cout << "Domain(" << strings.size() << "):" << endl;
            
            for(set<string>::const_iterator iter = strings.begin(); iter != strings.end(); iter++){
                cout << "  " << *iter << endl;
            }
        }
    }

    //schemeList	->	scheme schemeList | lambda
    void schemeList(){
        if(tokenType() == ID){
            scheme();
            schemeList(); 
        }
        else{
            //lambda
        }
    }

    //factlist -> fact factList | lambda
    void factList(){
        if(tokenType() == ID){
            fact();
            factList();
        }
        else{
            //lambda
        }
    }

    //rulelist -> rule ruleList | lambda
    void ruleList(){
        if(tokenType() == ID){
            rule();
            ruleList();
        }
        else{
            //lambda
        }
    }

    //queryList	->	query queryList | lambda
    void queryList(){
        if(tokenType() == ID){
            query();
            queryList();
        }
        else{
            //lambda
        }
    }
    
    //scheme   	-> 	ID LEFT_PAREN ID idList RIGHT_PAREN
    void scheme(){
        if(tokenType() == ID){
            Predicate pred(match(ID));
            match(LEFT_PAREN);
            pred.addValue(match(ID));
            idList(pred);
            match(RIGHT_PAREN);
            dataProgram.addSchemes(pred);
            preds.push_back(pred);
        }
        else{
            throwError();
        }
    }

    //fact    	->	ID LEFT_PAREN STRING stringList RIGHT_PAREN PERIOD
    void fact(){
        if(tokenType() == ID){
            Predicate pred(match(ID));
            match(LEFT_PAREN);
            strings.insert(tokens.at(0).getValue());
            pred.addValue(match(STRING));
            stringList(pred);
            match(RIGHT_PAREN);
            match(PERIOD);
            preds.push_back(pred);
            dataProgram.addFacts(pred);
        }
        else{
            throwError();
        }
    }

    //rule    	->	headPredicate COLON_DASH predicate predicateList PERIOD
    void rule(){
        if(tokenType() == ID){
            
            Predicate head = headPredicate();
            match(COLON_DASH);
            Predicate pred1 = predicate();
            vector<Predicate> predList;
            predicateList(predList);
            match(PERIOD);

            Rule rule(head);
            rule.addValue(pred1);
            for(size_t i = 0; i < predList.size(); i++){
                rule.addValue(predList.at(i));
            }
            rules.push_back(rule);
            dataProgram.addRules(rule);

        }
        else{
            throwError();
        }
    }

    //query	        ->      predicate Q_MARK
    void query(){
        if(tokenType() == ID){
            Predicate pred = predicate();
            match(Q_MARK);
            preds.push_back(pred);
            dataProgram.addQueries(pred);
        }
        else{
            throwError();
        }
    }

    //parameter	->	STRING | ID
    void parameter(Predicate& p){
        if(tokenType() == STRING){
            p.addValue(match(STRING));
        }
        else if(tokenType() == ID){
            p.addValue(match(ID));
        }
        else{
            throwError();
        }
    }

    //headPredicate	->	ID LEFT_PAREN ID idList RIGHT_PAREN
    Predicate headPredicate(){
        if(tokenType() == ID){
            Predicate pred(match(ID));
            match(LEFT_PAREN);
            pred.addValue(match(ID));
            idList(pred);
            match(RIGHT_PAREN);
            return pred;
        }
        else{
            throwError();
            Predicate errPred("error");
            return errPred;
        }
    }

    //predicate	->	ID LEFT_PAREN parameter parameterList RIGHT_PAREN
    Predicate predicate(){
        if(tokenType() == ID){
            Predicate pred(match(ID));
            match(LEFT_PAREN);
            parameter(pred);
            parameterList(pred);
            match(RIGHT_PAREN);
            return pred;
        }
        else{
            throwError();
            Predicate errPred("error");
            return errPred;
        }
    }

    //predicateList	->	COMMA predicate predicateList | lambda
    void predicateList(vector<Predicate>& predicates){
        if(tokenType() == COMMA){
            match(COMMA);
            predicates.push_back(predicate());
            predicateList(predicates);
        }
        else{
            //lambda
        }
    }

    //parameterList	-> 	COMMA parameter parameterList | lambda
    void parameterList(Predicate& p){
        if(tokenType() == COMMA){
            match(COMMA);
            parameter(p);
            parameterList(p);
        }
        else{
            //lambda
        }
    }

    //stringList	-> 	COMMA STRING stringList | lambda
    void stringList(Predicate& p){
        if(tokenType() == COMMA){
            match(COMMA);
            strings.insert(tokens.at(0).getValue());
            p.addValue(match(STRING));
            stringList(p);
        }
        else{
            //lambda
        }
    }

    //idList -> COMMA ID idList | lambda
    void idList(Predicate& p) {
        if (tokenType() == COMMA){
            match(COMMA);
            p.addValue(match(ID));
            idList(p);
        } 
        else{
        // lambda
        }
    }

    

};