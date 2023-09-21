#pragma once
#include <string>
#include <cctype>
#include <vector>
#include <sstream>
#include "Token.h"

class Scanner {
private:
    std::string input;
    std::vector<Token> Tokens;
    size_t numTokens;

public:
    Scanner(const std::string& in) : input(in), numTokens(0){}

    void scanToken(){
        TokenType type;
        size_t size = 0;
        int line = 1;
        int lineBuffer = 0;
        std::string value = "";
        while(input.size() > 0){

            while(isspace(input.at(0))){
                if(input.at(0) == '\n'){
                    ++line;
                }
                input = input.substr(1);
                if(input.size() <= 0){
                    break;
                }
            }

            if(input.size() <= 0){
                break;
            }

            switch(input.at(0)){
                case ',':
                    type = COMMA;
                    size = 1;
                    break;
                case '.':
                    type = PERIOD;
                    size = 1;
                    break;
                case '?':
                    type = Q_MARK;
                    size = 1;
                    break;
                case '(':
                    type = LEFT_PAREN;
                    size = 1;
                    break;
                case ')':
                    type = RIGHT_PAREN;
                    size = 1;
                    break;
                case ':':
                    if(input.size() > 1){
                        if(input.at(1) == '-'){
                            type = COLON_DASH;
                            size = 2;
                        }
                        else{
                            type = COLON;
                            size = 1;
                        }
                    }
                    else{
                        type = COLON;
                        size = 1;
                    }
                    break;
                case '*':
                    type = MULTIPLY;
                    size = 1;
                    break;
                case '+':
                    type = ADD;
                    size = 1;
                    break;
                case '\'':
                {
                size = 1;
                std::string inputString = input.substr(1);
                lineBuffer = 0;
                while(inputString.size() > 0){
                    if(inputString.at(0) == '\n'){
                        lineBuffer++;
                    }
                    if(inputString.at(0) != '\''){
                        inputString = inputString.substr(1);
                        size++;
                    }
                    else{
                        type = STRING;
                        size++;
                        break;
                    }
                }
                if(inputString.size() <= 0){
                    type = UNDEFINED;
                    break;
                }
                break;

                }
                case '#':
                {
                    size = 1;
                    type = COMMENT;
                    std::string inputString = input.substr(1);
                    while(inputString.size() > 0){
                        if(inputString.at(0) != '\n'){
                            inputString = inputString.substr(1);
                            size++;
                        }
                        else{
                            break;
                        }
                    }
                    break;
                }
                case 'F':
                {
                if(input.size() < 5){
                    size = 0;
                    for(size_t i = 0; i < input.size(); ++i){
                        if(isalpha(input.at(i)) || isdigit(input.at(i))){
                            size++;
                        }
                        else{
                            break;
                        }
                    }
                    type = ID;
                }

                else if(input.size() == 5){
                    type = FACTS;
                    size = 5;
                }

                else if(input.size() > 5){
                    if(input.substr(0,5) == "Facts" && !isalpha(input.at(5)) && !isdigit(input.at(5))){
                        type = FACTS;
                        size = 5;
                    }
                    else{
                        size = 0;
                        std::string inputString = input;
                        while(inputString.size() > 0){
                            if(isalpha(inputString.at(0)) || isdigit(inputString.at(0))){
                                inputString = inputString.substr(1);
                                size++;
                            }
                            else{
                                break;
                            }
                        }
                        type = ID; 
                    }
                }
                break;
                }

                case 'R':
                {
                if(input.size() < 5){
                    size = 0;
                    for(size_t i = 0; i < input.size(); ++i){
                        if(isalpha(input.at(i)) || isdigit(input.at(i))){
                            size++;
                        }
                        else{
                            break;
                        }
                    }
                    type = ID;
                }

                else if(input.size() == 5){
                    type = RULES;
                    size = 5;
                }

                else if(input.size() > 5){
                    if(input.substr(0,5) == "Rules" && !isalpha(input.at(5)) && !isdigit(input.at(5))){
                        type = RULES;
                        size = 5;
                    }
                    else{
                        size = 0;
                        std::string inputString = input;
                        while(inputString.size() > 0){
                            if(isalpha(inputString.at(0)) || isdigit(inputString.at(0))){
                                inputString = inputString.substr(1);
                                size++;
                            }
                            else{
                                break;
                            }
                        }
                        type = ID; 
                    }
                }
                break;
                }
                
                case 'S':
                {
                if(input.size() < 7){
                    size = 0;
                    for(size_t i = 0; i < input.size(); ++i){
                        if(isalpha(input.at(i)) || isdigit(input.at(i))){
                            size++;
                        }
                        else{
                            break;
                        }
                    }
                    type = ID;
                }

                else if(input.size() == 7){
                    type = SCHEMES;
                    size = 7;
                }

                else if(input.size() > 7){
                    if(input.substr(0,7) == "Schemes" && !isalpha(input.at(7)) && !isdigit(input.at(7))){
                        type = SCHEMES;
                        size = 7;
                    }
                    else{
                        std::string inputString = input;
                        size = 0;
                        while(inputString.size() > 0){
                            if(isalpha(inputString.at(0)) || isdigit(inputString.at(0))){
                                inputString = inputString.substr(1);
                                size++;
                            }
                            else{
                                break;
                            }
                        }
                        type = ID; 
                    }
                }
                break;
                }

                case 'Q':
                {
                if(input.size() < 7){
                    size = 0;
                    for(size_t i = 0; i < input.size(); ++i){
                        if(isalpha(input.at(i)) || isdigit(input.at(i))){
                            size++;
                        }
                        else{
                            break;
                        }
                    }
                    type = ID;
                }

                else if(input.size() == 7){
                    type = QUERIES;
                    size = 7;
                }

                else if(input.size() > 7){
                    if(input.substr(0,7) == "Queries" && !isalpha(input.at(7)) && !isdigit(input.at(7))){
                        type = QUERIES;
                        size = 7;
                    }
                    else{
                        std::string inputString = input;
                        size = 0;
                        while(inputString.size() > 0){
                            if(isalpha(inputString.at(0)) || isdigit(inputString.at(0))){
                                inputString = inputString.substr(1);
                                size++;
                            }
                            else{
                                break;
                            }
                        }
                        type = ID; 
                    }
                }
                break;
                }

                default:
                if(isalpha(input.at(0))){
                    size = 0;
                    for(size_t i = 0; i < input.size(); ++i){
                        if(isalpha(input.at(i)) || isdigit(input.at(i))){
                            size++;
                        }
                        else{
                            break;
                        }
                    }
                    type = ID;
                }
                else{
                    size = 1;
                    type = UNDEFINED;
                }
            }

            value = input.substr(0, size);
            if(input.size() > 0){
                input = input.substr(size); 
            }
            Tokens.push_back(Token(type, value, line));
            numTokens++;
            line += lineBuffer;
            lineBuffer = 0;
        }

        //EOF
        type = ENDOFFILE;
        value = "";
        Tokens.push_back(Token(type, value, line));
        numTokens++;
    }

    std::string toString(){
        std::ostringstream os;
        for(size_t i = 0; i < Tokens.size(); i++){
            os << Tokens[i] << std::endl;
        }
        os << "Total Tokens = " << numTokens;
        return os.str();
    }

};