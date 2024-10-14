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

// Registrar venta de combustible
void estacion::registrarVenta(double cantidad, string categoria, string metodoPago, string documentoCliente, double monto) {
    if (contadorVentas >= capacidadVentas) {
        cout << "Capacidad máxima alcanzada. Guardando ventas." << endl;
        guardarVentasEnArchivo();
        contadorVentas = 0; // Reiniciar el contador
    }

    time_t now = time(0);
    ventas[contadorVentas].fechaHora = ctime(&now); // Se usa ctime para obtener la fecha/hora actual
    ventas[contadorVentas].cantidadCombustible = cantidad;
    ventas[contadorVentas].categoria = categoria;
    ventas[contadorVentas].metodoPago = metodoPago;
    ventas[contadorVentas].documentoCliente = documentoCliente;
    ventas[contadorVentas].monto = monto;

    contadorVentas++;
}

// Guardar ventas en archivo
bool estacion::guardarVentasEnArchivo() {
    ofstream archivo("ventas.txt", ios::app); // Modo append
    if (!archivo) {
        cerr << "Error al abrir el archivo." << endl;
        return false;
    }

    if (archivo.tellp() == 0) { // Agregar cabeceras si el archivo está vacío
        archivo << "Fecha y Hora | Cantidad (L) | Categoría | Método de Pago | Cliente | Monto ($)" << endl;
    }

    for (int i = 0; i < contadorVentas; ++i) {
        archivo << ventas[i].fechaHora << " | "
                << ventas[i].cantidadCombustible << "L | "
                << ventas[i].categoria << " | "
                << ventas[i].metodoPago << " | "
                << ventas[i].documentoCliente << " | "
                << "$" << ventas[i].monto << endl;
    }

    archivo.close();
    cout << "Ventas guardadas exitosamente." << endl;
    return true;
}

// Mostrar ventas
void estacion::mostrarVentas() {
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

// Cargar objetos desde un archivo
estacion* estacion::TXTobj(const string& rutaArchivo) {
    unsigned int count = contadorlineas(rutaArchivo); // Determinar cuántas líneas tiene el archivo
    if (count == 0) {
        cout << "El archivo está vacío." << endl;
        return nullptr;
    }

    estacion* arrayEstaciones = new estacion[count]; // Crear arreglo dinámico
    string atributos[9]; // Asumiendo 9 atributos por estación
    string linea;
    unsigned int i = 0;

    ifstream archivo(rutaArchivo);
    if (!archivo.is_open()) {
        cout << "Error al abrir el archivo." << endl;
        return nullptr; // Si no se puede abrir, retornamos nullptr
    }

    // Leer línea por línea del archivo
    while (getline(archivo, linea) && i < count) {
        unsigned int posInicio = 0, posDelim, index = 0;

        // Parsear cada línea y extraer los atributos separados por ';'
        while ((posDelim = linea.find(';', posInicio)) != string::npos && index < 9) {
            atributos[index] = linea.substr(posInicio, posDelim - posInicio);
            posInicio = posDelim + 1;
            index++;
        }

        // Validar que se han leído todos los atributos necesarios
        if (index != 9) {
            cout << "Error: Línea incompleta en el archivo." << endl;
            continue; // O manejar el error de otra manera
        }

        // Crear y almacenar un objeto estación en el arreglo
        arrayEstaciones[i] = estacion(stoi(atributos[0]), atributos[1], atributos[2],
                                      atributos[3][0], stod(atributos[4]), stod(atributos[5]),
                                      atributos[6], stoi(atributos[7]), stoi(atributos[8]));
        i++;
    }

    archivo.close();
    return arrayEstaciones; // Retornar el arreglo de objetos
}

// Guardar estación en archivo
void estacion::guardarTXT(const string& rutaArchivo) {
    ofstream archivo(rutaArchivo, ios::app); // Modo 'append' para agregar sin borrar
    if (!archivo.is_open()) {
        cout << "Error al abrir el archivo para guardar." << endl;
        return;
    }

    // Guardar los atributos separados por ';'
    archivo << id << ';' << nombre << ';' << gerente << ';' << region << ';'
            << latitud << ';' << longitud << ';' << maquina << ';' << isla << ';'
            << activo << '\n';

    archivo.close();
}
