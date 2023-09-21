#include "Token.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include "Scanner.h"
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
    cout << scnr.toString();
}