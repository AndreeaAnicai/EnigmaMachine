/*
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

Enigma::Enigma(int argc, char **argv) {
	int i, j;
	error = 0;
	number_of_rotors = 0;
	plugboard = NULL;
	reflector = NULL;
	//rotor = NULL

	if (argc == 0 || argc == 1 || argc == 2) 
		error = 1; 

	if (error == 0) {
	plugboard = new Plugboard(argv[1]); /* 1st parameter = plugboard */
	error = plugboard->error;
	//cout<< "error plugboard " << plugboard->error << endl;
    }

	if (error == 0) {
		reflector = new Reflector(argv[2]); /* 2nd parameter = reflector */
		error = reflector->error; 
		//cout<< "reflector argument is " << argv[2] << endl;
		//cout<< "error reflector " << reflector->error << endl;

		if (error == 0) {
			if(argc == 4) 
				error = 1; 
			else if (argc > 4) {

				number_of_rotors = argc-4;
				rotor = new Rotor*[argc-4];

				for (i=0; (i < (argc-4) && (error == 0)); i++) {
					rotor[i] = new Rotor(argv[i+3]);  /* 1st .rot file in argv */ 
					error = rotor[i]->error;
					//cout<< "argument of rotor " << i << " is " << argv[i+3] << endl;
					//cout<< "error rotor " << i << " has error " << rotor[i]->error << endl;

					
					if (error != 0) {
						for (j=0; j<=i; j++)
		  					delete rotor[j];
						delete [] rotor;
	     			} 	
	     		}
	     		
				if (error == 0)
				error = set_rotor_position(rotor, argc-4, argv[argc-1]); /* argv[argc-1] - last element before input text */ 
				//cout<< "Return of set position = " << error << endl;
				
			}
		}
	}
}

int Enigma::encrypt(const int &letter) {

	int i=0, j=0, letter_input;
	char currentChar;
	
	if (number_of_rotors > 0) { // Rotate the right most rotor before 1st encoding 
		rotor[number_of_rotors - 1]->rotate();
		for (i = number_of_rotors -1; i>0; i--) { // Rotate rotor to the left if rotor to the right hits notch 
			for (j=0; j < (rotor[i]->notch_counter); j++) {
				if (rotor[i]->top_position == rotor[i]->notch[j])
					rotor[i-1]->rotate();
			}
		}
	}
	// Get encoding from plugboard if it exists 
	cout<< "0. input letter is " << char(letter + 65) << endl;
	letter_input = plugboard->encrypt(letter);
	cout<< "1. letter after plugboard is " << char(letter_input + 65) << endl;

	
	if (number_of_rotors > 0) {
		// Encode according to rotor top position, right to left 
		for (i = number_of_rotors-1; i>=0; i--) {
			letter_input = ((letter_input + rotor[i]->top_position) + NUM_OF_LETTERS + NUM_OF_LETTERS) % NUM_OF_LETTERS;
			letter_input = rotor[i]->shift_left(letter_input);
			letter_input = ((letter_input - rotor[i]->top_position) + NUM_OF_LETTERS + NUM_OF_LETTERS) % NUM_OF_LETTERS;
			cout<< "2. R-L letter after rotor " << i << " is " << char(letter_input + 65) << endl;
		}
		// Pass through reflector and encode 
		letter_input = reflector->encrypt(letter_input);
		cout<< "3. letter after reflector is " << char(letter_input + 65) << endl;

		// Encode according to rotor top position, left to right 
		if (number_of_rotors > 0) { 
			for (i=0; i <= number_of_rotors-1; i++) {
			letter_input = ((letter_input + rotor[i]->top_position) + NUM_OF_LETTERS + NUM_OF_LETTERS) % NUM_OF_LETTERS;
			letter_input = rotor[i]->shift_right(letter_input);
			letter_input = ((letter_input - rotor[i]->top_position) + NUM_OF_LETTERS + NUM_OF_LETTERS) % NUM_OF_LETTERS;
			currentChar = char(letter_input + 65);
			cout<< "4. L-R letter after rotor " << i << " is " << currentChar << endl;
			}
		}	
		// Pass through plugboard again before output 
		letter_input = plugboard->encrypt(letter_input);
		cout<< "5. letter after plugboard final " << char(letter_input + 65) << endl;
	
	}
	return letter_input;

}

