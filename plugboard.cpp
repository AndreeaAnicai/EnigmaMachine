#include "plugboard.h"
using namespace std;

Plugboard::Plugboard(const char *filename) {
	int input = 0, output = 0, count = 0;
	error = 0;
	for (int i=0; i<NUM_OF_LETTERS; i++) {
		mapping[i] = i;
	}
	ifstream in_stream;
	in_stream.open(filename);

	if (in_stream.fail()) {
		error = ERROR_OPENING_CONFIGURATION_FILE; 
		cerr << "Error opening plugboard configuration file " << filename << endl;
	}
	if(check_input_valid(filename) == 0) {
		error = NON_NUMERIC_CHARACTER;
		cerr << "Non-numeric character for mapping in plugboard file " << filename << endl;
	}
	   	while ((in_stream >> input) && (error == 0)) {
      		count++;
      		if (count > NUM_OF_PAIRS) {
				error = INCORRECT_NUMBER_OF_PLUGBOARD_PARAMETERS;
				cerr << "Incorrect number of parameters in plugboard file " << filename << endl;
    		}
      		else if (!(input >= 0 && input<= NUM_OF_LETTERS-1)) {
				error = INVALID_INDEX;
				cerr << input << " is not a number between 0 and 25 in plugboard file " << filename << endl;
      		}
     		else if (mapping[input] != input) {
	 			error = IMPOSSIBLE_PLUGBOARD_CONFIGURATION;
	 			cerr << "Incorrect mapping of letter which has already been mapped in plugboard file  " << filename << endl;
     		}
	 		else {
				if (!(in_stream >> output)) {
	  				error = INCORRECT_NUMBER_OF_PLUGBOARD_PARAMETERS;
	  				cerr << "Incorrect (odd) number of parameters in plugboard file " << filename << endl;
				}
				else if (!(output >= 0 && output<= NUM_OF_LETTERS-1)) {
	 				error = INVALID_INDEX;
	 				cerr << output << " is not a number between 0 and 25 in plugboard file " << filename << endl;
				}
				else {
	  				if (mapping[output] != output) {
	    				error = IMPOSSIBLE_PLUGBOARD_CONFIGURATION;
	    				cerr << "Incorrect mapping of letter to more than one letter in plugboard file " << filename << endl;
	  				}
	  				else if (input == output) {
	    				error = IMPOSSIBLE_PLUGBOARD_CONFIGURATION;
	    				cerr << "Incorrect mapping of letter to itself in plugboard file  " << filename << endl;
	  				}
	  				else {
	    				mapping[input] = output;
	    				mapping[output] = input;
	  				}
				}
      		}
    	}
	in_stream.close();
}

int Plugboard::encrypt(const int &letter) {
	return mapping[letter];
}



