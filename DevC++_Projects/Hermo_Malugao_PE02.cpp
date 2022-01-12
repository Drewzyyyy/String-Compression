/* Created by: Andrew Louis Hermo and April Rose Malugao
   Project name: Programming Exercise 1
   Subject: CMSC 124-H
   Affiliation: University of the Philippines Mindanao
*/
#include <iostream>
#include <stdlib.h>
#include <limits>
#include <string>
#include <ctype.h> 
#include <sstream>

using namespace std;

void Display();		// Displays the main menu
void ProgDesc();	// Displays the Program Description

void Compress(char c);	// Does string compression
void Expand(char c);		// Expands the compressed expression
int strToint(string exp);	// Converts string to integer
bool CheckExp(string h); // Check if expanded expression has proper formatting and syntax
bool CheckComp(string exp); // Check if compressed expression has proper formattingand syntax

int main() {
	char choice;
	while (1) {
		system("cls");											// Clears the console
		Display();												// Main Menu
		cin >> choice;
		cin.ignore(numeric_limits<streamsize>::max(), '\n');	// Removes the next line character from the cin
		cin.clear();											// Clears the input buffer
		if (choice == 'p' || choice == 'P') ProgDesc();			// Program Description
		else if (choice == 'c' || choice == 'C') Compress(choice);	// Apply String Compressions
		else if (choice == 'e' || choice == 'E') Expand(choice);	// Apply String Expansions
		else if (choice == 'x' || choice == 'X') break;			// Exit the program
		system("pause");
	}
	return 0;
}

void Display() {	// Displays the main menu
	cout << "Welcome to this String Expansion/Compression program! Please choose an\naction to perform..." << endl;
	cout << "\t[P] Program Description" << endl;
	cout << "\t[E] String Expansion" << endl;
	cout << "\t[C] String Compression" << endl;
	cout << "\t[X] Exit" << endl;
	cout << "Choice:";
}
void ProgDesc() {	// Displays the Program Description
	cout << "\nDeveloper 1: Andrew Louis Hermo - 2019-01621" << endl;
	cout << "Developer 2: April Rose Malugao - 2019-02237" << endl;
	cout << "\nProject started: March 19, 2021\tProject finished: March 20, 2021" << endl;
	cout << "\n[E] Takes a compressed form of a string then expands it" << endl;
	cout << "[C] Takes an expanded form of a string then compresses it" << endl;
	cout << "\nAndrew Louis R. Hermo :" << endl;
	cout << "\tString Compression" << endl;
	cout << "\nApril Rose Malugao :" << endl;
	cout << "\tString Expansion" << endl;
	cout << "\nLinkedIn: https://www.linkedin.com/in/alrhermo/" << endl;
}

bool CheckExp(string exp) { // Check if expanded expression has prope formatting and syntax
	for (int i = 0; i < exp.length(); i++) {	// Loops the expression to check every character
		if (!isalpha(exp[i])) return false;		// If there is any character that is not a letter then it is invalid
	}
	return true;	// Else if it consists of all letters then it is valid
}

void Compress(char c) {	// Does string compression
	string exp = "";		// Stores the expanded string
	char choice;			// Storage for the choice variable below
	//regex GoodChars("[a-zA-Z]+");	// Disallowed only for C++11
	while (1) {		// Loops while the user wants to continue compressing strings
		cout << "Enter expanded string: ";
		cin >> exp;
		cin.ignore(numeric_limits<streamsize>::max(), '\n');	// Removes the next line character from the cin
		cin.clear();											// Clears the input buffer
		if (CheckExp(exp)) {						// Checks if the expression matches the regular expression rules
			cout << "Compressed version: ";						
			int counter = 1;									// Counter for amount of repeating characters
			for (int i = 0; i < exp.length(); i++) {			// Looping the string to check each character
				if (exp[i] == exp[i+1]) {						// If the current character is the same as the next character then increment the counter
					counter++;									
					continue;									// Only increment the counter then continue the loop
				}
				if (counter > 1)cout << counter;				// If the current character is not the same to the next character then output the counter's value if it is not 1
				cout << exp[i];									//Output the current character
				counter = 1;									// Resets the counter to 1, since there is a new character to be checked
			}
		}
		else cout << "Invalid string" << endl;
		cout << "\n\t[1] Input another string" << endl;			// Let's the user choose whether to return or input another expression
		cout << "\t[0] Return to main menu" << endl;
		cout << "Choice:";
		cin >> choice;
		cin.ignore(numeric_limits<streamsize>::max(), '\n');	// Removes the next line character from the cin
		cin.clear();											// Clears the input buffer
		if (choice == '0') return;								// If the choice is 0 return to the main menu
		exp = "";												// Reset the inputted expression
		system("cls");											// Clear the screen
		Display();
		cout<<c<<endl;
	}
}


