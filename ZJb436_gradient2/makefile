LIB_PATH=../lib
UTILS_PATH=../utils
FLAG=
all: main zjb436
zjb436: zjb436.cpp
	g++ zjb436.cpp -o zjb436 ${FLAG}
main: main.cpp Gradient.o Gradient.h ${UTILS_PATH}/utils.h libImageProcess.so.1.0.0
	g++ main.cpp Gradient.o -I${UTILS_PATH} -L${LIB_PATH} -lImageProcess -o main ${FLAG}
libImageProcess.so.1.0.0:
	ln -s ${LIB_PATH}/libImageProcess.so.1.0.0 libImageProcess.so.1.0.0
Gradient.o: Gradient.cpp Gradient.h
	g++ -c Gradient.cpp -I${UTILS_PATH} -o Gradient.o ${FLAG}
clean:
	rm -f libImageProcess*
	rm -f *.o main zjb436
	rm -rf *.dSYM

