LIB_PATH=../lib
UTILS_PATH=../utils
FLAG=
all: main zjb438
zjb438: zjb438.cpp
	g++ -std=c++11 zjb438.cpp -o zjb438 ${FLAG}
main: main.cpp EnergyMap.o EnergyMap.h SeamCarve.o SeamCarve.h ${UTILS_PATH}/utils.h libImageProcess.so.1.0.0
	g++ -std=c++11 main.cpp EnergyMap.o SeamCarve.o -I${UTILS_PATH} -L${LIB_PATH} -lImageProcess -o main ${FLAG}
libImageProcess.so.1.0.0:
	ln -s ${LIB_PATH}/libImageProcess.so.1.0.0 libImageProcess.so.1.0.0
EnergyMap.o: EnergyMap.cpp EnergyMap.h
	g++ -std=c++11 -c EnergyMap.cpp -I${UTILS_PATH} -o EnergyMap.o ${FLAG}
SeamCarve.o: SeamCarve.cpp SeamCarve.h
	g++ -std=c++11 -c SeamCarve.cpp -I${UTILS_PATH} -o SeamCarve.o ${FLAG}
clean:
	rm -f libImageProcess*
	rm -f *.o main zjb438
	rm -rf *.dSYM

