#include "world_structure.h"
#include "read_value.h"
#define NB_STEPS 5

int main(int argc, char** argv) {
    int nb_cells = argc>=2?atoi(argv[2]):read_value(1);
    int nb_steps = argc>=3?atoi(argv[3]):3;

    printf("NB cells: %d",nb_cells);
    World_t* my_world = create_world_t(nb_cells);
    //display_world_t(my_world);

    int i;
    for (i = 0; i < NB_STEPS; ++i) {
        my_world = next_world_t(my_world,nb_cells);
        display_world_t(my_world,nb_cells);

    }



    delete_world_t(my_world,nb_cells);
  return 0;
}
