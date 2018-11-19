#include "enigma.h"
using namespace std;

Enigma::Enigma(int argc, char **argv) {
	int i, j;
	string filename, pb = ".pb", rf = ".rf", rot = ".rot", pos = ".pos";
	error = 0;
	number_of_rotors = 0;
	plugboard = NULL;
	reflector = NULL;

	if (argc == 0 || argc == 1 || argc == 2) {
		error = INSUFFICIENT_NUMBER_OF_PARAMETERS; 
		cerr << "Insufficient number of parameters - please include configuration files for plugboard and rotor" << endl;
	}
	else {
		for (i=0; i<argc; i++) {
			filename = argv[i];
			if (filename.find(pb) != std::string::npos) {
				plugboard = new Plugboard(argv[i]);
				if (error == 0) {
					error = plugboard->error;
				}
			}
			if (filename.find(rf) != std::string::npos) {
				reflector = new Reflector(argv[i]);
				if (error == 0) {
					error = reflector->error;
				}	
			}
		}
	}
	if (error == 0) {
		if (argc == 4) {
			error = INSUFFICIENT_NUMBER_OF_PARAMETERS; 
			cerr << "Insufficient number of parameters!" << endl;
		}
		else if (argc > 4) {
			number_of_rotors = argc-4;
			rotor = new Rotor*[argc-4];

			for (i=0; (i < (argc-4) && (error == 0)); i++) {
				rotor[i] = new Rotor(argv[i+3]);  
				error = rotor[i]->error;
				if (error != 0) {
					for (j=0; j<=i; j++)
		  				delete rotor[j];
					delete [] rotor;
	     		} 	
	     	}	
			if (error == 0) {
				error = set_rotor_position(rotor, argc-4, argv[argc-1]); 
			}
		}
	}
}

int Enigma::encrypt(const int &letter) {

	int i=0, j=0, letter_index;
	if (number_of_rotors > 0) { 
		rotor[number_of_rotors - 1]->rotate();
		for (i = number_of_rotors -1; i>0; i--) { 
			for (j=0; j < (rotor[i]->notch_counter); j++) {
				if (rotor[i]->top_position == rotor[i]->notch[j]) {
					rotor[i-1]->rotate();
				}
			}
		}
	}
	letter_index = plugboard->encrypt(letter);
	if (number_of_rotors > 0) {
		for (i = number_of_rotors-1; i>=0; i--) {
			letter_index = ((letter_index + rotor[i]->top_position) + NUM_OF_LETTERS + NUM_OF_LETTERS) % NUM_OF_LETTERS;
			letter_index = rotor[i]->shift_left(letter_index);
			letter_index = ((letter_index - rotor[i]->top_position) + NUM_OF_LETTERS + NUM_OF_LETTERS) % NUM_OF_LETTERS;
		}
	}
	letter_index = reflector->encrypt(letter_index);
		if (number_of_rotors > 0) { 
			for (i=0; i <= number_of_rotors-1; i++) {
				letter_index = ((letter_index + rotor[i]->top_position) + NUM_OF_LETTERS + NUM_OF_LETTERS) % NUM_OF_LETTERS;
				letter_index = rotor[i]->shift_right(letter_index);
				letter_index = ((letter_index - rotor[i]->top_position) + NUM_OF_LETTERS + NUM_OF_LETTERS) % NUM_OF_LETTERS;
			}
		}	 
		letter_index = plugboard->encrypt(letter_index);
	return letter_index;
}
