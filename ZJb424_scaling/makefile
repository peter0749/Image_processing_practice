LIB_PATH=../lib
UTILS_PATH=../utils
FLAG=
all: main zjb424
zjb424: zjb424.cpp
	g++ -std=c++11 zjb424.cpp -o zjb424 ${FLAG}
main: main.cpp Scale.o Scale.h ${UTILS_PATH}/utils.h libImageProcess.so.1.0.0
	g++ -std=c++11 main.cpp Scale.o -I${UTILS_PATH} -L${LIB_PATH} -lImageProcess -o main ${FLAG}
libImageProcess.so.1.0.0:
	ln -s ${LIB_PATH}/libImageProcess.so.1.0.0 libImageProcess.so.1.0.0
Scale.o: Scale.cpp Scale.h
	g++ -std=c++11 -c Scale.cpp -I${UTILS_PATH} -o Scale.o ${FLAG}
clean:
	rm -f libImageProcess*
	rm -f *.o main zjb424
	rm -rf *.dSYM

