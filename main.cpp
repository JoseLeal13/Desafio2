#include "estacion.h"
#include "tank.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main() {
    estacion est1("Termax", 12345, "José", 'N', 11.2408, -74.2052, "A", 2, 101);
    tank tank1(12344,200,2333,2333,1);
    tank tank2(1000,50,20,130,0);
    /*est1.agregarSurtidor("A1");
    est1.agregarSurtidor("A2");

    est1.mostrarInfo();

    est1.mostrarEstadoCombustibles();


    cout << "\nInformación del surtidor A1:" << endl;
    est1.mostrarSurtidor(0);*/
    int combustible;
    cout << "Ingrese combustible para vender: ";
    cin >>combustible;
    est1.venderCombustible(combustible);
    tank** lista=tank::objetos();
    lista[0].modcombustible(combustible,200);
    lista[1].modcombustible(combustible,30);
    //tank arreglo[2]={tank1,tank2};
    ofstream archivo("C:\\Users\\juan david\\Documents\\desafioII\\tank.txt");
    for(unsigned short int i=0;i<sizeof(lista)/sizeof(lista[0]);i++){

        if (archivo.is_open()) {
        // Guardamos el objeto en el archivo
        archivo << lista[i]<<"\n";
        cout << "Objeto guardado en tank.txt\n";
    } else {
        cout << "No se pudo abrir el archivo\n";
    }

    lista[i].mostrar();
    }
     archivo.close();
    /*tank1.modcombustible(combustible,200);
    unsigned short int resto= tank1.getrest(1);
    resto+=200;
    tank1.mostrar();
    */
    return 0;
}
