#pragma once
#include <vector>
#include <sstream>
#include "Scheme.h"

class Tuple : public vector<string>{
public:
    Tuple(vector<string> values) : vector<string>(values){}

    string toString(const Scheme& scheme) const{
        std::ostringstream os;
        for(size_t i = 0; i < size(); i++){
            if(i > 0){
                os << ", ";
            }
            const string& name = scheme.at(i);
            const string& value = at(i);
            os << name << "=" << value;
        }
        return os.str();
    }
};