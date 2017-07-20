LODEPNG_PATH=../lodepng
IMAGE_PATH=../Image
UTILS_PATH=../utils.h
all: main
main: main.cpp lodepng.o Image.o ${UTILS_PATH} Eraser.o Eraser.h
	g++ main.cpp lodepng.o Image.o Eraser.o -o main
lodepng.o: ${LODEPNG_PATH}/lodepng.cpp ${LODEPNG_PATH}/lodepng.h
	g++ -c ${LODEPNG_PATH}/lodepng.cpp -o lodepng.o
Image.o: ${IMAGE_PATH}/Image.cpp ${IMAGE_PATH}/Image.h
	g++ -c ${IMAGE_PATH}/Image.cpp -o Image.o
Eraser.o:
	g++ -c Eraser.cpp -o Eraser.o
clean:
	rm -f *.o main

