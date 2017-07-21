IMAGE_PATH=../Image
FLAG=
all: main zjb438
zjb438: zjb438.cpp
	g++ zjb438.cpp -o zjb438 ${FLAG}
main: main.cpp Pix.o PixDouble.o Image.o utils.o utils.h SeamCarve.o SeamCarve.h EnergyMap.o EnergyMap.h
	g++ main.cpp utils.o Image.o Pix.o PixDouble.o EnergyMap.o SeamCarve.o -o main ${FLAG}
SeamCarve.o: SeamCarve.cpp SeamCarve.h
	g++ -c SeamCarve.cpp -o SeamCarve.o
EnergyMap.o: EnergyMap.cpp EnergyMap.h
	g++ -c EnergyMap.cpp -o EnergyMap.o ${FLAG}
Image.o: ${IMAGE_PATH}/Image.cpp ${IMAGE_PATH}/Image.h 
	g++ -c ${IMAGE_PATH}/Image.cpp -o Image.o ${FLAG}
Pix.o: ${IMAGE_PATH}/Pix.h ${IMAGE_PATH}/Pix.cpp
	g++ -c ${IMAGE_PATH}/Pix.cpp -o Pix.o ${FLAG}
PixDouble.o: ${IMAGE_PATH}/PixDouble.h ${IMAGE_PATH}/PixDouble.cpp
	g++ -c ${IMAGE_PATH}/PixDouble.cpp -o PixDouble.o  ${FLAG}
utils.o: utils.h utils.cpp
	g++ -c utils.cpp -o utils.o  ${FLAG}
clean:
	rm -f *.o main zjb438
	rm -rf *.dSYM

