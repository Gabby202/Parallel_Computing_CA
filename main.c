
#include <sys/types.h>
#include <time.h>
#include <sys/time.h>
#include <hdf5_hl.h>
#include "structures.h"
#include "world_structure.h"
#include "read_value.h"
//road to master
int main(int argc, char** argv) {

    FILE* exportFile = NULL;
    int currentStep = 0;
    Config_t myConfig;

    struct timeval start, stop, processing_start, processing_stop, export_start, export_stop;
    double startTime=0, stopTime=0, stackExport=0, stackProcessing=0;
    gettimeofday(&start, NULL);
    startTime = (start.tv_sec*1E6+start.tv_usec)/1E6;



    if (initConfig(&myConfig)==NULL){
        fprintf(stderr,"\nCouldn't get config, aborting ...\n\n\n");
        exit(EXIT_FAILURE);
    }

    if (argc>1)myConfig.CELLS=(unsigned long)atol(argv[1]);
    if (argc>2)myConfig.STEPS=(unsigned long)atoi(argv[2]);
    if (argc>3)myConfig.EXPORT=(unsigned int)atoi(argv[3]);
    if (argc>4)myConfig.THREADS=(unsigned int)atoi(argv[4]);

    printf("\n*******************\nNB cells: %lu\nNB steps: %lu\n*******************\n",myConfig.CELLS,myConfig.STEPS);

    clean_worlds_dir();
    exportFile = initExport(&myConfig);
    if (exportFile==NULL && myConfig.EXPORT==1){
        fprintf(stderr,"\nNo file to export into, aborting ...\n\n\n");
        closeExport(exportFile,&myConfig);
        exit(EXIT_FAILURE);
    }
    printf("\nCreating worlds\n");

    current_world = create_world_t(&myConfig);
    tempWorld = create_world_t(&myConfig);

    if (current_world==NULL || tempWorld==NULL){
        fprintf(stderr,"\nThe world couldn't be created, aborting ...\n\n\n");
        closeExport(exportFile,&myConfig);
        delete_world_t();
        exit(EXIT_FAILURE);
    }
    currentStep++;

    printf("\nProcessing and exporting worlds\n");

    for (currentStep; currentStep < myConfig.STEPS; currentStep++) {
        gettimeofday(&export_start,NULL);
        if(export_world_t(exportFile,&myConfig)==0){
            fprintf(stderr,"\nStep %d couldn't be exported, aborting ...\n\n\n",currentStep);
            closeExport(exportFile,&myConfig);
            delete_world_t();
            exit(EXIT_FAILURE);
        }
        gettimeofday(&export_stop,NULL);
        stackExport += (export_stop.tv_sec*1E6 +export_stop.tv_usec)-(export_start.tv_sec*1E6 +export_start.tv_usec);

        gettimeofday(&processing_start,NULL);
        if (next_world_t(&myConfig)==NULL){
            fprintf(stderr,"\nStep %d couldn't be processed, aborting ...\n\n\n",currentStep);
            delete_world_t();
            exit(EXIT_FAILURE);
        }
        gettimeofday(&processing_stop,NULL);
        stackProcessing+= (processing_stop.tv_sec*1E6 +processing_stop.tv_usec)-(processing_start.tv_sec*1E6 +processing_start.tv_usec);

    }

    closeExport(exportFile,&myConfig);
    delete_world_t();
    printf("\nProcessing : %.3lf\nExporting : %.3lf",stackProcessing/1E6,stackExport/1E6);

    gettimeofday(&stop, NULL);
    stopTime = (stop.tv_sec*1E6 +stop.tv_usec)/1E6;

    printf("\n*****************\nTotal -- %.3lf\n\n",stopTime-startTime);

    return 0;
}
