/*
 * 雑多な関数群 
*/
#include <stdio.h>
#include <string.h>
#include "lib/func.h"

// コンソールからn文字受け取って配列にする
int input(char* buffer, int bufferLen){
    int count = 0;
    for(int i = 0; i < bufferLen - 1; i++){
        int typedValue = getc(stdin);
        char c = ' ';
        
        if(typedValue != EOF && typedValue != '\n' && count < (bufferLen - 1)){
            count++;
            c = (char)typedValue;
            memcpy((buffer + i), &c, 1);
        }else{
            break;
        }
    }
    char endChar = '\0';
    memcpy((buffer + bufferLen - 1), &endChar, 1);
    return count + 1;
}