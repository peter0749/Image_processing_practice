IMAGE_PATH=../Image
all: main
main: main.cpp Image.o Eraser.o Eraser.h utils.h utils.o Pix.o PixDouble.o
	g++ main.cpp utils.o Image.o Eraser.o Pix.o PixDouble.o -o main
Image.o: ${IMAGE_PATH}/Image.cpp ${IMAGE_PATH}/Image.h
	g++ -c ${IMAGE_PATH}/Image.cpp -o Image.o
Pix.o: ${IMAGE_PATH}/Pix.cpp ${IMAGE_PATH}/Pix.h
	g++ -c ${IMAGE_PATH}/Pix.cpp -o Pix.o
PixDouble.o: ${IMAGE_PATH}/PixDouble.cpp ${IMAGE_PATH}/PixDouble.h
	g++ -c ${IMAGE_PATH}/PixDouble.cpp -o PixDouble.o
Eraser.o: Eraser.h Eraser.cpp
	g++ -c Eraser.cpp -o Eraser.o
utils.o: utils.h utils.cpp
	g++ -c utils.cpp -o utils.o
clean:
	rm -f *.o main

