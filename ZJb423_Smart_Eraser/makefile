IMAGE_PATH=../Image
all: main
main: main.cpp Image.o Eraser.o Eraser.h utils.h utils.o
	g++ main.cpp utils.o Image.o Eraser.o -o main
Image.o: ${IMAGE_PATH}/Image.cpp ${IMAGE_PATH}/Image.h
	g++ -c ${IMAGE_PATH}/Image.cpp -o Image.o
Eraser.o: Eraser.h Eraser.cpp
	g++ -c Eraser.cpp -o Eraser.o
utils.o: utils.h utils.cpp
	g++ -c utils.cpp -o utils.o
clean:
	rm -f *.o main

