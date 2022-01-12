#pragma once
#include <string>

bool checkExp(std::string exp);				// Checks if expression is viable for evaluation
std::string ExpAdjust(std::string exp);		// Adjust the expression in case there are special cases
int getPrecedence(char op); 				// Returns the precendence of an operator
std::string toPostfix(std::string exp); 	// Converts the infix expression to postfix
void EvalPost(std::string exp);				// Evaluates the answer of the postfix expression
