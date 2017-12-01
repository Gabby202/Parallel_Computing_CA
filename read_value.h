
#ifndef PARALLEL_COMPUTING_PROJECT_READ_VALUE_H
#define PARALLEL_COMPUTING_PROJECT_READ_VALUE_H



#include <stdio.h>
#include <stdlib.h>
#include "world_structure.h"
#include "string.h"
#include "errno.h"
#define BACKUP_FILE 'world'
//#define TRACE
#define FILE_PREFIX "worlds/world"
#define FILE_SUFFIX ".txt"

int read_value(int);
void clean_worlds_dir();
void export_world_t(World_t my_world,int step,int nb_cells);

#endif //PARALLEL_COMPUTING_PROJECT_READ_VALUE_H
