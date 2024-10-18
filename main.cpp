#include "estacion.h"
#include "tank.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>// Para system()
#include <cctype>
using namespace std;

void Mopcion(); // mostrar opciones
void Mopred(); // mostrar opciones de la red
void Mopes(); // mostrar opciones para una estacion
void MopSurtidores(); // mostrar opciones para los surtidores
void ingresarDatosEstacion(string& nombre, unsigned int& id, string& gerente, char& region,
                           double& latitud, double& longitud, string& maquina,
                           unsigned short int& isla, unsigned short int& activo);

void simularventa(double cant,string categoria,
                  string metodoPago,string documentoCliente,
                  estacion obj,tank obj2, string archivoEst); //funcion para simular ventas

/*
int main() {
    const string archivoEstacion = "C:\\Users\\juan david\\Documents\\desafioII\\estacion.txt";
    const string archivoSurtidor = "C:\\Users\\juan david\\Documents\\desafioII\\surtidora.txt";

    // Cargar las estaciones desde el archivo
    estacion* estaciones = estacion::TXTobj(archivoEstacion, archivoSurtidor);
    tank* array=tank::TXTobj("C:\\Users\\juan david\\Documents\\desafioII\\tank.txt");
    // Comprobar si la carga fue exitosa
    if (estaciones == nullptr) {
        cout << "Error al cargar las estaciones." << endl;
        return 1; // Salir del programa con error
    }



    estacion estacion1("Termax", 77777, "Carlos", 'S', 4.50971, -73.08175,
                       "Máquina XPTO", 4, 1);
    estacion1.agregarSurtidor(890, false, 0);
    estacion1.mostrarEstadoSurtidores();

    estaciones[0].agregarSurtidor(56565,true,5);
    estaciones[1].agregarSurtidor(34352,false,0);


    try {
        estaciones[0].guardarSurtidoresTXT(archivoEstacion);
        estaciones[1].guardarSurtidoresTXT(archivoSurtidor);
    } catch (const exception& e) {
        cerr << "Ocurrió un error";
    }
    simularventa(20,"regular","efectivo","1066269364",estaciones,array,"C:\\Users\\juan david\\Documents\\desafioII\\estacion.txt");



}

*/
int main() {
    string archivotanks="C:\\Users\\juan david\\Documents\\desafioII\\tank.txt";
    const string archivoEst = "C:\\Users\\juan david\\Documents\\desafioII\\estacion.txt";
    const string archivoSurtidor = "C:\\Users\\juan david\\Documents\\desafioII\\surtidora.txt";
    string archivoventas="C:\\Users\\juan david\\Documents\\desafioII\\ventas.txt";

    //Estsaved[2].mostrarInfo();
    //Estsaved[2].mostrarEstadoSurtidores();

    unsigned short int opcion=0;
    while(opcion!=3){
        unsigned int tam=estacion::contadorlineas(archivoEst);
        estacion* Estsaved=estacion::TXTobj(archivoEst,archivoSurtidor);
        tank* tankes=tank::TXTobj(archivotanks);
        string nombre;
        unsigned int id;
        string gerente;
        char region;
        double latitud;
        double longitud;
        string maquina;
        unsigned short int isla,activo,surtidores;
        unsigned int idsurtidor;

         system("cls");
        Mopcion();  //muestra opciones para gestionar red o estaciones
        cin>>opcion;
        if (opcion==1){ //gestionar la red
            system("cls");
            unsigned short int opcred = 6; // opcion red
            while (opcred != 0) {
                Mopred(); // muestra las opciones de la gestion de red
                cin >> opcred;
             if (opcred==1){ //agregar estacion
            system("cls");
            ingresarDatosEstacion(nombre, id, gerente, region, latitud, longitud, maquina, isla, activo);
            estacion Est1(nombre, id, gerente, region, latitud, longitud, maquina, isla, activo);
            tank tank1(id,activo);
            cout <<"Ingrese cantidad de surtidores: ";
            cin>>surtidores;
            while(surtidores>0){
                cout<<"Ingrese el Id del surtidor: ";
                cin>>id;
                Est1.agregarSurtidor(id,1,0);
                surtidores--;
            }
            tank::Saveobj(tankes,tank1,archivotanks);
            Est1.guardarTXT(archivoEst);
            Est1.guardarSurtidoresTXT(archivoSurtidor);
            cout<<"Estacion creada correctamente..."<<endl;
            system("cls");
            //tank1.gettank();
            Est1.mostrarEstadoSurtidores();

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
                    objel=i;        //indice objeto a elminiar
                    break;
                }

            }
            try {
               // estacion::guardarTXT(Estsaved,Estsaved[objel],archivoEst);
                tank::Saveobj(tankes,tankes[objel],archivotanks);
            } catch (const exception& e) {
                cerr << "Ocurrió un error";
            }

            cout <<"Estacion eliminada Correctamente..."<<endl;
            Estsaved[objel].mostrarInfo();
            tankes[objel].gettank();



            //break;
        }else if(opcred==3){// calcular las ventas
             system("cls");
            cout<<"el registro de venta es: "<<endl;
            Estsaved[0].mostrarVentas();
            //break;
        }else if (opcred==4){//fijar el precio de los combustibles
             system("cls");
            unsigned int tam=estacion::contadorlineas(archivoEst);
            float newpricea=0,newpriceb=0,newpricec=0;
            cout<<"Ingrese el nuevo precio de los combustibles."<<endl;
            cout<<"Ingrese el precio del combustible regular: ";
            cin>>newpricea;
            cout<<"Ingrese el precio del combustible premium: ";
            cin>>newpriceb;
            cout<<"Ingrese el precio del combustible ecoextra: ";
            cin>>newpricec;
            for (unsigned short int i=0;i<tam;i++){
                tankes[i].setprecios(newpricea,newpriceb,newpricec);
            }
            //tankes[0].getprice();

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

                        unsigned short int cantsurti=0;
                        unsigned int idsurti=0;
                        MopSurtidores();
                        cin>>ops;
                        if (ops==1){
                            unsigned int tam=estacion::contadorlineas(archivoEst);
                            unsigned short int cantsurti=0;
                            system("cls");
                            cout<<"Ingrese el Id de la estacion a agregar: ";
                            cin>>id;
                            for (unsigned short int i=0;i<tam;i++){
                                if(Estsaved[i].getId()==id){
                                    cout<<"Ingrese cantidad de surtidores a agregar surtidor: ";
                                    cin>>cantsurti;
                                    if(cantsurti<(12-Estsaved[i].getcantsurti())){
                                        while(cantsurti>0){
                                            cout<<"Ingrese el Id de los surtidores: ";
                                            cin>>idsurtidor;
                                            Estsaved[i].agregarSurtidor(idsurtidor,true,0);
                                            cout<<idsurtidor<<" agregado correctamente.."<<endl;
                                            cantsurti-=1;
                                        }
                                        //[i].getsurtidores();
                                        break;
                                    }

                                }
                            }
                        }else if(ops==2){
                            system("cls");
                            cout<<"Ingrese el Id de la estacion en donde se encuentra el surtidor: ";
                            cin>>id;
                            for (unsigned short int i=0;i<tam;i++){
                                if(Estsaved[i].getId()==id){
                                    Estsaved[i].getsurtidores();
                                    cout<<"Ingrese el Id del surtidor a eliminar ";
                                    cin>>idsurti;     //esta variable obtiene el id del surtidor a eliminar
                                    Estsaved[i].eliminarSurtidor(idsurti);
                                    cout<<"Surtidor eliminado correctamente.."<<endl;
                                    break;
                                }
                            }

                        }else if (ops == 3) {
                            //unsigned int idsurti=0;
                            system("cls");
                            //Estsaved[1].mostrarInfo();
                            cout<<"Ingrese el Id de la estacion que tiene el surtidor:  ";
                            cin>>id;
                            for (unsigned short int i=0;i<tam;i++){

                                if(Estsaved[i].getId()==id){
                                    cout<<"Ingrese el Id del surtidor a activar: ";
                                    cin>>idsurti;   //guardar el id del surtidor a activar
                                    unsigned short int indice=Estsaved[i].getIdsurt(idsurti);
                                    Estsaved[i].activarSurtidor(indice,true);
                                    cout<<"Surtidor activado correctamente.."<<endl;
                                    //Estsaved[i].mostrarEstadoSurtidores();
                                    break;
                                }
                            }
                        } else if (ops == 4) {
                            system("cls");
                            cout<<"Ingrese el Id del surtidor a desactivar: ";
                            cin>>id;
                            for (unsigned short int i=0;i<tam;i++){
                                if(Estsaved[i].getId()==id){
                                    cout<<"Ingrese el Id del surtidor a desactivar: ";
                                    cin>>idsurti;
                                    unsigned short int indice=Estsaved[i].getIdsurt(idsurti);
                                    Estsaved[i].activarSurtidor(indice,false);
                                    cout<<"Surtidor desactivado correctamente.."<<endl;
                                }
                            }
                        } else if (ops == 0) {
                            system("cls");
                            break;
                        } else {
                            system("cls");
                            cout << "Ingrese una opcion valida" << endl;
                        }
                    }
                } else if (opce == 2) {     //simular venta
                system("cls");
                    for(int i=0;i<5;i++){
                double cant=32;
                string categoria="regular";
                string metodoPago="efectivo";
                string documentoCliente="12121231";
                /*cout <<"Ingrese la cantidad de combustible: ";
                cin>>cant;
                cout<<"Ingrese el metodo de pago: ";
                cin>>metodoPago;
                cout<<"Ingrese el tipo de combustible: ";
                cin>>categoria;
                cout<<"Ingrese su documento: ";
                cin>>documentoCliente;

                *//*simularventa(cant,categoria,
                             metodoPago, documentoCliente,
                             Estsaved[2],tankes[2],archivoEst);
                */
                Estsaved[2].registrarVenta(cant, categoria, metodoPago,
                                           documentoCliente,72000,4,
                                           1066269364);

                cout <<"Buena venta...."<<endl;
                    }
                } else if (opce == 3) { //agregar combustible ramdon
                    system("cls");

                    system("cls");
                    cout<<"Ingrese la estacion a la cual quiere asignarle combustible: ";
                    cin>>id;
                    float nume[3]={0};
                    for (unsigned short int i;i<tam;i++){

                        if(Estsaved[i].getId()==id){

                            srand(static_cast<unsigned>(time(0)));
                            for(unsigned short int i=0;i<3;i++){
                                float numeroAleatorio = rand() % 101 + 100;
                                nume[i]=numeroAleatorio;
                            }

                            tankes[i].setcombus(nume[0],nume[1],nume[2]);
                            break;
                        }

                    }
                }
            }

        } else if (opcion == 3) {
            cout << "Saliendo de el programa...." << endl;
            break;
        } else {
            system("cls");
            cout << "Ingrese una opcion valida." << endl;
        }

        estacion::guardarSurtidoresTXT(Estsaved,archivoSurtidor);
        estacion::guardarTXT(Estsaved,archivoEst);
        tank:: Saveobj(tankes,archivotanks);
    }

    return 0;
}



