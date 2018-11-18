#include "reflector.h"
using namespace std;

int check_input_valid(const string &filename);

Reflector::Reflector(const char *filename) {
	int input, output, count = 0;
	error = 0;
	for (int i=0; i<NUM_OF_LETTERS; i++){ /* Initialise reflector to baseline configuration */
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
	 		error = INVALID_REFLECTOR_MAPPING;
	 	}
	 	else {
			if (!(in_stream >> output) && (count <= 13)) {
	  			error = INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS;
	  		}
			else if (!(output >= 0 && output<= NUM_OF_LETTERS-1)) {
	 			error = INVALID_INDEX;
	 		}
			else {
	  			if (mapping[output] != output){
	    			error = INVALID_REFLECTOR_MAPPING;
	    		}
	  			else if (input == output) {
	    			error = INVALID_REFLECTOR_MAPPING;
	  			}
	  			else {
	    			mapping[input] = output;
	    			mapping[output] = input;
	  			}
			}
      	}
    }
    if (count != NUM_OF_PAIRS && error == 0) {
		error = INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS;
    }
in_stream.close();
}

int Reflector::encrypt(const int &letter) {
	return mapping[letter];
}
