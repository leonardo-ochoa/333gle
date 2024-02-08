CFLAGS = -Wall -g -std=c++17

ex6: ex6.o Vector.o
	g++ $(CFLAGS) -o ex6 ex6.o Vector.o

ex6.o: ex6.cc Vector.h
	g++ $(CFLAGS) -c ex6.cc

Vector.o: Vector.cc Vector.h
	g++ $(CFLAGS) -c Vector.cc

clean:
	rm ex6 *.o
