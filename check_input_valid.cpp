#include "check_input_valid.h"

using namespace std;

/* Check input is digit NON_NUMERIC_CHARACTER (4) */

/*
int main() {

	const char *filename;
	filename = "plugboards/I.pb";
	int error = check_input_valid(filename);
	cout<< "error is " << error << endl;

	return 0;
}
*/

int check_input_valid(const string &filename) {

	string string;
	ifstream in_stream;
  	in_stream.open(filename);

  	if (!in_stream)
  		return 1;

	while (in_stream >> string)
		for (int i=0; i< int(string.length()); i++) {
			if(!isdigit(string[i]))
				return 0;
	}
	return 1;
}
