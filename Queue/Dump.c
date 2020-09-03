/*
 *
*/
#include "Queue.h"
#include <stdio.h>
#include <string.h>

// require: max 31 * QUEUE_SIZE  bytes
void dumpQueue(Queue *queue, char* buffer){
    int idx = 0;
    for(int i = 0; i < QUEUE_SIZE; i++){
        char itemBuf[35];
        dumpItem(&(queue->data[i]), itemBuf);
        idx += sprintf(buffer + idx, "%s\n", itemBuf);
    }
}

// require: max 31 bytes
void dumpItem(Item *item, char* buffer){
    char dataBuf[30];
    dumpu8Array(item->data, item->can_dlc, dataBuf);
    sprintf(buffer, "%02X: %s", item->can_id, dataBuf);
}

// require: max 25 bytes
void dumpu8Array(uint8_t *data, int length, char *buffer){
    int idx = 0;
    for(int i = 0; i < length; i++){
        idx += sprintf(buffer + idx, "%02X ", data[i]);
    }
}