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

    //check to see if the parameter is a variable or constant
    bool isConst(){ 
        if(p[0] == '\''){
            return true;
        }
        else{
            return false;
        }
    }

    friend ostream& operator<<(ostream& os, const Parameter& p){
        os << p.toString();
        return os;
    }
};