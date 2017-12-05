
#ifndef PARALLEL_COMPUTING_PROJECT_READ_VALUE_H
#define PARALLEL_COMPUTING_PROJECT_READ_VALUE_H



#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "errno.h"
#include "structures.h"
//#define TRACE
#define FILE_PREFIX "worlds/world"
#define FILE_SUFFIX ".txt"
#define CONFIG_FILENAME "vars.md"

int testConfig(Config_t*);
Config_t* initConfig(Config_t*);
int read_value(char*);
void clean_worlds_dir();
void export_world_t(World_t my_world,int,Config_t*);

#endif //PARALLEL_COMPUTING_PROJECT_READ_VALUE_H
