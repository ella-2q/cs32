#include <iostream>
#include <string>
#include <stack>
#include <cassert>
using namespace std;

bool isValid(const string infix);
int precedence(const char input);
int evaluate(string infix, string& postfix, bool& result);

int evaluate(string infix, string& postfix, bool& result){
    // Evaluates a boolean expression
    //   If infix is a syntactically valid infix boolean expression,
    //   then set postfix to the postfix form of that expression, set
    //   result to the value of that expression, and return zero. If
    //   infix is not a syntactically valid expression, return 1; in
    //   that case, postfix may or may not be changed, but result must
    //   be unchanged.
    
    
    
    //infix to postfix conversion step:
    
    postfix = "";
    stack<char> operatorStack;
    
    if (isValid(infix) == false){
        return 1;
    }
    
    string spaceRemoved = "";
    for(int i = 0; i < infix.size(); i++){
        if(infix[i] == ' ')
        {
            continue;
        }
        spaceRemoved += infix[i];
    }

    infix = spaceRemoved;
    
    for (int i = 0; i < infix.size(); i++){
        char current = infix[i];
        
        switch (current){
            case 'F':
            case 'T':
                postfix = postfix + current;
                break;
            case '(':
                operatorStack.push(current);
                break;
            case ')':
                // pop stack until matching '('
                while (operatorStack.top() != '('){
                    postfix = postfix + operatorStack.top();
                    operatorStack.pop();
                }
                operatorStack.pop(); //removing the '('
                break;
            case '!':
            case '^':
            case '&':
                while (!operatorStack.empty() && operatorStack.top() != '(' && precedence(current) <= precedence(operatorStack.top())) {
                    postfix = postfix + operatorStack.top();
                    operatorStack.pop();
                }
                operatorStack.push(current);
                break;
                
            default:
                return 1; // Invalid character
        }
    }
    while (!operatorStack.empty()){
        postfix = postfix + operatorStack.top();
        operatorStack.pop();
    }
    
    
    
    // evaluation of the postfix expression:
    stack<bool> operandS;
    for (int i = 0; i < postfix.length(); i++){
        char current = postfix[i];
        if (current == 'T'){
            operandS.push(true);
        }
        else if (current == 'F'){
            operandS.push(false);
        }
        else if (current == '!'){
            bool operandTop = operandS.top();
            operandS.pop();
            operandS.push(!operandTop);
        }
        else {
            bool operand2 = operandS.top();
            operandS.pop();
            bool operand1 = operandS.top();
            operandS.pop();
            
            if (current == '&'){
                operandS.push(operand1 && operand2);
            }
            if (current == '^'){
                operandS.push(operand1 ^ operand2);
            }

        }
        
    }
    
    result = operandS.top();
    return 0;
}

int precedence(const char input){
    switch (input){
        case '!':
            return 3;
        case '&':
            return 2;
        case '^':
            return 1;
        case 'T':
        case 'F':
            return 4;
        default:
            return 0;
    }
}


