
#include "read_value.h"


int read_value(int line) {


#ifdef TRACE
  printf("(read_value) from file ");
#endif

  int i;
  int value = 0; //value to return
  char output[256];

  FILE* fpointer = fopen("vars.md", "r"); //set to read only
  if (fpointer == NULL) {
    printf("Cant find file!\n");
    return 10;
  }


  for(i = 1; fgets(output, sizeof(output), fpointer) != NULL; i++) {
    //NB_CELLS is first line of textfile
    //add cases for each line of vars.md you want to read
    switch(line) {
    case 1:
      value = atoi(output);
      break;
    case 2:
      value = atoi(output);
      break;
    }
  }
  printf("\nNB_CELLS : %d\n",value);
  fclose(fpointer);

  return value;
}
