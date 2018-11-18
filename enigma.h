#ifndef ENIGMA_H
#define ENIGMA_H

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <cstdlib>
#include "plugboard.h"
#include "reflector.h"
#include "rotor.h"
#include "utilities.h"
#include "errors.h"
#include "check_input_valid.h"
using namespace std;

class Enigma {
private:
  Plugboard *plugboard;
  Reflector *reflector;
  Rotor **rotor;
public:
  int number_of_rotors;
  int error; 
  Enigma(int argc, char **argv);
  int encrypt(const int &letter);
};

#endif
