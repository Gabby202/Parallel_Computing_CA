#== Gabby 01/11/2017 ==#
all: myapp

CC: gcc

myapp: main.o world_structure.o read_value.o world_structure.h read_value.h
	$(CC) -o myapp main.o world_structure.o read_value.o world_structure.h read_value.h

main.o: main.c world_structure.h read_value.h
	$(CC) -c main.c

world_structure.o: world_structure.c world_structure.h
	$(CC) -c world_structure.c

read_value.o: read_value.c vars.md read_value.h
	$(CC) -c read_value.c
clean:
	-rm *.o myapp
