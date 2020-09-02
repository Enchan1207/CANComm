/*
 * フレーム受信スレッドまわり
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

#include "Receive.h"
#include "SocketCAN.h"

#include <linux/can.h>
#include <linux/can/raw.h>

// 受信コールバック
void onReceive(struct can_frame *frame){
    // char buffer[40];
    // getFormattedFrameStr(frame, buffer);
    // printf("%s", buffer);
}

// 受信スレッド
int *receiveThread(void *socket){
    int CANSocket = *(int*)socket;
    int receivedBytes = recvLoop(CANSocket, 0, onReceive);

    printf("socket timeout. %d bytes received.\n", receivedBytes);

    void *p = malloc(sizeof(int));
    *(int *)(p) = receivedBytes;
    pthread_exit(p);
}

// 受信ループ
int recvLoop(int CANSocket,int timeout, void (*callback)(struct can_frame *frame)){
    int endReq = 0;
    unsigned long int received = 0;
    while(!endReq){
        // スレッドブロックして受信
        struct can_frame receivedFrame;
        if (readFrame(CANSocket, &receivedFrame, timeout) != 0){
            endReq = 1;
            continue;
        }

        // コールバック呼び出し
        callback(&receivedFrame);
        received++;
    }
    return received;
}