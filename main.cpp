#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <cctype>
#include <vector>
#include "check_input_valid.h"
#include "utilities.h"
#include "errors.h"
#include "enigma.h"
using namespace std;

	int main(int argc, char *argv[]) {

	Enigma enigma(argc, argv);
	switch(enigma.error) {
		case 1: return INSUFFICIENT_NUMBER_OF_PARAMETERS;
		case 2: return INVALID_INPUT_CHARACTER;
		case 3: return INVALID_INDEX;
		case 4: return NON_NUMERIC_CHARACTER;
		case 5: return IMPOSSIBLE_PLUGBOARD_CONFIGURATION;
		case 6: return INCORRECT_NUMBER_OF_PLUGBOARD_PARAMETERS;
		case 7: return INVALID_ROTOR_MAPPING;
		case 8: return NO_ROTOR_STARTING_POSITION;
		case 9: return INVALID_REFLECTOR_MAPPING;
		case 10: return INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS;
		case 11: return ERROR_OPENING_CONFIGURATION_FILE;
		default: break;
	}
	char currentChar, wrongChar;
	int index;
	cin >> ws;

	while((cin >> ws >> currentChar)) {
		if (islower(currentChar) != 0 || isalpha(currentChar) == 0) {
			wrongChar = currentChar;
			cerr << " - " << wrongChar << " is not a valid input character" << endl;
			cerr << "Input characters must be upper case letters A-Z)!" << endl;
			return INVALID_INPUT_CHARACTER;
		}
		index = currentChar - ASCII_A;
		index = enigma.encrypt(index);
		currentChar = char(index) + ASCII_A;
		cout << currentChar;
	}

	return NO_ERROR;

}
