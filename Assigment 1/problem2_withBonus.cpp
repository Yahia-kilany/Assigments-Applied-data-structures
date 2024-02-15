#include <iostream>
#include <string>
#include "stackt.h" // Assuming stackt.h contains the Stackt template class definition

using namespace std;

// Function declarations
string spaceInfix(string infix);
bool isOperator(char c);
int getPrecedence(char op);
string infixToPostfix(string infix);
double calculate(double a, double b, char oper);
double evaluatePostfix(string expression);

int main() {
    // Input infix expression from the user
    string infixExpression;
    cout << "Enter an infix expression: ";
    getline(cin, infixExpression);

    // Add spaces to the infix expression
    string spacedInfix = spaceInfix(infixExpression);
    cout << "Space infix " << spacedInfix << endl;

    // Convert infix expression to postfix
    string postfixExpression = infixToPostfix(spacedInfix);
    cout << "Postfix expression: " << postfixExpression << endl;

    // Evaluate the postfix expression
    double result = evaluatePostfix(postfixExpression);
    cout << "Result: " << result << endl;

    return 0;
}

// Function to check if a character is an operator
bool isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

// Function to get the precedence of an operator
int getPrecedence(char op) {
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

// Function to add spaces to an infix expression
string spaceInfix(string infix) {
    string newInfix = "";
    for (char& c : infix) {
        if (isOperator(c) || c == '(' || c == ')') {
            newInfix += ' '; // Add space before operator or parenthesis
            newInfix += c;
            newInfix += ' '; // Add space after operator or parenthesis
        } else {
            newInfix += c;
        }
    }
    return newInfix;
}

// Function to convert infix expression to postfix
string infixToPostfix(string infix) {
    Stackt<char> operatorStack; // Stack to store operators
    string postfix = ""; // Final postfix expression

    for (char& c : infix) {
        if (isalnum(c) || c == ' ') { // If it's an operand or space, add it to the postfix expression. 
        //an issue with this implementation is that if there are parenthesis in the expression resulting postfix expression may have too many spaces between it's elements
            postfix += c;
        }
         else if (c == '(') { // If it's a left parenthesis, push it onto the operator stack
            operatorStack.push(c);
        } else if (c == ')') { // If it's a right parenthesis
            // Pop and add operators from the stack to postfix until a left parenthesis is encountered
            while (!operatorStack.isEmpty() && operatorStack.top() != '(') {
                postfix += operatorStack.top();
                operatorStack.pop();
            }
            operatorStack.pop(); // Pop the left parenthesis from the stack
        } else if (isOperator(c)) { // If it's an operator
            // Pop operators from the stack with higher or equal precedence and add them to postfix
            while (!operatorStack.isEmpty() && getPrecedence(operatorStack.top()) >= getPrecedence(c)) {
                postfix += operatorStack.top();
                operatorStack.pop();
            }
            operatorStack.push(c); // Push the current operator onto the stack
        }
    }

    // Pop any remaining operators from the stack and add them to the postfix expression
    while (!operatorStack.isEmpty()) {
        postfix += operatorStack.top();
        operatorStack.pop();
    }

    return postfix;
}

// Function to perform arithmetic operations
double calculate(double a, double b, char oper) {
    switch (oper) {
        case '+':
            return a + b;
        case '-':
            return b - a;
        case '*':
            return a * b;
        case '/':
            if (a == 0) {
                throw runtime_error("Cannot divide by zero");
            }
            return b / a;
        default:
            throw runtime_error("Invalid operator");
    }
}

// Function to evaluate a postfix expression
double evaluatePostfix(string expression) {
    Stackt<double> stack; // Stack to store operands
    for (int i = 0; i < expression.length(); i++) {
        char c = expression[i];
        if (c == ' ')
            continue;
        else if (isOperator(c)) { // If it's an operator
            double s1 = stack.top();
            stack.pop();
            double s2 = stack.top();
            stack.pop();
            double temp = calculate(s1, s2, c); // Perform operation
            stack.push(temp); // Push result back to the stack
        } else { // If it's an operand
            double num = 0;
            // Extract the operand (possibly multi-digit number)
            while (isdigit(c)) {
                num = num * 10 + (c - '0');
                i++;
                c = expression[i];
            }
            i--; // Move the pointer back to the last digit of the operand
            stack.push(num); // Push operand to the stack
        }
    }
    double result = stack.top(); // The final result is on the top of the stack
    stack.pop();
    return result;
}