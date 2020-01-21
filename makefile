a.out: main.o compress.o
		g++ main.o compress.o 

main.o:main.cpp
		g++ -c main.cpp

compress.o:compress.cpp
		g++ -c compress.cpp