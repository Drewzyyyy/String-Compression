/* Created by: Andrew Louis Hermo and April Rose Malugao
   Project name: Programming Exercise 1
   Subject: CMSC 124-H
   Affiliation: University of the Philippines Mindanao
*/
#include <iostream>
#include <stdlib.h>
#include <limits>
#include <iostream>
#include <ios>
#include <ctype.h>
#include <string>
#include <sstream>
#include <bits/stdc++.h>

using namespace std;

void Display(); 											// Displays the main menu
void ProgDesc();											// Displays the Program Description
void Eval(char c);											// Evaluates the expression inputted by the user and outputs the answer

bool checkExp(string exp);									// Checks if expression is viable for evaluation
string ExpAdjust(string exp);								// Adjust the expression in case there are special cases
int getPrecedence(char op); 								// Returns the precendence of an operator
string toPostfix(string exp); 								// Converts the infix expression to postfix
void EvalPost(string exp);									// Evaluates the answer of the postfix expression
int strToint(string exp);									// Converts string to integer

int main(){
	char choice;
	while(1){
		system("cls");										// Clears the console
		Display();											// Main menu
		cin>>choice;										
		cin.ignore(numeric_limits<streamsize>::max(),'\n');	// Removes the next line character from the cin
		cin.clear();										// Clears the input buffer
		if(choice=='p'||choice=='P') ProgDesc();			// If the choice is p or P then open Program Description
		else if(choice=='e'||choice=='E') Eval(choice);		// If the choice is e or E then open Evaluation of Infix Expression
		else if(choice=='x'||choice=='X') break;			// Exit the program
		else cout<<"Invalid choice"<<endl;					// Else the input is invalid
		system("pause");									// Pause the console after every output
	}
	return 0;												// End the program
}

void Display() {											// Displays the main menu
	cout<<"Welcome to this Expression Evaluator program! Please choose an action to\nperform..."<<endl;
	cout<<"\t[P] Program Description"<<endl;
	cout<<"\t[E] Evaluate Expression"<<endl;
	cout<<"\t[X] Exit"<<endl;
	cout<<"Choice: ";
}

void ProgDesc(){											// Displays the Program Description
	cout<<"\nDeveloper 1: Andrew Louis Hermo - 2019-01621"<<endl;
	cout<<"Developer 2: April Rose Malugao - 2019-02237"<<endl;
	cout<<"\nProject started: March 17, 2021\tProject finished: March 19, 2021"<<endl;
	cout<<"\n[E] Evaluates the arithemetic expressions inputted by the user, and outputs the answer"<<endl;
	cout<<"[X] Exits the program"<<endl;
	cout<<"\nAndrew Louis R. Hermo :"<<endl;
	cout<<"\tEvaluation of Postfix, Error Checking and Display Function"<<endl;
	cout<<"\nApril Rose Malugao :"<<endl;
	cout<<"\tMain Menu, Program Descripntion, and Postfix Convertion"<<endl;
	cout<<"\nLinkedIn: https://www.linkedin.com/in/alrhermo/"<<endl;
}

void Eval(char c){											// Evaluates the expression inputted by the user and outputs the answer
	string exp;												// Stores the expression inputted by the user
	char choice;											// Stores the user's choice
	while(1){												// Loops until the user wants to return to the main menu
		cout<<"Input expression: ";
		getline(cin,exp);									// Get the user input
		if(!checkExp(exp)) cout<<"Invalid infix expression"<<endl;	// If the expression has a wrong syntax then output invalid
		else{												// If it is valid, evaluate the expression
			exp = ExpAdjust(exp);							// Adjust the expression for synatax purposes
			cout<<"Your infix expression: "<<exp<<endl;
			exp = toPostfix(exp);							// Convert the infix expression to postfix
			cout<<"Converted to postfix: "<<exp<<endl;
			EvalPost(exp);									// Evalusate the postfix expression and display the answer
		}
		cout<<"[1] Input again"<<endl;						// Ask the user if he/she wants to input another expression
		cout<<"[0] Return to main menu"<<endl;
		cout<<"Choice:";
		cin>>choice;										// Take the user expression
		if(choice!='1') return;								// If it is 0 or any other number, then return to main menu
		cin.ignore(numeric_limits<streamsize>::max(),'\n');	// Ignore the next line character of the cin
		cin.clear();										// Clear the input buffer
		system("cls");										// Clear the console
		Display();											// Display the main menu
		cout<<c<<endl;										// Then the choice of the user, to copy the output before clearing the screen
	}
}

