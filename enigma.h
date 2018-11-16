#ifndef ENIGMA_H
#define ENIGMA_H

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include "plugboard.h"
#include "reflector.h"
#include "rotor.h"
#include "check_input_valid.h"
using namespace std;

class Enigma {
private:
  Plugboard *plugboard;
  Reflector *reflector;
  Rotor **rotor;
public:
  int number_of_rotors;
  int error; /* check for error code */
  Enigma(int argc, char **argv);
  //~Enigma(); /* Deconstructor */
  int encrypt(const int &letter);
};

#endif
