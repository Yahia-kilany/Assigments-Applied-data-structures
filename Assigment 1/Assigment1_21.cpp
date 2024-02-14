#include <iostream>
#include <string>
#include "stackt.h"
using namespace std;

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

// Function to convert infix expression to postfix
string infixToPostfix (string infix) {
    Stackt<char> operatorStack;
    string postfix = "";

    for (char& c : infix) {
        if (isalnum (c)) { // If it's an operand, add it to the postfix expression
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
bool isDigit (char c) {
    return c >= '0' && c <= '9';
}

// Function to evaluate a postfix expression
double evaluatePostfix (string postfix) {
    Stackt<double> operandStack;
    for (char& c : postfix) {
        if (isDigit (c)) { // If it's a digit, convert it to a number and push onto the operand stack
            operandStack.push (c - '0');
        }
        else { // If it's an operator
            double operand2 = operandStack.top ();
            operandStack.pop ();
            double operand1 = operandStack.top ();
            operandStack.pop ();

            // Perform the operation based on the operator
            switch (c) {
            case '+':
                operandStack.push (operand1 + operand2);
                break;
            case '-':
                operandStack.push (operand1 - operand2);
                break;
            case '*':
                operandStack.push (operand1 * operand2);
                break;
            case '/':
                operandStack.push (operand1 / operand2);
                break;
                // Add more cases for other operators if needed
            default:
                cout << "Invalid operator encountered." << endl;
                exit (1);
            }
        }
    }
    return operandStack.top ();
}
int main () {
    string infixExpression;
    cout << "Enter an infix expression: ";
    getline (cin , infixExpression);
    string postfixExpression = infixToPostfix (infixExpression);
    cout << "Postfix expression: " << postfixExpression << endl;

    double result = evaluatePostfix (postfixExpression);
    cout << "Result: " << result << endl;

    return 0;
}