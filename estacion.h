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
    unsigned short int id;
    unsigned short int est;
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

    unsigned short int surtidores[12];  // Arreglo para almacenar los identificadores de surtidores
    unsigned short int contadorSurtidores;  // Para llevar el conteo de surtidores añadidos
    unsigned short int ventaSurtidor[12];   //Para guardar ventas de cada surtidor
    bool surtidorActivo[12];  //Para activar o desactivar surtidor
    Venta* ventas;  // Puntero para almacenar las ventas dinámicamente (arreglo bidimensional)
    unsigned short int contadorVentas;  // Contador para las ventas realizadas
    unsigned short int capacidadVentas;  // Capacidad actual del arreglo

public:
    // Constructor
    //sobrecarga para poder inicializar el objeto sin nada
    estacion();
    estacion(string nombre, unsigned int id, string gerente,
             char region, double latitud, double longitud, string maquina,
             unsigned short int isla, unsigned short int activo);

    // Destructor
    ~estacion();

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
    void setactivo(unsigned short int activi);

    // Métodos para surtidores
    void agregarSurtidor(unsigned short int  idSurtidor);
    void eliminarSurtidor(unsigned short int idSurtidor);
    void activarSurtidor(unsigned short int indice, bool estado);
    void mostrarEstadoSurtidores() const;
    void registrarVentaSurtidor(unsigned short int id);
    // Información de la estación
    void mostrarInfo() const;
    void mostrarEstadoCombustibles() const;

    // Métodos de venta
    void venderCombustible(string tipo) const;
    void registrarVenta(double cantidad, string categoria, string metodoPago, string documentoCliente, double monto, unsigned short int id, unsigned short int est);
    bool guardarVentasEnArchivo();
    void mostrarVentas();

    // Métodos para manejar estaciones desde archivos

    static unsigned int contadorlineas(const string& rutaArchivo);
    static estacion* TXTobj(const string& rutaArchivo);
    void guardarTXT(const string& rutaArchivo);
};

#endif // ESTACION_H
