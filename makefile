all: myapp

CC: gcc

myapp: init.o create_world.o print_world.o mtd.h
	$(CC) -o myapp init.o create_world.o print_world.o mtd.h

init.o: init.c mtd.h
	$(CC) -c init.c

create_world.o: create_world.c
	$(CC) -c create_world.c

print_world.o: print_world.c
	$(CC) -c print_world.c

clean:
	-rm *.o myapp
