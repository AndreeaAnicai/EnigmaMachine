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

Reflector::Reflector(string filename) {
	error = 0;

	for (int i=0; i<26; i++){ /* Initialise reflector to baseline configuration */
		mapping[i] = i;
	}

	ifstream in_stream;
 	in_stream.open(filename);
  	if (in_stream.fail()) /* Check filename can be opened */
		error = 11; 

	string number;
	int input = 0, output = 0, count = 0;

	while ( (in_stream >> number) && (error == 0) && (count <= 13) ) {
		count++; /* Count the input pairs */
      	if (!check_if_number(number)) /* Verify input */
			error = 4;

		input = stoi(number); /* Change 1st number from string to int */

		if (!(input>= 0 && input <= 25)) /* Verify range */
			error = 3; 
		if (mapping[input] != input) /* Check if letter has been previously configured */
	  		error = 9; 
		if (!(in_stream >> number)) /* Read the 2nd number in the pair / check it exists */
	  		error = 10; 	
		if (!check_if_number(number)) /* Verify if digit */
	  		error = 4; 

	  	output = stoi (number); /* Change 2nd number from string to int */
			
	  	if (!(output >= 0 && output <= 25)) /* Verify range */
			error = 3; 
	 	if (mapping[output] != output) /* Check if letter has been previously configured */
	    	error = 9;
	 	else if (input == output) /* Check if letter connects to itself */
	    		error = 9; 
	  	else {	
	    	mapping[input] = output; /* Swap numbers */
	    	mapping[output] = input;
	  		}
    }

    /* Check if reflector configuration is correct */
    if (count != 13) 
    	error = 10;

in_stream.close();

}

int Reflector::encrypt(const int &letter) {
	return mapping[letter];
}