bool checkExp(string exp){	// Checks if expression is viable for evaluation
	
	/*
		Parenthesis count is to check if there are equal amounts of parenthesis, and no closing parenthesis goes first than the opening parenthesis.
		Example:
			( (1 + 2 ) 		= Invalid
			( ( ( (1 + 2 	= Invalid
			) 1 + 2 ( 		= Invalid
			( ( ) )			= Invalid
			( 1 + 2 ) 		= Valid
			1 + 2 			= Valid
			
		Operator count is to check if there is a succeeding operator after another operator, meaning the syntax is invalid.
		So if the operator count > 1, then it is invalid.
		Example:
			1++2			= Invalid
			(1+2)*-4		= Inalid
			1+2				= Valid
	*/
	
	int parenthesis_count = 0;						// Counts the number of parenthesis in the epxression
	int operator_count = 0;							// Counts the number of operators in the expression
	int num_count = 0;

	for(int i = 0; i<exp.length();i++){				// Loops the entire string of operators
	
		if(isdigit(exp[i])){						// Checks if the character is a digit then continues to the next index
			num_count++;
			operator_count=0;						// Resets the operator count to 0
			if(exp[i+1]=='(') exp.insert(i+1,"*");
			continue;
		}
		else if(exp[i]==' '){ 						// If the characrer is a space then continues to the next index
			continue;
		}				

		if(exp[i]=='+') operator_count++;			// If it is a addition operator increment the operator count
		else if(exp[i]=='-'){						// If it is a subtraction operator increment the operator count
			if(exp[i-1]=='('&&isdigit(exp[i+1])) return false;	// Rejects negative number in parenthesis
			else if(i==0&&isdigit(exp[i+1])) return false;		// Rejects a negative number at the start
			operator_count++;
		}
		else if(exp[i]=='*') operator_count++;		// If it is a multilication operator increment the operator count
		else if(exp[i]=='/') operator_count++;		// If it is a division operator increment the operator count
		else if(exp[i]=='%') operator_count++;		// If it is a modulus operator increment the operator count
		else if(exp[i]=='(') parenthesis_count++;	// If it is an opening parenthesis increment the operator count
		else if(exp[i]==')') parenthesis_count--;	// If it is a closing parenthesis decrement the operator count
		else return false;

		if(parenthesis_count<0) return false;		// If the parenthesis count is less than 0, meaning there is a leading closing parenthesis, then the expression is invalid
		if(operator_count>1) return false;			// If the operator count is more than 1, meaning there is an operator succeeding an operator, then the expression is invalid
	}
	if(parenthesis_count>0) return false;			// If the parenthesis count is not equal to 0, then it is invalid
	if(operator_count!=0) return false;				// If the operators are not set to 0, meaning the last character was not a closing parenthesis or a number, then it is invalid
	if(num_count==0) return false;					// If there are no numbers then it is invalid
	return true;									// Else it is a valid expression
}

string ExpAdjust(std::string exp){					// Adjust the expression in case there are special cases
	for(int i = 0;i<exp.length();i++){				// Loops the entire string
		if(isdigit(exp[i]) && exp[i+1]=='(') exp = exp.insert(i+1,"*");		// If the current character is a digit then the next character is an opening parenthesis, add a * character
		else if(exp[i]==')' && isdigit(exp[i+1])) exp = exp.insert(i+1,"*");	// If the current character is an closing parenthesis then the next character is a digit, add a * character
		else if(exp[i]==')' && exp[i+1]=='(') exp = exp.insert(i+1,"*");	// If the current character isa closing parenthesis and the next character is an opening parenthesis, add a * character
		
		if(!isdigit(exp[i]) && exp[i+1] != ' '){	// If the current character is not a digit, and the next character does not have space, add a space
			exp = exp.insert(i+1," ");				// Adds the space
			i++;									// Moves the counter to the next number as to stop an infinite loop
		}
		else if(isdigit(exp[i]) && !isdigit(exp[i+1])){	// If the current chartacter is a digit, and the next character is not a digit, add a space
			exp.insert(i+1," ");						// Adds the space
			i++;										// Moves the counter to the next number as to stop an infinite loop
		}
	}
	return exp;
}

int getPrecedence(char op){							// Returns the precendence of an operator
	switch(op){
		case ')':									// Lowest Precedence, but means that the stack must be cleared
			return 1;
		case '(':									// Second precedence, added immediately to the stack
			return 2;
		case '+':
		case '-':									// Third precedence, if the operator is +, or - 
			return 3;
		case '%':
		case '*':
		case '/':
			return 4;								// The highest precedence is for * and /
	}
	return 0;
}

