LIB_PATH=../lib
UTILS_PATH=../utils
FLAG=
all: main zjb434
zjb434: zjb434.cpp
	g++ -std=c++11 zjb434.cpp -o zjb434 ${FLAG}
main: main.cpp Gradient.o Gradient.h ${UTILS_PATH}/utils.h libImageProcess.so.1.0.0
	g++ -std=c++11 main.cpp Gradient.o -I${UTILS_PATH} -L${LIB_PATH} -lImageProcess -o main ${FLAG}
libImageProcess.so.1.0.0:
	ln -s ${LIB_PATH}/libImageProcess.so.1.0.0 libImageProcess.so.1.0.0
Gradient.o: Gradient.cpp Gradient.h
	g++ -std=c++11 -c Gradient.cpp -I${UTILS_PATH} -o Gradient.o ${FLAG}
clean:
	rm -f libImageProcess*
	rm -f *.o main zjb434
	rm -rf *.dSYM

