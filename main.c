/*
 * CAN通信 
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

#include <linux/can.h>
#include <linux/can/raw.h>

#include "lib/SocketCAN/SocketCAN.h"
#include "lib/ReceiveThread/Receive.h"
#include "lib/func.h"

int main(int argc, char **argv){
    // CANソケットを開く
    printf("Opening can socket...");
    int CANSocket = openCANSocket("vcan1");
    if(CANSocket < 0){
        perror("failed. Couldn't open CAN Socket\n");
        return 1;
    }
    printf("finished.\n");

    // 受信スレッドにソケットを渡して開始
    printf("Open Receive Thread...\n");
    pthread_t rcvThread;
    pthread_create(&rcvThread, NULL, (void *)receiveThread, &CANSocket);

    // 文字入力を待機したのち、怒涛のcansend開始
    char buffer[8];
    int bytes = input(buffer, sizeof buffer);

    printf("start to send can frame.\n");
    unsigned int length = 1000;
    struct can_frame frame;
    for(int i = 0; i < length; i++){
        frame.can_id = 0x114;
        frame.can_dlc = bytes;
        memcpy(frame.data, buffer, 8);
        sendFrame(CANSocket, &frame);
        usleep(10);
    }
    printf("%d frames has sent.\n", length);
    
/*
    // 文字送信
    int endReq = 0;
    while(!endReq){
        printf("\nCAN >");
        char buffer[8] = {0,0,0,0,0,0,0,0};
        int bytes = input(buffer, sizeof buffer);
        if(buffer[0] == '\0'){
            endReq = 1;
            continue;
        }

        struct can_frame frame;
        frame.can_id = 0x114;
        frame.can_dlc = bytes;
        memcpy(frame.data, buffer, 8);

        sendFrame(CANSocket, &frame);
    }
    printf("REPLMode Exit.");
*/

    void *rcvThreadStatus;
    pthread_join(rcvThread, &rcvThreadStatus);
    closeCANSocket(CANSocket);
	return 0;
}
