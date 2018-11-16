/* Rotor maps to the one on the left during input 
and to the one on the right during output */

/* also determines of other rotors via notch */

#ifndef ROTOR_H
#define ROTOR_H

#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include "check_input_valid.h"

using namespace std;

class Rotor{
private:
	int mapping[2][26];
public:
	int error; /* Check for error code */
	int* notch;
	int notch_counter;
	int top_position;

	Rotor(string filename);
	~Rotor(); /* Deconstructor */

	friend int set_rotor_position(Rotor **rotor, int number_of_rotors, const char *filename);
	int encrypt_right(const int &letter); /* Right to left */
	int encrypt_left(const int &letter); /* Left to right */
	void rotate();
};

#endif

