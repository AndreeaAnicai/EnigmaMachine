#include <iostream>
#include <fstream>
#include <cstdio>
#include <string>
#include <cstdlib>
#include <cctype>
#include <cstring>
#include "check_input_valid.h"
#include "utilities.h"
#include "errors.h"
#include "enigma.h"

using namespace std;

int main(int argc, char *argv[]) {

Enigma enigma(argc, argv);
switch(enigma.error) {
	case 1: 
		cerr << endl << "Parameters must specify at least the plugboard and reflector input" << endl;
		return INSUFFICIENT_NUMBER_OF_PARAMETERS;
	case 2: 
		cerr << endl << "Only uppercase letters are allowed" << endl;
		return INVALID_INPUT_CHARACTER;
	case 3: 
		cerr << "Input file contains numbers not in range [0,25]" << endl;
		return INVALID_INDEX;
	case 4: 
		cerr << "Input file contains non-digit characters" << endl;
		return NON_NUMERIC_CHARACTER;
	case 5: 
		cerr << "Plugboard letter has already been mapped or" << endl;
		cerr << "letter maps to itself" << endl;
		return IMPOSSIBLE_PLUGBOARD_CONFIGURATION;
	case 6: 
		cerr << "Input file numbers are not in pairs or" << endl;
		cerr << "file contains more than 13 pairs of numbers" << endl;
		return INCORRECT_NUMBER_OF_PLUGBOARD_PARAMETERS;
	case 7:
		cerr << "Input does not contain mappings for all letters or" << endl;
		cerr << "rotor letter has already been mapped or" << endl;
		cerr << "notch has already been assigned to a rotor" << endl;
	 	return INVALID_ROTOR_MAPPING;
	case 8: 
		cerr << "Input does not contain rotor starting positions" << endl;
		return NO_ROTOR_STARTING_POSITION;
	case 9: 
		cerr << "Letter has already been mapped or" << endl;
		cerr << "letter maps to itself" << endl;
		return INVALID_REFLECTOR_MAPPING;
	case 10: 
		cerr << "File does not contain exactly 13 pairs of numbers or" << endl;
		cerr << "Input file numbers are not in pairs" << endl;
		return INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS;
	case 11: 
		cerr << "Input file cannot be opened" << endl;
		return ERROR_OPENING_CONFIGURATION_FILE;
	default:
		break;
	}
char currentChar;
int index;

cin >> ws;
while(cin >> ws >> currentChar){
	if (islower(currentChar) != 0 || isalpha(currentChar) == 0) {
		return INVALID_INPUT_CHARACTER;
	}
	index = currentChar - ASCII_A;
	index = enigma.encrypt(index);
	currentChar = char(index) + ASCII_A;
	cout << currentChar;
}
return NO_ERROR;

}

