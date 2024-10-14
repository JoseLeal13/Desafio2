#include <string>
#include "tank.h"
#include <fstream>
#include <iostream>
using namespace std;


//contructor de los objetos
tank::tank(unsigned int id_,unsigned short int regular_,unsigned short int premiun_,unsigned short int ecoextra_,unsigned short int activo_) {
    id=id_;
    combustibles[0]=regular_;
    combustibles[1]=premiun_;
    combustibles[2]=ecoextra_;
    activo=activo_;
    total=regular_+premiun_+ecoextra_;
}
void tank::mostrar(){
    cout << id << " id tank"<<endl;
    cout << "regular: "<<combustibles[0]<<endl;
    cout << "premiun: "<<combustibles[1]<<endl;
    cout << "ecoextra: "<<combustibles[2]<<endl;
    cout << "tank status: "<< activo<<endl;
    cout << "total: "<<total<<endl;
}
void tank::modcombustible(unsigned short int tcombustible,unsigned short int cant){
    if (tcombustible>=0&&tcombustible<=3){
        if(cant<=combustibles[tcombustible-1]){
            combustibles[tcombustible-1]-=cant;
            cout << "Se ha retirado: "<<cant<<" galones del tipo "<<tcombustible<<endl;
        }else{
            cout << "cantidad insuficiente de combustible "<<endl;
        }
    }else{
        cout << "Tipo invalido de combustible"<<endl;
    }

}

int tank::getrest(unsigned short int tcombustibles){
    return combustibles[tcombustibles-1];
}
ostream& operator<<(ostream& os, const tank& tank) {
    /*esta funcion tiene como unico objetivo sobrecargar el operador "<<" para asi
     * poder guaradar los objetos de la clase en un archivo txt.
    */
    os <<tank.id<<";"<< tank.combustibles[0]<< ";" << tank.combustibles[1]<<";"<<tank.combustibles[2]<<";"<<tank.total<<";"<<tank.activo;
    return os;
}

/*tank* tank::objetos(){
    string linea;
    tank* arreglo = new tank[4];
    unsigned int lista[6];
    unsigned int atributo;
    ifstream tankes("C:\\Users\\juan david\\Documents\\desafioII\\tank.txt");
    if(!tankes.is_open()){
        cout<< "No se pudo abrir el archivo"<<endl;
        return nullptr;
    }
    while(getline(tankes,linea)){
        unsigned int posInicio = 0, posDelim,index=0;
        while ((posDelim = linea.find(';', posInicio)) != string::npos&&index<6){
            atributo = stoi(linea.substr(posInicio, posDelim - posInicio));
            lista[index]=atributo;
            posInicio = posDelim + 1;
            index++;
        }
        tank tankn(lista[0],lista[1],lista[2],lista[3],lista[4],lista[5]);
        for (unsigned short int i=0;i<4;i++)){
                arreglo[i]=tankn;
                cout<<arreglo[i]<<endl;
        }

    }
    tankes.close();
    return arreglo;
*/
