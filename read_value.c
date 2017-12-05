
#include "read_value.h"
#include "structures.h"


int read_value(char* valueName) {
#ifdef TRACE
  printf("(read_value) from file %s",CONFIG_FILENAME);
#endif
    int i;
    int value = 0; //value to return
    char output[256],varName[50],tempChar;

    FILE* fpointer = fopen(CONFIG_FILENAME, "r"); //set to read only

    if (fpointer == NULL) {
        fprintf(stderr,"(read_value)Cant find file %s\n",CONFIG_FILENAME);
        return 0;
    }
    do{
        tempChar= (char)fgetc(fpointer);
        if(tempChar!='#'){
            for (i=0;(tempChar)!=' ' &&i<50;i++){
                varName[i]=tempChar;
                tempChar=(char)fgetc(fpointer);
            }
            varName[i] = '\0';
            if (strcmp(varName,valueName)==0){
                value = atoi(fgets(output,20,fpointer));
            }
        }
    }while (fgets(output,200,fpointer)!=NULL && value==0);

  fclose(fpointer);

  return value;
}

void clean_worlds_dir(){


#ifdef TRACE
    printf("\ncleaning");
#endif
    char fileName[50];
    int i=0;
    do{
        sprintf(fileName, "%s%d%s",FILE_PREFIX,i,FILE_SUFFIX);
#ifdef TRACE
        printf("\n  suppr: %s",fileName);
#endif
        i++;
    }while (remove(fileName)==0);

}

/**
 * save the last step in a .csv file
 * @param my_world
 * @return 0 if error, 1 if ok
 */
