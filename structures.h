#ifndef PARALLEL_COMPUTING_PROJECT_STRUCTURES_H
#define PARALLEL_COMPUTING_PROJECT_STRUCTURES_H

//#define TRACE

typedef enum {EMPTY = 1	, HEALTHY = 2, INFECTED =3, DEAD_INFECTIOUS=4, NATURAL_DEAD=5, PROTECTED=6} status_t;
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
}Config_t;
typedef struct {
    status_t status;
    int age;
    int state_duration;
} Cell_t;

typedef Cell_t*** World_t;


#endif //PARALLEL_COMPUTING_PROJECT_STRUCTURES_H
