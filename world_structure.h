//use not to have multiple declaration of the file
#ifndef PARALLEL_COMPUTING_PROJECT_WORLD_STRUCTURE_H
#define PARALLEL_COMPUTING_PROJECT_WORLD_STRUCTURE_H

//#define TRACE

#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <sys/types.h>
#include <time.h>
#include "structures.h"

World_t create_world_t (Config_t* );
World_t next_world_t(World_t ,Config_t* );
void display_world_t(World_t ,Config_t* );
void delete_world_t(World_t ,Config_t* );

#endif //PARALLEL_COMPUTING_PROJECT_WORLD_STRUCTURE_H
