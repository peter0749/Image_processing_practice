IMAGE_PATH=../Image
FLAG=-g
all: main Scale
Scale: Scale.cpp Pix.o PixDouble.o Image.o utils.o utils.h
	g++ Scale.cpp utils.o Image.o Pix.o PixDouble.o -o Scale ${FLAG}
main: main.cpp Pix.o PixDouble.o Image.o utils.o utils.h
	g++ main.cpp utils.o Image.o Pix.o PixDouble.o -o main ${FLAG}
Image.o: ${IMAGE_PATH}/Image.cpp ${IMAGE_PATH}/Image.h 
	g++ -c ${IMAGE_PATH}/Image.cpp -o Image.o ${FLAG}
Pix.o: ${IMAGE_PATH}/Pix.h ${IMAGE_PATH}/Pix.cpp
	g++ -c ${IMAGE_PATH}/Pix.cpp -o Pix.o ${FLAG}
PixDouble.o: ${IMAGE_PATH}/PixDouble.h ${IMAGE_PATH}/PixDouble.cpp
	g++ -c ${IMAGE_PATH}/PixDouble.cpp -o PixDouble.o  ${FLAG}
utils.o: utils.h utils.cpp
	g++ -c utils.cpp -o utils.o  ${FLAG}
clean:
	rm -f *.o main Scale
	rm -rf *.dSYM

