#include "Relation.h"
#include <iostream>
using namespace std;

int main(int argc, char* argv[]){

    vector<string> names = {"ID", "Name", "Major"};
    Scheme scheme(names,"students");
    Relation relation("student", scheme);

    vector<string> values[] = {
        {"'42'", "'Ann'", "'CS'"},
        {"'32'", "'Bob'", "'CS'"},
        {"'64'", "'Ned'", "'EE'"},
        {"'16'", "'Jim'", "'EE'"},
    };

    for(auto& value : values){
        Tuple tuple(value);
        cout << tuple.toString(scheme) << endl;
        relation.addTuple(tuple);
    }

    cout << "relation:" << endl;
    cout << relation.toString();
    
    vector<string> newNames = {"A", "B", "C"};

    Relation result = relation.rename(newNames);

    cout << "rename result:" << endl;
    cout << result.toString();
    vector<unsigned int> columns = {1,2,0};

    Relation result1 = relation.project(columns);
    cout << endl << "project result:" << endl;
    cout << result1.toString();
}