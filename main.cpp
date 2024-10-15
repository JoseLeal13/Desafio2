#include "estacion.h"
#include "tank.h"
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <cstdlib>
using namespace std;
void Mopcion();//mostrar opciones
void Mopred();//mostrar opciones de la red
void Mopes();//mostrar opciones para una estacion
void MopSurtidores();//mostrar opciones para los surtidores
void ingresarDatosEstacion(string& nombre, unsigned int& id, string& gerente, char& region,
                           double& latitud, double& longitud, string& maquina,
                           unsigned short int& isla, unsigned short int& activo);

int main() {
    string archivotanks="C:\\Users\\juan david\\Documents\\desafioII\\tank.txt";
    string archivoEst="C:\\Users\\juan david\\Documents\\desafioII\\estacion.txt";
    string archivoventas="C:\\Users\\juan david\Documents\\desafioII\\ventas.txt";
    estacion* Estsaved=estacion::TXTobj(archivoEst);
    tank* tankes=tank::TXTobj(archivotanks);
    string nombre;
    unsigned int id;
    string gerente;
    char region;
    double latitud;
    double longitud;
    string maquina;
    unsigned short int isla,activo,surtidores;
    string idsurtidor;
    unsigned short int opcion=0;
    while(opcion!=3){
         system("cls");
        Mopcion();  //muestra opciones para gestionar red o estaciones
        cin>>opcion;
        if (opcion==1){ //gestionar la red
            system("cls");
            unsigned short int opcred=6;//opcion red
        while(opcred!=0){
            Mopred();//muestra las opciones de la gestion de red
            cin>>opcred;

        if (opcred==1){ //agregar estacion
            system("cls");
            ingresarDatosEstacion(nombre, id, gerente, region, latitud, longitud, maquina, isla, activo);
            estacion Est1(nombre, id, gerente, region, latitud, longitud, maquina, isla, activo);
            tank tank1(id,activo);
            cout <<"Ingrese cantidad de surtidores: ";
            cin>>surtidores;
            while(surtidores>0){
                cout<<"Ingrese el Id del surtidor: ";
                cin>>idsurtidor;
                Est1.agregarSurtidor(idsurtidor);
                surtidores-=1;
            }
            tank::Saveobj(tankes,tank1,archivotanks);
            Est1.guardarTXT(archivoEst);
            cout<<"Estacion creada correctamente..."<<endl;
            system("cls");
            //tank1.gettank();
            //Est1.mostrarSurtidor(2);

        }else if(opcred==2){//eliminar una estacion
             system("cls");
            unsigned int tam=estacion::contadorlineas(archivoEst);
            cout<<"Ingrese el Id de la estacion a eliminar: ";
            cin>>id;
            unsigned short int objel;
            for (unsigned int i=0;i<tam;i++){
                if(id==Estsaved[i].getId()&&tankes[i].Getid()==id){
                    Estsaved[i].mostrarInfo();
                    tankes[i].gettank();
                    Estsaved[i].setactivo(0);
                    tankes[i].setactivo(0);
                    objel=i;
                    break;
                }

            }
            estacion::guardarTXT(Estsaved,Estsaved[objel],archivoEst);
            //tank::Saveobj(tankes,tankes[objel],archivotanks);

            cout <<"Estacion eliminada Correctamente..."<<endl;
            Estsaved[objel].mostrarInfo();
            tankes[objel].gettank();



            //break;
        }else if(opcred==3){// calcular las ventas
             system("cls");
            cout<<"calculando ventas..."<<endl;
            //break;
        }else if (opcred==4){//fijar el precio de los combustibles
             system("cls");
            unsigned int tam=estacion::contadorlineas(archivoEst);
            float newpricea=0,newpriceb=0,newpricec=0;
            cout<<"Ingrese el nuevo precio de los combustibles."<<endl;
            cin>>newpricea;
            cin>>newpriceb;
            cin>>newpricec;
            for (unsigned short int i=0;i<tam;i++){
                tankes[i].setprecios(newpricea,newpriceb,newpricec);
            }
            tankes[0].getprice();

        }else if (opcred==0){
             system("cls");
            cout<<"saliendo de el programa..."<<endl;
            break;
           }
        else{
             system("cls");
            cout <<"Ingrese una opcion valida."<<endl;
           }
        }
    }
    //gestionar las estaciones
    else if(opcion==2){
            system("cls");
            unsigned short int opce=8;//opcion estacion
            while(opce!=0){
            Mopes();
                cin>>opce;
            if (opce==1){
                system("cls");
                    unsigned int short ops=8;
                    while(ops!=0){
                        MopSurtidores();
                        cin>>ops;
                        if (ops==1){
                            system("cls");
                            cout<< "Agregando surtior"<<endl;
                        }else if(ops==2){
                            system("cls");
                            cout<< "Eliminando surtidor"<<endl;
                        }else if(ops==3){
                            system("cls");
                            cout << "Activando surtidor"<<endl;
                        }else if (ops==4){
                            system("cls");
                            cout<<"Desactivando surtidor"<<endl;
                        }else if (ops==5){
                            system("cls");
                            cout<<"mostrando historial"<<endl;
                        }else if(ops==0){
                            system("cls");
                            break;
                        }else{
                            system("cls");
                            cout<<"Ingrese una opcion valida"<<endl;
                        }
                    }
            }else if(opce==2){
                system("cls");
                break;
            }
            else if(opce==3){
                system("cls");
                break;
            }else if(opce==4){
                system("cls");
                break;
            }

        }
    }else if (opcion==3){
        cout<<"Saliendo de el programa...."<<endl;
        break;
    }else{
        cout << "Ingrese una opcion valida."<<endl;
    }

    }
    return 0;
}



