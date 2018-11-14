#ifndef PLUGBOARD_H
#define PLUGBOARD_H

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include "check_input_valid.h"

using namespace std;

class Plugboard{
private:
	int mapping[26];
public:
	int error; /* check for error code */
	Plugboard(string filename);
	int encrypt(const int &letter);
};

#endif 
