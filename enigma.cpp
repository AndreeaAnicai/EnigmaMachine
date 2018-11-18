/*
Enigma machine configuration is:

RF <- R0 <- R1 <- R2 <- PB  
|
----> R0 -> R1 -> R2 -> output
*/
#include "enigma.h"
using namespace std;

Enigma::Enigma(int argc, char **argv) {
	int i, j;
	string filename, subs1 = ".pb", subs2 = ".rf", subs3 = ".rot", subs4 = ".pos";
	error = 0;
	number_of_rotors = 0;
	plugboard = NULL;
	reflector = NULL;
	//rotor = NULL

	if (argc == 0 || argc == 1) 
		error = INSUFFICIENT_NUMBER_OF_PARAMETERS; 

	for (i=0; i<argc; i++) {
		filename = argv[i];
		if (filename.find(subs1) != std::string::npos) {
			plugboard = new Plugboard(argv[i]);
			error = plugboard->error;
			//cout<< "plugboard argument is " << argv[i] << endl;
		}
		if (filename.find(subs2) != std::string::npos) {
			reflector = new Reflector(argv[i]);
			error = reflector->error;
			//cout<< "reflector argument is " << argv[i] << endl;
		}
	}
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
	//}
}

int Enigma::encrypt(const int &letter) {

	int i=0, j=0, letter_input;
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
	letter_input = plugboard->encrypt(letter);

	
	if (number_of_rotors > 0) {
		// Encode according to rotor top position, right to left 
		for (i = number_of_rotors-1; i>=0; i--) {
			letter_input = ((letter_input + rotor[i]->top_position) + NUM_OF_LETTERS + NUM_OF_LETTERS) % NUM_OF_LETTERS;
			letter_input = rotor[i]->shift_left(letter_input);
			letter_input = ((letter_input - rotor[i]->top_position) + NUM_OF_LETTERS + NUM_OF_LETTERS) % NUM_OF_LETTERS;
		}
	}
	// Pass through reflector and encode 
	letter_input = reflector->encrypt(letter_input);

		// Encode according to rotor top position, left to right 
		if (number_of_rotors > 0) { 
			for (i=0; i <= number_of_rotors-1; i++) {
				letter_input = ((letter_input + rotor[i]->top_position) + NUM_OF_LETTERS + NUM_OF_LETTERS) % NUM_OF_LETTERS;
				letter_input = rotor[i]->shift_right(letter_input);
				letter_input = ((letter_input - rotor[i]->top_position) + NUM_OF_LETTERS + NUM_OF_LETTERS) % NUM_OF_LETTERS;
			}
		}	
		// Pass through plugboard again before output 
		letter_input = plugboard->encrypt(letter_input);
	return letter_input;
}

