libreria: main.o libro.o cliente.o
	g++ main.o libro.o cliente.o -o ./bin/libreria

main.o: ./src/main.cpp
	g++ ./src/main.cpp -c

libro.o: ./src/lib/libro/libro.cpp
	g++ ./src/lib/libro/libro.cpp -c

cliente.o: ./src/lib/cliente/cliente.cpp
	g++ ./src/lib/cliente/cliente.cpp -c

clean:
	del /s *.o