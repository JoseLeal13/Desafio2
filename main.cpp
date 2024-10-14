#include "estacion.h"
#include "tank.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
void Mopcion();//mostrar opciones
void Mopred();//mostrar opciones de la red
void Mopes();//mostrar opciones para una estacion
void MopSurtidores();//mostrar opciones para los surtidores
/*int main() {
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
            cout<<"agregando estacion..."<<endl;

            //break;
        }else if(opcred==2){//eliminar una estacion
             system("cls");
            cout<<"eliminando estacion..."<<endl;
            //break;
        }else if(opcred==3){// calcular las ventas
             system("cls");
            cout<<"calculando ventas..."<<endl;
            //break;
        }else if (opcred==4){//fijar el precio de los combustibles
             system("cls");
            cout<<"fijando precios..."<<endl;
            //break;
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
*/
int main(){
    //tank:tankes myTank(0, 0.0,0.0, 0.0, 1);
    tank tankn(12345,20,12,148,1);
    tank tank2(121234,23,23,154,0);
    tank tank3(12345,23,21,12,0);
    tank lista[3]={tankn,tank2,tank3};
    tankn.gettank();
    tank* array=tank::TXTobj("C:\\Users\\juan david\\Documents\\desafioII\\tank.txt");
    tank::Saveobj(array,lista,"C:\\Users\\juan david\\Documents\\desafioII\\tank.txt");
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

