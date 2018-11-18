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
