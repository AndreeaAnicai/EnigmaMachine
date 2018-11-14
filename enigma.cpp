/* The enigma function encrypts a message in several steps:
- plugboard - swaps letters connected by a cable 
- rotor - each maps the input letter to a different letter 
- reflector - swaps letters according to specific mapping 

Input:
- int argc - number of parameters passes
- array of c-strings w/ the values of the command line parameters 
	- [0] enigma 
	- [1] plugboard/IV.pb 
	- [2] reflectors/I.rf
	- [3] rotors/II.rot
	- [4] rotors/I.pos
	- <input.txt> 

Check input is well formed:
INSUFFICIENT_NUMBER_OF_PARAMETERS         1
INVALID_INPUT_CHARACTER                   2
INVALID_INDEX                             3
NON_NUMERIC_CHARACTER                     4
IMPOSSIBLE_PLUGBOARD_CONFIGURATION        5
INCORRECT_NUMBER_OF_PLUGBOARD_PARAMETERS  6
INVALID_ROTOR_MAPPING                     7
NO_ROTOR_STARTING_POSITION                8
INVALID_REFLECTOR_MAPPING                 9
INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS  10
ERROR_OPENING_CONFIGURATION_FILE          11
NO_ERROR 								  0

Enigma machine configuration is:

RF <- R0 <- R1 <- R2 <- PB  
|
----> R0 -> R1 -> R2 -> output
*/


#include "enigma.h"

using namespace std;

/* Initialise machine to baseline configuration */
Enigma::Enigma(int argc, char *argv[]) {
	error = 0;
	plugboard = NULL;
	reflector = NULL;
	rotor = NULL;
	number_of_rotors = 0;

	if (argc == 0 || argc == 1 || argc == 2) /* Check if the file is missing config for plugboard/ reflectors/ rotor pos */
		error = 1; 

	plugboard = new Plugboard(argv[1]); /* 1st parameter = plugboard */
	error = plugboard->error;

	if (error == 0) {
		reflector = new Reflector(argv[2]); /* 2nd parameter = reflector */
		error = reflector->error; 

		if (error == 0) {
			if(argc ==4)
				error = 1; 
			else {//argc > 4
				rotor = new Rotor*[argc-4]; /* 3rd parameter = rotor */
				number_of_rotors = argc-4;

				for (int i=0; i<(argc-4) && (error == 0); i++) {
					rotor[i] = new Rotor(argv[i+3]); /* 1st .rot file in argv */
					error = rotor[i]->error;
				}
				if (error == 0)
					error = set_rotor_position(rotor, argc-4, argv[argc-1]); /* argv[argc-1] is the last element before input text */ 

			}
		}
	}
} 	


int Enigma::encrypt(const int &letter) {

	int i=0, j=0;

	/* Get encoding from plugboard if it exists */
	int letter_input = plugboard->encrypt(letter);

	/* Rotate the right most rotor before 1st encoding */
	if (number_of_rotors > 0) {
		rotor[number_of_rotors - 1]->rotate();

		/* Rotate rotor to the left if rotor to the right hits notch */
		for (i = number_of_rotors -1; i>0; i--) {
			for (j=0; j < (rotor[i]->notch_counter); j++) {
				if (rotor[i]->top_position == rotor[i]->notch[j])
					rotor[i-1]->rotate();
			}
		}
	}

	/* Pass through rotors and encode at every step */
	if (number_of_rotors > 0) {

		/* Encode according to rotor top position, right to left */
		for (i=number_of_rotors; i>0; i--) {
			letter_input = ((letter_input + rotor[i]->top_position) + 26) % 26;
			letter_input = rotor[i]->encrypt_right(letter_input);
			letter_input = ((letter_input - rotor[i]->top_position) + 26) % 26;
		}

		/* Pass through reflector and encode */
		letter_input = reflector->encrypt(letter_input);

		if (number_of_rotors > 0) {

			/* Encode according to rotor top position, left to right */
			for (i=0; i < number_of_rotors; i++) {
			letter_input = ((letter_input + rotor[i]->top_position) + 26) % 26;
			letter_input = rotor[i]->encrypt_left(letter_input);
			letter_input = ((letter_input - rotor[i]->top_position) + 26) % 26;
			}
		}

		/* Pass through plugboard again before output */
		letter_input = plugboard->encrypt(letter_input);
	}
	return letter_input;

}
