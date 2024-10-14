#include "estacion.h"
#include <iostream>
#include <ctime>
#include <fstream>
using namespace std;

// Definición del constructor
estacion::estacion(string nombre, unsigned int id, string gerente, char region, double latitud, double longitud, string maquina, unsigned short int isla, unsigned short int activo)
    : nombre(nombre), id(id), gerente(gerente), region(region), latitud(latitud), longitud(longitud),
    maquina(maquina), isla(isla), activo(activo), contadorSurtidores(0), contadorVentas(0), capacidadVentas(5) {
    ventas = new Venta[capacidadVentas]; // Inicializa el arreglo dinámico para ventas
}

estacion::~estacion() {
    // Liberar la memoria asignada al arreglo dinámico
    delete[] ventas; // Liberar el arreglo de objetos Venta
}

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

<<<<<<< HEAD
// Método para vender un tipo de combustible
void estacion::venderCombustible(int tipo) const {
    if (tipo == 1) {
         cout << "Vendiendo combustible Regular." << endl;
        }else if (tipo == 2) {
            cout << "Vendiendo combustible Premium." << endl;
        }else if (tipo == 3) {
            cout << "Vendiendo combustible Ecomax." << endl;
        }else {
        cout << "Tipo de combustible no válido." << endl;
=======
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
>>>>>>> 1783d13a218e46fb82a58b90e49fec59d0f791ac
    }
}

void estacion::registrarVenta(double cantidad, string categoria, string metodoPago, string documentoCliente, double monto) {
    // Agregar la nueva venta
    time_t now = time(0);
    ventas[contadorVentas].fechaHora = ctime(&now); // Cambiado a . en lugar de ->
    ventas[contadorVentas].cantidadCombustible = cantidad;
    ventas[contadorVentas].categoria = categoria;
    ventas[contadorVentas].metodoPago = metodoPago;
    ventas[contadorVentas].documentoCliente = documentoCliente;
    ventas[contadorVentas].monto = monto;

    contadorVentas++;

    // Si alcanzamos 5 ventas, guardamos y reiniciamos
    if (contadorVentas == capacidadVentas) {
        cout << "Se han registrado " << capacidadVentas << " ventas. Guardando ventas." << endl;
        guardarVentasEnArchivo();

        // Reiniciar el contador de ventas
        contadorVentas = 0;

        // Volver a usar el arreglo existente, no es necesario reasignar memoria
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
        archivo << "Fecha: " << ventas[i].fechaHora // Cambiado a . en lugar de ->
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
void estacion::mostrarVentas() {
    // Guardar las ventas actuales en el archivo antes de mostrar
    guardarVentasEnArchivo();

    // Mostrar el contenido del archivo de ventas
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
