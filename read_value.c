
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
    printf("\n (clean_worlds_dir) suppr file : %s",EXPORT_FILENAME);
#endif
remove(EXPORT_FILENAME);
}

/**
 * save the given world in a file
 * the file name is defined by FILE_PREFIX and FILE_SUFFIX from the header file.
 * Cann write on stderr on error
 * @param my_world, the current step, the config structure
 * @return 0 if error, 1 if ok
 */
int export_world_t(FILE* backup_file, Config_t* myConfig) {
    if (myConfig->EXPORT==1){
        int temp;
        temp = (int)fwrite(current_world, sizeof(Cell_t),myConfig->CELLS*myConfig->CELLS,backup_file);
        if (temp!=myConfig->CELLS*myConfig->CELLS){
            fprintf(stderr, "\n(export_world_t) Cannot write in the file!\n");
            return 0;
        }
    }
    return 1;
}


/**
 * Initialise the variables of the structure from the config file.
 * The configuration file name is define in the header file by CONFIG_FILENAME
 * @param pointer on the config structure.
 * @return the same pointer or NULL on error
 */
Config_t* initConfig(Config_t* myConfig) {

#ifdef TRACE
    printf("(initConfig) from file %s",CONFIG_FILENAME);
#endif
    int i=0,j=0;
    char output[256],varName[50],tempChar;


    //myConfig = (Config_t*) malloc(sizeof(Config_t));
    if ( myConfig == NULL){
        fprintf(stderr, "(initConfig) memory allocation failled (Config_t).\n");
        return NULL;
    }

    FILE* fpointer = fopen(CONFIG_FILENAME, "r"); //set to read only
    if (fpointer == NULL) {
        fprintf(stderr,"(initConfig) Cant find file %s\n",CONFIG_FILENAME);
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
                myConfig->CELLS =(unsigned long)  atol(fgets(output,20,fpointer));
            }else if (strcmp(varName,"STEPS")==0){
                myConfig->STEPS =(unsigned long)  atol(fgets(output,20,fpointer));
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
            }else if (strcmp(varName,"INFECTED_SPREADING")==0){
                myConfig->INFECTED_SPREADING = (unsigned int) atoi(fgets(output,20,fpointer));
            }else if (strcmp(varName,"THREADS")==0){
                myConfig->THREADS = (unsigned int) atoi(fgets(output,20,fpointer));
            }else if (strcmp(varName,"EXPORT")==0){
                myConfig->THREADS = (unsigned int) atoi(fgets(output,20,fpointer));
            }
        } else{
            j =fgets(output,200,fpointer)!=NULL;
        }
    }while (j && tempChar!=EOF);


    fclose(fpointer);

    return testConfig(myConfig);
}

