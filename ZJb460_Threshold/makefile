LIB_PATH=../lib
UTILS_PATH=../utils
FLAG=
all: main zjb460
zjb460: zjb460.cpp
	g++ zjb460.cpp -O3 -o zjb460
main: main.cpp Threshold.o Threshold.h ${UTILS_PATH}/utils.h libImageProcess.so.1.0.0
	g++ main.cpp Threshold.o -I${UTILS_PATH} -L${LIB_PATH} -lImageProcess -o main ${FLAG}
libImageProcess.so.1.0.0:
	ln -s ${LIB_PATH}/libImageProcess.so.1.0.0 libImageProcess.so.1.0.0
Threshold.o: Threshold.cpp Threshold.h
	g++ -c Threshold.cpp -I${UTILS_PATH} -o Threshold.o ${FLAG}
clean:
	rm -f libImageProcess*
	rm -f *.o main zjb460
	rm -rf *.dSYM

