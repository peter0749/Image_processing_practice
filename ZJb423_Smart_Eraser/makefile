LIB_PATH=../lib
UTILS_PATH=../utils
FLAG=
all: main
main: main.cpp Eraser.o Eraser.h ${UTILS_PATH}/utils.h libImageProcess.so.1.0.0
	g++ main.cpp Eraser.o -I${UTILS_PATH} -L${LIB_PATH} -lImageProcess -o main ${FLAG}
libImageProcess.so.1.0.0:
	ln -s ${LIB_PATH}/libImageProcess.so.1.0.0 libImageProcess.so.1.0.0
Eraser.o: Eraser.cpp Eraser.h
	g++ -c Eraser.cpp -I${UTILS_PATH} -o Eraser.o ${FLAG}
clean:
	rm -f libImageProcess*
	rm -f *.o main
	rm -rf *.dSYM