Config_t* testConfig(Config_t *myConfig) {
    if(myConfig==NULL){
        fprintf(stderr,"\n(testConfig) NULL pointer\n");
        return NULL;
    }
    if(myConfig->CELLS > 10000 || myConfig->CELLS <4) {
        fprintf(stderr,"\n(testConfig) CELLS\n");
        return NULL;
    }
    if(myConfig->STEPS > 5000 || myConfig->STEPS <1) {
        fprintf(stderr,"\n(testConfig) STEPS\n");
        return NULL;
    }
    if(myConfig->EMPTY > 100 || myConfig->EMPTY <0) {
        fprintf(stderr,"\n(testConfig) EMPTY\n");
        return NULL;
    }
    if(myConfig->INFECTED > 100 || myConfig->INFECTED <1) {
        fprintf(stderr,"\n(testConfig) INFECTED\n");
        return NULL;
    }
    if(myConfig->PROTECTED > 100 || myConfig->PROTECTED <0) {
        fprintf(stderr,"\n(testConfig) PROTECTED\n");
        return NULL;
    }
    if(myConfig->AGING > 1000 || myConfig->AGING <0) {
        fprintf(stderr,"\n(testConfig) AGING\n");
        return NULL;
    }
    if(myConfig->BIRTH > 10000 || myConfig->BIRTH <0) {
        fprintf(stderr,"\n(testConfig) BIRTH\n");
        return NULL;
    }
    if(myConfig->NATURAL_CONTAMINATION > 100 || myConfig->NATURAL_CONTAMINATION <0) {
        fprintf(stderr,"\n(testConfig) NATURAL_CONTAMINATION\n");
        return NULL;
    }
    if(myConfig->INFECTIOUS_CONTAMINATION > 100 || myConfig->INFECTIOUS_CONTAMINATION <0) {
        fprintf(stderr,"\n(testConfig) INFECTIOUS_CONTAMINATION\n");
        return NULL;
    }
    if(myConfig->INFECTED_STEP1 > 50 || myConfig->INFECTED_STEP1 <0) {
        fprintf(stderr,"\n(testConfig) INFECTED_STEP1\n");
        return NULL;
    }
    if(myConfig->INFECTED_STEP2 > 50 || myConfig->INFECTED_STEP2 <0) {
        fprintf(stderr,"\n(testConfig) INFECTED_STEP2\n");
        return NULL;
    }
    if(myConfig->INFECTED_STEP3 > 50 || myConfig->INFECTED_STEP3 <0) {
        fprintf(stderr,"\n(testConfig) INFECTED_STEP3\n");
        return NULL;
    }
    if(myConfig->DEATH_DURATION > 1000 || myConfig->DEATH_DURATION <0) {
        fprintf(stderr,"\n(testConfig) DEATH_DURATION\n");
        return NULL;
    }
    if(myConfig->INFECTIOUSNESS1 > 100 || myConfig->INFECTIOUSNESS1 <0) {
        fprintf(stderr,"\n(testConfig) INFECTIOUSNESS1\n");
        return NULL;
    }
    if(myConfig->INFECTIOUSNESS2 > 100 || myConfig->INFECTIOUSNESS2 <0) {
        fprintf(stderr,"\n(testConfig) INFECTIOUSNESS2\n");
        return NULL;
    }
    if(myConfig->INFECTIOUSNESS3 > 100 || myConfig->INFECTIOUSNESS3 <0) {
        fprintf(stderr,"\n(testConfig) INFECTIOUSNESS3\n");
        return NULL;
    }
    if(myConfig->PROTECTION_DURATION > 1000 || myConfig->PROTECTION_DURATION <0) {
        fprintf(stderr,"\n(testConfig) PROTECTION_DURATION\n");
        return NULL;
    }
    if(myConfig->INFECTED_SPREADING > 100 || myConfig->INFECTED_SPREADING <0) {
        fprintf(stderr,"\n(testConfig) INFECTED_SPREADING\n");
        return NULL;
    }
    if(myConfig->THREADS > 16 || myConfig->THREADS <0) {
        fprintf(stderr,"\n(testConfig) THREADS\n");
        return NULL;
    }
    if(myConfig->EXPORT > 1 || myConfig->THREADS <0) {
        fprintf(stderr,"\n(testConfig) THREADS\n");
        return NULL;
    }

    return myConfig;
}

void* initExport(Config_t* config) {
    FILE* backup_file = NULL;
    if (config->EXPORT==1){
        backup_file = fopen(EXPORT_FILENAME,"wb");
        if ( backup_file == NULL ){
            fprintf(stderr, "\n(initExport) Cannot create the storage file.\n\tBe sure to have a worlds folder in the working directory!\n");
            return NULL;
        }
    } else{
        return config;
    }

    return backup_file;
}

int closeExport(FILE *backupFile, Config_t* config) {

    if(config->EXPORT ==1){
        int temp = fclose(backupFile);
        if (temp!=0){
            fprintf(stderr, "\n(closeExport) Cannot close the file!\n");
            return 0;
        }
    }
    return 1;
}

