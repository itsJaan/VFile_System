//
// Created by Javier Nunez on 2/6/2019.
//

#include "Bitmap.h"

void Bitmap::initBitMap(char *bitMap, int Block_Amount) {
    for(int i = 0; i < Block_Amount/8; i++){
        bitMap[i] = 0;
    }
}
void Bitmap::setOn(char *bitMap, int nBlock) {
    int positionByte = nBlock/8;
    int iniPosition = (nBlock/8) * 8;

    for(int i = iniPosition, x = 7; i < (positionByte * 8) + 8; i++, x--){
        if(i == nBlock){
            bitMap[positionByte] |= 1 << x;
            break;
        }
    }
}
void Bitmap::setOf(char *bitMap, int nBlock) {
    int positionByte = nBlock/8;
    int iniPosition = (nBlock/8) * 8;

    for(int i = iniPosition, x = 7; i < (positionByte * 8) + 8; i++, x--){
        if(i == nBlock){
            bitMap[positionByte] &= ~(1 << x);
            break;
        }
    }
}