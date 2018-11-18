/* ANDREEA ANICAI C++ ENIGMA C2

The Rotor - each maps a letter to a specific other letter - given
in the configuration file, but they can also rotate, which changes
the mapping to a different output. They have notches - designated 
letters that when reaching the 12 o'clock position trigger the rotation
of the adjacent rotor. 

The rotors are mapped as a 2D array - mapping[0][] contains the outer
letters which rotate and mapping[1][] which represents the current mapping.

The top position designated the letter currently at 12 o'clock. 

*/

#ifndef ROTOR_H
#define ROTOR_H

#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include "utilities.h"
#include "errors.h"
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
	int shift_left(const int &letter); 
	int shift_right(const int &letter); 
	void rotate();

	friend int set_rotor_position(Rotor **rotor, int number_of_rotors, const char *filename);
};

#endif

