/*
 * フレーム解析スレッド
*/
#include "Analyser.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

#include "SocketCAN.h"
#include "Queue.h"

#include <linux/can.h>
#include <linux/can/raw.h>

int *analyseThread(void *alThreadConf){
    AlThreadConf conf = (AlThreadConf) alThreadConf;

    int endReq = 0;
    char buffer[35];
    while(!endReq){
        Item item;
        deQueue(conf->queue, &item);

        memset(buffer, \0, 35);
        dumpItem(&item, buffer);
        printf("%s", buffer);
    }
    pthread_exit(NULL);
}