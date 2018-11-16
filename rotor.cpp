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

/*
int main(){

	string filename;
	filename = "rotors/I.rot";
	Rotor *rotor;
	rotor = new Rotor(filename);
	for(int i=0; i<26; i++) {
		cout<< "mapping[" << i << "]= " << rotor->mapping[1][i] << endl;
	}

	int letter = 5;
	int letter_r = rotor->encrypt_right(letter);
	int letter_l = rotor->encrypt_left(letter);

	cout<< "letter was 5 and it encrypts right to "<< letter_r << endl;
	cout<< "letter was 5 and it encrypts left to "<< letter_l << endl;

	return 0;
}
*/

Rotor::Rotor (string filename){
	error = 0;

	for (int i=0; i<26; i++){ /* Initialise rotor to baseline configuration */
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

  	int i, j, input;

  	/*if (in_stream >> input) {
		cerr << "Non-numeric character for mapping in rotor file " << filename << endl;
		error = 4; 
	}
  	while (!in_stream.eof() && (error == 0) && (i<26)) { // Put first 26 numbers into the rotor mapping array 
  		i = 0;
  		if (!(in_stream >> input)) {
			cerr << "Non-numeric character for mapping in rotor file 1" << filename << endl;
			error = 4; 
  		if (!(in_stream >> input))
  			error = 7; 
	  	if (!(input >= 0 && input<= 25)) // Verify range 
			error = 3; 
		for (j=0; j<i; j++) { // Check if number has already been mapped 
			if((i>0) && (mapping[1][j] == input) )
				error = 7; 
		}
	
		mapping[1][i] = input;
		i++;
	}
	*/


	/*
	if (error == 0) { // Put notch specifications into notch pointer array 
		notch = new int[26];
		i = 0; 

		while (!in_stream.eof() && (error == 0)) {

			if (!(in_stream >> input)) {
				cerr << "Non-numeric character for mapping in rotor file 2 " << filename << endl;
				error = 4; 
			}
	  		if (!(input >= 0 && input<= 25)) // Verify range 
				error = 3; 
			for (int j=0; j<i; j++) //  Check if number has already been mapped 
				if ((i>0) && (notch[j] == input)) {
					error = 7; 
				} 
			notch_counter++;
			notch[i] = input;
			i++;
		}

		in_stream.close();

		if (notch_counter == 0) {
			error = 7; 
		}
	}
	}
	*/


	for (i=0; i<26 && (error == 0); i++){
		in_stream >> input; 
		mapping[1][i] = input;
	}

	notch = new int[26];
	for (i=0; (in_stream >> input) && (error == 0); i++) {
		notch[i] = input;
		notch_counter ++;
	}

	in_stream.close();

}
	int set_rotor_position(Rotor **rotor, int number_of_rotors, const char *filename) {

		int input, i;

		ifstream in_stream;
		in_stream.open(filename);
		if (in_stream.fail()) 
			return 11; 
		/*
		for (i=0; i<number_of_rotors; i++){

			if (in_stream >> input) {
				cerr << "Non-numeric character for mapping in rotor file " << filename << endl;
				error = 4; 
			}
			if (!(in_stream >> input))
  				return 8;	
	  		if (!(input >= 0 && input<= 25)) // Verify range 
				return 3; 
  
			rotor[i]->top_position = input; // Set the top_position pointer of each rotor to the specified input 
			cout<< "top-position is set to " << rotor[i]->top_position << endl;
		}
		*/

		for (i=0; i < number_of_rotors; i++) {
			in_stream >> input; 
			rotor[i]->top_position = input;
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
		top_position = (((top_position+1) + 26 +26) % 26);
	}

	Rotor::~Rotor() {
		delete[] notch;
	}















