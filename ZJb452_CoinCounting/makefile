LIB_PATH=../lib
UTILS_PATH=../utils
THRES_PATH=../ZJb460_Threshold
GRADIENT_PATH=../ZJb436_gradient2
FLAG=
all: main zjb452
zjb452: zjb452.cpp
	g++ zjb452.cpp -O3 -o zjb452
main: main.cpp Threshold.o ${THRES_PATH}/Threshold.h Gradient.o ${GRADIENT_PATH}/Gradient.h Hough.o Hough.h ${UTILS_PATH}/utils.h libImageProcess.so.1.0.0
	g++ main.cpp Threshold.o Gradient.o Hough.o -I${UTILS_PATH} -I${THRES_PATH} -I${GRADIENT_PATH} -L${LIB_PATH} -lImageProcess -o main ${FLAG}
libImageProcess.so.1.0.0:
	ln -s ${LIB_PATH}/libImageProcess.so.1.0.0 libImageProcess.so.1.0.0
Threshold.o: ${THRES_PATH}/Threshold.cpp ${THRES_PATH}/Threshold.h
	g++ -c ${THRES_PATH}/Threshold.cpp -I${UTILS_PATH} -I${THRES_PATH} -o Threshold.o ${FLAG}
Gradient.o: ${GRADIENT_PATH}/Gradient.h ${GRADIENT_PATH}/Gradient.cpp
	g++ -c ${GRADIENT_PATH}/Gradient.cpp -I${UTILS_PATH} -I${GRADIENT_PATH} -o Gradient.o ${FLAG}
Hough.o: Hough.cpp Hough.h
	g++ -c Hough.cpp -o Hough.o ${FLAG}
clean:
	rm -f libImageProcess*
	rm -f *.o main zjb460 zjb458
	rm -rf *.dSYM

