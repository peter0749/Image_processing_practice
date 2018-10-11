LIB_PATH=../lib
UTILS_PATH=../utils
THRES_PATH=../ZJb460_Threshold
GRADIENT_PATH=../ZJb436_gradient2
FLAG=
all: main
main: main.cpp Threshold.o ${THRES_PATH}/Threshold.h Gradient.o ${GRADIENT_PATH}/Gradient.h Edge.o Edge.h ${UTILS_PATH}/utils.h libImageProcess.so.1.0.0
	g++ -std=c++11 main.cpp Threshold.o Gradient.o Edge.o -I${UTILS_PATH} -I${THRES_PATH} -I${GRADIENT_PATH} -L${LIB_PATH} -lImageProcess -o main ${FLAG}
libImageProcess.so.1.0.0:
	ln -s ${LIB_PATH}/libImageProcess.so.1.0.0 libImageProcess.so.1.0.0
Threshold.o: ${THRES_PATH}/Threshold.cpp ${THRES_PATH}/Threshold.h
	g++ -std=c++11 -c ${THRES_PATH}/Threshold.cpp -I${UTILS_PATH} -I${THRES_PATH} -o Threshold.o ${FLAG}
Gradient.o: ${GRADIENT_PATH}/Gradient.h ${GRADIENT_PATH}/Gradient.cpp
	g++ -std=c++11 -c ${GRADIENT_PATH}/Gradient.cpp -I${UTILS_PATH} -I${GRADIENT_PATH} -o Gradient.o ${FLAG}
Edge.o: Edge.cpp Edge.h
	g++ -std=c++11 -c Edge.cpp -o Edge.o -I${UTILS_PATH} -I${GRADIENT_PATH} -I${THRES_PATH} ${FLAG}
clean:
	rm -f libImageProcess*
	rm -f *.o main 
	rm -rf *.dSYM

