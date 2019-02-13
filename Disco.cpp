//
// Created by Javier Nunez on 2/6/2019.
//

#include "Disco.h"

bool Disco:: CrearDisco() {
    string discName;
    cout << "Ingrese nombre del Disco: ";
    cin >> discName;
    if (Existe(discName)){
        cout << "Ya existe un disco con ese nombre" << endl;
        return false;
    }
    createMetaDataDisk(discName);
    return true;
}
bool Disco::Existe(string directoryName) {
    string temporalName = directoryName + ".dat";
    ifstream file(temporalName, ios::in | ios::binary);
    if (!file)
        return false;
    return true;
}
bool Disco:: createMetaDataDisk(string discName){
    ofstream disc(discName + ".dat", ios::out | ios::binary);
    if (!disc.is_open()) {
        disc.open(discName + ".dat");
    }

    metadata *md = new metadata;
    cout << "Ingrese cantidad de entradas que permitira:";
    cin >> md->Entry_Amount;




    //Caculos de METADATA
    //Bloques directos e indirectos
    md->General_Blocks=md->Entry_Amount*33308;
    md->L1_Blocks=md->Entry_Amount*2081;//2048+33
    md->L2_Blocks=md->Entry_Amount*65;
    md->L3_Blocks=md->Entry_Amount*1;
    ////////////////////////////////////////
    md->Disc_Size=((md->Block_Size*md->General_Blocks)/1024)/1024;


    Directories *dir=new Directories(md->General_Blocks,md->Entry_Amount,discName);
    File_Entry array[md->Entry_Amount];
    dir->fillArray(array);

    //BITMAP
    Bitmap *map=new Bitmap();
    map->w=md->General_Blocks/8;
    map->x=md->L1_Blocks/8;
    map->y=md->L2_Blocks/8;
    map->z=md->L3_Blocks/8;
    map->bloquesOcupados=0;

    map->BloquesDirectos=new char[map->w];
    map->initBitMap(map->BloquesDirectos, md->General_Blocks);


    //Escribimos en disco
    disc.seekp(0, ios::end);
    disc.write(reinterpret_cast<char*>(md), sizeof(metadata));
    disc.write(reinterpret_cast<char*>(map), sizeof(Bitmap));
    cout<<"Cargando....\n"<<endl;
    //entradas
    for (int i = 0; i < md->Entry_Amount; i++) {
        File_Entry entryEscribir=array[i];
        disc.write(reinterpret_cast<char*>(&entryEscribir), sizeof(File_Entry));
    }
    //bloques
    for (int i = 0; i < md->General_Blocks; i++) {
        bloque_directo *dataEscribir = new bloque_directo();
        disc.write((char*)dataEscribir, sizeof(bloque_directo));
    }

    cout << "Se creo exitosamente el nuevo disco : "<<discName<<endl<<endl;

    cout<<"Entradas Permitidas: "<<md->Entry_Amount<<endl;
    cout<<"Tamano: "<<md->Disc_Size<<" mbs"<<endl;
    cout<<"Bit map size: "<<"\n\t\tBloques Directos: "<<map->w<<"\n\t\tBloques Nivel 1: "<<map->x<<
        "\n\t\tBloques Nivel 2: "<<map->y<<"\n\t\tBloques Nivel 3: "<<map->z+1<<endl<<endl;
    disc.close();
    return true;
}