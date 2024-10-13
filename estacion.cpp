#include "estacion.h"
#include <iostream>
#include <ctime>
#include <fstream>
using namespace std;

// Definición del constructor
estacion::estacion(string nombre, unsigned int id, string gerente, char region, double latitud, double longitud, string maquina, unsigned short int isla, unsigned short int activo)
    : nombre(nombre), id(id), gerente(gerente), region(region), latitud(latitud), longitud(longitud),
    maquina(maquina), isla(isla), activo(activo), contadorSurtidores(0), contadorVentas(0) {}

// Getters
string estacion::getNombre() const {
    return nombre;
}

unsigned int estacion::getId() const {
    return id;
}

string estacion::getGerente() const {
    return gerente;
}

char estacion::getRegion() const {
    return region;
}

double estacion::getLatitud() const {
    return latitud;
}

double estacion::getLongitud() const {
    return longitud;
}

string estacion::getMaquina() const {
    return maquina;
}

unsigned short int estacion::getIsla() const {
    return isla;
}

unsigned short int estacion::getActivo() const {
    return activo;
}

// Método para agregar un surtidor
void estacion::agregarSurtidor(string idSurtidor) {
    if (contadorSurtidores < 12) {
        surtidores[contadorSurtidores++] = idSurtidor;
    } else {
        cout << "No se pueden agregar más surtidores, el límite es 12." << endl;
    }
}

// Mostrar información de un surtidor
void estacion::mostrarSurtidor(int indice) const {
    if (indice >= 0 && indice < contadorSurtidores) {
        cout << "Surtidor " << surtidores[indice] << " de la estación " << nombre << endl;
    } else {
        cout << "Índice de surtidor no válido." << endl;
    }
}

// Mostrar información básica de la estación
void estacion::mostrarInfo() const {
    cout << "Nombre: " << nombre << "\nID: " << id << "\nGerente: " << gerente
         << "\nRegión: " << region << "\nUbicación: (" << latitud << ", " << longitud << ")"
         << "\nMáquina: " << maquina << "\nIsla: " << isla << "\nActivo: " << activo << endl;
}

// Verificar estado de combustibles
void estacion::mostrarEstadoCombustibles() const {
    cout << "Estado de los combustibles:\n";
    cout << "- Regular: " << ((activo & 1) ? "Disponible" : "No disponible") << endl;
    cout << "- Premium: " << ((activo & 2) ? "Disponible" : "No disponible") << endl;
    cout << "- Ecomax: " << ((activo & 4) ? "Disponible" : "No disponible") << endl;
}

// Vender combustible
void estacion::venderCombustible(string tipo) const {
    if (tipo == "Regular" && (activo & 1)) {
        cout << "Vendiendo Regular." << endl;
    } else if (tipo == "Premium" && (activo & 2)) {
        cout << "Vendiendo Premium." << endl;
    } else if (tipo == "Ecomax" && (activo & 4)) {
        cout << "Vendiendo Ecomax." << endl;
    } else {
        cout << "El tipo de combustible no está disponible." << endl;
    }
}

// Registrar venta
void estacion::registrarVenta(double cantidad, string categoria, string metodoPago, string documentoCliente, double monto) {
    if (contadorVentas < 5) {
        time_t now = time(0);
        ventas[contadorVentas++] = {ctime(&now), cantidad, categoria, metodoPago, documentoCliente, monto};
        cout << "Venta registrada." << endl;

        if (contadorVentas == 5) {
            if (guardarVentasEnArchivo()) {
                contadorVentas = 0;
            }
        }
    } else {
        cout << "Límite de ventas alcanzado." << endl;
    }
}

// Guardar ventas en archivo
bool estacion::guardarVentasEnArchivo() {
    ofstream archivo("ventas.txt", ios::app);
    if (!archivo) {
        cerr << "Error al abrir el archivo." << endl;
        return false;
    }

    for (int i = 0; i < contadorVentas; ++i) {
        archivo << "Fecha: " << ventas[i].fechaHora
                << " Cantidad: " << ventas[i].cantidadCombustible << "L "
                << "Categoría: " << ventas[i].categoria << " "
                << "Pago: " << ventas[i].metodoPago << " "
                << "Cliente: " << ventas[i].documentoCliente << " "
                << "Monto: $" << ventas[i].monto << endl;
    }
    archivo.close();
    cout << "Ventas guardadas." << endl;
    return true;
}

// Mostrar ventas
void estacion::mostrarVentas() const {
    ifstream archivo("ventas.txt");
    if (!archivo) {
        cerr << "Error al abrir el archivo." << endl;
        return;
    }

    string linea;
    while (getline(archivo, linea)) {
        cout << linea << endl;
    }
    archivo.close();
}
