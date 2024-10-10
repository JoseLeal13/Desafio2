#include "estacion.h"
#include <iostream>

using namespace std;

int main() {
    estacion miEstacion("Terpel", 12345, "José", 'N', 10.9804, -74.7889, "A1", 5, 111);

    cout << "Información inicial de la estación:" << endl;
    miEstacion.mostrarInfo();

    cout << "\nModificando el número de islas..." << endl;
    miEstacion.setIsla(10);

    cout << "Información después de modificar las islas:" << endl;
    miEstacion.mostrarInfo();

    return 0;
}
