#include "Node.h"
#include "Graph.h"
#include <iostream>
#include <vector>
#include "Interpreter.h"
using namespace std;

int main(int argc, char* argv[]){

  // predicate names for fake rules
  // first is name for head predicate
  // second is names for body predicates
    pair<string,vector<string>> ruleNames[] = {
        { "A", { "B", "C" } },
        { "B", { "A", "D" } },
        { "B", { "B" } },
        { "E", { "F", "G" } },
        { "E", { "E", "F" } },
    };

  vector<Rule> rules;

  for (auto& rulePair : ruleNames) {
    string headName = rulePair.first;
    Rule rule = Rule(Predicate(headName));
    vector<string> bodyNames = rulePair.second;
    for (auto& bodyName : bodyNames)
      rule.addValue(Predicate(bodyName));
    rules.push_back(rule);
  }

  Graph graph = Interpreter::makeGraph(rules);
  cout << graph.toString();

}