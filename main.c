/*
 * CAN通信 
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <linux/can.h>
#include <linux/can/raw.h>

#include "SocketCAN.h"

int main(int argc, char **argv){
    // CANソケットを開く
    printf("Opening can socket...");
    int CANSocket = openCANSocket("vcan1");
    if(CANSocket < 0){
        perror("failed. Couldn't open CAN Socket\n");
        return 1;
    }
    printf("finished.\n");

    // ちょっとだけデータ投げる
    struct can_frame frame;
    frame.can_id = 0x114;
    frame.can_dlc = 5;
    sprintf(frame.data, "AAAAA");
    sendFrame(CANSocket, &frame);

    // 受信ループ
    int endReq = 0;
    unsigned long int received = 0;

    int n = 0;
    while(!endReq){
        // スレッドブロックして受信
        struct can_frame frame;
        if (readFrame(CANSocket, &frame, 10) != 0){
            printf("timeout...");
            endReq = 1;
            continue;
        }

        // フレームを整形して表示
        char str[40];
        getFormattedFrameStr(&frame, str);
        printf("%s", str);
        received++;

        // ID: 0123が来たら終了
        if(frame.can_id == 0x123){
            endReq = 1;
        }
    }
    printf("%lu messages received.\n", received);

    // ソケットを閉じる
    closeCANSocket(CANSocket);
	return 0;
}
