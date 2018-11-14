/* 
The plugboard swaps 2 letter's input signals if they are 
connected. If there is no conenction the input signal remains
the same.

Input:
- even number of numbers (possibly 0) 
- separated by white space
- read off in pairs
- numbers represent the indexes of the letters

Output informative message
Exit as input is read

Check input is well formed:
INVALID_INDEX                             3
NON_NUMERIC_CHARACTER                     4
IMPOSSIBLE_PLUGBOARD_CONFIGURATION        5
INCORRECT_NUMBER_OF_PLUGBOARD_PARAMETERS  6
ERROR_OPENING_CONFIGURATION_FILE          11
NO_ERROR                                  0 
*/


#include "plugboard.h"

using namespace std;

Plugboard::Plugboard(string filename){
	error = 0;

	/* Initialise plugboard to baseline configuration */
	for (int i=0; i<26; i++){
		mapping[i] = i;
	}

	ifstream in_stream;
	in_stream.open(filename);

	/* Check filename can be opened */
	if (in_stream.fail())
		error = 11; 

	string number;
	int input = 0, output = 0, count = 0;

	while ( (in_stream >> number) && (error == 0) ) {
		
		count++; /* Count the input pairs */
		if (count > 13) 
			error = 6; 
      	if (!check_if_number(number)) /* Verify if digit */
			error = 4; 

		input = stoi(number); /* Change 1st number from string to int */

	  	if (!(input >= 0 && input<= 25)) /* Verify range */
			error = 3; 
		if (mapping[input] != input) /* Check if letter has been previously configured */
	  		error = 5; 
		if (!(in_stream >> number)) /* Read the 2nd number in the pair / check it exists */
	  		error = 6;
		if (!check_if_number(number)) /* Verify if digit */
	  		error = 4; 

	  	output = stoi (number); /* Change 2nd number from string to int */

	  	if (!(output >= 0 && output<= 25))  /* Verify range */
			error = 3; 
	 	if (mapping[output] != output) /* Check if letter has been previously configured */
	    		error = 5; 
	 	else if (input == output) /* Check if letter connects to itself */
	    			error = 5; 
	  	else { 
	    	mapping[input] = output; /* Swap numbers' configuration */
	    	mapping[output] = input;
	  			}
    }

	in_stream.close();
}

int Plugboard::encrypt(const int &letter){
	return mapping[letter];
}



