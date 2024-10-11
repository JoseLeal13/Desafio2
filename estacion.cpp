#include "estacion.h"
#include <iostream>

using namespace std;

// Definición del constructor
estacion::estacion(string nombre, unsigned int id, string gerente, char region, double latitud, double longitud, string maquina, unsigned short int isla, unsigned short int activo)
{
    this->nombre = nombre;
    this->id = id;
    this->gerente = gerente;
    this->region = region;
    this->latitud = latitud;  // Latitud de tipo double
    this->longitud = longitud;  // Longitud de tipo double
    this->maquina = maquina;
    this->isla = isla;
    this->activo = activo;
    this->contadorSurtidores = 0;  // Inicializamos el contador de surtidores
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
    if (contadorSurtidores < 12) { // Solo permite agregar hasta 12 surtidores
        surtidores[contadorSurtidores] = idSurtidor;  // Guardar el identificador del surtidor
        contadorSurtidores++;  // Incrementar el contador
    } else {
        cout << "No se pueden agregar más surtidores, el límite es 12." << endl;
    }
}

// Método para mostrar información de un surtidor
void estacion::mostrarSurtidor(int indice) const {
    if (indice < contadorSurtidores && indice >= 0) {
        cout << "Surtidor " << surtidores[indice] << " de la estación " << nombre << endl;
        cout << "Activo: " << activo << endl;
    } else {
        cout << "Índice de surtidor no válido." << endl;
    }
}

// Método para mostrar información básica de la estación
void estacion::mostrarInfo() const
{
    cout << "Nombre de la estación: " << nombre << endl;
    cout << "ID: " << id << endl;
    cout << "Gerente: " << gerente << endl;
    cout << "Región: " << region << endl;
    cout << "Ubicación (Latitud, Longitud): " << latitud << ", " << longitud << endl;
    cout << "Máquina: " << maquina << endl;
    cout << "Isla: " << isla << endl;
    cout << "Activo: " << activo << endl;

    cout << "Surtidores en la estación: " << endl;
    for (int i = 0; i < contadorSurtidores; i++) {
        cout << "- " << surtidores[i] << endl;
    }
}