void Mopcion(){//mostrar opciones
    cout << "1. Gestionar la red de estaciones."<<endl;
    cout << "2. Gestionar las estaciones de servicio."<<endl;
    cout << "3. Salir"<<endl;
    return;

}
void Mopred(){  //mostrar opciones para la gestion de la red
    cout << "0.  Atras."<<endl;
    cout << "1.  Agregar estaciones de servicio."<<endl;
    cout << "2.  Eliminar una E/S de la red nacional."<<endl;
    cout << "3.  Calcular el monto total de las ventas."<<endl;
    cout << "4.  Fijar los precios del combustible para toda la red."<<endl;
    return;
}
void Mopes(){ //mostras opciones para la gestion de una estacion
    cout<<"0. Atras."<<endl;
    cout<<"1. Para configuar surtidores."<<endl;
    cout<<"2. Reporte litros vendidos."<<endl;
    cout<<"3. Simular una venta."<<endl;
    cout<<"4. Asignar capacidad tanque de suministro."<<endl;
    return;
}
void MopSurtidores(){
    cout<<"0. Atras."<<endl;
    cout<<"1. Agregar surtidor."<<endl;
    cout<<"2. Eliminar surtidor."<<endl;
    cout<<"3. Activar surtidor."<<endl;
    cout<<"4. Desactivar surtidor."<<endl;
    cout<<"5. Historial de surtidor."<<endl;
}


void ingresarDatosEstacion(string& nombre, unsigned int& id, string& gerente, char& region,
                           double& latitud, double& longitud, string& maquina,
                           unsigned short int& isla, unsigned short int& activo) {
    cout << "Ingrese nombre de la estacion: ";
    cin.ignore();
    getline(cin, nombre);
    cout << "Ingrese identificacion de la estacion: ";
    cin >> id;
    cout << "Ingrese nombre del gerente de la estacion: ";
    cin.ignore();
    getline(cin, gerente);
    cout << "Ingrese region de la estacion (N/S/C): ";
    cin >> region;
    cout << "Ingrese coordenadas estacion (Latitud-Longitud): ";
    cin >> latitud >> longitud;
    cout << "Ingrese el modelo de surtidoras: ";
    cin >> maquina;
    cout << "Ingrese la cantidad de islas de la estacion: ";
    cin >> isla;
    cout << "Ingrese si la estacion esta activa (1 o 0): ";
    cin >> activo;
}

