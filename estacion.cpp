#include "estacion.h"
#include <iostream>
#include <string>

using namespace std;

// Definición del constructor
estacion::estacion(string nombre, unsigned short int id, string gerente, char region, double latitud, double longitud, string maquina, unsigned short int isla, unsigned short int activo)
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
}

// Getters
string estacion::getNombre() const {
    return nombre;
}

unsigned short int estacion::getId() const {
    return id;
}

string estacion::getGerente() const {
    return gerente;
}

char estacion::getRegion() const {
    return region;
}

// Los getters de latitud y longitud devuelven double ahora
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

// Setter para modificar las islas
void estacion::setIsla(unsigned short int nuevaIsla) {
    isla = nuevaIsla;
}

// Método para mostrar información básica
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
}
