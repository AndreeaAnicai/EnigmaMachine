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

/*
int main(){

	int argc = 7, index = 3;
	char currentChar;
	char *argv[6] = {"plugboards/IV.pb", "reflectors/I.rf", "rotors/I.rot","rotors/II.rot","rotors/III.rot", "rotors/II.pos"}; 
	Enigma *enigma; 
	enigma = new Enigma(argc, argv);
	
	cout << "number of rotors = " << enigma->number_of_rotors << endl;
	index = enigma->encrypt(index);

	cout<< "index after enigma = " << index << endl;

	currentChar = char(index) + 65;
	cout << "letter is " << currentChar << endl;

	return 0;
}
*/

/* Initialise machine to baseline configuration */
Enigma::Enigma(int argc, char **argv) {
	int i, j;
	error = 0;
	number_of_rotors = 0;
	plugboard = NULL;
	reflector = NULL;
	/*rotor = NULL*/

	if (argc == 0 || argc == 1 || argc == 2) /* Check if the file is missing config for plugboard/ reflectors/ rotor pos */
		error = 1; 

	if (error == 0) {
	/**/plugboard = new Plugboard(argv[1]); /* 1st parameter = plugboard */
	error = plugboard->error;
	//cout<< "error plugboard " << plugboard->error << endl;
    }

	if (error == 0) {
		/**/reflector = new Reflector(argv[2]); /* 2nd parameter = reflector */
		error = reflector->error; 
		//cout<< "error reflector " << reflector->error << endl;

		if (error == 0) {
			if(argc == 4) {
				error = 1; 
				//cout << "error from incorrect arg " << error << endl;
			}
			else if (argc > 4) {

				number_of_rotors = argc-4;
				rotor = new Rotor*[argc-4];

				for (i=0; (i < (argc-4) && (error == 0)); i++) {
					rotor[i] = new Rotor(argv[i+2]);  /* 1st .rot file in argv */ 
					error = rotor[i]->error;
					//cout<< "error rotor " << i << " has error " << rotor[i]->error << endl;

					
					if (error != 0) {
						for (j=0; j<=i; j++)
		  					delete rotor[j];
						delete [] rotor;
	     			} 
	     			
	     		}
	     		
				if (error == 0)
				error = set_rotor_position(rotor, argc-4, argv[argc-2]); /* argv[argc-1] - last element before input text */ 
				//cout<< "Return of set position = " << error << endl;
				
			}
		}
	}
} 	

int Enigma::encrypt(const int &letter) {

	int i=0, j=0, letter_input;
	//cout<< "Input letter index = "<< letter << endl;

	/* Rotate the right most rotor before 1st encoding */
	if (number_of_rotors > 0) {
		rotor[number_of_rotors - 1]->rotate();
		//cout<< "Trying to rotate rotor " <<  endl;

		/* Rotate rotor to the left if rotor to the right hits notch */
		for (i = number_of_rotors -1; i>0; i--) {
			for (j=0; j < (rotor[i]->notch_counter); j++) {
				if (rotor[i]->top_position == rotor[i]->notch[j])
					rotor[i-1]->rotate();
			}
		}
	}


	/* Get encoding from plugboard if it exists */
	letter_input = plugboard->encrypt(letter);
	//cout<< "1. Letter after first plugboard pass "<< letter_input << endl;

	/* Pass through rotors and encode at every step */
	if (number_of_rotors > 0) {
		//cout<< "In the if for looping over rotors " << "no rotors = " << number_of_rotors << endl;

		/* Encode according to rotor top position, right to left */
		for (i = number_of_rotors-1; i>=0; i--) {

			letter_input = ((letter_input + rotor[i]->top_position) + 26 + 26) % 26;
			//cout<< "letter + tp forward "<< letter_input << " rotor " << i << endl;

			letter_input = rotor[i]->encrypt_right(letter_input);
			//cout<< "letter encrypt to right "<< letter_input << " rotor " << i << endl;

			letter_input = ((letter_input - rotor[i]->top_position) + 26 +26) % 26;
			//cout<< "letter - tp forward "<< letter_input << " rotor " << i << endl;
		}

		/* Pass through reflector and encode */
		letter_input = reflector->encrypt(letter_input);
		//cout<< "2. Letter after reflector "<< letter_input << endl;

		if (number_of_rotors > 0) {

			/* Encode according to rotor top position, left to right */
			for (i=0; i <= number_of_rotors-1; i++) {
			letter_input = ((letter_input + rotor[i]->top_position) + 26 +26) % 26;
			//cout<< "letter + tp backward "<< letter_input << " rotor " << i << endl;

			letter_input = rotor[i]->encrypt_left(letter_input);
			//cout<< "letter encrypt to left "<< letter_input << " rotor " << i << endl;

			letter_input = ((letter_input - rotor[i]->top_position) + 26 +26) % 26;
			//cout<< "letter - tp backward "<< letter_input << " rotor " << i << endl;
			}
		}

		/* Pass through plugboard again before output */
		letter_input = plugboard->encrypt(letter_input);
		//cout<< "3. letter plugboard final "<< letter_input << endl;
	}
	return letter_input;

}

