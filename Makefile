libreria: main.o
	g++ main.o -o ./bin/libreria

main.o: ./src/main.cpp
	g++ ./src/main.cpp -c

clean:
	del /s *.o