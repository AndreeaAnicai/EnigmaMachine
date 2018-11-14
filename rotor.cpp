/* 
The rotor should have:
- an absolute frame - 12 o'clock position
- each letter mapped with regards to that frame of reference

Input:
- 26 numbers separated by white space specifying encoding
- remaining numbers specifying the positions of the notches

Output informative message
Exit as input is read

Check input is well formed:
INVALID_INDEX                             3
NON_NUMERIC_CHARACTER                     4
INVALID_ROTOR_MAPPING                     7
NO_ROTOR_STARTING_POSITION                8
ERROR_OPENING_CONFIGURATION_FILE          11
NO_ERROR                                  0                               0 
*/

#include "rotor.h"

using namespace std;

Rotor::Rotor (string filename){
	error = 0;

	/* Initialise rotor to baseline configuration */
	for (int i=0; i<26; i++){
		mapping[0][i]=i;
		mapping[1][i]=i;
	}

	notch = NULL;
	notch_counter = 0;
	top_position = 0;

	ifstream in_stream;
  	in_stream.open(filename);
  	if (in_stream.fail()) /* Check filename can be opened */
		error = 11; 

  	string number;
  	int input = 0;

  	for(int i=0; i<26 && (error == 0); i++) { /* Put first 26 numbers into the rotor mapping array */
  		if (!(in_stream >> number))
  			error = 7; 
      	if (!check_if_number(number)) /* Verify if digit */
			error = 4; 

		input = stoi(number);

	  	if (!(input >= 0 && input<= 25)) /* Verify range */
			error = 3; 
		for (int j=0; j<i; j++) { /* Check if number has already been mapped */
			if( (i>0) && (mapping[1][j] == input) ){
				error = 7; 
				break;
			}
			else 
				mapping[1][i] = input;
		}

	}
	if (error == 0) { /* Put notch specifications into notch pointer array */
		int *notch, i;
		notch = new int[26];

		for (i=0; (in_stream >> number) && (error == 0); i++) {
      		if (!check_if_number(number)) /* Verify if digit */
				error = 4;

			input = stoi(number);

	  		if (!(input >= 0 && input<= 25)) /* Verify range */
				error = 3; 
			for (int j=0; j<i; j++) { /* Check if number has already been mapped*/
				if( (i>0) && (notch[j] == input)){
					error = 7; 
					break;
				}
				else {
					notch[i] = input;
					notch_counter++;
				}
			}
		}
	in_stream.close();

	if (notch_counter == 0)
		error = 7; 
	
	}
}
	int set_rotor_position(Rotor **rotor, int number_of_rotors, string filename) {

		int input;

		ifstream in_stream;
		in_stream.open(filename);
		if (in_stream.fail()) /* Check filename can be opened */
			return 11; 

		string number;

		for (int i=0; i<number_of_rotors; i++){
			if (!(in_stream >> number))
  				return 8;
      		if (!check_if_number(number)) /* Verify if digit */
				return 4;
     	 	
			input = stoi(number); /* Change 1st number from string to int */
	  		if (!(input >= 0 && input<= 25)) /* Verify range */
				return 3; 
  
			rotor[i]->top_position = input; /* Set the top_position pointer of each rotor to the specified input */
		}
		return 0;
	}

	int Rotor::encrypt_right(const int &letter){
		return mapping[1][letter];
	}

	int Rotor::encrypt_left(const int &letter){
		for (int i=0; i<26; i++) {
			if(mapping[1][i] == letter)
				return mapping[0][i];
		}
		return letter;
	} 

	void Rotor::rotate(){
		top_position = (((top_position+1) + 26) % 26);
	}

	Rotor::~Rotor() {
		delete[] notch;
	}















