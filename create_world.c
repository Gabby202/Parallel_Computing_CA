#include <stdio.h>
#include <stdlib.h>
int *create_world(int n) {
  
  //apply input to array
  int *cells = malloc(sizeof(int)*n);
  
  //loop array, add integer to each cell
  int i;
  for(i = 0; i < n; i++) {
    cells[i] = 0;
  }
   return cells;
}
