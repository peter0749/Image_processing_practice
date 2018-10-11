all: ImageProcess.o Pix.o PixDouble.o
ImageProcess.o: Image.cpp Image.h
	g++ -std=c++11 -c Image.cpp -o ImageProcess.o
Pix.o: Pix.cpp Pix.h
	g++ -std=c++11 -c Pix.cpp -o Pix.o
PixDouble.o: PixDouble.cpp PixDouble.h
	g++ -std=c++11 -c PixDouble.cpp -o PixDouble.o
clean:
	rm -f *.o

