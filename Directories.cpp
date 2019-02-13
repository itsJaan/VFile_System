//
// Created by Javier Nunez on 1/29/2019.
//

#include "Directories.h"

#include <iostream>
#include <fstream>
#include "Structuras.h"
#include "Disco.h"
#include "Bitmap.h"

using namespace std;

int Cantidad_Ocupados=0;

Directories::Directories(int p ,int t, string discName) {
    this->tam=t;
    this->bloquesCant=p;
    this->discName=discName;
    this->Actual_Pos=-1;
    this->actualUbicationString=" ";
}
void Directories::fillArray(File_Entry array[]) {
    for (int i = 0; i < this->tam; i++) {
        File_Entry entry;
        entry.libre = false;
        array[i] = entry;
    }
};
bool Directories::CreateDirectory(File_Entry array[], char tipo) {
    File_Entry tmp;
    int actual = this->Actual_Pos;
    cout<<"Ingrese el nombre del directorio: ";
    cin>>tmp.nombre ;
    tmp.libre = true;
    tmp.tipo=tipo;
    if(tipo=='D')
        tmp.size=117;
    tmp.padre=actual;
    int cont=0;
    for(int d; d<tam;d++){
        if(array[d].libre==true)
            Cantidad_Ocupados++;
    }
    for(int i=0; i<this->tam ; i++){
        if(array[i].libre == false){
            if(i<Cantidad_Ocupados){
                array[i].libre = true;
                tmp.libre = true;
                tmp.primer_hijo = -1;
                tmp.hermano_derecho = -1;
                array[i] = tmp;
                cout << "Se creo la carpeta: " << tmp.nombre << "\n";
                for (int h = 0; h < this->tam; h++) {
                    if (h != i && array[h].hermano_derecho == -1 && array[h].padre==array[i].padre) {
                        array[h].hermano_derecho = i;
                        return true;
                    }
                    if(array[h].primer_hijo==-1 && h==actual){
                        array[h].primer_hijo=i;
                        return true;
                    }
                }
                break;
            }
            array[i].libre = true;
            tmp.libre = true;
            tmp.primer_hijo = -1;
            tmp.hermano_derecho = -1;
            array[i] = tmp;
            cout << "Se creo la carpeta: " << tmp.nombre << "\n";
            if(Cantidad_Ocupados>0) {
                for (int j = 0; j < this->tam; j++) {

                    if (array[j].padre == array[i].padre && array[j].hermano_derecho == -1) {
                        array[j].hermano_derecho = i;
                        return true;
                    }
                    if(array[j].primer_hijo==-1 && j==actual){
                        array[j].primer_hijo=i;
                        return true;
                    }
                }
            }
            break;
        }
        cont++;
        if(cont==this->tam)
            cout<<"Ya no hay suficiente espacio\n";
    }
    Cantidad_Ocupados=0;
};
bool Directories::ChangeDirectory(File_Entry array[]){
    string nom;
    cout<<"Ingrese nombre de Carpeta:";
    cin>>nom;
    for(int i=0; i<tam; i++) {
        if(i==tam)
            cout << "No existe Carpeta" << endl;
        if (array[i].nombre == nom && array[i].padre == this->Actual_Pos) {
            actualUbicationString = nom;
            this->Actual_Pos = i;

            return true;
        }
    }
    cout << "No se puede accesar a la carpeta." << endl;
    return false;
}
void Directories::goBack(File_Entry array[]){
    File_Entry tmp;
    for(int i=0; i<tam ; i++){
        if(i==this->Actual_Pos) {
            if(array[i].padre==-1)
                actualUbicationString=" ";
            else
                actualUbicationString=array[i].nombre;
            this->Actual_Pos = array[i].padre;
            break;
        }
    }
}
bool Directories::DeleteDirectory(File_Entry array[], string nametoDelete , Bitmap *bitmap){
    int actual = this->Actual_Pos;
    int x=0;
    for(int i=0; i<tam ; i++){
        File_Entry tmp , tmp2 , tmp3;
        if(array[i].nombre==nametoDelete) {
            //File Vacio
            File_Entry entry;
            ///////////////////
            tmp = array[i];//raiz
            if (tmp.tipo == 'A'){//Si es archivo
                int n=tmp.size/4096;
                DeleteArchive(array, nametoDelete , bitmap, n);
            }
            if(tmp.primer_hijo!=-1) {
                if(array[tmp.primer_hijo].hermano_derecho!=-1){//primer hijo
                    actual = tmp.primer_hijo;//int para ubicar primer hijo
                    tmp2=array[actual];
                    //delete (&tmp2);
                    entry.primer_hijo-1;
                    entry.hermano_derecho-1;
                    entry.size=0;
                    entry.padre-1;
                    entry.libre = false;

                    array[i] = entry;

                    x=array[actual].hermano_derecho;
                    tmp3=array[x];
                    tmp.primer_hijo=tmp3.hermano_derecho;//asignacion 3er hijo
                    //array[tmp.primer_hijo].hermano_derecho=array[array[tmp3.hermano_derecho].hermano_derecho].hermano_derecho;
//                    delete(&tmp3);
                    entry.primer_hijo-1;
                    entry.hermano_derecho-1;
                    entry.size=0;
                    entry.padre-1;
                    entry.libre = false;

                    array[x] = entry;
                    DeleteDirectory(array, array[i].nombre, bitmap);
                    DeleteDirectory(array, array[x].nombre , bitmap);
                    DeleteDirectory(array, array[actual].nombre, bitmap);
                }
                actual = tmp.primer_hijo;
                //delete(&tmp);
                entry.primer_hijo-1;
                entry.hermano_derecho-1;
                entry.size=0;
                entry.padre-1;
                entry.libre = false;
                array[i] = entry;
                DeleteDirectory(array, array[actual].nombre, bitmap);
            }

            //delete(&tmp);
            entry.primer_hijo-1;
            entry.hermano_derecho-1;
            entry.size=0;
            entry.padre-1;
            entry.libre = false;

            array[i] = entry;
            this->Actual_Pos=-1;

            // Actualizaciones de Hijos y Hermanos
            for(int j=0;j<tam;j++){
                if(array[j].padre==tmp.padre&&tmp.hermano_derecho==-1&&array[j].hermano_derecho==i){
                    array[j].hermano_derecho=-1;
                    return true;
                }
                if(array[j].padre==tmp.padre&&tmp.hermano_derecho!=1&&array[j].hermano_derecho==i){
                    array[j].hermano_derecho=tmp.hermano_derecho;
                    return true;
                }
                if(tmp.hermano_derecho!=-1&&array[j].primer_hijo==i) {
                    array[j].primer_hijo = tmp.hermano_derecho;
                    return true;
                }
                if(tmp.hermano_derecho==-1&&array[j].primer_hijo==i){
                    array[j].primer_hijo=-1;
                    return true;
                }
            }
        }
    }
};
void Directories::DeleteArchive(File_Entry array[], string nametoDelete , Bitmap *bitmap , int bloques) {
    cout<<bloques<<endl;
    for( int i=bloques ; i<=0 ;i -- ){
        cout<<"desactivando\n";
        bitmap->setOf(bitmap->BloquesDirectos, i);
    }
    cout<<"Se borro Archivo"<<nametoDelete<<endl;
}
void Directories::ListInside(File_Entry array[]){
    cout<<"Nombre de Carpteta \t Tipo \t Tamano"<<endl;
    for(int i=0; i<this->tam ; i++){
        if(array[i].padre==this->Actual_Pos){
            if(array[i].libre){
                cout<<"   "<<array[i].nombre<<"  \t\t "<<array[i].tipo<< " \t "<<array[i].size<<"bytes"<<endl;
            }else
                cout<<"";
        }
    }
}
void Directories::DirectoriesandArchivesList(File_Entry array[]){
    cout<<"        Nombre   \t Tipo \tPadre  \tHermano Derecho \tPrimer Hijo"<<endl;
    for(int i=0; i<this->tam; i++ ){
        if(array[i].libre){
            cout<<i<<"    "
                     "    "<<array[i].nombre<<
                "  \t\t  "<<array[i].tipo<<
                "   \t "<<array[i].padre<<
                "   \t\t "<<array[i].hermano_derecho<<
                "   \t\t "<<array[i].primer_hijo<<endl;
        }else
            cout<<"";
    }
}
void Directories::actualizar_Disco(metadata *md, File_Entry *array , Bitmap *bitmap) {
    ofstream disc(discName + ".dat", ios::out | ios::binary);
    if (!disc.is_open()) {
        disc.open(discName + ".dat");
    }

    disc.seekp(0, ios::end);
    disc.write(reinterpret_cast<char*>(md), sizeof(metadata));
    disc.seekp(sizeof(Bitmap), ios::end);
    //disc.write(reinterpret_cast<char*>(&bitmap), sizeof(Bitmap));
    cout<<"Actualizando..."<<endl;
    for (int i = 0; i <tam ; i++) {
        File_Entry entryEscribir=array[i];
        disc.write(reinterpret_cast<char*>(&entryEscribir), sizeof(File_Entry));
    }
    for (int i = 0; i < md->General_Blocks; i++) {
        bloque_directo *dataEscribir = new bloque_directo();
        disc.write((char*)dataEscribir, sizeof(bloque_directo));
    }
    cout << "Disco * "<<discName<<" *  Actualizado Automaticamente"<<"\t\t"<<"\t\t";
    cout<<"Entradas Permitidas: "<<md->Entry_Amount<<"\t\t";
    cout<<"Tamano: "<<md->Disc_Size<<" mbs"<<endl;
     disc.close();
}
bool Directories::ImportArchive(File_Entry array[] , Bitmap *bitmap){
    File_Entry tmp;
    int bloquesAOcupar=0;

    cout<<"Nombre del documento:";
    cin>>tmp.nombre;
    ifstream lectura(tmp.nombre, ios::in | ios::binary);
    if(lectura) {
        lectura.seekg(0 , ios::end);
        sizeArchivos=lectura.tellg();
        if(sizeArchivos<= (bloquesCant*4096)){
            /************************************************Guardando en Arreglo*********************************************/
            int actual = this->Actual_Pos;
            tmp.padre=actual;
            tmp.tipo='A';
            tmp.size=sizeArchivos;
            int cont=0;
            for(int d; d<tam;d++){
                if(array[d].libre==true)
                    Cantidad_Ocupados++;
            }
            for(int i=0; i<this->tam ; i++){
                if(array[i].libre == false){
                    if(i<Cantidad_Ocupados){
                        array[i].libre = true;
                        tmp.libre = true;
                        tmp.primer_hijo = -1;
                        tmp.hermano_derecho = -1;
                        array[i] = tmp;
                        cout << "Se creo la carpeta: " << tmp.nombre << "\n";
                        for (int h = 0; h < this->tam; h++) {
                            if (h != i && array[h].hermano_derecho == -1 && array[h].padre==array[i].padre) {
                                array[h].hermano_derecho = i;
                                return true;
                            }
                            if(array[h].primer_hijo==-1 && h==actual){
                                array[h].primer_hijo=i;
                                return true;
                            }
                        }break;
                    }
                    array[i].libre = true;
                    tmp.libre = true;
                    tmp.primer_hijo = -1;
                    tmp.hermano_derecho = -1;
                    array[i] = tmp;
                    cout << "Se creo la carpeta: " << tmp.nombre << "\n";
                    if(Cantidad_Ocupados>0) {
                        for (int j = 0; j < this->tam; j++) {
                            if (array[j].padre == array[i].padre && array[j].hermano_derecho == -1) {
                                array[j].hermano_derecho = i;
                                return true;
                            }
                            if(array[j].primer_hijo==-1 && j==actual){
                                array[j].primer_hijo=i;
                                return true;
                            }
                        }
                    }break;
                }cont++;
                if(cont==this->tam)
                    cout<<"Ya no hay suficiente espacio\n";
            }Cantidad_Ocupados=0;
            /************************************************Guardando en Arreglo*********************************************/

            bloquesAOcupar=tmp.size/4096;
            if(bloquesAOcupar==0)
                bloquesAOcupar++;
            for(int c=bitmap->bloquesOcupados+1; c<bloquesAOcupar; c++) {
                //cout<<"Cargando Bitmap...\n";
                bitmap->setOn(bitmap->BloquesDirectos, c);
                bitmap->bloquesOcupados++;
            }
        }else{
            cout<<"Espacio Insuficiente..\n";
        }
    }else{
        cout<<"No se pudo Abrir..\n";
    }
};
bool Directories::ExportArchive(File_Entry Array[], Bitmap *bitmap){
    File_Entry tmp;
    char n_nombre[20];
    cout<<"Nombre del documento:";
    cin>>tmp.nombre;
    cout<<"Nuevo Nombre:";
    cin>>n_nombre;

    ofstream escritura(n_nombre, ios::out | ios::binary);
    escritura.seekp(0, ios::end);
    char *d;
   for(int i=0;i<((tmp.size/1024)/2); i++){
        d+=' ';
        escritura.write((char*)(&d), sizeof(d));
        //if(i==(tmp.size/1024))break;
    }

    return true;
};

