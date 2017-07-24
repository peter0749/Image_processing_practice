LIB_PATH=../lib
UTILS_PATH=../utils
FLAG=
all: main effect zjb427
zjb427: zjb427.cpp
	g++ zjb427.cpp -o zjb427 ${FLAG}
main: main.cpp LinearGradient.o LinearGradient.h ${UTILS_PATH}/utils.h libImageProcess.so.1.0.0
	g++ main.cpp LinearGradient.o -I${UTILS_PATH} -L${LIB_PATH} -lImageProcess -o main ${FLAG}
effect: effect.cpp LinearGradient.o LinearGradient.h ${UTILS_PATH}/utils.h libImageProcess.so.1.0.0
	g++ effect.cpp LinearGradient.o -I${UTILS_PATH} -L${LIB_PATH} -lImageProcess -o effect ${FLAG}
libImageProcess.so.1.0.0:
	ln -s ${LIB_PATH}/libImageProcess.so.1.0.0 libImageProcess.so.1.0.0
LinearGradient.o: LinearGradient.cpp LinearGradient.h
	g++ -c LinearGradient.cpp -I${UTILS_PATH} -o LinearGradient.o ${FLAG}
clean:
	rm -f libImageProcess*
	rm -f *.o main zjb427 effect
	rm -rf *.dSYM

