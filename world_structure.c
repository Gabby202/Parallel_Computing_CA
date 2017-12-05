#include "world_structure.h"
#include "structures.h"

/**
 * create a World_t of size from read_value()
 * initialize the cells with a random number between 0 and 3 for the status and 1 for the days_infected
 * @return a pointer of World_t
 */
World_t create_world_t (Config_t* config){

    #ifdef TRACE
        printf("\t*************** create_world(%d)\n",(config->CELLS));
    #endif

    //to generate random numbers
    time_t t;
    srand((unsigned) time(&t));
    int i, j;


    World_t myWorld = (Cell_t***) malloc(sizeof(Cell_t**)*(config->CELLS));
    if ( myWorld == NULL){
        fprintf(stderr, "(create_world_t) memory allocation failled (world_t) %d Bytes Aborting...\n",(int)sizeof(Cell_t*)*(config->CELLS));
        return NULL;
    }
    for (i = 0;  i<(config->CELLS) ; i++) {
        myWorld[i] = (Cell_t**) malloc(sizeof(Cell_t*)*(config->CELLS)*(config->CELLS));
        if ( myWorld[i] == NULL){
            fprintf(stderr, "(create_world_t) memory allocation failled (world_t*) %d Bytes Aborting...\n",(int)sizeof(Cell_t*)*(config->CELLS)*(config->CELLS));
            return NULL;
        }
    }


    for (i = 0; i < (config->CELLS); i++) {
        for (j = 0; j < (config->CELLS); j++) {
            Cell_t* my_cell = (Cell_t*) malloc(sizeof(Cell_t));
            if ( my_cell == NULL ){
                fprintf(stderr, "(create_world_t) memory allocation failled (Cell_t)! Aborting...\n");
                return NULL;
            }
            if (rand() % 100<config->INFECTED)	{
                my_cell->status = INFECTED;
            }else if (rand() % 100 < config->EMPTY) {
                my_cell->status = EMPTY;
            }else if (rand() % 100 < config->PROTECTED) {
                my_cell->status = PROTECTED;
            }
            else {
                my_cell->status = HEALTHY;
            }
            //printf("test : %d\n", my_cell->status);
            my_cell->age = rand() % 100;
            my_cell->state_duration = 0;
            myWorld[i][j] = my_cell;
        }
    }
    return myWorld;
}

/**
 * @param current_world !! WARNING!!! this param will be free()
 * @return the next world
 */
