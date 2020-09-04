/*
 *
*/
#include "Queue.h"
#include <string.h>

// アイテム初期化
void initItem(Item *item){
    item->can_id = 0;
    memset(item->data, 0, 8);
}

// 値を指定して初期化
void setItem(Item *item, uint8_t id, uint8_t *data){
    item->can_id = id;
    memcpy(item->data, data, 8);
}