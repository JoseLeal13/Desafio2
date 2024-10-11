#include "estacion.h"
#include <iostream>

int main() {
    // Crear una estación
    estacion est1("Termax1", 12345, "José", 'N', 11.2408, -74.2052, "A", 2, 111);

    // Agregar algunos surtidores
    est1.agregarSurtidor("A1");
    est1.agregarSurtidor("A2");

    // Mostrar información de la estación
    est1.mostrarInfo();

    // Mostrar información de un surtidor específico
    cout << "\nInformación del surtidor A1:" << endl;
    est1.mostrarSurtidor(0); // Surtidor en el índice 0 ("A1")

    return 0;
}
