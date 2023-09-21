#include "Relation.h"
#include <iostream>
using namespace std;

int main(int argc, char* argv[]){

    /*vector<string> names = {"ID", "Name", "Major"};
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
    cout << result1.toString();*/

    Scheme scheme1( { "A", "B" }, "scheme 1");
    Scheme scheme2( { "B", "C" }, "scheme 2");

    Tuple tuple1( {"'1'", "'2'"} );
    Tuple tuple2( {"'3'", "'4'"} );


    Scheme scheme3( { "X", "Y" }, "scheme 3");
    Scheme scheme4( { "X", "Y", "Z" }, "scheme 4");

    Tuple tuple3( {"'1'", "'4'"} );
    Tuple tuple4( {"'1'", "'2'", "'4'"} );

    /*cout << Relation::joinable(scheme1, scheme2, tuple1, tuple2) << endl;
    cout << Relation::joinable(scheme2, scheme3, tuple1, tuple2) << endl;
    cout << Relation::joinable(scheme3, scheme4, tuple1, tuple4) << endl;
    cout << Relation::joinable(scheme3, scheme4, tuple3, tuple4) << endl;*/

      Relation studentRelation("students", Scheme( {"ID", "Name", "Major"}, "students"));

    vector<string> studentValues[] = {
        {"'42'", "'Ann'", "'CS'"},
        {"'64'", "'Ned'", "'EE'"},
    };

    for (auto& value : studentValues){
        studentRelation.addTuple(Tuple(value));
    }

    Relation courseRelation("courses", Scheme( {"ID", "Course"}, "courses"));

    vector<string> courseValues[] = {
        {"'42'", "'CS 100'"},
        {"'32'", "'CS 232'"},
    };

    for (auto& value : courseValues){
        courseRelation.addTuple(Tuple(value));
    }
    studentRelation.join(courseRelation);
}