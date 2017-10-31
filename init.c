#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "mtd.h"

int main() {
  
  //input nuber of cells
  int n;
  printf("\nEnter number of cells: ");
  scanf("%d", &n);

  //create reference to array of cells to be made
  int *cells;
  
  //returns address of array, sets *cells pointer to this address
  cells = create_world(n);

  //passes address of array to print grid of cells
  print_world(cells, n);

  //free memory taken by cells
  free(cells);
  cells = NULL;
 
  return 0;
}
