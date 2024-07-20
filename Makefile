libreria: main.o libro.o
	g++ main.o libro.o -o ./bin/libreria

main.o: ./src/main.cpp
	g++ ./src/main.cpp -c

libro.o: ./src/lib/libro/libro.cpp
	g++ ./src/lib/libro/libro.cpp -c

clean:
	del /s *.o