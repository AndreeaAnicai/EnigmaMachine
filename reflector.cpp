/*
The reflector maps each letter to a different one. Letters are wired up in pairs.
Then it sends the mapped letter back through the rotors. 

Input:
- even number of numbers separated by whitespace 
- must have exactly 13 pairs 

Check input is well formed:
INVALID_INDEX                             3
NON_NUMERIC_CHARACTER                     4
INVALID_REFLECTOR_MAPPING                 9
INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS  10
ERROR_OPENING_CONFIGURATION_FILE          11
NO_ERROR                                  0
*/



#include "reflector.h"
using namespace std;

/*
int main(){

	string filename;
	filename = "reflectors/I.rf";
	Reflector *reflector;
	reflector = new Reflector(filename);

	int letter = 5, letter_e;
	for(int i=0; i<26; i++)
		cout<< "mapping[" << i << "]= " << reflector->mapping[i] << endl;
	letter_e = reflector->encrypt(letter);
	cout << "return of rf encryption " << letter_e << endl;

	return 0;
}
*/


Reflector::Reflector(string filename) {
	error = 0;

	for (int i=0; i<26; i++){ /* Initialise reflector to baseline configuration */
		mapping[i] = i;
	}

	ifstream in_stream;
 	in_stream.open(filename);
  	if (in_stream.fail()) /* Check filename can be opened */
		error = 11; 

	int input, output, count = 0;

	/*

	if (!(in_stream >> input)) {
		cerr << "Non-numeric character for mapping in reflector file 1" << filename << endl;
		error = 4; 
	}
	while ( (!in_stream.eof()) && (error == 0) && (count <= 13) ) {
		count++; // Count the input pairs 

		if (!(input>= 0 && input <= 25)) // Verify range 
			error = 3; 
		if (mapping[input] != input) // Check if letter has been previously configured 
	  		error = 9; 

	  	if (error == 0) {
			if (!(in_stream >> output)) // Read the 2nd number in the pair / check it exists 
	  			error = 10; 		
	  		if (!(output >= 0 && output <= 25)) // Verify range 
				error = 3; 
	 		if (mapping[output] != output) // Check if letter has been previously configured 
	    		error = 9;
	 		else if (input == output) // Check if letter connects to itself 
	    		error = 9; 
	  		else {	
	    		mapping[input] = output; // Swap numbers 
	    		mapping[output] = input;
	  		}
	  	}
	  	if (in_stream >> input);
	  	else if (! (in_stream.eof()) )  {
	  		cerr << "Non-numeric character for mapping in plugboard file 2 " << filename << endl;
			error = 4; 
	  	}
    }
    */
    while (!in_stream.eof() && (error == 0)) {
    	count++; 
    		
    	in_stream >> input; 
    	in_stream >> output;

	  	mapping[input] = output; 
	    mapping[output] = input;
	}

in_stream.close();

}

int Reflector::encrypt(const int &letter) {
	return mapping[letter];
}








