/*
 * 
*/
#ifndef QUEUE_H
#define QUEUE_H

#include <pthread.h>
#include <stdlib.h>
#include <sys/time.h>

/* -------- */
#define QUEUE_SIZE 10000
#ifndef uint8_t
    #define uint8_t unsigned char
#endif

/* -------- */
typedef struct item {
    unsigned long can_id;
    uint8_t can_dlc;
    uint8_t data[8];
} Item;

typedef struct queue {
    Item data[QUEUE_SIZE];
    int first;
    int last;
    int length;

    pthread_mutex_t mutex;
    pthread_cond_t isNotEmpty;
    pthread_cond_t isNotFull;

    struct timespec timeout;
} Queue;

/* -------- */
void initQueue(Queue *queue, int timeout);
int deinitQueue(Queue *queue);
int enQueue(Queue *queue, Item *item);
int deQueue(Queue *queue, Item *item);

void initItem(Item *item);
void setItem(Item *item, uint8_t id, uint8_t *data);

void dumpQueue(Queue *queue, char* buffer);
void dumpItem(Item *item, char* buffer);
void dumpu8Array(uint8_t *data, int length, char *buffer);

#endif