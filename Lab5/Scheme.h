#pragma once
#include <vector>
#include <string>
using namespace std;

class Scheme : public vector<string>{
public:
    string name;
    Scheme(vector<string> names, string label) : vector<string>(names), name(label) {}
    Scheme() : name("") {}

    

};