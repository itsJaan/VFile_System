//
// Created by Javier Nunez on 2/6/2019.
//

#ifndef VIRTUAL_FILE_SYSTEM2_0_DISCO_H
#define VIRTUAL_FILE_SYSTEM2_0_DISCO_H

#include <iostream>
#include <fstream>
#include "Structuras.h"
#include "Directories.h"
#include "Bitmap.h"

 using namespace std;

class Disco {
public:
    string discName;
    bool CrearDisco();
    bool Existe(string directoryName);
    bool createMetaDataDisk(string fileName);
};


#endif //VIRTUAL_FILE_SYSTEM2_0_DISCO_H
