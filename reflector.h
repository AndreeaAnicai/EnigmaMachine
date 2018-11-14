#ifndef REFLECTOR_H
#define REFLECTOR_H

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include "check_input_valid.h"

using namespace std;

class Reflector{
private:
	int mapping[26];
public:
	int error; /* check for error code */
	Reflector(string filename);
	int encrypt(const int &letter);
};

#endif
