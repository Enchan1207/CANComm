/*
 * SocketCANユーティリティ
*/
#include "SocketCAN.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <errno.h>

#include <net/if.h>
#include <sys/ioctl.h>
#include <sys/socket.h>

#include "Queue.h"

#include <linux/can.h>
#include <linux/can/raw.h>

int openCANSocket(char *channel){
    int sock;
    struct sockaddr_can addr;
    struct ifreq ifr;

    sock = socket(PF_CAN, SOCK_RAW, CAN_RAW);
	if (sock < 0) {
		perror("Socket error");
		return -1;
	}
	strcpy(ifr.ifr_name, channel);
	ioctl(sock, SIOCGIFINDEX, &ifr);

	memset(&addr, 0, sizeof(addr));
	addr.can_family = AF_CAN;
	addr.can_ifindex = ifr.ifr_ifindex;

	if (bind(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
		perror("Bind error");
        return -1;
	}

    return sock;
}

int closeCANSocket(int CANSocket){
    return close(CANSocket);
}

int sendFrame(int CANSocket, struct can_frame *frame){
    int n = write(CANSocket, frame, sizeof(struct can_frame));
    if (n != sizeof(struct can_frame)) {
        return 1;
    }
    return 0;
}

int readFrame(int CANSocket, struct can_frame *frame, int timeout){
    struct can_frame receive;

    // fd初期化
    fd_set readfds;
    FD_ZERO(&readfds);
    FD_SET(CANSocket, &readfds);

    // 受信タイムアウト時間設定(tiemout>0で適用)
    struct timeval tv, *timeoutVal;

    if (timeout > 0) {
        tv.tv_sec = timeout;
        tv.tv_usec = 0;
        timeoutVal = &tv;
    }else{
        timeoutVal = NULL;
    }

    // fdに設定されたソケットが読み込み可能になるまで待機
    int n = select(CANSocket + 1, &readfds, NULL, NULL, timeoutVal);

    if (n <= 0) {
        perror("Socket timeout.\n");
        return -1;
    }

    if (FD_ISSET(CANSocket, &readfds)) {
        // 受信バイト数を取得
        int nbytes = recv(CANSocket, &receive, sizeof(struct can_frame), 0);
        
        // 受信データ量がcan_frameのサイズに合っていなければ、不正CANフレームとして処理
        if (nbytes < sizeof(struct can_frame)) {
            perror("incomplete CAN frame\n");
            return 1;
        }

        // ポインタに値を渡す
        *frame = receive;

        return 0;
    }
}

void getFormattedFrameStr(struct can_frame *frame, char* frameInfo){
    int infoLen = sprintf(frameInfo, "%03X [%d] ",(*frame).can_id, (*frame).can_dlc);
    int cellLen = infoLen;
    for(int i = 0; i < (*frame).can_dlc; i++){
        cellLen += sprintf((frameInfo + cellLen), "%02X ", (*frame).data[i]);
    }
    sprintf((frameInfo + cellLen), "\r\n");
}