//
// Created by zan on 8/16/23.
//
#include "log.h"

#define LOG_FILE_NAME "log.txt"
#define OPEN_MODE "w"

void logInit() {

    p_logStream = fopen(LOG_FILE_NAME, OPEN_MODE);
}