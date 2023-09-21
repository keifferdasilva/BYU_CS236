#include "Token.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include "Scanner.h"
#include "Parser.h"
using namespace std;

int main(int argc, char* argv[]){
    if(argc <= 1){
        cout << "No input file given";
    }
    ifstream is(argv[1]);
    string input;
    
    if(!is){
        cout << "Failed to open" << endl;
    }

    while(is.peek() != EOF){
        input += is.get();
    }


    Scanner scnr = Scanner(input);
    scnr.scanToken();

    vector<Token> tokens = scnr.getTokens();

    Parser parser(tokens);

    try{
        parser.parse();
    }catch(Token& t){
        cout << "Failure!" << endl << "  " << t;
    }
    catch(string& s){
        cout << s;
    }
    
}