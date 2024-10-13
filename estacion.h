#ifndef ESTACION_H
#define ESTACION_H

#include <string>
using namespace std;

struct Venta {
    string fechaHora;
    double cantidadCombustible;
    string categoria;
    string metodoPago;
    string documentoCliente;
    double monto;
};

class estacion {
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

    string surtidores[12];  // Arreglo para almacenar los identificadores de surtidores
    unsigned short int contadorSurtidores;  // Para llevar el conteo de surtidores añadidos

    Venta ventas[5];  // Arreglo para almacenar hasta 5 ventas
    unsigned short int contadorVentas;  // Contador para las ventas realizadas

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

    // Métodos para surtidores
    void agregarSurtidor(string idSurtidor);
    void mostrarSurtidor(int indice) const;

    // Información de la estación
    void mostrarInfo() const;
    void mostrarEstadoCombustibles() const;

    // Métodos de venta
    void venderCombustible(string tipo) const;
    void registrarVenta(double cantidad, string categoria, string metodoPago, string documentoCliente, double monto);
    bool guardarVentasEnArchivo();
    void mostrarVentas() const;
};

#endif // ESTACION_H
