LIB_PATH=../lib
UTILS_PATH=../utils
FLAG= -Ofast
all: main
main: main.cpp TextureTransfer.o TextureTransfer.h ${UTILS_PATH}/utils.h libImageProcess.so.1.0.0
	g++ -std=c++11 main.cpp TextureTransfer.o -I${UTILS_PATH} -L${LIB_PATH} -lImageProcess -o main ${FLAG}
libImageProcess.so.1.0.0:
	ln -s ${LIB_PATH}/libImageProcess.so.1.0.0 libImageProcess.so.1.0.0
TextureTransfer.o: TextureTransfer.cpp TextureTransfer.h
	g++ -std=c++11 -c TextureTransfer.cpp -I${UTILS_PATH} -o TextureTransfer.o ${FLAG}
clean:
	rm -f libImageProcess*
	rm -f *.o main zjb445
	rm -rf *.dSYM

