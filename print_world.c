#include <string.h>
#include <stdio.h>

void print_world(int cells[], int n) {
  int i;
  for(i = 0; i < n; i++) {
    
    //print new line every row of 10
    if(i % 10 == 0) {
      printf("\n");
    }
    printf("%d", cells[i]);
  }

  printf("\n");
}
