
int read_value(int line) {
 
  int i;
  int value; //value to return
  FILE* fpointer = fopen("vars.md", "r"); //set to read only

  if (fpointer == NULL) {
    printf("Cant find file!\n");
    return 1;
  }

  char output[256];

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
  printf("\n");
  fclose(fpointer);

  return value;
}
