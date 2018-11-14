#include <iostream>
#include <fstream>
#include <cstdio>
#include <string>
#include <cstdlib>
#include "check_input_valid.h"
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
		default:
		break;

	}

char currentChar;
int index;

cin >> ws;
cout << "Please input message to be encoded: ";

while(cin >> currentChar){
	if (islower(currentChar) != 0 || isalpha(currentChar) == 0) {
		cerr << endl << " Only uppercase letters allowed! " << endl;
		return INVALID_INPUT_CHARACTER;
	}
	index = currentChar - 65;
	index = enigma.encrypt(index);
	currentChar = char(index) + 65;
	cout << currentChar;
}
cout << endl;

return NO_ERROR;

}

