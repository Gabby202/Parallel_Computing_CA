//use not to have multiple declaration of the file
#ifndef PARALLEL_COMPUTING_PROJECT_WORLD_STRUCTURE_H
#define PARALLEL_COMPUTING_PROJECT_WORLD_STRUCTURE_H



#define NB_CELLS 100
#define TRACE 0

#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <sys/types.h>
#include <time.h>


typedef struct {
    int status;
    int days_infected;
} Cell_t;

typedef struct World {
    struct World* previous_step;
    Cell_t* world[NB_CELLS][NB_CELLS];
} World_t;


World_t* create_world_t ();
World_t* next_world_t(World_t*);
World_t* rewind_world_t(World_t*);
void display_world_t(World_t* );

#endif //PARALLEL_COMPUTING_PROJECT_WORLD_STRUCTURE_H