string toPostfix(std::string exp){ 					// Converts the infix expression to postfix
	stack<char> s;									// Initiate a stack for the operators
	string final = "";								// Storage for the final postfix expression
	for(int i = 0;i<exp.length();i++){				// Loops to check the entire string
		if(exp[i]==' ') continue;					// If it is a space then move to the next character
		if(isdigit(exp[i])){						// If it is a digit immediately add to the final postfix
			final += (exp[i]);
			if(!isdigit(exp[i+1])) final+=" ";
		}
		else if(getPrecedence(exp[i])!=0){			// If the precedence is not 0, meaning it is a parenthesis and operator, then enter the nested else if statement
			if(exp[i]=='(') s.push(exp[i]);			// If it is an opening parenthesis immediately add to the stack
			else if (exp[i]==')'){					// If it is a closing parenthesis then clear the stack
				while(s.top()!='('){				// Continues until the stack is empty, th
					if(s.top()!='('){				// Checks if the top of the stack is not an opening parenthesis, if so add it to the final postfix 
						final+=s.top();				// Adds the character at the top of the srack to the final postfix string
						final+=" ";					// Adds a space for readability
					}
					s.pop();						// Pops the top of the stack until it is empty
				}
				s.pop();
			}
			else if(s.empty()||getPrecedence(exp[i])>getPrecedence(s.top())){	// If the stack is empty or the current infix character has greater precedence than the top of the stack, push it to the stack
				s.push(exp[i]);						// Push it to the stack since it is either empty or has greater precedence
			}
			else if(getPrecedence(exp[i])<=getPrecedence(s.top())){	// If the top of the stack has greater or equal precedence than the infix character, pop the top of the stack
				while(!s.empty()){					// Loops until the stack is empty
					if(s.top()=='(') break;			// If the top of the stack is already an opening bracket, break the loop
					else if(getPrecedence(exp[i])<=getPrecedence(s.top())){	// If the top of the stack is still greater or equal than the infix character, pop the stack
						final+=s.top();				// Adds the top of the stack to the final postfix string
						final+=" ";					// Adds a space for readability
						s.pop();					// Pops the top of the stack
					}
					else break;						// If the infix character now has a greater precedence, then break the loop
				}
				s.push(exp[i]);						// Push the current infix character to the stack
			}
		}
	}
	while(!s.empty()){								// If the stack is still not empty, pop out all operators
		if(s.top()!='('||s.top()!=')'){				// If the top of the stack is not a parenthesis, then add it to the final postfix string
			final+=s.top();							// Adds the top of the stack to the final postfix string
			final+=" ";								// Adds a space for readability
		}
		s.pop();									// Pops the top of the stack
	}
	return final;									// Return the final postfix string
}

int strToint(string exp){									// Converts string to integer
	stringstream conv;
	int val;
	conv << exp;
	conv >> val;
	return val; 
}

void EvalPost(string exp){							// Evaluates the answer of the postfix expression

	/*
		Example: 1 2 3 * +
		Process:
		Char	||		Stack		||		Evaluate:		||		Description:
		1		||		null		||		null			||		Add 1 to the stack
		2		||		1			||		null			||		Add 2 to the stack
		3		||		2 1			||		null			||		Add three to the stack
		*		||		3 2 1		||		null			||		Pop 3 and 2
				||		1			||		(2*3)			||		Multiply 2 by 3
				||		1			||		6				||		Add 6 to the stack
				||		6 1			||		null			||		Added 6 to the stack
		+		||		6 1			||		null			||		Pop 6 and 1
				||		null		||		1+6				||		Add 6 to 1
				||		null		||		7				||		Add 7 to the stack
				||		7			||		null			||		Reached the end of the string, the top of the stack is the answer
		Answer:	7
		
	*/

	stack<int> s;									// Creates a stack of integers
	stringstream convert;
	int a = 0, b = 0, c = 0;						// Storage for the values to be computed, a and b for the computing variable, and c for the result
	string num = "";
	for(int i = 0;i < exp.length();i++){			// Loops the entire string of characters
		if(isdigit(exp[i])){						// If character is a digit, convert it to integer then push to the stack
			for(int j = i;exp[j]!=' ';j++,i++){
				num+=exp[j];
			}
			a = strToint(num);						// Converts the string to integer
			num = " ";
			s.push(a);								// Push the integer to the stack
		}
		else if(exp[i]==' ') continue;				// If the character is a space, continue to the next index
		else{										// If it is an operator then evaluate by popping two integers from the stack
			b = s.top();							// Takes the top of the stack as the second value to be evaluated
			s.pop();								// Pop the top of the stack
			a = s.top();							// Take the next top of the stack as the first value to be evaluated
			s.pop();								// Pop the top of the stack
			switch(exp[i]){							// Check what operator is to be used
				case '+':							// Adds the two integers
					c = a + b;						// Add b to a then store in c
					s.push(c);						// Push c to the stack
					break;							// Move to the next character
					
				case '-':							// Subtract the two integers
					c = a - b;						// Subtract b from a then store in c
					s.push(c);						// Push c to the stack
					break;							// Move to the next character
					
				case '/':							// Divide the two integers
					c = a / b;						// Divides a by b then store in c
					s.push(c);						// Push c to the stack
					break;							// Move to the next character
					
				case '*':							// Multiply the two integers
					c = a * b;						// Multiply a by b then store in c
					s.push(c);						// Push c to the stack
					break;							// Move to the next character
					
				case '%':							// Finds the modulus of the two integers
					c = a % b;						// Apply a modulo b then store in c
					s.push(c);						// Push c to the stack
					break;							// Move to the next character
			}
		}
	}
	cout<<"The answer to the expression is "<<s.top()<<endl;	// Output the top of the stack which is the answer
}
