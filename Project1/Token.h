#pragma once
#include <iostream>
#include <sstream>
using namespace std;

enum TokenType{
    COMMA, PERIOD, Q_MARK, LEFT_PAREN, RIGHT_PAREN, COLON, COLON_DASH,
    MULTIPLY, ADD, SCHEMES, FACTS, RULES, QUERIES, ID, STRING, COMMENT, UNDEFINED, ENDOFFILE
};

class Token {

private:
    TokenType type;
    string value;
    int line;


public:
    Token(TokenType t, string v, int l) : type(t), value(v), line(l){}
    
    string toString() const{
        ostringstream os;
        os << "(" << typeName(type) << ",\"" << value << "\"," << line << ")";
        return os.str();
    }

    string typeName(TokenType type) const {
        switch (type) {
        case COMMA:
            return "COMMA";
            break;
        case ID:
            return "ID";
            break;
        case STRING:
            return "STRING";
            break;
        case UNDEFINED:
            return "UNDEFINED";
            break;
        case COLON:
            return "COLON";
            break;
        case COLON_DASH:
            return "COLON_DASH";
            break;
        case ENDOFFILE:
            return "EOF";
            break;
        case PERIOD:
            return "PERIOD";
            break;
        case Q_MARK:
            return "Q_MARK";
            break;
        case LEFT_PAREN:
            return "LEFT_PAREN";
            break;
        case RIGHT_PAREN:
            return "RIGHT_PAREN";
            break;
        case MULTIPLY:
            return "MULTIPLY";
            break;
        case ADD:
            return "ADD";
            break;
        case SCHEMES:
            return "SCHEMES";
            break;
        case FACTS:
            return "FACTS";
            break;
        case RULES:
            return "RULES";
            break;
        case QUERIES:
            return "QUERIES";
            break;
        case COMMENT:
            return "COMMENT";
            break;
        default:
            return " ";
            break;
        } 
    }

    friend std::ostream& operator<<(std::ostream& os, Token& token){
        os << token.toString();
        return os;
    }
};