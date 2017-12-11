
#ifndef PARALLEL_COMPUTING_PROJECT_READ_VALUE_H
#define PARALLEL_COMPUTING_PROJECT_READ_VALUE_H



#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "errno.h"
#include "structures.h"
//#define TRACE
#define CONFIG_FILENAME "config.ini"
#define EXPORT_FILENAME "world.bin"

Config_t * testConfig(Config_t*);
Config_t* initConfig(Config_t*);
int read_value(char*);
void clean_worlds_dir();
int export_world_t(FILE*, Config_t*);
void* initExport(Config_t*);
int closeExport(FILE* backuFile,Config_t*);

#endif //PARALLEL_COMPUTING_PROJECT_READ_VALUE_H
