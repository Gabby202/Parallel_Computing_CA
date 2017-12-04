#include "world_structure.h"
#include "read_value.h"
#define NB_STEPS 50
#define TRACE
//road to master
int main(int argc, char** argv) {
    int nb_cells = argc>1?atoi(argv[1]):read_value(1);
    int nb_steps = argc>2?atoi(argv[2]):NB_STEPS;
    int currentStep = 0;
    unsigned long a ,b;
    time_t startTime =time(NULL);
    clean_worlds_dir();
#ifdef TRACE
    printf("NB cells: %d\nNB steps: %d\n",nb_cells,nb_steps);
    a = startTime;
    b = (unsigned long)time(NULL);
    printf("Cleaning worlds folder -- %lu s\n", b-a);

    printf("Processing step and file writing step %d ",currentStep);
#endif
    //startTime = time(NULL);
    World_t my_world = create_world_t(nb_cells);
    if (my_world==NULL){
        exit(EXIT_FAILURE); /* indicate failure.*/
    }
    World_t temp_world ;
    export_world_t(my_world,currentStep ,nb_cells);

    //display_world_t(my_world,nb_cells);
    for (currentStep; currentStep < nb_steps; currentStep++) {
#ifdef TRACE1
        printf("\rProcessing step and file writing step %d",currentStep);
#endif
        temp_world = next_world_t(my_world,nb_cells);
        my_world= temp_world;
        //display_world_t(my_world,nb_cells);
        export_world_t(my_world, currentStep ,nb_cells);

    }

#ifdef TRACE
    a = startTime;
    b = (unsigned long)time(NULL);
    printf(" -- %lu s\n",b-a);
#endif
    delete_world_t(my_world,nb_cells);
  return 0;
}
