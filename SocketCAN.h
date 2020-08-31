/*
 * SocketCANユーティリティ
*/
#include <linux/can.h>
#include <linux/can/raw.h>

int openCANSocket(char *channel);
int closeCANSocket(int CANSocket);
int sendFrame(int CANSocket, struct can_frame *frame);
int readFrame(int CANSocket, struct can_frame *frame, int timeout);
void getFormattedFrameStr(struct can_frame *frame, char* frameInfo)