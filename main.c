/*
 * CAN通信 
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

#include "Queue.h"
#include "SocketCAN.h"
#include "Receive.h"
#include "Analyse.h"
#include "func.h"

#include <linux/can.h>
#include <linux/can/raw.h>

int main(int argc, char **argv){
    // CAN Rxキュー初期化
    Queue rxQueue, *Q;
    Q = &rxQueue;
    initQueue(Q);

    // CANソケットを開く
    char *channel = "vcan1";
    printf("Opening can socket... %s", channel);
    int CANSocket = openCANSocket(channel);
    if(CANSocket < 0){
        perror("failed. Couldn't open CAN Socket\n");
        return 1;
    }
    printf("OK\n");

    // ソケットと受信キュー、タイムアウト時間を渡して、受信スレッド開始
    RxThreadConf rxtConf;
    rxtConf.CANSocket = CANSocket;
    rxtConf.timeout = 10;
    rxtConf.queue = Q;

    pthread_t rxThread;
    pthread_create(&rxThread, NULL, (void *)receiveThread, &rxtConf);

    // フレーム解析スレッドを開始
    AlThreadConf altConf;
    altConf.CANSocket = CANSocket;
    altConf.timeout = 10;
    altConf.queue = Q;

    pthread_t alThread;
    pthread_create(&alThread, NULL, (void *)alThread, &altConf);

    void *rxThreadStat;
    pthread_join(rxThread, &rxThreadStat);
    int rxBytes = *(int *)rxThreadStat;
    printf("%d bytes received.\n", rxBytes);

    // 終了処理
    closeCANSocket(CANSocket);
    deinitQueue(Q);
	return 0;
}
