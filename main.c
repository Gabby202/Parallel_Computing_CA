#include "world_structure.h"
#include "read_value.h"
#define NB_STEPS 50
//road to master
int main(int argc, char** argv) {
    int nb_cells = argc>=1?atoi(argv[1]):read_value(1);
    int nb_steps = argc>=2?atoi(argv[2]):NB_STEPS;
    int currentStep = 0;


    clean_worlds_dir();
    printf("NB cells: %d",nb_cells);
    World_t my_world = create_world_t(nb_cells);
    World_t temp_world ;
    export_world_t(my_world,currentStep ,nb_cells);
    //display_world_t(my_world);

    display_world_t(my_world,nb_cells);
    for (currentStep; currentStep < nb_steps; currentStep++) {
        temp_world = next_world_t(my_world,nb_cells);
        my_world= temp_world;
        //display_world_t(my_world,nb_cells);
        export_world_t(my_world, currentStep ,nb_cells);

    }

    delete_world_t(my_world,nb_cells);
  return 0;
}
