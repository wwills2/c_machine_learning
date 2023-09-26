/*
 Created by zan on 8/16/23.
*/
#include "log.h"

#define LOG_FILE_NAME "lib_ml_basics_log.txt"
#define OPEN_MODE "w"

FILE *p_logStream;

void logInit(void) {
    int res;
    p_logStream = fopen(LOG_FILE_NAME, OPEN_MODE);
    setbuf(p_logStream, NULL); //disable buffer for log file stream
    res = LOG(p_logStream,"logger initialized\n");

    if (!res){
        perror("Failed to initialize logger. This is fatal, killing\n");
        exit(-1);
    }
}

void logFinalize(void){
    fclose(p_logStream);
}
