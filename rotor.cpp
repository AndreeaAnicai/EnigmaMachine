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
		error = ERROR_OPENING_CONFIGURATION_FILE; 
  	}
	if(check_input_valid(filename) == 0) {
		error = NON_NUMERIC_CHARACTER;
	}
	for (i=0; i<NUM_OF_LETTERS && (error == 0); i++) {
		if (!(in_stream >> input)) {
			error = INVALID_ROTOR_MAPPING;
		}
     	else if (!(input >= 0 && input<= NUM_OF_LETTERS-1)) {
			error = INVALID_INDEX;
      	}
        else {
        	for (j=0; j<i; j++) {
      			if ((i>0) && (mapping[1][j] == input)) {
      	  			error = INVALID_ROTOR_MAPPING;
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
			error = INVALID_INDEX;
		}
		else {
			/*
        	for (j=0; j<i; j++) {
      			if ((i>0) && (notch[j] == input)) {
      	  			error = INVALID_ROTOR_MAPPING;
      			}
      		*/
      		if (error == 0) {
      			notch[i] = input;
				notch_counter ++;
      			
      		}
      	}
	}
	in_stream.close();

	if (notch_counter == 0) {
		error = INVALID_ROTOR_MAPPING;
	}
}
	int set_rotor_position(Rotor **rotor, int number_of_rotors, const char *filename) {
		int input, i;
		ifstream in_stream;
		in_stream.open(filename);
		if (in_stream.fail()) {
			return ERROR_OPENING_CONFIGURATION_FILE; 
		}
		if(check_input_valid(filename) == 0) {
			return NON_NUMERIC_CHARACTER;
		}
		for (i=0; i < number_of_rotors; i++) {
			if (!(in_stream >> input)) {
				return NO_ROTOR_STARTING_POSITION;
			}
			else if (!(input >= 0 && input<= NUM_OF_LETTERS-1)) {
				return INVALID_INDEX;
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















