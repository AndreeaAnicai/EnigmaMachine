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

/*
int main(){

	string filename;
	filename = "plugboards/I.pb";
	Plugboard *plugboard;
	plugboard = new Plugboard(filename);

	int letter = 5, letter_e;
	for(int i=0; i<26; i++)
		cout<< "mapping[" << i << "]= " << plugboard->mapping[i] << endl;
	letter_e = plugboard->encrypt(letter);
	cout << "return of pb encryption " << letter_e << endl;

	return 0;
}
*/

Plugboard::Plugboard(string filename) {
	error = 0;

	/* Initialise plugboard to baseline configuration */
	for (int i=0; i<26; i++)
		mapping[i] = i;

	ifstream in_stream;
	in_stream.open(filename);

	/* Check filename can be opened */
	if (in_stream.fail())
		error = 11; 

	int input, output, count = 0;

	/*

	if (! (in_stream >> input) ) {
		cerr << "Non-numeric character for mapping in plugboard file 1 " << filename << endl;
		error = 4; 
	}
	while (!in_stream.eof() && (error == 0)) {
		
		count++; // Count the input pairs 
		if (count > 13) 
			error = 6; 
	  	if (!(input >= 0 && input<= 25)) // Verify range 
			error = 3; 
		if (mapping[input] != input) // Check if letter has been previously configured 
	  		error = 5; 

	  	if(error == 0)	{
			if (!(in_stream >> output)) // Read the 2nd number in the pair / check it exists 
	  			error = 6;
	  		if (!(output >= 0 && output<= 25))  // Verify range 
				error = 3; 
	 		if (mapping[output] != output) // Check if letter has been previously configured 
	    		error = 5; 
	 		else if (input == output) // Check if letter connects to itself 
	    		error = 5; 
	  		else { 
	    		mapping[input] = output; // Swap numbers' configuration 
	    		mapping[output] = input;
	  			}
	  	}
	  	if (in_stream >> input);
	  	else if (! (in_stream.eof()) )  {
	  		cerr << "Non-numeric character for mapping in plugboard file 2 " << filename << endl;
			error = 4; 
	  	)

    }*/

    	while (!in_stream.eof() && (error == 0)) {
    		count++; 

    		in_stream >> input; 
    		in_stream >> output;

	  		mapping[input] = output; 
	    	mapping[output] = input;
	    }

	in_stream.close();
}

int Plugboard::encrypt(const int &letter) {
	return mapping[letter];
}



