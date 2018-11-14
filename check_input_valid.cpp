#include "check_input_valid.h"

using namespace std;

/* Check input is digit NON_NUMERIC_CHARACTER (4) */
bool check_if_number(const string &string) {
	for (int i=0; i< int(string.length()); i++) {
		if(! isdigit(string[i]) )
			return 0;
	}
	
	return 1;
}


