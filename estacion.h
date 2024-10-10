#ifndef ESTACION_H
#define ESTACION_H
#include <string>
using namespace std;

class estacion
{
private:
    string nombre;               // Nombre de la estación
    unsigned short int id;       // ID de la estación
    string gerente;              // Nombre del gerente
    char region;                 // Región de la estación
    double latitud;              // Latitud (coordenadas GPS)
    double longitud;             // Longitud (coordenadas GPS)
    string maquina;              // Máquina de la estación

public:
    unsigned short int isla;     // Número de isla
    unsigned short int activo;   // Estado de actividad

    // Constructor
    estacion(string nombre, unsigned short int id, string gerente, char region,
             double latitud, double longitud, string maquina,
             unsigned short int isla, unsigned short int activo);

    // Getters
    string getNombre() const;
    unsigned short int getId() const;
    string getGerente() const;
    char getRegion() const;
    double getLatitud() const;
    double getLongitud() const;
    string getMaquina() const;
    unsigned short int getIsla() const;
    unsigned short int getActivo() const;

    // Setter para modificar el número de isla
    void setIsla(unsigned short int nuevaIsla);

    // Método para mostrar la información de la estación
    void mostrarInfo() const;
};

#endif // ESTACION_H
