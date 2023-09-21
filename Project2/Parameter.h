#pragma once
#include <string>
using std::string;

class Parameter{
private:
    string p;
public:
    Parameter(string s) : p(s){}

    void setString(const string& s){
        p = s;
    }

    string toString() const{
        return p;
    }

    friend ostream& operator<<(ostream& os, const Parameter& p){
        os << p.toString();
        return os;
    }
};