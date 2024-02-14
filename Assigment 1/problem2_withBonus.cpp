#include <iostream>
#include <string>
#include "stackt.h"

using namespace std;

// Function declarations
string spaceInfix (string infix);
bool isOperator (char c);
int getPrecedence (char op);
string infixToPostfix (string infix);
double calculate (double a , double b , char oper);
double evaluatePostfix (string expression);

int main () {
    string infixExpression;
    cout << "Enter an infix expression: ";
    getline (cin , infixExpression);
    string spacedInfix = spaceInfix (infixExpression);
    cout << "Space infix " << spacedInfix << endl;
    string postfixExpression = infixToPostfix (spacedInfix);
    cout << "Postfix expression: " << postfixExpression << endl;
    double result = evaluatePostfix (postfixExpression);
    cout << "Result: " << result << endl;

    return 0;
}

// Function to check if a character is an operator
bool isOperator (char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

// Function to get the precedence of an operator
int getPrecedence (char op) {
    switch (op) {
    case '+':
    case '-':
        return 1;
    case '*':
    case '/':
        return 2;
    default:
        return 0;
    }
}
string spaceInfix (string infix) {
    string newInfix = "";
    for (char& c : infix) {

        if (isOperator (c) || c == '(' || c == ')') {
            newInfix += ' ';
            newInfix += c;
            newInfix += ' ';
        }
        else {
            newInfix += c;
        }
    }
    return newInfix;
}
// Function to convert infix expression to postfix
string infixToPostfix (string infix) {
    Stackt<char> operatorStack;
    string postfix = "";

    for (char& c : infix) {
        if (isalnum (c) || c == ' ') { // If it's an operand, add it to the postfix expression
            postfix += c;
        }
        else if (c == '(') { // If it's a left parenthesis, push it onto the operator stack
            operatorStack.push (c);
        }
        else if (c == ')') { // If it's a right parenthesis, pop and add operators from the stack to postfix until a left parenthesis is encountered
            while (!operatorStack.isEmpty () && operatorStack.top () != '(') {
                postfix += operatorStack.top ();
                operatorStack.pop ();
            }
            operatorStack.pop (); // Pop the left parenthesis from the stack
        }
        else if (isOperator (c)) { // If it's an operator
            while (!operatorStack.isEmpty () && getPrecedence (operatorStack.top ()) >= getPrecedence (c)) {
                postfix += operatorStack.top (); // Pop operators from the stack with higher or equal precedence and add them to postfix
                operatorStack.pop ();
            }
            operatorStack.push (c); // Push the current operator onto the stack
        }
    }

    // Pop any remaining operators from the stack and add them to the postfix expression
    while (!operatorStack.isEmpty ()) {
        postfix += operatorStack.top ();
        operatorStack.pop ();
    }

    return postfix;
}

// Function to evaluate a postfix expression
double calculate (double a , double b , char oper) {
    switch (oper) {
    case '+':
        return a + b;
    case '-':
        return b - a;
    case '*':
        return a * b;
    case '/':
        if (a == 0)
            throw runtime_error ("Cannot divide by zero");
        return b / a;
    default:
        throw runtime_error ("Invalid operator");
    }
}

double evaluatePostfix (string expression) {
    Stackt<double> stack;
    for (int i = 0; i < expression.length (); i++) {
        char c = expression[i];

        if (c == ' ')
            continue;

        else if (isOperator (c)) {
            double s1 = stack.top ();
            stack.pop ();
            double s2 = stack.top ();
            stack.pop ();
            double temp = calculate (s1 , s2 , c);
            stack.push (temp);
        }
        else {
            double num = 0;

            while (isdigit (c)) {
                num = num * 10 + (c - '0');
                i++;
                c = expression[i];
            }
            i--;
            stack.push (num);
        }
    }
    double result = stack.top ();
    stack.pop ();
    return result;
}