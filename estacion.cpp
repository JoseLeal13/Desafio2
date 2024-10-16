#include "estacion.h"
#include <iostream>
#include <ctime>
#include <fstream>
#include <string>
using namespace std;

// Definición del constructor
estacion::estacion(string nombre, unsigned int id, string gerente, char region, double latitud, double longitud, string maquina, unsigned short int isla, unsigned short int activo)
    : nombre(nombre), id(id), gerente(gerente), region(region), latitud(latitud), longitud(longitud),
    maquina(maquina), isla(isla), activo(activo), contadorSurtidores(0), contadorVentas(0), capacidadVentas(5) {
    ventas = new Venta[capacidadVentas]; // Inicializa el arreglo dinámico para ventas
}
estacion::estacion() : nombre(""),id(0),gerente(""),region('N'),latitud(0.0f),longitud(0.0f),
    maquina(""),isla(0),activo(0),contadorSurtidores(0),contadorVentas(0),capacidadVentas(5){}

// Destructor
estacion::~estacion() {
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

void estacion::setactivo(unsigned short int activi){
    activo=activi;
}
// Método para agregar un surtidor
void estacion::agregarSurtidor(unsigned short int idSurtidor) {
    if (contadorSurtidores >= 12) {
        cout << "Capacidad máxima de surtidores alcanzada." << endl;
        return;
    }
    surtidores[contadorSurtidores] = idSurtidor;
    surtidorActivo[contadorSurtidores] = 0;  // Inicialmente desactivado
    ventaSurtidor[contadorSurtidores] = 0;   // Inicialmente sin ventas
    contadorSurtidores++;
    cout << "Surtidor " << idSurtidor << " agregado." << endl;
}

void estacion::eliminarSurtidor(unsigned short int idSurtidor) {
    if (contadorSurtidores <= 2) {
        cout << "No se pueden eliminar más de 2 surtidores." << endl;
        return;
    }

    bool encontrado = false;
    for (int i = 0; i < contadorSurtidores; i++) {
        if (surtidores[i] == idSurtidor) {
            surtidores[i] = surtidores[contadorSurtidores - 1];  // Reemplazar con el último
            contadorSurtidores--;
            encontrado = true;
            cout << "Surtidor " << idSurtidor << " eliminado." << endl;
            break;
        }
    }

    if (!encontrado) {
        cout << "Surtidor no encontrado." << endl;
    }
}

// Activar o desactivar un surtidor
void estacion::activarSurtidor(unsigned short int indice, bool estado) {
    if (indice >= 12) {
        cout << "Índice de surtidor inválido." << endl;
        return;
    }
    surtidorActivo[indice] = estado ? 1 : 0;
    cout << "Surtidor " << surtidores[indice]
         << (estado ? " activado." : " desactivado.") << endl;
}

// Registrar una venta para un surtidor específico
void estacion::registrarVentaSurtidor(unsigned short int id) {
    if (id >= 12) {
        cout << "ID de surtidor inválido." << endl;
        return;
    }
    if (surtidorActivo[id] == 0) {
        cout << "El surtidor está desactivado. No se puede registrar la venta." << endl;
        return;
    }
    ventaSurtidor[id]++;
    cout << "Venta registrada para surtidor " << surtidores[id] << "." << endl;
}

// Mostrar el estado de los surtidores
void estacion::mostrarEstadoSurtidores() const {
    for (unsigned short int i = 0; i < contadorSurtidores; ++i) {
        cout << "Surtidor: " << surtidores[i]
             << " | Estado: " << (surtidorActivo[i] ? "Activo" : "Inactivo")
             << " | Ventas: " << ventaSurtidor[i] << endl;
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

// Registrar venta de combustible
void estacion::registrarVenta(double cantidad, string categoria, string metodoPago,
                              string documentoCliente, double monto, unsigned short int id, unsigned short int est) {
    if (contadorVentas >= capacidadVentas) {
        cout << "Capacidad máxima alcanzada. Guardando ventas." << endl;
        guardarVentasEnArchivo();
        contadorVentas = 0;  // Reiniciar el contador
    }

    if (id >= 12 || surtidorActivo[id] == 0) {
        cout << "Surtidor inválido o inactivo." << endl;
        return;
    }

    // Registrar venta en el surtidor
    registrarVentaSurtidor(id);
    unsigned short int idSurtidor = surtidores[id];

    // Almacenar los datos de la venta
    time_t now = time(0);
    string fechaHora = ctime(&now);
    fechaHora.pop_back();  // Eliminar '\n'
    ventas[contadorVentas].fechaHora = fechaHora;
    ventas[contadorVentas].cantidadCombustible = cantidad;
    ventas[contadorVentas].categoria = categoria;
    ventas[contadorVentas].metodoPago = metodoPago;
    ventas[contadorVentas].documentoCliente = documentoCliente;
    ventas[contadorVentas].monto = monto;
    ventas[contadorVentas].id = idSurtidor;
    ventas[contadorVentas].est = est;

    contadorVentas++;
}


// Guardar ventas en archivo
bool estacion::guardarVentasEnArchivo() {
    ofstream archivo("ventas.txt", ios::app); // Modo append
    if (!archivo) {
        cerr << "Error al abrir el archivo." << endl;
        return false;
    }

    // Guardar cada venta en el archivo
    for (int i = 0; i < contadorVentas; ++i) {
        archivo << ventas[i].fechaHora << " | "
                << ventas[i].cantidadCombustible << "L | "
                << ventas[i].categoria << " | "
                << ventas[i].metodoPago << " | "
                << ventas[i].documentoCliente << " | "
                << "$" << ventas[i].monto << " | "
                << ventas[i].id << " | "
                << ventas[i].est << endl;
    }

    archivo.close();
    cout << "Ventas guardadas exitosamente." << endl;
    return true;
}

// Mostrar ventas
void estacion::mostrarVentas() {
    guardarVentasEnArchivo();
    ifstream archivo("C:\\Users\\Lenovo\\Documents\\Desafio2\\ventas.txt");
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

// Contar líneas en un archivo
unsigned int estacion::contadorlineas(const string& rutaArchivo) {
    string linea;
    unsigned int count = 0;
    ifstream archivo(rutaArchivo);
    while (getline(archivo, linea)) {
        count++;
    }
    archivo.close();
    return count;
}

// Guardar estación en archivo
void estacion::guardarTXT(const string& rutaArchivo) {
    ofstream archivo(rutaArchivo, ios::app); // Modo 'append' para agregar sin borrar
    if (!archivo.is_open()) {
        cout << "Error al abrir el archivo para guardar." << endl;
        return;
    }

// Método para cargar las estaciones desde un archivo
estacion* estacion::TXTobj(const string& rutaArchivo, const string& rutaSurtidores) {
    unsigned int count = contadorlineas(rutaArchivo);
    if (count == 0) {
        cout << "El archivo de estaciones está vacío." << endl;
        return nullptr;
    }

    estacion* arrayEstaciones = new estacion[count];
    string atributos[9];
    string linea;
    unsigned int i = 0;

    ifstream archivo(rutaArchivo);
    if (!archivo.is_open()) {
        cout << "Error al abrir el archivo de estaciones." << endl;
        delete[] arrayEstaciones;
        return nullptr;
    }

    while (getline(archivo, linea) && i < count) {
        unsigned int posInicio = 0, posDelim, index = 0;

        // Procesar la línea para extraer los atributos
        while ((posDelim = linea.find(';', posInicio)) != string::npos && index < 9) {
            atributos[index] = linea.substr(posInicio, posDelim - posInicio);
            posInicio = posDelim + 1;
            index++;
        }
        // Añadir el último atributo después del último delimitador
        if (index < 9) {
            atributos[index] = linea.substr(posInicio);
        }

        // Crear la estación con los atributos leídos
        arrayEstaciones[i] = estacion(
            atributos[0],
            stoi(atributos[1]),
            atributos[2],
            atributos[3][0],
            stod(atributos[4]),
            stod(atributos[5]),
            atributos[6],
            static_cast<unsigned short>(stoi(atributos[7])),
            static_cast<unsigned short>(stoi(atributos[8]))
            );

        i++;
    }

    archivo.close();

    // Cargar los surtidores y asociarlos a las estaciones
    unsigned short numSurtidores;
    Surtidor* surtidores = TXTsurtidor(rutaSurtidores, numSurtidores);

    if (surtidores) {
        for (unsigned short j = 0; j < numSurtidores; j++) {
            for (unsigned int k = 0; k < count; k++) {
                // Comparar idEstacion con idSurtidor de cada surtidor
                if (arrayEstaciones[k].getId() == surtidores[j].idEstacion) {
                    arrayEstaciones[k].agregarSurtidor(surtidores[j].idSurtidor);
                }
            }
        }
        delete[] surtidores;
    }

    cout << "Estaciones cargadas correctamente desde el archivo." << endl;
    return arrayEstaciones;
}


Surtidor* estacion::TXTsurtidor(const string& rutaArchivo, unsigned short& count) {
    count = contadorlineas(rutaArchivo);
    if (count == 0) {
        cout << "El archivo de surtidores está vacío." << endl;
        return nullptr;
    }

    Surtidor* arraySurtidores = new Surtidor[count];
    string atributos[4];
    string linea;
    unsigned int i = 0;

    ifstream archivo(rutaArchivo);
    if (!archivo.is_open()) {
        cout << "Error al abrir el archivo de surtidores." << endl;
        delete[] arraySurtidores;
        return nullptr;
    }

    while (getline(archivo, linea) && i < count) {
        unsigned int posInicio = 0, posDelim, index = 0;

        // Procesar la línea para extraer los atributos
        while ((posDelim = linea.find(';', posInicio)) != string::npos && index < 4) {
            atributos[index] = linea.substr(posInicio, posDelim - posInicio);
            posInicio = posDelim + 1;
            index++;
        }
        // Añadir el último atributo después del último delimitador
        if (index < 4) {
            atributos[index] = linea.substr(posInicio);
        }

        // Crear el surtidor con los atributos leídos
        arraySurtidores[i] = Surtidor(
            static_cast<unsigned short>(stoi(atributos[0])),  // idEstacion
            static_cast<unsigned short>(stoi(atributos[1])),  // idSurtidor
            atributos[2] == "1", // activo
            stod(atributos[3])   // ventas
            );
        i++;
    }

    archivo.close();
    return arraySurtidores;
    }
}
