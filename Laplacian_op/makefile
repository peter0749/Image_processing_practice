LIB_PATH=../lib
UTILS_PATH=../utils
FLAG=
all: main 
main: main.cpp Laplacian.o Laplacian.h ${UTILS_PATH}/utils.h libImageProcess.so.1.0.0
	g++ -std=c++11 main.cpp Laplacian.o -I${UTILS_PATH} -L${LIB_PATH} -lImageProcess -o main ${FLAG}
libImageProcess.so.1.0.0:
	ln -s ${LIB_PATH}/libImageProcess.so.1.0.0 libImageProcess.so.1.0.0
Laplacian.o: Laplacian.cpp Laplacian.h
	g++ -std=c++11 -c Laplacian.cpp -I${UTILS_PATH} -o Laplacian.o ${FLAG}
clean:
	rm -f libImageProcess*
	rm -f *.o main zjb436
	rm -rf *.dSYM

