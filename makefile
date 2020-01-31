a.out: main.o compress.o shapes.o decompress.o
		g++ main.o compress.o shapes.o decompress.o -lglut -lGL -L /home/amin/Documents/huffman_tree/chilkat/lib -lchilkat-9.5.0 -lpthread -lresolv

main.o:main.cpp
		g++ -c main.cpp -lglut -lGL 

compress.o:compress.cpp
		g++ -c compress.cpp -L /home/amin/Documents/huffman_tree/chilkat/lib -lchilkat-9.5.0 -lpthread -lresolv

shapes.o:shapes.cpp	
		g++ -c shapes.cpp -lglut -lGL

decompress.o:decompress.cpp
		g++ -c decompress.cpp -L /home/amin/Documents/huffman_tree/chilkat/lib -lchilkat-9.5.0 -lpthread -lresolv