#include "estacion.h"
#include <iostream>

int main() {
    estacion est1("Termax", 12345, "José", 'N', 11.2408, -74.2052, "A", 2, 7);
    est1.agregarSurtidor("A1");
    est1.agregarSurtidor("A2");

    est1.mostrarInfo();

    est1.mostrarEstadoCombustibles();

    cout << "\nInformación del surtidor A1:" << endl;
    est1.mostrarSurtidor(0);

    est1.venderCombustible("Regular");
    est1.venderCombustible("Premium");
    est1.venderCombustible("Ecomax");
    est1.venderCombustible("Disel");

    est1.registrarVenta(50.0, "Regular", "Tarjeta", "123456789", 250.0);
    est1.registrarVenta(30.0, "Premium", "Efectivo", "987654321", 180.0);
    est1.registrarVenta(40.0, "Ecomax", "Tarjeta", "112233445", 200.0);
    est1.registrarVenta(50.0, "Regular", "Tarjeta", "123456789", 250.0);
    est1.registrarVenta(30.0, "Premium", "Efectivo", "987654321", 180.0);
    est1.registrarVenta(40.0, "Ecomax", "Tarjeta", "112233445", 200.0);

    est1.mostrarVentas();


    return 0;
}
