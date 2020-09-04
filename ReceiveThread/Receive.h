/*
 * フレーム受信スレッド周り
*/
#ifndef RECEIVE_H
#define RECEIVE_H

/* -------- */
#include <linux/can.h>
#include <linux/can/raw.h>
#include <pthread.h>
#include "Queue.h"

/* -------- */
typedef struct rxthreadconf {
    int CANSocket;
    int timeout;
    Queue* queue;
} RxThreadConf;

/* -------- */
void *receiveThread(void *rxThreadConf);

#endif