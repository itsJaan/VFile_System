//
// Created by Javier Nunez on 1/29/2019.
//

#ifndef VIRTUAL_FILE_SYSTEM2_0_DIRECTORIES_H
#define VIRTUAL_FILE_SYSTEM2_0_DIRECTORIES_H

#include <iostream>
#include "Structuras.h"
#include "Disco.h"
#include "Bitmap.h"

using namespace std;

class Directories {
public:
    int tam , bloquesCant;
    int Actual_Pos;
    int sizeArchivos;
    string discName, actualUbicationString;
    //AUXILIARES
    void generateDate();
    void fillArray(File_Entry array[]);
    void actualizar_Disco(metadata *md,File_Entry array[],Bitmap *bitmap);
    void DeleteArchive(File_Entry array[], string nametoDelete, Bitmap*bitmap, int bloques);


    Directories(int p, int t, string discName);
    bool CreateDirectory(File_Entry array[], char tipo);
    bool ChangeDirectory(File_Entry array[]);
    void goBack(File_Entry array[]);
    void ListInside(File_Entry array[]);
    void DirectoriesandArchivesList(File_Entry array[]);
    bool DeleteDirectory(File_Entry array[], string nametoDelete, Bitmap *bitmap);
    bool ImportArchive(File_Entry Array[], Bitmap *bitmap);
    bool ExportArchive(File_Entry Array[], Bitmap *bitmap);

};


#endif //VIRTUAL_FILE_SYSTEM2_0_DIRECTORIES_H
