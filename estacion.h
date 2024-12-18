
#ifndef ESTACION_H
#define ESTACION_H

#include <cstdlib>
#include <ctime>
#include <string>
using namespace std;

struct surtidor {
    unsigned  int idEstacion; // Id de la estación
    unsigned  int idSurtidor;  // Id del surtidor
    bool activo;                    // Estado del surtidor
    double ventas;                  // Ventas realizadas
};
struct Venta {
    string fechaHora;
    double cantidadCombustible;
    string categoria;
    string metodoPago;
    string documentoCliente;
    double monto;
    unsigned short int id;
    unsigned int est;
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

    unsigned short int surtidores[12]={0};  // Arreglo para almacenar los identificadores de surtidores
    unsigned short int contadorSurtidores;  // Para llevar el conteo de surtidores añadidos
    unsigned short int ventaSurtidor[12];   //Para guardar ventas de cada surtidor
    bool surtidorActivo[12]={false};  //Para activar o desactivar surtidor
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
    void getsurtidores();
    unsigned int getIdsurt(unsigned int idsurtidor);      //devuelve el indice del surtidor
    unsigned short int getcantsurti()const;
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
    void agregarSurtidor(unsigned short int  idSurtidor, bool activo, unsigned short int ventas);
    void eliminarSurtidor(unsigned short int idSurtidor);
    void activarSurtidor(unsigned short int indice, bool estado);
    void mostrarEstadoSurtidores() const;
    void registrarVentaSurtidor(unsigned short int id);
    // Información de la estación
    void mostrarInfo() const;
    void mostrarEstadoCombustibles() const;

    // Métodos de venta
    void venderCombustible(string tipo) const;

    void registrarVenta(double cantidad, string categoria, string metodoPago,
                        string documentoCliente, double monto, unsigned short int id,
                        unsigned int est);

    void getVentas();

    bool guardarVentasEnArchivo();

    void mostrarVentas();

    // Métodos para manejar estaciones desde archivos
    static unsigned int contadorlineas(const string& rutaArchivo);
    void guardarTXT(const string& rutaArchivo);
    static void guardarTXT(estacion* array, estacion obj, const string& rutaArchivo);
    static void guardarTXT(estacion* array, const string& rutaArchivo);

    //Métodos para manejar surtidores desde archivos
    void guardarSurtidoresTXT(const string& rutaArchivo);
    static void guardarSurtidoresTXT(estacion* array,const string& rutaArchivo);
    static estacion* TXTobj(const string& rutaArchivo, const string& rutaSurtidores);
    static surtidor* TXTsurtidor(const string& rutaArchivo, unsigned short& count);

};

#endif // ESTACION_H