int strToint(string exp) {									// Converts string to integer
	stringstream conv;										// Creates a stringstream variable
	int val;												// Storage for the converted value
	conv << exp;											// The string is inserted to the stringstream
	conv >> val;											// The string is extracted as an integer
	return val;
}

bool CheckComp(std::string exp) { // Check if compressed expression has prope formattingand syntax
	int subSize = 0;			// Check the radix size of the substring expression, example 12p has subsize of 2 with 1 and 2
	for (int i = 0; i < exp.length(); i++) {		// Loops the entire expression to check each character
		if (isdigit(exp[i])) subSize++;				// If the digit is a character then add to the substring size
		else if (isalpha(exp[i])) {					// If it is a letter then check if it has only ones place values then check if it is 0
			if (subSize == 1 && exp[i - 1] == '0') return false;	// If the substring value is 0 then it is not valid
			subSize = 0;	// Reset the substring size to 0
		}
		else return false;	// If it is not a digit or letter then it is not valid
	}
	if (subSize != 0) return false;	// if the substring size still is not 0, then it is not valid
	return true;	// Else if it has no errors then it is valid
}

void Expand(char c) {	// Expands the compressed expression
	string exp = "";		// Stores the expanded string
	char choice;			// Storage for the choice variable below
	//regex GoodChars("(([1-9][0-9]*)?[a-zA-Z])+");	// Disallowed only for C++11
	while(1){
		cout << "Enter compressed string: ";
		cin >> exp;
		cin.ignore(numeric_limits<streamsize>::max(), '\n');	// Removes the next line character from the cin
		cin.clear();											// Clears the input buffer
		if (CheckComp(exp)) {									// Checks if the expression is valid
			int count = 1;										// Creates an INTEGER storage for the multiple digits of the character
			string counter = "";								// Serves as a string buffer, that would be the converted to integer for the multiple digits of the character
			cout << "Expanded form is: ";
			for (int i = 0; i < exp.length(); i++) {			// Loops the entire string to check every character
				if(isdigit(exp[i])){							// Checks if the current character is a digit
					counter+=exp[i];							// If it is, then add it to the string buffer
				}
				else if(counter.length()==0){					// If the counter is blank, meaning it is merely one character then just output it
					cout << exp[i];
				}
				else {
					count = strToint(counter);					// Converts the string buffer to integer, for multiplying the character
					counter = "";								// Resets the string buffer to blank
					for (int j = 0; j < count; j++) {			// Loops the amount of times the integer amounted to
						cout << exp[i];
					}
				}
			}
		}
		else cout << "Invalid string" << endl;
		cout << "\n\t[1] Input another string" << endl;			// Let's the user choose whether to return or input another expression
		cout << "\t[0] Return to main menu" << endl;
		cout << "Choice:";
		cin >> choice;
		cin.ignore(numeric_limits<streamsize>::max(), '\n');	// Removes the next line character from the cin
		cin.clear();											// Clears the input buffer
		if (choice == '0') return;								// If the choice is 0 return to the main menu
		exp = "";												// Reset the inputted expression
		system("cls");											// Clear the screen
		Display();
		cout<<c<<endl;
	}
}
