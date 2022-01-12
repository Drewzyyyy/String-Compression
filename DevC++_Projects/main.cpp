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
#include "validate.h"

using namespace std;

void Display(); 											// Displays the main menu
void ProgDesc();											// Displays the Program Description
void Eval(char c);											// Evaluates the expression inputted by the user and outputs the answer

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
	cout<<"Developer 2: April Rose Malugao - 2019-01621"<<endl;
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
