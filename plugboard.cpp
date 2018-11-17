/* 
Check input is well formed:
INVALID_INDEX                             3
NON_NUMERIC_CHARACTER                     4
IMPOSSIBLE_PLUGBOARD_CONFIGURATION        5
INCORRECT_NUMBER_OF_PLUGBOARD_PARAMETERS  6
ERROR_OPENING_CONFIGURATION_FILE          11
NO_ERROR                                  0 
*/


#include "plugboard.h"
using namespace std;

Plugboard::Plugboard(const char *filename) {
	int input, output, count = 0;
	error = 0;
	for (int i=0; i<NUM_OF_LETTERS; i++) {// Initialise plugboard to baseline configuration 
		mapping[i] = i;
	}
	ifstream in_stream;
	in_stream.open(filename);
	if (in_stream.fail()) {
		error = 11; 
		cerr << "Input file cannot be opened" << endl;
	}
	if(check_input_valid(filename) == 0) {
		error = 4;
		cerr << "Input file contains non-digit characters" << endl;
	}
	   	while ((in_stream >> input) && (error == 0)) {
      		count++;
      		if (!(input >= 0 && input<= NUM_OF_LETTERS-1)) {
				error = 3;
				cerr << "Input file contains numbers not in range [0,25]" << endl;
      		}
     		else if (mapping[input] != input) {
	 			error = 5;
	 			cerr << "Letter has already been mapped" << endl;
     		}
	 		else {
				if (!(in_stream >> output)) {
	  				error = 6;
	  				cerr << "Input file numbers are not in pairs" << endl;
				}
				else if (!(output >= 0 && output<= NUM_OF_LETTERS-1)) {
	 				error = 3;
	 				cerr << "Input file contains numbers not in range [0,25]" << endl;
				}
				else {
	  				if (mapping[output] != output) {
	    				error = 5;
	    				cerr << "Letter has already been mapped" << endl;
	  				}
	  				else if (input == output) {
	    				error = 5;
	    				cerr << "Letter maps to itself" << endl;
	  				}
	  				else {
	    				mapping[input] = output;
	    				mapping[output] = input;
	  				}
				}
      		}
    	}
    	if (count > NUM_OF_PAIRS) {
			error = 6;
			cerr << "File contains more than 13 pairs of numbers" << endl;
    	}

	in_stream.close();
}

int Plugboard::encrypt(const int &letter) {
	return mapping[letter];
}



