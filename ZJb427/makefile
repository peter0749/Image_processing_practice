CC = g++
UTILS_DIR = ../utils
IMAGE_DIR = ../Image
IMG_LIB = ../lib

all: main zjb427 effect dep
dep:
	ln -s ${IMG_LIB}/libImageProcess.so.1.0.0 libImageProcess.so.1.0.0
main: main.cpp ${UTILS_DIR}/utils.h ${IMAGE_DIR}/Image.h ${IMAGE_DIR}/Pix.h ${IMAGE_DIR}/PixDouble.h LinearGradient.h LinearGradient.o
	g++ main.cpp LinearGradient.o -L${IMG_LIB} -lImageProcess -o main
effect: effect.cpp ${UTILS_DIR}/utils.h ${IMAGE_DIR}/Image.h ${IMAGE_DIR}/Pix.h ${IMAGE_DIR}/PixDouble.h LinearGradient.h LinearGradient.o
	g++ effect.cpp LinearGradient.o -L${IMG_LIB} -lImageProcess -o effect
LinearGradient.o: LinearGradient.cpp LinearGradient.h
	g++ -c LinearGradient.cpp -o LinearGradient.o
zjb427: zjb427.cpp
	g++ zjb427.cpp -o zjb427
clean:
	rm -f libImageProcess*
	rm -f main *.o zjb427 effect