void export_world_t(World_t my_world, int step, Config_t* myConfig) {
    FILE* backup_file = NULL;
    char fileName[255];
    sprintf(fileName, "%s%d%s",FILE_PREFIX, step,FILE_SUFFIX);
    backup_file = fopen(fileName,"w");

    if ( backup_file == NULL ){
        fprintf(stderr, "(export_world_t) Cannot open the backup file! Aborting...\n%s",strerror(errno));
        exit(EXIT_FAILURE); /* indicate failure.*/
    }

    int i,j , temp=1;
    for (i=0;i<myConfig->CELLS;i++){
        for (j = 0;  j < myConfig->CELLS; j++) {
            temp = fprintf(backup_file,"%d",my_world[i][j]->status);
            if (temp<=0){
                fprintf(stderr, "(export_world_t) Cannot write in the file! Aborting...\n");
                exit(EXIT_FAILURE); /* indicate failure.*/
            }
        }
        //fprintf(backup_file,"\n");
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

Config_t* initConfig(Config_t* myConfig) {

#ifdef TRACE
    printf("(initConfig) from file %s",CONFIG_FILENAME);
#endif
    int i=0,j=0;
    char output[256],varName[50],tempChar;


    //myConfig = (Config_t*) malloc(sizeof(Config_t));
    if ( myConfig == NULL){
        fprintf(stderr, "(initConfig) memory allocation failled (Config_t). Aborting...\n");
        return NULL;
    }

    FILE* fpointer = fopen(CONFIG_FILENAME, "r"); //set to read only

    if (fpointer == NULL) {
        fprintf(stderr,"(initConfig)Cant find file %s\n",CONFIG_FILENAME);
        return NULL;
    }
    do{
        tempChar= (char)fgetc(fpointer);
        if(tempChar!='#'){
            for (i=0;(tempChar)!=' ' &&i<50;i++){
                varName[i]=tempChar;
                tempChar=(char)fgetc(fpointer);
            }
            varName[i] = '\0';
            if (strcmp(varName,"CELLS")==0){
                myConfig->CELLS =(unsigned int)  atoi(fgets(output,20,fpointer));
            }else if (strcmp(varName,"STEPS")==0){
                myConfig->STEPS =(unsigned int)  atoi(fgets(output,20,fpointer));
            }else if (strcmp(varName,"EMPTY")==0){
                myConfig->EMPTY = (unsigned int) atoi(fgets(output,20,fpointer));
            }else if (strcmp(varName,"INFECTED")==0){
                myConfig->INFECTED = (unsigned int) atoi(fgets(output,20,fpointer));
            }else if (strcmp(varName,"PROTECTED")==0){
                myConfig->PROTECTED = (unsigned int) atoi(fgets(output,20,fpointer));
            }else if (strcmp(varName,"AGING")==0){
                myConfig->AGING =(unsigned int)  atoi(fgets(output,20,fpointer));
            }else if (strcmp(varName,"BIRTH")==0){
                myConfig->BIRTH = (unsigned int) atoi(fgets(output,20,fpointer));
            }else if (strcmp(varName,"NATURAL_CONTAMINATION")==0){
                myConfig->NATURAL_CONTAMINATION = (unsigned int) atoi(fgets(output,20,fpointer));
            }else if (strcmp(varName,"INFECTIOUS_CONTAMINATION")==0){
                myConfig->INFECTIOUS_CONTAMINATION =(unsigned int)  atoi(fgets(output,20,fpointer));
            }else if (strcmp(varName,"INFECTED_STEP1")==0){
                myConfig->INFECTED_STEP1 = (unsigned int) atoi(fgets(output,20,fpointer));
            }else if (strcmp(varName,"INFECTED_STEP2")==0){
                myConfig->INFECTED_STEP2 =(unsigned int)  atoi(fgets(output,20,fpointer));
            }else if (strcmp(varName,"INFECTED_STEP3")==0){
                myConfig->INFECTED_STEP3 = (unsigned int) atoi(fgets(output,20,fpointer));
            }else if (strcmp(varName,"DEATH_DURATION")==0){
                myConfig->DEATH_DURATION =(unsigned int)  atoi(fgets(output,20,fpointer));
            }else if (strcmp(varName,"INFECTIOUSNESS1")==0){
                myConfig->INFECTIOUSNESS1 = (unsigned int) atoi(fgets(output,20,fpointer));
            }else if (strcmp(varName,"INFECTIOUSNESS2")==0){
                myConfig->INFECTIOUSNESS2 = (unsigned int) atoi(fgets(output,20,fpointer));
            }else if (strcmp(varName,"INFECTIOUSNESS3")==0){
                myConfig->INFECTIOUSNESS3 = (unsigned int) atoi(fgets(output,20,fpointer));
            }else if (strcmp(varName,"PROTECTION_DURATION")==0){
                myConfig->PROTECTION_DURATION = (unsigned int) atoi(fgets(output,20,fpointer));
            }
        } else{
            j =fgets(output,200,fpointer)!=NULL;
        }
    }while (j && tempChar!=EOF);

    fclose(fpointer);

    return myConfig;
}

int testConfig(Config_t *myConfig) {
    if(myConfig==NULL){
        fprintf(stderr,"(testConfig) NULL ");
        return 0;
    }
    if(myConfig->CELLS > 500) {
        fprintf(stderr,"(testConfig) CELLS");
        return 0;
    }
    if(myConfig->STEPS > 500) {
        fprintf(stderr,"(testConfig) STEPS");
        return 0;
    }
    if(myConfig->EMPTY > 50) {
        fprintf(stderr,"(testConfig) EMPTY");
        return 0;
    }
    if(myConfig->INFECTED > 90) {
        fprintf(stderr,"(testConfig) INFECTED");
        return 0;
    }
    if(myConfig->PROTECTED > 80) {
        fprintf(stderr,"(testConfig) PROTECTED");
        return 0;
    }
    if(myConfig->AGING > 1000) {
        fprintf(stderr,"(testConfig) AGING");
        return 0;
    }
    if(myConfig->BIRTH > 1000) {
        fprintf(stderr,"(testConfig) BIRTH");
        return 0;
    }
    if(myConfig->NATURAL_CONTAMINATION > 80) {
        fprintf(stderr,"(testConfig) NATURAL_CONTAMINATION");
        return 0;
    }
    if(myConfig->INFECTIOUS_CONTAMINATION > 80) {
        fprintf(stderr,"(testConfig) INFECTIOUS_CONTAMINATION");
        return 0;
    }
    if(myConfig->INFECTED_STEP1 > 10) {
        fprintf(stderr,"(testConfig) INFECTED_STEP1");
        return 0;
    }
    if(myConfig->INFECTED_STEP2 > 10) {
        fprintf(stderr,"(testConfig) INFECTED_STEP2");
        return 0;
    }
    if(myConfig->INFECTED_STEP3 > 10) {
        fprintf(stderr,"(testConfig) INFECTED_STEP3");
        return 0;
    }
    if(myConfig->DEATH_DURATION > 100) {
        fprintf(stderr,"(testConfig) DEATH_DURATION\n");
    }
    if(myConfig->INFECTIOUSNESS1 > 80) {
        fprintf(stderr,"(testConfig) INFECTIOUSNESS1\n");
        return 0;
    }
    if(myConfig->INFECTIOUSNESS2 > 80) {
        fprintf(stderr,"(testConfig) INFECTIOUSNESS2\n");
        return 0;
    }
    if(myConfig->INFECTIOUSNESS3 > 80) {
        fprintf(stderr,"(testConfig) INFECTIOUSNESS3\n");
        return 0;
    }
    if(myConfig->PROTECTION_DURATION > 80) {
        fprintf(stderr,"(testConfig) PROTECTION_DURATION\n");
        return 0;
    }

    return 1;
}

