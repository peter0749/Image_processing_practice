IMAGE_PATH = ../Image
UTILS_PATH = ../utils
all: libImageProcess.so.1.0.0
libImageProcess.so.1.0.0: utils.o Image.o Pix.o PixDouble.o
	g++ -std=c++11 -shared -o libImageProcess.so.1.0.0 utils.o Image.o Pix.o PixDouble.o
	rm -f *.o
	ln -s libImageProcess.so.1.0.0 libImageProcess.so.1
	ln -s libImageProcess.so.1 libImageProcess.so
utils.o: ${UTILS_PATH}/utils.cpp ${UTILS_PATH}/utils.h
	g++ -std=c++11 -c -fPIC ${UTILS_PATH}/utils.cpp -o utils.o
Pix.o: ${IMAGE_PATH}/Pix.cpp ${IMAGE_PATH}/Pix.h
	g++ -std=c++11 -c -fPIC ${IMAGE_PATH}/Pix.cpp -o Pix.o
PixDouble.o: ${IMAGE_PATH}/PixDouble.cpp ${IMAGE_PATH}/PixDouble.h
	g++ -std=c++11 -c -fPIC ${IMAGE_PATH}/PixDouble.cpp -o PixDouble.o
Image.o: ${IMAGE_PATH}/Image.cpp ${IMAGE_PATH}/Image.h
	g++ -std=c++11 -c -fPIC ${IMAGE_PATH}/Image.cpp -o Image.o
clean:
	rm -f *.o
	rm -f libImageProcess.so*

