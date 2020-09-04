/*
 *
*/
#include "Queue.h"
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <pthread.h>

#define NDEBUG

// キュー初期化
void initQueue(Queue *queue){
    for(int i = 0; i < QUEUE_SIZE; i++){
        initItem(&(queue->data[i]));
    }
    queue->first = 0;
    queue->last = 0;
    queue->length = 0;

    pthread_mutex_init(&queue->mutex, NULL);
    pthread_cond_init(&queue->isNotEmpty, NULL);
    pthread_cond_init(&queue->isNotFull, NULL);
}

int deinitQueue(Queue *queue){
    int rst = 0;
    rst = pthread_cond_destroy(&queue->isNotEmpty);
    assert(rst == 0);
    rst = pthread_cond_destroy(&queue->isNotFull);
    assert(rst == 0);
    rst = pthread_mutex_destroy(&queue->mutex);
    assert(rst == 0);
    
    return rst;
}

// enqueue
int enQueue(Queue *queue, Item *item){
    pthread_mutex_lock(&queue->mutex);

    // キューはいっぱい?
    while(queue->length == QUEUE_SIZE){
        printf("waiting deQueue....");
        int rst = pthread_cond_wait(&queue->isNotFull, &queue->mutex);
        assert(rst == 0);
    }

    // data[last] にデータを詰めて、last++
    queue->length++;
    int *last = &(queue->last);
    queue->data[*last] = *item;
    (*last)++;

    pthread_mutex_unlock(&queue->mutex);
    pthread_cond_signal(&queue->isNotEmpty);
    return 0;
}

// dequeue
int deQueue(Queue *queue, Item *item){
    pthread_mutex_lock(&queue->mutex);

    // キューにデータはある?
    while (queue->length == 0) {
        printf("waiting enQueue....");
        int rst = pthread_cond_wait(&queue->isNotEmpty, &queue->mutex);
        assert(rst == 0);
    }

    // data[first]のデータを取り出して、first++
    queue->length--;
    int *first = &(queue->first);
    *item = queue->data[*first];
    (*first)++;

    pthread_mutex_unlock(&queue->mutex);
    pthread_cond_signal(&queue->isNotFull);
    return 0;
}