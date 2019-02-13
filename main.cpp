#include <iostream>
#include <fstream>
#include "Structuras.h"
#include "Directories.h"
#include "Disco.h"
#include "Bitmap.h"

using namespace std;

int main(){
    int o;
    Disco disco;
    do {
        cout<<"--------Main Menu--------\n";
        cout<<"1.Crear Disco\n";
        cout<<"2.Usar Disco Existente\n";
        cout<<"0.Salir"<<endl;
        cout<<"Ingrese su opcion:";
        cin>>o;

        switch(o) {
            case 1:
                disco.CrearDisco();
                break;
            case 2:
                string nombre;
                cout<<"Ingrese nombre del Disco: ";
                cin>>nombre;
                string temporalN= nombre+".dat";

                if(disco.Existe(nombre)){
                    string opcion;
                    metadata *md= new metadata();
                    Bitmap *map= new Bitmap();

                    ifstream lectura(temporalN, ios::in|ios::binary);

                    lectura.seekg(0,ios::beg);
                    lectura.read(reinterpret_cast<char *>(md), sizeof(metadata));
                    lectura.seekg(sizeof(metadata), ios::beg);
                    lectura.read(reinterpret_cast<char*>(map), sizeof(Bitmap));

                    Directories *dir=new Directories(md->General_Blocks,md->Entry_Amount, disco.discName);
                    dir->discName=nombre;
                    File_Entry array[md->Entry_Amount];
                    for(int i=0 ; i<md->Entry_Amount; i++) {
                        lectura.read(reinterpret_cast<char*>(&array[i]), sizeof(File_Entry));
                    }
                    cout<<"========Metadata========="<<endl;
                    cout<<"Entradas Permitidas: "<<md->Entry_Amount<<"\tTamano: "<<md->Disc_Size<<" mbs"<<endl;
                    cout<<"Bit map size: "<<"\n\t\tBloques Directos: "<<map->w<<"\n\t\tBloques Nivel 1: "<<map->x<<
                        "\n\t\tBloques Nivel 2: "<<map->y<<"\n\t\tBloques Nivel 3: "<<map->z+1<<endl<<endl;



                    bool continuar = true;
                    string nameToDelete;
                    do {
                        cout << "\n===========================================================================" << endl;
                        cout <<"Disco:"<<dir->discName<<"\n\t"<<dir->Actual_Pos<<endl;
                        cout << "===========================================================================" << endl;
                        cout << "mkdir - Crear Directorio " << endl;
                        cout << "cd - Cambiar Directorio" << endl;
                        //cout<<  "Ls - Directories y Archivos Dentro"<<endl;
                        cout << "ls - Listar Directorios y Archivos" << endl;
                        cout << "rm - Eliminar Directorio/Archivo" << endl;
                        cout << "i - Importar Archivo" << endl;
                        cout << "e -  Exportar Archivo" << endl;
                        cout << "go -  Regresar" << endl;
                        cout << "p - Salir al menu principal" << endl;
                        cout << "" << endl;
                        cout << "::";
                        cin >> opcion;
                        cout << "===========================================================================" << endl;


                        switch (opcion.at(0)) {
                            case 'm':
                                dir->CreateDirectory(array,'D');
                                //dir->actualizar_Disco(md,array);
                                break;
                            case 'c':
                                dir->ChangeDirectory(array);
                                break;
                            case 'L':
                                dir->DirectoriesandArchivesList(array);
                                break;
                            case 'l':
                                dir->ListInside(array);
                                break;
                            case 'r':
                                cout<<"Nombre Carpeta:";
                                cin>>nameToDelete;
                                dir->DeleteDirectory(array, nameToDelete,map);
                                break;
                            case 'i':
                                dir->ImportArchive(array,map);
                                break;
                            case 'e':
                                dir->ExportArchive(array, map);
                                break;
                            case 'g':
                                dir->goBack(array);
                                break;
                            case 'p':
                                dir->actualizar_Disco(md,array,map);
                                continuar = false;
                                break;
                        }
                    } while (continuar);
                    lectura.close();
                }else
                    cout<<"Disco Invalido\n";
        }
    }while(o!=0);
    return 0;
}


