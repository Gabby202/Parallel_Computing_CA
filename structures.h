#ifndef PARALLEL_COMPUTING_PROJECT_STRUCTURES_H
#define PARALLEL_COMPUTING_PROJECT_STRUCTURES_H

//#define TRACE

#include <sys/types.h>
#include <time.h>


typedef enum {EMPTY = 1	, HEALTHY = 2, INFECTED =3, DEAD_INFECTIOUS=4, NATURAL_DEAD=5, PROTECTED=6} Status_t;

typedef struct {
    unsigned int CELLS;
    unsigned int STEPS;
    unsigned int EMPTY;
    unsigned int INFECTED;
    unsigned int PROTECTED;
    unsigned int AGING;
    unsigned int BIRTH;
    unsigned int NATURAL_CONTAMINATION;
    unsigned int INFECTIOUS_CONTAMINATION;
    unsigned int INFECTED_STEP1;
    unsigned int INFECTED_STEP2;
    unsigned int INFECTED_STEP3;
    unsigned int DEATH_DURATION;
    unsigned int INFECTIOUSNESS1;
    unsigned int INFECTIOUSNESS2;
    unsigned int INFECTIOUSNESS3;
    unsigned int PROTECTION_DURATION;
    unsigned int INFECTED_SPREADING;
}Config_t;

typedef struct {
    char status;
    char age;
    char state_duration;
} Cell_t;

typedef Cell_t* World_t;

typedef struct {
    Config_t* config;
    World_t world;
    World_t tempWorld;
    int threadNum;
}ThreadParam_t;

World_t current_world,tempWorld;

#endif //PARALLEL_COMPUTING_PROJECT_STRUCTURES_H
