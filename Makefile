libreria: main.o libro.o cliente.o empleado.o admin.o conversiones.o definiciones.o
	g++ main.o libro.o cliente.o empleado.o admin.o conversiones.o definiciones.o -o ./bin/libreria

main.o: ./src/main.cpp
	g++ ./src/main.cpp -c

libro.o: ./src/lib/libro/libro.cpp
	g++ ./src/lib/libro/libro.cpp -c

cliente.o: ./src/lib/cliente/cliente.cpp
	g++ ./src/lib/cliente/cliente.cpp -c

empleado.o: ./src/lib/empleado/empleado.cpp
	g++ ./src/lib/empleado/empleado.cpp -c

admin.o: ./src/lib/admin/admin.cpp
	g++ ./src/lib/admin/admin.cpp -c

conversiones.o: ./src/lib/herramientas/conversiones.cpp
	g++ ./src/lib/herramientas/conversiones.cpp -c

definiciones.o: ./src/lib/definiciones.cpp
	g++ ./src/lib/definiciones.cpp -c

clean:
	del /s *.o