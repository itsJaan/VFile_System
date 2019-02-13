//
// Created by Javier Nunez on 2/6/2019.
//

#ifndef VIRTUAL_FILE_SYSTEM2_0_BITMAP_H
#define VIRTUAL_FILE_SYSTEM2_0_BITMAP_H


class Bitmap {
public:
    int  w,x,y,z;
    int bloquesOcupados;
    char *BloquesDirectos= new char[w];
    char *BloquesL1= new char [x];
    char *BloquesL2= new char [y];
    char *BloquesL3= new char [z];

    void initBitMap(char *bitMap , int Block_Amount);
    void setOn(char *bitMap, int nBlock);
    void setOf(char *bitMap, int nBlock);
};


#endif //VIRTUAL_FILE_SYSTEM2_0_BITMAP_H
