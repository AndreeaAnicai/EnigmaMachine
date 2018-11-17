/* 
Check input is well formed:
INVALID_INDEX                             3
NON_NUMERIC_CHARACTER                     4
INVALID_ROTOR_MAPPING                     7
NO_ROTOR_STARTING_POSITION                8
ERROR_OPENING_CONFIGURATION_FILE          11
NO_ERROR                                  0                               0
*/

#include "rotor.h"
using namespace std;

Rotor::Rotor (const char *filename) {
	error = 0;
	top_position = 0;
	notch_counter = 0;
	notch = NULL;
	int i, j, input;
	for (int i=0; i<NUM_OF_LETTERS; i++){ /* Initialise rotor to baseline configuration */
		mapping[0][i]=i;
		mapping[1][i]=i;
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
	for (i=0; i<NUM_OF_LETTERS && (error == 0); i++) {
		if (!(in_stream >> input)) {
			error = 7;
			cerr << "Input does not contain mappings for all letters" << endl;
		}
     	else if (!(input >= 0 && input<= NUM_OF_LETTERS-1)) {
			error = 3;
			cerr << "Input file contains numbers not in range [0,25]" << endl;
      	}
        else {
        	for (j=0; j<i; j++) {
      			if ((i>0) && (mapping[1][j] == input)) {
      	  			error = 7;
      	  			cerr << "Letter has already been mapped" << endl;
      			}
      	  	}
      		if (error == 0) {
      	  		mapping[1][i] = input;
      		}
        }
	}
	notch = new int[NUM_OF_LETTERS];
	for (i=0; (in_stream >> input) && (error == 0); i++) {
		if (!(input >= 0 && input<= NUM_OF_LETTERS-1)) {
			error = 3;
			cerr << "Input file contains numbers not in range [0,25]" << endl;
		}
		else {
        	for (j=0; j<i; j++) {
      			if ((i>0) && (notch[j] == input)) {
      	  			error = 7;
      	  			cerr << "Notch has already been assigned" << endl;
      			}
      			if (error == 0) {
      				notch[i] = input;
					notch_counter ++;
      			}
      		}
      	}
	}
	in_stream.close();
}
	int set_rotor_position(Rotor **rotor, int number_of_rotors, const char *filename) {

		int input, i, error;

		ifstream in_stream;
		in_stream.open(filename);
		if (in_stream.fail()) {
			return 11; 
			cerr << "Input file cannot be opened" << endl;
		}
		if(check_input_valid(filename) == 0) {
			error = 4;
			cerr << "Input file contains non-digit characters" << endl;
		}
		for (i=0; i < number_of_rotors; i++) {
			if (!(in_stream >> input)) {
				error = 8;
				cerr << "Input does not contain rotor starting positions" << endl;
			}
			else if (!(input >= 0 && input<= NUM_OF_LETTERS-1)) {
				error = 3;
				cerr << "Input file contains numbers not in range [0,25]" << endl;
      		}
      		else {
      			rotor[i]->top_position = input;
      		}
		}
		return 0;
	}

	void Rotor::rotate() {
		top_position = (((top_position+1) + NUM_OF_LETTERS + NUM_OF_LETTERS) % NUM_OF_LETTERS);
	}

	int Rotor::shift_left(const int &letter){
		return mapping[1][letter];
	}

	int Rotor::shift_right(const int &letter) {
		for (int i=0; i<NUM_OF_LETTERS; i++) {
			if(mapping[1][i] == letter)
				return mapping[0][i];
		}
		return letter;
	} 

	Rotor::~Rotor() {
		delete[] notch;
	}















