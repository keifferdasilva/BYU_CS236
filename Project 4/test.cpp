#include "Relation.h"
#include <iostream>
using namespace std;

int main(int argc, char* argv[]){

    vector<string> names = {"ID", "Name", "Major"};
    vector<string> names1 = {"Name", "Address"};
    Scheme scheme1(names1, "SN");
    Scheme scheme(names,"students");
    Relation relation("student", scheme);
    Relation relation1("SN", scheme1);

    vector<string> values[] = {
        {"'42'", "'Ann'", "'CS'"},
        {"'32'", "'Bob'", "'CS'"},
        {"'64'", "'Ned'", "'EE'"},
        {"'16'", "'Jim'", "'EE'"},
    };

    vector<string> values1[] = {
        {"'Ann'", "'1234 Birch'"},
        {"'Bob'", "'5678 Pine'"},
        {"'Ned'", "'2468 Aspen'"},
        {"'Jim'", "'1357 Apple'"},
    };

    for(auto& value : values){
        Tuple tuple(value);
        cout << tuple.toString(scheme) << endl;
        relation.addTuple(tuple);
    }

    for(auto& value : values1){
        Tuple tuple(value);
        //cout << tuple.toString(scheme) << endl;
        relation1.addTuple(tuple);
    }

    cout << "relation:" << endl;
    cout << relation.toString();

    cout << "Relation1:" << endl;
    cout << relation1.toString();
    
    /*vector<string> newNames = {"A", "B", "C"};

    Relation result = relation.rename(newNames);

    cout << "rename result:" << endl;
    cout << result.toString();*/
    vector<unsigned int> columns = {1,2,0};

    Relation result1 = relation.project(columns);
    cout << endl << "project result:" << endl;
    cout << result1.toString();

    
    cout << endl << "natJoin:" << endl;
    Relation result = result.natJoin(relation, relation1);
    cout << result.toString();
}