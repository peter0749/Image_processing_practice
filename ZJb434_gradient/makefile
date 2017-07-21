IMAGE_PATH=../Image
FLAG=-g
all: main zjb434
zjb434: zjb434.cpp
	g++ zjb434.cpp -o zjb434 ${FLAG}
main: main.cpp Pix.o PixDouble.o Image.o utils.o utils.h Gradient.o Gradient.h
	g++ main.cpp utils.o Image.o Pix.o PixDouble.o Gradient.o -o main ${FLAG}
Gradient.o: Gradient.cpp Gradient.h
	g++ -c Gradient.cpp -o Gradient.o ${FLAG}
Image.o: ${IMAGE_PATH}/Image.cpp ${IMAGE_PATH}/Image.h 
	g++ -c ${IMAGE_PATH}/Image.cpp -o Image.o ${FLAG}
Pix.o: ${IMAGE_PATH}/Pix.h ${IMAGE_PATH}/Pix.cpp
	g++ -c ${IMAGE_PATH}/Pix.cpp -o Pix.o ${FLAG}
PixDouble.o: ${IMAGE_PATH}/PixDouble.h ${IMAGE_PATH}/PixDouble.cpp
	g++ -c ${IMAGE_PATH}/PixDouble.cpp -o PixDouble.o  ${FLAG}
utils.o: utils.h utils.cpp
	g++ -c utils.cpp -o utils.o  ${FLAG}
clean:
	rm -f *.o main zjb434
	rm -rf *.dSYM

