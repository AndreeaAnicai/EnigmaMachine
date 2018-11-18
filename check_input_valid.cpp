#include "check_input_valid.h"
using namespace std;

int check_input_valid(const string &filename) {

	string string;
	ifstream in_stream;
  	in_stream.open(filename);

  	if (!in_stream)
  		return 0;

	while (in_stream >> string)
		for (int i=0; i< int(string.length()); i++) {
			if(!isdigit(string[i]))
				return 0;
	}
	return 1;
}