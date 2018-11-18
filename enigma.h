/* ANDREEA ANICAI C++ ENIGMA C2

The Enigma Machine - it controls the encryption through each component.
The class has pointers to all other objects - plugboard, reflector and
rotors and from each collects the correct letter encryption and the 
error returned.

Enigma machine configuration is:

RF <- R0 <- R1 <- R2 <- PB  
|
----> R0 -> R1 -> R2 -> output
*/

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
  int number_of_rotors;
public:
  int error; 
  Enigma(int argc, char **argv);
  int encrypt(const int &letter);
};

#endif
