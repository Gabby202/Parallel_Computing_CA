
#ifndef PARALLEL_COMPUTING_PROJECT_READ_VALUE_H
#define PARALLEL_COMPUTING_PROJECT_READ_VALUE_H



#include <stdio.h>
#include <stdlib.h>
#include "world_structure.h"
#define BACKUP_FILE 'world'
//#define TRACE

int read_value(int);

void export_world_t(World_t my_world,int step,int nb_cells);

#endif //PARALLEL_COMPUTING_PROJECT_READ_VALUE_H
