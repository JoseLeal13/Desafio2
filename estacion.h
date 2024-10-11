#ifndef ESTACION_H
#define ESTACION_H

#include <string>
using namespace std;

class estacion
{
private:
    string nombre;
    unsigned int id;
    string gerente;
    char region;
    double latitud;
    double longitud;
    string maquina;
    unsigned short int isla;
    unsigned short int activo;

    string surtidores[12];  // Arreglo para almacenar los identificadores de hasta 12 surtidores
    unsigned short int contadorSurtidores;  // Para llevar el conteo de surtidores añadidos

public:
    // Constructor
    estacion(string nombre, unsigned int id, string gerente, char region, double latitud, double longitud, string maquina, unsigned short int isla, unsigned short int activo);

    // Getters
    string getNombre() const;
    unsigned int getId() const;
    string getGerente() const;
    char getRegion() const;
    double getLatitud() const;
    double getLongitud() const;
    string getMaquina() const;
    unsigned short int getIsla() const;
    unsigned short int getActivo() const;

    // Método para agregar un surtidor
    void agregarSurtidor(string idSurtidor);

    // Método para mostrar información de un surtidor
    void mostrarSurtidor(int indice) const;

    // Método para mostrar información básica de la estación
    void mostrarInfo() const;
};

#endif // ESTACION_H
