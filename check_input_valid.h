/* ANDREEA ANICAI C++ ENIGMA C2

This function takes in a string as a paramater and checks
if the string contains any non-digit characters; it returns
0 if the string contains non-digits or it can't open the file
and 1 otherwise.  

*/

#ifndef CHECK_INPUT_VALID_H
#define CHECK_INPUT_VALID_H

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstdlib>
using namespace std;


/* Check input is digit */
int check_input_valid(const string &filename);

#endif 