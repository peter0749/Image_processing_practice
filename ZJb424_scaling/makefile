IMAGE_PATH=../Image
FLAG=-g
all: main zjb424
zjb424: zjb424.cpp
	g++ zjb424.cpp -o zjb424 ${FLAG}
main: main.cpp Pix.o PixDouble.o Image.o utils.o Scale.o Scale.h utils.h
	g++ main.cpp utils.o Image.o Pix.o PixDouble.o Scale.o -o main ${FLAG}
Scale.o: Scale.cpp Scale.h
	g++ -c Scale.cpp -o Scale.o ${FLAG}
Image.o: ${IMAGE_PATH}/Image.cpp ${IMAGE_PATH}/Image.h 
	g++ -c ${IMAGE_PATH}/Image.cpp -o Image.o ${FLAG}
Pix.o: ${IMAGE_PATH}/Pix.h ${IMAGE_PATH}/Pix.cpp
	g++ -c ${IMAGE_PATH}/Pix.cpp -o Pix.o ${FLAG}
PixDouble.o: ${IMAGE_PATH}/PixDouble.h ${IMAGE_PATH}/PixDouble.cpp
	g++ -c ${IMAGE_PATH}/PixDouble.cpp -o PixDouble.o  ${FLAG}
utils.o: utils.h utils.cpp
	g++ -c utils.cpp -o utils.o  ${FLAG}
clean:
	rm -f *.o main zjb424
	rm -rf *.dSYM

