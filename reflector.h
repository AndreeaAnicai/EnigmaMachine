/* ANDREEA ANICAI C++ ENIGMA C2

The Reflector - swaps letters' inputs after they have
passed through the rotors, according to the configuration
file (ending in .rf). There should be a mapping for every
letter. 

All letters are initially mapped to themselves and then
changed according to the configuration file.

*/

#ifndef REFLECTOR_H
#define REFLECTOR_H

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include "utilities.h"
#include "errors.h"
#include "check_input_valid.h"
using namespace std;

class Reflector{
private:
	int mapping[NUM_OF_LETTERS];
public:
	int error; 
	Reflector(const char *filename);
	int encrypt(const int &letter);
};

#endif