void Mopcion(){//mostrar opciones
    cout << "1. Gestionar la red de estaciones."<<endl;
    cout << "2. Gestionar las estaciones de servicio."<<endl;
    cout << "3. Salir"<<endl;

}

void Mopred() { // mostrar opciones para la gestion de la red
    cout << "0.  Atras." << endl;
    cout << "1.  Agregar estaciones de servicio." << endl;
    cout << "2.  Eliminar una E/S de la red nacional." << endl;
    cout << "3.  mostrar las ventas totales de las ventas." << endl;
    cout << "4.  Fijar los precios del combustible para toda la red." << endl;
    return;
}

void Mopes() { // mostrar opciones para la gestion de una estacion
    cout << "0. Atras." << endl;
    cout << "1. Para configurar surtidores." << endl;
    cout << "2. Simular una venta." << endl;
    cout << "3. Asignar capacidad tanque de suministro." << endl;
    return;
}

void MopSurtidores() {
    cout << "0. Atras." << endl;
    cout << "1. Agregar surtidor." << endl;
    cout << "2. Eliminar surtidor." << endl;
    cout << "3. Activar surtidor." << endl;
    cout << "4. Desactivar surtidor." << endl;
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

    cout << "Ingrese coordenadas estacion (Latitud-Longitud): " << endl;
    cin >> latitud >> longitud;

    cout << "Ingrese el modelo de surtidoras: ";
    cin >> maquina;

    cout << "Ingrese la cantidad de islas de la estacion: ";
    cin >> isla;

    cout << "Ingrese si la estacion esta activa (1 o 0): ";
    cin >> activo;
}


