#include "reflector.h"
using namespace std;

Reflector::Reflector(const char *filename) {
	int input = 0, output = 0, count = 0, i;
	error = 0;
	for (i=0; i<NUM_OF_LETTERS; i++){ 
		mapping[i] = i;
	}
	ifstream in_stream;
 	in_stream.open(filename);

  	if (in_stream.fail()) {
		error = ERROR_OPENING_CONFIGURATION_FILE; 
		cerr << "Error opening reflector configuration file " << filename << endl;
  	}
	if(check_input_valid(filename) == 0) {
		error = NON_NUMERIC_CHARACTER;
		cerr << "Non-numeric character for mapping in reflector file " << filename << endl;
	}
	while ((in_stream >> input) && (error == 0)) {
      	count++;
      	if (count > NUM_OF_PAIRS) {
			error = INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS;
			cerr << "Incorrect (odd) number of parameters in reflector file reflector.rf " << filename << endl;
		}
      	else if (!(input >= 0 && input<= NUM_OF_LETTERS-1)) {
			error = INVALID_INDEX;
			cerr << input << " is not a number between 0 and 25 in reflector file " << filename << endl;
      	}
     	else if (mapping[input] != input) {
	 		error = INVALID_REFLECTOR_MAPPING;
	 		cerr << "Incorrect mapping of letter which has already been mapped in reflector file  " << filename << endl;
	 	}
	 	else {
	 		if (!(in_stream >> output) && (count <= NUM_OF_PAIRS)) {
	  			error = INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS;
	  			cerr << "Incorrect (odd) number of parameters in reflector file " << filename << endl;
			}
			else if (!(output >= 0 && output<= NUM_OF_LETTERS-1)) {
	 			error = INVALID_INDEX;
	 			cerr << output << " is not a number between 0 and 25 in reflector file " << filename << endl;
	 		}
			else {
	  			if (mapping[output] != output){
	    			error = INVALID_REFLECTOR_MAPPING;
	    			cerr << "Incorrect mapping of letter to more than one letter in reflector file " << filename << endl;
	    		}
	  			else if (input == output) {
	    			error = INVALID_REFLECTOR_MAPPING;
	    			cerr << "Incorrect mapping of letter to itself in reflector file " << filename << endl;
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
		cerr << "Insufficient number of mappings in reflector file " << filename << endl;
    }
in_stream.close();
}

int Reflector::encrypt(const int &letter) {
	return mapping[letter];
}
