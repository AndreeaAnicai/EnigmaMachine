#ifndef ROTOR_H
#define ROTOR_H

#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include "utilities.h"
#include "check_input_valid.h"

using namespace std;

class Rotor{
private:
	int mapping[2][NUM_OF_LETTERS];
public:
	int error; 
	int* notch;
	int notch_counter;
	int top_position;

	Rotor(const char *filename);
	~Rotor(); 

	friend int set_rotor_position(Rotor **rotor, int number_of_rotors, const char *filename);
	int shift_left(const int &letter); /* Right to left */
	int shift_right(const int &letter); /* Left to right */
	void rotate();
};

#endif

