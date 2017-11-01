#include "world_structure.h"
#define NB_STEPS 10000

int main() {

    World_t* my_world = create_world_t();
    //display_world_t(my_world);
    int i;
    for (i = 0; i < NB_STEPS; ++i) {
        my_world = next_world_t(my_world);
    }

    my_world = rewind_world_t(my_world);
    //display_world_t(my_world);

  return 0;
}
