#include <string>
#include "tank.h"
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;


//contructor de los objetos  Sobrecarga
//----------------------
tank::tank() : id(0), combustibles{0.0f, 0.0f, 0.0f},precios{0.0f,0.0f,0.0f}, total(0.0f), activo(0) {}

tank::tank(unsigned int id_,float regular_,float premiun_,float ecoextra_,
           float pr,float pp,float peco,unsigned short int activo_)
    : id(id_), combustibles{regular_, premiun_, ecoextra_},precios{pr,pp,peco}, total(regular_ + premiun_ + ecoextra_),activo(activo_){}


tank::tank(unsigned int id_,unsigned short int activo_)
    : id(id_), activo(activo_){
    srand(static_cast<unsigned>(time(0)));
    for(unsigned int i=0;i<3;i++){
        unsigned int numeroAleatorio = rand() % 101 + 100;
        unsigned int numprecio =rand()%20001+20000;
        combustibles[i]=numeroAleatorio;
        precios[i]=numprecio;
    }
    total=combustibles[0]+combustibles[1]+combustibles[2];
}
//-------------------------

void tank::gettank(){
    cout <<  "id tank: " <<id<<endl;
    cout << "regular: "<<combustibles[0]<<endl;
    cout << "premiun: "<<combustibles[1]<<endl;     //muestra unicamente los valores de un objeto
    cout << "ecoextra: "<<combustibles[2]<<endl;
    cout << "tank status: "<< activo<<endl;
    cout << "total: "<<total<<endl;
}
void tank::settank(unsigned short int tcombustible,unsigned short int cant){ //ingresa tipo de combustible(indice) y cantidad
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
    os <<tank.id<<";"<< tank.combustibles[0]<< ";" << tank.combustibles[1]<<";"<<tank.combustibles[2]<<";"<<
        tank.total<<";"<<tank.activo<<";"<<tank.precios[0]<<";"<<tank.precios[1]<<";"<<tank.precios[2];
    return os;
}

unsigned int tank:: contadorlineas(){
    string linea="";
    unsigned int count=0;
    ifstream objetostanks("C:\\Users\\juan david\\Documents\\desafioII\\tank.txt");
    while(getline(objetostanks,linea)){
        count++;
    }
    objetostanks.close();
    return count;
}

tank* tank::TXTobj(const string& rutaArchivo){
    unsigned int count=contadorlineas();
    tank* arrobjetos = new tank[count];
    string atributos[9];
    string linea="";
    unsigned short int i=0;
    ifstream txt(rutaArchivo);
    if (!txt.is_open()) {
        cout << "Error al abrir el archivo." << endl;
        return nullptr;        // Si no se puede abrir el archivo, retornamos null
    }
    while(getline(txt,linea)){
        unsigned int posInicio = 0, posDelim, index = 0;
        while ((posDelim = linea.find(';', posInicio)) != string::npos&&index<9){
            atributos[index]= linea.substr(posInicio, posDelim - posInicio);
            posInicio = posDelim + 1;
            index++;
        }
        arrobjetos[i]= tank(stoi(atributos[0]),stof(atributos[1]),
                             stof(atributos[2]),stof(atributos[3]),stof(atributos[6]),
                             stof(atributos[7]),stof(atributos[8]), stoi(atributos[5]));
        i++;
    }
    txt.close();
    return arrobjetos;
}
void tank:: Saveobj(tank* array,tank obj,const string& archivo){    //guardar objetos en archivo
    unsigned int tam=contadorlineas();
    ofstream texto(archivo);
    texto<<obj<<endl;
    for(unsigned int i=0;i<tam;i++){
        texto<<array[i]<<endl;
    }
    texto.close();
}
void tank::setprecios(float pr,float pp,float peco){
    precios[0]=pr;
    precios[1]=pp;
    precios[2]=peco;
    return;
}


//destructor
//---------
tank::~tank(){}
//---------
