/*
 * フレーム受信スレッド
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

#include "Receive.h"
#include "SocketCAN.h"
#include "Queue.h"

#include <linux/can.h>
#include <linux/can/raw.h>

int *receiveThread(void *rxThreadConf){
    RxThreadConf conf = *(RxThreadConf *)rxThreadConf;

    int rxBytes = 0;
    int endReq = 0;
    while(!endReq){
        struct can_frame rxFrame;
        if (readFrame(conf.CANSocket, &rxFrame, conf.timeout) != 0){
            endReq = 1;
            continue;
        }
        Item item;
        item.can_id = rxFrame.can_id;
        item.can_dlc = rxFrame.can_dlc;
        item.data = rxFrame.data;
        enQueue(conf.queue, &item);
        rxBytes++;
    }
    
    void *p = malloc(sizeof(int));
    *(int *)(p) = rxBytes;
    pthread_exit(p);
}
