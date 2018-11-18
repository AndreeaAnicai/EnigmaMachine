enigma: main.o enigma.o plugboard.o reflector.o rotor.o check_input_valid.o 
	g++ -Wall -g main.o enigma.o plugboard.o reflector.o rotor.o check_input_valid.o -o enigma

%.o: %.cpp
	g++ -Wall -g -c $<

main.o: enigma.h errors.h utilities.h

enigma.o: enigma.h plugboard.h reflector.h rotor.h errors.h

.PHONY: clean
clean:
	rm -f enigma *.o