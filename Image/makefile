all: ImageProcess.o Pix.o PixDouble.o
ImageProcess.o: Image.cpp Image.h
	g++ -c Image.cpp -o ImageProcess.o
Pix.o: Pix.cpp Pix.h
	g++ -c Pix.cpp -o Pix.o
PixDouble.o: PixDouble.cpp PixDouble.h
	g++ -c PixDouble.cpp -o PixDouble.o
clean:
	rm -f *.o

