LIB_PATH=../lib
UTILS_PATH=../utils
FLAG=
all: main
main: main.cpp HistEQ.o HistEQ.h ${UTILS_PATH}/utils.h libImageProcess.so.1.0.0
	g++ -std=c++11 main.cpp HistEQ.o -Ofast -I${UTILS_PATH} -L${LIB_PATH} -lImageProcess -o main ${FLAG}
libImageProcess.so.1.0.0:
	ln -s ${LIB_PATH}/libImageProcess.so.1.0.0 libImageProcess.so.1.0.0
HistEQ.o: HistEQ.cpp HistEQ.h
	g++ -std=c++11 -c HistEQ.cpp -Ofast -I${UTILS_PATH} -o HistEQ.o ${FLAG}
clean:
	rm -f libImageProcess*
	rm -f *.o main 
	rm -rf *.dSYM

