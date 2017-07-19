all: main
main: main.cpp lodepng.o ../lodepng/lodepng.h
	g++ main.cpp lodepng.o -o main
lodepng.o: ../lodepng/lodepng.cpp ../lodepng/lodepng.h
	g++ -c ../lodepng/lodepng.cpp -o lodepng.o 
clean:
	rm -f *.o main

