#ifndef REFLECTOR_H
#define REFLECTOR_H

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include "utilities.h"
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
