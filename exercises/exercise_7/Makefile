CFLAGS = -Wall -g -std=c++17

ex7: Vector.o ex7.o
	g++ $(CFLAGS) -o ex7 Vector.o ex7.o

%.o: %.cc Vector.h
	g++ $(CFLAGS) -c $<

clean:
	rm -rf ex7 *.o *~ *.dSYM