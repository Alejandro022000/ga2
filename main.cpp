#include <iostream>
#include <fstream>
#include <string>
#include "ArgumentManager.h"
#include "queue.h"
#include <stack>
#include <algorithm>
using namespace std;

bool validParenthesis(string exp){
    stack<char> st;
    for(int i=0; i < exp.length(); i++){
        if(exp[i] == '(' || exp[i] == '[' || exp[i] == '{'){
            st.push(exp[i]);
        }
        else if(exp[i] == ')'){
            if(st.empty() || st.top() != '('){
                return false;
            }
            st.pop();
        }
        else if(exp[i] == ']'){
            if(st.empty() || st.top() != '['){
                return false;
            }
            st.pop();
        }
        else if(exp[i] == '}'){
            if(st.empty() || st.top() != '{'){
                return false;
            }
            st.pop();
        }
    }
    return st.empty();
}

bool redundantBrackets(string exp){
    stack<char> s;
    for(int i=0; i < exp.length(); i++){
        if(exp[i] == ')'){
            if(s.top() == '('){
                return true;
            }
            while(s.top() != '('){
                s.pop();
            }
            s.pop();
        }
        else if(exp[i] == '}'){
            if(s.top() == '{'){
                return true;
            }
            while(s.top() != '{'){
                s.pop();
            }
            s.pop();
        }
        else if(exp[i] == ']'){
            if(s.top() == '['){
                return true;
            }
            while(s.top() != '['){
                s.pop();
            }
            s.pop();
        }
        else{
            s.push(exp[i]);
        }
    }
    return false;
}

int prec(char c) {
  if (c == '/' || c == '*')
    return 2;
  else if (c == '+' || c == '-')
    return 1;
  else
    return 0;
}

string infixToPostfix(string s) {
  stack<char> st;
  string postfix;
 
  for (int i=0; i<s.length(); i++) {
    if (s[i] >= '0' && s[i] <= '9')
      postfix += s[i];

    else if (s[i] == '(')
      st.push('(');
       else if (s[i] == '[')
      st.push('[');
      else if (s[i] == '{')
      st.push('{');

    else if (s[i] == ')') {
      while (st.top() != '(') {
        postfix += st.top();
        st.pop();
      }
      st.pop();
    }

    else if (s[i] == ']') {
      while (st.top() != '[') {
        postfix += st.top();
        st.pop();
      }
      st.pop();
    }

    else if (s[i] == '}') {
      while (st.top() != '{') {
        postfix += st.top();
        st.pop();
      }
      st.pop();
    }

    else {
      while (!st.empty() && prec(s[i]) <= prec(st.top())) {
          postfix += st.top();
          st.pop();
      }
      st.push(s[i]);
    }
  }

  while (!st.empty()) {
    postfix += st.top();
    st.pop();
  }
 
  return postfix;
}

int evaluatePostfix(string s) {
  stack<int> st;

  for (int i=0; i<s.length(); i++) {
    if (s[i] >= '0' && s[i] <= '9')
      st.push(s[i] - '0');
    else {
      int val1 = st.top(); st.pop();
      int val2 = st.top(); st.pop();
      switch (s[i]) {
        case '+': st.push(val2 + val1); break;
        case '-': st.push(val2 - val1); break;
        case '*': st.push(val2 * val1); break;
        case '/': st.push(val2 / val1); break;
      }
    }
  }
  return st.top();
}

int main(int argc, char *argv[]){   
    ArgumentManager am(argc, argv);
    ifstream input(am.get("input"));
    ofstream output(am.get("output"));
    /*
    ifstream input("input1.txt");
    ofstream output("output1.txt");    
    */
    string input_str; //equation
    my_queue queue;  //queue

    while (getline(input, input_str)) {
        input_str.erase(remove(input_str.begin(), input_str.end(), '\n'), input_str.end());
        input_str.erase(remove(input_str.begin(), input_str.end(), '\r'), input_str.end());

        if(!input_str.empty()){                        
            if (validParenthesis(input_str)){ //check if is valid (validParenthesis)
                if(!redundantBrackets(input_str)){
                    string infix = infixToPostfix(input_str);// infix to postfix
                    int priority = evaluatePostfix(infix);// evaluate postfix               
                    queue.enqueue(priority, input_str);// add to priority queue depending on the solution of the equation(lower number means higer priority)
                }
            }
        }      
    }
    queue.print_queue(output);// output queue to file
    
    return 0;
}