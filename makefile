#== Gabby 01/11/2017 ==#

all: myapp

CC: gcc

myapp: main.o world_structure.o world_structure.h
	$(CC) -o myapp main.o world_structure.o world_structure.h

main.o: main.c world_structure.h
	$(CC) -c main.c

world_structure.o: world_structure.c world_structure.h
	$(CC) -c world_structure.c

clean:
	-rm *.o myapp
