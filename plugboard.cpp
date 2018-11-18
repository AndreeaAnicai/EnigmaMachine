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
		error = ERROR_OPENING_CONFIGURATION_FILE; 
	}
	if(check_input_valid(filename) == 0) {
		error = NON_NUMERIC_CHARACTER;
	}
	   	while ((in_stream >> input) && (error == 0)) {
      		count++;
      		if (!(input >= 0 && input<= NUM_OF_LETTERS-1)) {
				error = INVALID_INDEX;
      		}
     		else if (mapping[input] != input) {
	 			error = IMPOSSIBLE_PLUGBOARD_CONFIGURATION;
     		}
	 		else {
				if (!(in_stream >> output)) {
	  				error = INCORRECT_NUMBER_OF_PLUGBOARD_PARAMETERS;
				}
				else if (!(output >= 0 && output<= NUM_OF_LETTERS-1)) {
	 				error = INVALID_INDEX;
				}
				else {
	  				if (mapping[output] != output) {
	    				error = IMPOSSIBLE_PLUGBOARD_CONFIGURATION;
	  				}
	  				else if (input == output) {
	    				error = IMPOSSIBLE_PLUGBOARD_CONFIGURATION;
	  				}
	  				else {
	    				mapping[input] = output;
	    				mapping[output] = input;
	  				}
				}
      		}
    	}
    	if (count > NUM_OF_PAIRS) {
			error = INCORRECT_NUMBER_OF_PLUGBOARD_PARAMETERS;
    	}

	in_stream.close();
}

int Plugboard::encrypt(const int &letter) {
	return mapping[letter];
}



