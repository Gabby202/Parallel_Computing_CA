#include "world_structure.h"

/**
 * create a World_t of size from read_value()
 * initialize the cells with a random number between 0 and 3 for the status and 1 for the days_infected
 * @return a pointer of World_t
 */
World_t* create_world_t (int NB_CELLS){

    #ifdef TRACE
        printf("\n***************\nCreating a new world !");
    #endif

    //to generate random numbers
    time_t t;
    srand((unsigned) time(&t));
    int i, j;


    World_t* myWorld = (World_t*) malloc(sizeof(World_t*));
    myWorld->world = (Cell_t***) malloc(sizeof(Cell_t**)*NB_CELLS);
    for (i = 0;  i<NB_CELLS ; i++) {
        myWorld->world[i] = (Cell_t**) malloc(sizeof(Cell_t*)*NB_CELLS*NB_CELLS);
    }



    if ( myWorld == NULL || myWorld->world == NULL){
        fprintf(stderr, "(create_world_t) memory allocation failled! Aborting...\n");
        exit(EXIT_FAILURE); /* indicate failure.*/
    }

    myWorld->previous_step = NULL;
    for (i = 0; i < NB_CELLS; i++) {
        for (j = 0; j < NB_CELLS; j++) {
            Cell_t* my_cell = (Cell_t*) malloc(sizeof(Cell_t));
            if ( my_cell == NULL ){
                fprintf(stderr, "(create_world_t) memory allocation failled! Aborting...\n");
                exit(EXIT_FAILURE); /* indicate failure.*/
            }
            my_cell->days_infected = 1;
            my_cell->status = rand()%4;
            myWorld->world[i][j] = my_cell;
        }
    }
    return myWorld;
}

/**
 * compute a step, for the moment 50% of the cells get status+1
 * @param current_world
 * @return the next world
 */
World_t* next_world_t(World_t *current_world,int NB_CELLS) {

#ifdef TRACE
     printf("\n***************\nCreating a new future!");
#endif

    int i, j;
    World_t* new_world = (World_t*) malloc(sizeof(World_t));
    new_world->world = (Cell_t***) malloc(sizeof(Cell_t**)*NB_CELLS);
    for (i = 0;  i<NB_CELLS ; i++) {
        new_world->world[i] = (Cell_t**) malloc(sizeof(Cell_t*)*NB_CELLS*NB_CELLS);
    }

    if ( new_world == NULL ){
        fprintf(stderr, "(next_world_t) memory allocation failled! Aborting...\n");
        exit(EXIT_FAILURE); /* indicate failure.*/
    }
    new_world->previous_step = current_world;

    for (i = 0; i < NB_CELLS; i++) {
        for (j = 0; j < NB_CELLS; j++) {
            Cell_t* my_cell = (Cell_t*) malloc(sizeof(Cell_t));
            if ( my_cell == NULL ){
                fprintf(stderr, "(next_world_t) memory allocation failled! Aborting...\n");
                exit(EXIT_FAILURE); /* indicate failure.*/
            }
            my_cell->days_infected = 1;
            my_cell->status = (current_world->world[i][j]->status + (rand()%2))%4;
            new_world->world[i][j] = my_cell;
        }
    }

    return new_world;
}

/**
 * go back in time to change the odds
 * @param my_world
 * @return the world the the previous step
 */
World_t *rewind_world_t(World_t *my_world,int NB_CELLS) {
#ifdef TRACE
     printf("\n***************\nGoing back in time !");
#endif
    if ( my_world == NULL || my_world->previous_step ==NULL){
        fprintf(stderr, "(rewind_world_t) No world or previous world! Aborting...\n");
        exit(EXIT_FAILURE); /* indicate failure.*/
    }

    int i, j;
    for (i = 0; i < NB_CELLS; i++) {
        for (j = 0; j < NB_CELLS; j++) {
            free(my_world->world[i][j]);
        }
    }
    World_t* previous_world = my_world->previous_step;
    free(my_world);
    return previous_world;
}

/**
 * print the status of each cell
 * @param myWorld
 */
void display_world_t (World_t *myWorld,int NB_CELLS) {

#ifdef TRACE
     printf("\n***************\nThe current world : \n");
#endif
    int i, j;
    for (i = 0; i < NB_CELLS; ++i) {
        printf("\n\t");
        for (j = 0; j < NB_CELLS; ++j) {
            printf("%d  ",myWorld->world[i][j]->status);
        }
    }
    printf("\n");
}

void delete_world_t(World_t *my_world,int NB_CELLS) {
#ifdef TRACE
    printf("(delete_world_t) Goodbye cuel world ");
#endif

    int i, j;
    World_t* previous_world;
    do{
        previous_world = my_world->previous_step;
        for (i = 0; i < NB_CELLS; i++) {
            for (j = 0; j < NB_CELLS; j++) {
                free(my_world->world[i][j]);
            }
            free(my_world->world[i]);
        }
        free(my_world);
        my_world=previous_world;
    }while (my_world!=NULL);

}

