/* ANDREEA ANICAI C++ ENIGMA C2

The Plugboard - swaps letters' inputs before the
rotors and after passing through the reflector and
rotors, according to the confuguration file (ending in .pb)

All letters are initially mapped to themselves and then
changed according to the configuration file.

*/

#ifndef PLUGBOARD_H
#define PLUGBOARD_H

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include "utilities.h"
#include "errors.h"
#include "check_input_valid.h"
using namespace std;

class Plugboard{
private:
	int mapping[NUM_OF_LETTERS];
public:
	int error; 
	Plugboard(const char *filename);
	int encrypt(const int &letter);
};

#endif 