void simularventa(double cant,string categoria,
                  string metodoPago,string documentoCliente,
                  estacion obj,tank obj2, string archivoEst){
    string lowerTipo;
    unsigned short int tipo=0;
    unsigned int tam=estacion::contadorlineas(archivoEst);
    // Convertir cada carácter a minúscula
    for (char c : categoria) {
        lowerTipo += tolower(c);
    }

    if (lowerTipo == "regular") {
        tipo= 1;
    } else if (lowerTipo == "premiun") {
        tipo= 2;
    } else if (lowerTipo == "ecoextra") {
        tipo= 3;
    }
    double monto;                   //cuanto debe pagar el usuario
    unsigned int idsurti;
    unsigned int idEst;
    cout<<"Ingrese la estacion en la que se ecuentra ";
    cin>>idEst;
    cout <<"Ingrese el surtidor en el que esta comprando: ";
    cin>>idsurti;
    while(tam>=0){
        tam--;
        if(obj.getId()==idEst){
            float combustible[3]={obj2.getrest(1),obj2.getrest(2),obj2.getrest(3)};  //cantidad de combustible en est.
            float precio=obj2.getprice(tipo);
            if(combustible[tipo-1]!=0){
                unsigned short int indice=obj.getIdsurt(idsurti);
                if(cant<combustible[tipo-1]){
                    monto=cant*precio;
                    try {
                        obj.registrarVenta(cant, categoria, metodoPago,
                                                documentoCliente,monto,indice,
                                                idEst);
                         cout<<"ocurrio un error jajs xd"<<endl;
                        //obj[tam].guardarVentasEnArchivo();
                        /*obj2[tam].settank(tipo,cant);                    //restarle al tanke la cantidad de combustible
                        obj2[tam].gettank();*/

                    } catch (const exception& e) {
                        cerr << "Ocurrió un error";
                    }

                }else{
                cout<<"Cantidad insuficiente....."<<endl;
                }
            }else{
                cout<<"No hay combustible del tipo "<<(tipo == 1 ? "Regular" : tipo == 2 ? "Premium" :
                        tipo == 3 ? "Ecoextra" : "Tipo de combustible no válido")<<endl;
            }
        }
    }
    cout<<"estacion invalida"<<endl;

}


