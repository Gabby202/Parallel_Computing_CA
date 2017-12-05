
#include <sys/types.h>
#include <time.h>
#include "structures.h"
#include "world_structure.h"
#include "read_value.h"
#define TRACE
//road to master
int main(int argc, char** argv) {
    Config_t myConfig;
    myConfig = *initConfig(&myConfig);
    if (testConfig(&myConfig)==0)exit(EXIT_FAILURE);

    if (argc>1)myConfig.CELLS=(unsigned int)atoi(argv[1]);
    if (argc>2)myConfig.STEPS=(unsigned int)atoi(argv[2]);
    int currentStep = 0;
    unsigned long a ,b;
    time_t startTime =time(NULL);
    clean_worlds_dir();
#ifdef TRACE
    printf("\nNB cells: %d\nNB steps: %d\n",myConfig.CELLS,myConfig.STEPS);
    a = startTime;
    b = (unsigned long)time(NULL);
    printf("Cleaning worlds folder -- %lu s\n", b-a);

    printf("Processing step and file writing step %d ",currentStep);
#endif
    //startTime = time(NULL);
    World_t my_world = create_world_t(&myConfig);
    if (my_world==NULL){
        exit(EXIT_FAILURE); /* indicate failure.*/
    }
    World_t temp_world ;
    export_world_t(my_world,currentStep ,&myConfig);

    //display_world_t(my_world,nb_cells);
    for (currentStep; currentStep < myConfig.STEPS; currentStep++) {
#ifdef TRACE1
        printf("\rProcessing step and file writing step %d",currentStep);
#endif
        temp_world = next_world_t(my_world,&myConfig);
        my_world= temp_world;
        //display_world_t(my_world,nb_cells);
        export_world_t(my_world, currentStep ,&myConfig);

    }

#ifdef TRACE
    a = startTime;
    b = (unsigned long)time(NULL);
    printf(" -- %lu s\n",b-a);
#endif
    delete_world_t(my_world,&myConfig);
  return 0;
}
