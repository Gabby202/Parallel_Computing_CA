
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

void clean_worlds_dir(){
printf("cleaning");
    char fileName[50];
    int i=0;
    do{
        sprintf(fileName, "%s%d%s",FILE_PREFIX,i,FILE_SUFFIX);
        printf("\n  suppr: %s",fileName);
        i++;
    }while (remove(fileName)==0);

    fprintf(stdout, "(clean world) \n\t%s\n",strerror(errno));
}

/**
 * save the last step in a .csv file
 * @param my_world
 * @return 0 if error, 1 if ok
 */
void export_world_t(World_t my_world, int step, int nb_cells) {
    FILE* backup_file = NULL;
    char fileName[255];
    sprintf(fileName, "%s%d%s",FILE_PREFIX, step,FILE_SUFFIX);
    backup_file = fopen(fileName,"w");

    if ( backup_file == NULL ){
        fprintf(stderr, "(export_world_t) Cannot open the backup file! Aborting...\n%s",strerror(errno));
        exit(EXIT_FAILURE); /* indicate failure.*/
    }

    int i,j , temp=1;
    for (i=0;i<nb_cells;i++){
        for (j = 0;  j < nb_cells; j++) {
            temp = fprintf(backup_file,"%d,",my_world[i][j]->status);
            if (temp<=0){
                fprintf(stderr, "(export_world_t) Cannot write in the file! Aborting...\n");
                exit(EXIT_FAILURE); /* indicate failure.*/
            }
        }
        fprintf(backup_file,"\n");
        if (temp<=0){
            fprintf(stderr, "(export_world_t) Cannot write in the file! Aborting...\n");
            exit(EXIT_FAILURE); /* indicate failure.*/
        }
    }

    temp = fclose(backup_file);
    if (temp!=0){
        fprintf(stderr, "(export_world_t) Cannot close the file! Aborting...\n");
        exit(EXIT_FAILURE); /* indicate failure.*/
    }
}

