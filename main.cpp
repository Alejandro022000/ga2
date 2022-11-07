#include <iostream>
#include <fstream>
#include <string>
#include "ArgumentManager.h"
#include "queue.h"
using namespace std;

int main(int argc, char *argv[]){
    /*
    ArgumentManager am(argc, argv);
    ifstream input(am.get("input"));
    ofstream output(am.get("output"));
    */
    ifstream input("input1.txt");
    ofstream output("output1.txt");    

    string input_str; //equation
    my_queue queue;  //queue

    while (getline(input, input_str)) {
        if(!input_str.empty())
        {
            //TODO check if is validsdas
            //TODO infix to postfix
            //TODO evaluate postfix
            //TODO add to priority queue depending on the solution of the equation(lower number means higer priority)
        }        
    }

    //TODO output queue to file

    return 0;
}