World_t next_world_t(World_t current_world,Config_t* config) {

#ifdef TRACE
     printf("\t*************** next_world()\n");
#endif

    int i, j;
    World_t new_world = (Cell_t***) malloc(sizeof(Cell_t**)*(config->CELLS));
    if ( new_world == NULL ){
        fprintf(stderr, "(next_world_t) memory allocation failled (World_t)! Aborting...\n");
        return NULL; /* indicate failure.*/
    }
    for (i = 0;  i<(config->CELLS) ; i++) {
        new_world[i] = (Cell_t**) malloc(sizeof(Cell_t*)*(config->CELLS)*(config->CELLS));
        if ( new_world[i] == NULL ){
            fprintf(stderr, "(next_world_t) memory allocation failled (World_t*) %d Bytes Aborting...\n",(int)sizeof(Cell_t*)*(config->CELLS)*(config->CELLS));
            exit(EXIT_FAILURE); /* indicate failure.*/
        }
    }


    for (i = 0; i < (config->CELLS); i++) {
        for (j = 0; j < (config->CELLS); j++) {
            Cell_t* my_cell = (Cell_t*) malloc(sizeof(Cell_t));
            if ( my_cell == NULL ){
                fprintf(stderr, "(next_world_t) memory allocation failled (Cell_t) Aborting...\n");
                exit(EXIT_FAILURE); /* indicate failure.*/
            }

            new_world[i][j]=my_cell;

            int infection_prob;
            status_t temp_status;

            if (i % 100 == config->AGING)current_world[i][j]->age++;

            temp_status = current_world[i][j]->status;

            //todo death  0.0012%
            switch (current_world[i][j]->status) {
                case EMPTY:
                    if (rand()% 10000 < config->BIRTH) {
                        temp_status = HEALTHY;
                    }
                    break;
                case HEALTHY:
                    infection_prob = 0;
                    if (current_world[(i +(config->CELLS)  - 1) % (config->CELLS)][(j +(config->CELLS)- 1) % (config->CELLS)]->status == DEAD_INFECTIOUS) infection_prob = +config->INFECTIOUS_CONTAMINATION;
                    else if (current_world[(i +(config->CELLS)  - 1) % (config->CELLS)][(j +(config->CELLS)- 1) % (config->CELLS)]->status == NATURAL_DEAD) infection_prob = +config->NATURAL_CONTAMINATION;
                    if (current_world[(i +(config->CELLS)  - 1) % (config->CELLS)][(j +(config->CELLS)- 0) % (config->CELLS)]->status == DEAD_INFECTIOUS) infection_prob = +config->INFECTIOUS_CONTAMINATION;
                    else if (current_world[(i +(config->CELLS)  - 1) % (config->CELLS)][(j +(config->CELLS)- 0) % (config->CELLS)]->status == NATURAL_DEAD) infection_prob = +config->NATURAL_CONTAMINATION;
                    if (current_world[(i +(config->CELLS)  - 1) % (config->CELLS)][(j +(config->CELLS)+ 1) % (config->CELLS)]->status == DEAD_INFECTIOUS) infection_prob = +config->INFECTIOUS_CONTAMINATION;
                    else if (current_world[(i +(config->CELLS)  - 1) % (config->CELLS)][(j +(config->CELLS)+ 1) % (config->CELLS)]->status == NATURAL_DEAD) infection_prob = +config->NATURAL_CONTAMINATION;
                    if (current_world[(i +(config->CELLS)  - 0) % (config->CELLS)][(j +(config->CELLS)- 1) % (config->CELLS)]->status == DEAD_INFECTIOUS) infection_prob = +config->INFECTIOUS_CONTAMINATION;
                    else if (current_world[(i +(config->CELLS)  - 0) % (config->CELLS)][(j +(config->CELLS)- 1) % (config->CELLS)]->status == NATURAL_DEAD) infection_prob = +config->NATURAL_CONTAMINATION;
                    if (current_world[(i +(config->CELLS)  - 0) % (config->CELLS)][(j +(config->CELLS)+ 1) % (config->CELLS)]->status == DEAD_INFECTIOUS) infection_prob = +config->INFECTIOUS_CONTAMINATION;
                    else if (current_world[(i +(config->CELLS)  - 0) % (config->CELLS)][(j +(config->CELLS)+ 1) % (config->CELLS)]->status == NATURAL_DEAD) infection_prob = +config->NATURAL_CONTAMINATION;
                    if (current_world[(i +(config->CELLS)  + 1) % (config->CELLS)][(j +(config->CELLS)- 1) % (config->CELLS)]->status == DEAD_INFECTIOUS) infection_prob = +config->INFECTIOUS_CONTAMINATION;
                    else if (current_world[(i +(config->CELLS)  + 1) % (config->CELLS)][(j +(config->CELLS)- 1) % (config->CELLS)]->status == NATURAL_DEAD) infection_prob = +config->NATURAL_CONTAMINATION;
                    if (current_world[(i +(config->CELLS)  + 1) % (config->CELLS)][(j +(config->CELLS)- 0) % (config->CELLS)]->status == DEAD_INFECTIOUS) infection_prob = +config->INFECTIOUS_CONTAMINATION;
                    else if (current_world[(i +(config->CELLS)  + 1) % (config->CELLS)][(j +(config->CELLS)- 0) % (config->CELLS)]->status == NATURAL_DEAD) infection_prob = +config->NATURAL_CONTAMINATION;
                    if (current_world[(i +(config->CELLS)  + 1) % (config->CELLS)][(j +(config->CELLS)+ 1) % (config->CELLS)]->status == DEAD_INFECTIOUS) infection_prob = +config->INFECTIOUS_CONTAMINATION;
                    else if (current_world[(i +(config->CELLS)  + 1) % (config->CELLS)][(j +(config->CELLS)+ 1) % (config->CELLS)]->status == NATURAL_DEAD) infection_prob = +config->NATURAL_CONTAMINATION;
                    if (rand() % 100 < infection_prob) {
                        temp_status = INFECTED;
                    }
                    break;
                case INFECTED:
                    if (current_world[i][j]->state_duration ==config->INFECTED_STEP3) {
                        temp_status = PROTECTED;
                    }else if (current_world[i][j]->state_duration <= config->INFECTED_STEP1) {
                        if (rand() % 100 < config->INFECTIOUSNESS1) {
                            temp_status = DEAD_INFECTIOUS;
                        }
                    }else if (current_world[i][j]->state_duration <= config->INFECTED_STEP2) {
                        if (rand() % 100 < config->INFECTIOUSNESS2) {
                            temp_status = DEAD_INFECTIOUS;
                        }
                    }else {
                        if (rand() % 100 < config->INFECTIOUSNESS3) {
                            temp_status = DEAD_INFECTIOUS;
                        }
                    }
                    break;
                case DEAD_INFECTIOUS:
                    if (current_world[i][j]->state_duration == config->DEATH_DURATION)
                        temp_status = EMPTY;
                    break;
                case NATURAL_DEAD:
                    if (current_world[i][j]->state_duration == config->DEATH_DURATION)
                        temp_status = EMPTY;
                    break;
                case PROTECTED:
                    if (current_world[i][j]->state_duration == config->PROTECTION_DURATION)
                        temp_status = HEALTHY;
                    break;
                default:
                    break;

            }
            new_world[i][j]->state_duration = (current_world[i][j]->status == temp_status) ? current_world[i][j]->state_duration+1 : 0;
            new_world[i][j]->status = temp_status;
            new_world[i][j]->age = current_world[i][j]->age;
        }
    }
    delete_world_t(current_world, config);
    //current_world =  new_world;
    return new_world;
}

/**
 * print the status of each cell
 * @param World to display
 */
void display_world_t (World_t myWorld,Config_t* config) {
#ifdef TRACE
     printf("\t*************** display_world() \n");
#endif
    int i, j;
    Cell_t* tempCell;
    for (i = 0; i < config->CELLS; i++) {
        printf("\n\t");
        for (j = 0; j < config->CELLS; j++) {
            tempCell = myWorld[i][j];
            printf("%d  ",myWorld[i][j]->status);
        }
    }
    printf("\n");
}

void delete_world_t(World_t my_world,Config_t* config) {
#ifdef TRACE
    printf("\t*************** delete_world_t()\n");
#endif

    int i, j;
        for (i = 0; i < config->CELLS; i++) {
            for (j = 0; j < config->CELLS; j++) {
                free(my_world[i][j]);
            }
            free(my_world[i]);
        }
        free(my_world);

}

