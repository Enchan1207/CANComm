/*
 * フレーム受信スレッド周り
*/
#ifndef RECEIVE_H
#define RECEIVE_H

#include <linux/can.h>
#include <linux/can/raw.h>
#include <pthread.h>

int recvLoop(int CANSocket,int timeout, void (*callback)(struct can_frame *frame));
void onReceive(struct can_frame *frame);
int *receiveThread(void *socket);

#endif