#include "world_structure.h"
#include "structures.h"

/**
 * create a World_t of size from the config structure
 * initialize the cells with ratios got from the config structure
 * @param config_t* the config structure
 * @return a pointer of World_t or NULL on error
 */
World_t create_world_t (Config_t* config){

    #ifdef TRACE
        printf("\n\t*************** create_world(%d)\n",(config->CELLS));
    #endif

    //to generate random numbers
    time_t t;
    srand((unsigned) time(&t));
    int i, j;


    World_t myWorld = (World_t) malloc(sizeof(Cell_t)*(config->CELLS)*config->CELLS);

    if ( myWorld == NULL){
        fprintf(stderr, "\n(create_world_t) memory allocation failed (world_t) %d Bytes\n",(int)sizeof(Cell_t)*(config->CELLS)*(config->CELLS));
        return NULL;
    }

    for (i = 0; i < (config->CELLS); i++) {
        for (j = 0; j < (config->CELLS); j++) {
            Cell_t my_cell ;
            if (rand() % 100<config->INFECTED)	{
                my_cell.status = INFECTED;
            }else if (rand() % 100 < config->EMPTY) {
                my_cell.status = EMPTY;
            }else if (rand() % 100 < config->PROTECTED) {
                my_cell.status = PROTECTED;
            }
            else {
                my_cell.status = HEALTHY;
            }
            //printf("test : %d\n", my_cell->status);
            my_cell.age = rand() % 100;
            my_cell.state_duration = 0;
            myWorld[i*config->CELLS+j] = my_cell;
        }
    }
    return myWorld;
}

/**
 * process a step
 * @param config
 * @return the next world or NULL on error
 */
World_t next_world_t(Config_t* config) {

#ifdef TRACE
     printf("\t*************** next_world()\n");
#endif

    int i, j,k;
    Cell_t* neighbor[8];
    int infection_prob;
    Status_t temp_status;
        for(i=0;i<config->CELLS;i++){
        for(j=0;j<config->CELLS;j++){
            if (i % 100 == config->AGING)current_world[i*config->CELLS+j].age++;

            temp_status = (Status_t) current_world[i*config->CELLS+j].status;
            neighbor[0]= &current_world[(i +(config->CELLS)  - 1) % (config->CELLS)*config->CELLS+(j +(config->CELLS)- 1) % (config->CELLS)];
            neighbor[1]= &current_world[(i +(config->CELLS)  - 0) % (config->CELLS)*config->CELLS+(j +(config->CELLS)- 1) % (config->CELLS)];
            neighbor[2]= &current_world[(i +(config->CELLS)  + 1) % (config->CELLS)*config->CELLS+(j +(config->CELLS)- 1) % (config->CELLS)];
            neighbor[3]= &current_world[(i +(config->CELLS)  - 1) % (config->CELLS)*config->CELLS+(j +(config->CELLS)- 0) % (config->CELLS)];
            neighbor[4]= &current_world[(i +(config->CELLS)  + 1) % (config->CELLS)*config->CELLS+(j +(config->CELLS)- 0) % (config->CELLS)];
            neighbor[5]= &current_world[(i +(config->CELLS)  - 1) % (config->CELLS)*config->CELLS+(j +(config->CELLS)+ 1) % (config->CELLS)];
            neighbor[6]= &current_world[(i +(config->CELLS)  - 0) % (config->CELLS)*config->CELLS+(j +(config->CELLS)+ 1) % (config->CELLS)];
            neighbor[7]= &current_world[(i +(config->CELLS)  + 1) % (config->CELLS)*config->CELLS+(j +(config->CELLS)+ 1) % (config->CELLS)];
            //todo death  0.0012%
            switch (current_world[i*config->CELLS+j].status) {
                case EMPTY:
                    if (rand()% 10000 < config->BIRTH) {
                        temp_status = HEALTHY;
                    }
                    break;
                case HEALTHY:
                    infection_prob = 0;

                    for (k=0;k<8;k++){
                        if (neighbor[k]->status == DEAD_INFECTIOUS) infection_prob =+ config->INFECTIOUS_CONTAMINATION;
                        if (neighbor[k]->status == NATURAL_DEAD) infection_prob =+ config->NATURAL_CONTAMINATION;
                        if (neighbor[k]->status == INFECTED) infection_prob =+ config->INFECTED_SPREADING;
                    }

                    if (rand() % 100 < infection_prob) {
                        temp_status = INFECTED;
                    }
                    break;
                case INFECTED:
                    if (current_world[i*config->CELLS+j].state_duration <= config->INFECTED_STEP1) {
                        if (rand() % 100 < config->INFECTIOUSNESS1) {
                            temp_status = DEAD_INFECTIOUS;
                        }
                    }else if (current_world[i*config->CELLS+j].state_duration <= config->INFECTED_STEP2) {
                        if (rand() % 100 < config->INFECTIOUSNESS2) {
                            temp_status = DEAD_INFECTIOUS;
                        }
                    }else if (current_world[i*config->CELLS+j].state_duration <= config->INFECTED_STEP3) {
                        if (rand() % 100 < config->INFECTIOUSNESS3) {
                            temp_status = DEAD_INFECTIOUS;
                        }
                    }else {
                        temp_status = PROTECTED;
                    }
                    break;
                case DEAD_INFECTIOUS:
                    if (current_world[i*config->CELLS+j].state_duration == config->DEATH_DURATION)
                        temp_status = EMPTY;
                    break;
                case NATURAL_DEAD:
                    if (current_world[i*config->CELLS+j].state_duration == config->DEATH_DURATION)
                        temp_status = EMPTY;
                    break;
                case PROTECTED:
                    if (current_world[i*config->CELLS+j].state_duration == config->PROTECTION_DURATION)
                        temp_status = HEALTHY;
                    break;
                default:
                    break;

            }
            tempWorld[i*config->CELLS+j].state_duration =(char) ((current_world[i*config->CELLS+j].status == temp_status) ? current_world[i*config->CELLS+j].state_duration+1 :0);
            tempWorld[i*config->CELLS+j].status = temp_status;
            tempWorld[i*config->CELLS+j].age = current_world[i*config->CELLS+j].age;

            resWorld = current_world;
            current_world = tempWorld;
            tempWorld = resWorld;

        }
        }
    return current_world;
}

/**
 * print the status of each cell
 * @param World to display
 */
void display_world_t (World_t myWorld,Config_t* config) {
#ifdef TRACE
     printf("\t*************** display_world() \n");
#endif/*
    int i, j;
    Cell_t* tempCell;
    for (i = 0; i < config->CELLS; i++) {
        printf("\n\t");
        for (j = 0; j < config->CELLS; j++) {
            tempCell = myWorld[i][j];
            printf("%d  ",myWorld[i][j]->status);
        }
    }
    printf("\n");*/
}

void delete_world_t() {
#ifdef TRACE
    printf("\t*************** delete_world_t()\n");
#endif

        free(current_world);
        free(tempWorld);

}

