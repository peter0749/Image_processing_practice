LIB_PATH=../lib
UTILS_PATH=../utils
FLAG=
all: main zjb460 zjb458
zjb460: zjb460.cpp
	g++ -std=c++11 zjb460.cpp -O3 -o zjb460
zjb458: zjb458.cpp
	g++ -std=c++11 zjb458.cpp -O3 -o zjb458
main: main.cpp Threshold.o Threshold.h ${UTILS_PATH}/utils.h libImageProcess.so.1.0.0
	g++ -std=c++11 main.cpp Threshold.o -I${UTILS_PATH} -L${LIB_PATH} -lImageProcess -o main ${FLAG}
libImageProcess.so.1.0.0:
	ln -s ${LIB_PATH}/libImageProcess.so.1.0.0 libImageProcess.so.1.0.0
Threshold.o: Threshold.cpp Threshold.h
	g++ -std=c++11 -c Threshold.cpp -I${UTILS_PATH} -o Threshold.o ${FLAG}
clean:
	rm -f libImageProcess*
	rm -f *.o main zjb460 zjb458
	rm -rf *.dSYM

