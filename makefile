a.out: main.o compress.o shapes.o decompress.o
		g++ main.o compress.o shapes.o decompress.o -lglut -lGL

main.o:main.cpp
		g++ -c main.cpp -lglut -lGL 

compress.o:compress.cpp
		g++ -c compress.cpp

shapes.o:shapes.cpp	
		g++ -c shapes.cpp -lglut -lGL

decompress.o:decompress.cpp
		g++ -c decompress.cpp