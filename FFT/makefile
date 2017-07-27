all: main
main: main.cpp fft.o fft.h fft.hpp
	g++ main.cpp fft.o -o main
fft.o: fft.cpp fft.h
	g++ -c fft.cpp -o fft.o
clean:
	rm -f *.o main

