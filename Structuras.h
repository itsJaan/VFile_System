//
// Created by Javier Nunez on 1/22/2019.
//

#ifndef VIRTUAL_FILE_SYSTEM2_0_STRUCTURAS_H
#define VIRTUAL_FILE_SYSTEM2_0_STRUCTURAS_H

//---------Bloques-----------------
struct bloque_directo{
    char data[4096];
};
struct bloque_n1{
    bloque_directo p[16];
};
struct bloque_n2{
    bloque_n1 p[32];
};
struct bloque_n3{
    bloque_n2 p[64];
};
//--------------------------------
struct Date{
    char dia[2];
    char mes[2];
    char anio[4];
};//size 8
struct File_Entry{
    char nombre[30];
    int size;
    char tipo=' ';
    Date fecha;

     int padre=-1;
     int primer_hijo=-1;
     int hermano_derecho=-1;
     bool libre=false;

 /*Manejo de directorios

        Recordar de hacer  los file entries como un arreglo lineal de  entry amount para la cantidad
        evaluando padre como roots , primer hijo para el primer hijo  desde el lado izquierdo del arreglo
        apuntando a la posicion del mismo en los arareglos, hermano derecho para   hermanos en el mismo directorio
        para el primer hijo para poder movernos en el directorio/arreglos

     */
    unsigned int bl_directo[12];
    unsigned int bl_indirecto[3];


};//size 121 tot size
//-------------------------------------
 struct metadata{
     int Entry_Amount;
     int Block_Size = 4096;
     int General_Blocks;//=Entry_Amount*33308;
     int L1_Blocks;
     int L2_Blocks;
     int L3_Blocks;
     unsigned int Disc_Size;//=( Block_Size*Block_Amount ) + (Entry_Amount*103);
 };


#endif //VIRTUAL_FILE_SYSTEM2_0_STRUCTURAS_H
