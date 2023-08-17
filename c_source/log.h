//
// Created by zan on 8/16/23.
//
#ifndef C_MACHINE_LEARNING_LOG_H
#define C_MACHINE_LEARNING_LOG_H

#include <stdio.h>

#define LOG fprintf

extern FILE *p_logStream;
void logInit();

#endif //C_MACHINE_LEARNING_LOG_H
