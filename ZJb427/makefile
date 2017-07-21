CC = g++
UTILS_DIR = ../utils
IMAGE_DIR = ../Image

all: main
main: main.cpp ${UTILS_DIR}/utils.h utils.o ${IMAGE_DIR}/Image.h Image.o ${IMAGE_DIR}/Pix.h Pix.o ${IMAGE_DIR}/PixDouble.h PixDouble.o LinearGradient.o LinearGradient.h
	g++ main.cpp Pix.o PixDouble.o Image.o utils.o LinearGradient.o -o main
utils.o: ${UTILS_DIR}/utils.h ${UTILS_DIR}/utils.cpp
	g++ -c ${UTILS_DIR}/utils.cpp -o utils.o
Pix.o: ${IMAGE_DIR}/Pix.h ${IMAGE_DIR}/Pix.cpp
	g++ -c ${IMAGE_DIR}/Pix.cpp -o Pix.o
PixDouble.o: ${IMAGE_DIR}/PixDouble.h ${IMAGE_DIR}/PixDouble.cpp
	g++ -c ${IMAGE_DIR}/PixDouble.cpp -o PixDouble.o
Image.o: ${IMAGE_DIR}/Image.h ${IMAGE_DIR}/Image.cpp
	g++ -c ${IMAGE_DIR}/Image.cpp -o Image.o
LinearGradient.o: LinearGradient.cpp LinearGradient.h
	g++ -c LinearGradient.cpp -o LinearGradient.o
clean:
	rm -f main *.o

