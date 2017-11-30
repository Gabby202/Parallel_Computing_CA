//use not to have multiple declaration of the file
#ifndef PARALLEL_COMPUTING_PROJECT_WORLD_STRUCTURE_H
#define PARALLEL_COMPUTING_PROJECT_WORLD_STRUCTURE_H

//#define TRACE

#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <sys/types.h>
#include <time.h>

typedef enum {EMPTY = 1	, HEALTHY = 2, INFECTED =3, DEAD_INFECTIOUS=4, NATURAL_DEAD=5, PROTECTED=6} status_t;

typedef struct {
    status_t status;
    int age;
    int state_duration;
} Cell_t;

typedef Cell_t*** World_t;


World_t create_world_t (int );
World_t next_world_t(World_t ,int );
World_t rewind_world_t(World_t ,int );
void display_world_t(World_t ,int );
void delete_world_t(World_t ,int );

#endif //PARALLEL_COMPUTING_PROJECT_WORLD_STRUCTURE_H
