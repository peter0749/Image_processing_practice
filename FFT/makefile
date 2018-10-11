all: main FFT2.o
FFT2.o: FFT2.cpp
	g++ -std=c++11 -c FFT2.cpp -o FFT2.o
main: main.cpp FFT.o FFT.h FFT.hpp
	g++ -std=c++11 main.cpp FFT.o -o main
FFT.o: FFT.cpp FFT.h
	g++ -std=c++11 -c FFT.cpp -o FFT.o
clean:
	rm -f *.o main

