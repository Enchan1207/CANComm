/*
 * フレーム解析
*/
#ifndef ANALYSER_H
#define ANALYSER_H

/* -------- */
#include <pthread.h>
#include "Queue.h"

/* -------- */
typedef struct althreadconf {
    int CANSocket;
    int timeout;
    Queue* rxQueue;
} AlThreadConf;

/* -------- */
int *analyseThread(void *alThreadConf);

#endif