bool isValid(string infix){
    
    //remove spaces
    
    string spaceRemoved = "";
    for(int i = 0; i < infix.size(); i++){
        if(infix[i] == ' ')
        {
            continue;
        }
        spaceRemoved += infix[i];
    }

    infix = spaceRemoved;
    

    //check if empty
    if (infix == ""){
        return false;
    }
    
    
    // check it starts with a valid symbol
    switch(infix[0]){
        case '&':
            return false;
        case '^':
            return false;
        default:
            break;
    }
    
    //check that all characters are valid
    for (int i = 0; i < infix.size(); i++){
        if (infix[i] != 'T' && infix[i] != 'F' && infix[i] != '!' && infix[i] != '&' && infix[i] != '^' && infix[i] != '(' &&  infix[i] != ')'){
            return false;
        }
    }
    
    //check that phrase doesn't end with an invalid operator.
    
    char end = infix[infix.size() - 1];
    
    if (end != 'T' && end != 'F' && end != ')'){
        return false;
    }
    
    // check for empty parantheses
    
    for (int i = 0; i < infix.size(); i++){
        
        if (infix[i] == '(' && (i + 1 < infix.size())){
            if (infix[i + 1] == ')'){
                return false;
            }
        }
    }
    
    //check that there is a T or F before and after &
    
    for (int i = 1; i < infix.size() - 1; i++){
        if (infix[i] == '&'){
            if (infix[i - 1] != 'T' && infix[i - 1] != 'F'){
                return false;
            }
            if (infix[i + 1] != 'T' && infix[i + 1] != 'F' && infix[i + 1] != '('){
                return false;
            }
        }
    }
    
    
    //check that each parantheses is in the right order
    int openCount = 0;
    int closedCount = 0;
    
    for (int i = 0; i < infix.size(); i ++){
        if (closedCount > openCount){
            return false;
        }
        if (infix[i] == '(') openCount++;
        if (infix[i] == ')') closedCount++;
        
    }
    
    if (closedCount != openCount){
        return false;
    }
    
    //check theres no operand right after (
    
    for (int i = 0; i < infix.size() - 1; i++){
        if (infix[i] == '('){
            if (infix[i + 1] != 'T' && infix[i + 1] != 'F' && infix[i + 1] != '('){
                return false;
            }
                
        }
    }
    
    // binary operator right before )
    for (int i = 1; i < infix.size(); i++){
        if (infix[i] == ')'){
            if (infix[i - 1] != 'T' && infix[i - 1] != 'F' && infix[i - 1] != ')'){
                return false;
            }
                
        }
    }
    
    // ! must be followed by T, F, !, or (
    for (int i = 0; i < infix.size(); i++) {
        if (infix[i] == '!') {
            if (i + 1 >= infix.size() ||  // check for trailing '!'
                (infix[i + 1] != 'T' && infix[i + 1] != 'F' && infix[i + 1] != '!' && infix[i + 1] != '(')) {
                return false;
            }
        }
    }
    
    //check that T and F are not right next to each other
    for (int i = 1; i < infix.size(); i++) {
        if ((infix[i] == 'T' || infix[i] == 'F') &&
            (infix[i - 1] == 'T' || infix[i - 1] == 'F')) {
            return false;
        }
    }
    
    //check that there is an operator between T/F and ( as well as T/F and )
    for (int i = 0; i < infix.size() - 1; i++) {
        if (infix[i] == 'F' || infix[i] == 'T') {
            if (infix[i + 1] == '(') {
                return false;
            }
        }
        if (infix[i] == ')'){
            if (infix[i + 1] == 'T' || infix[i + 1] == 'F'){
                return false;
            }
        }
        
    }
    
    return true;
}

    
/*
 postfix psuedocode
 Initialize the operand stack to empty
 For each character ch in the postfix string
 if ch is an operand
 push the value that ch represents onto the operand stack
 else // ch is a binary operator
 set operand2 to the top of the operand stack
 pop the stack
 set operand1 to the top of the operand stack
 pop the stack
 apply the operation that ch represents to operand1 and
 operand2, and push the result onto the stack
 When the loop is finished, the operand stack will contain one item,
 the result of evaluating the expression
 */

int main()
 {
 string pf;
 bool answer;
 assert(evaluate("T^ F", pf, answer) == 0  &&  pf == "TF^"  &&  answer);
 assert(evaluate("T^", pf, answer) == 1);
 assert(evaluate("F F", pf, answer) == 1);
 assert(evaluate("TF", pf, answer) == 1);
 assert(evaluate("()", pf, answer) == 1);
 assert(evaluate("()T", pf, answer) == 1);
 assert(evaluate("T(F^T)", pf, answer) == 1);
 assert(evaluate("T(&T)", pf, answer) == 1);
 assert(evaluate("(T&(F^F)", pf, answer) == 1);
 assert(evaluate("T|F", pf, answer) == 1);
 assert(evaluate("", pf, answer) == 1);
 assert(evaluate("F  ^  !F & (T&F) ", pf, answer) == 0 &&  pf == "FF!TF&&^"  &&  !answer);
 assert(evaluate(" F  ", pf, answer) == 0 &&  pf == "F"  &&  !answer);
 assert(evaluate("((T))", pf, answer) == 0 &&  pf == "T"  &&  answer);
 cout << "Passed all tests" << endl;
    
 }
