#include "estacion.h"
#include <iostream>
#include <ctime>
#include <fstream>
#include <string>
using namespace std;

// Definición del constructor
estacion::estacion(string nombre, unsigned int id, string gerente, char region,
                   double latitud, double longitud, string maquina,
                   unsigned short int isla, unsigned short int activo,
                   unsigned short int numeroVentas)
    : nombre(nombre), id(id), gerente(gerente), region(region), latitud(latitud),
    longitud(longitud), maquina(maquina), isla(isla), activo(activo),
    numeroVentas(numeroVentas), contadorVentas(0), capacidadVentas(5) {
    ventas = new Venta[capacidadVentas];  // Asignación de memoria
}

// Constructor por defecto
estacion::estacion()
    : nombre(""), id(0), gerente(""), region('N'), latitud(0.0), longitud(0.0),
    maquina(""), isla(0), activo(0), numeroVentas(0), contadorSurtidores(0),
    contadorVentas(0), capacidadVentas(5) {
    ventas = new Venta[capacidadVentas];  // Asignación en constructor por defecto
}

// Destructor
estacion::~estacion() {
    if (ventas != nullptr) {  // Verificar si el puntero es válido antes de liberar
        delete[] ventas;
        ventas = nullptr;  // Evitar puntero colgante
    }
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
unsigned short int estacion::getVenta() const {
    return numeroVentas;
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
    numeroVentas++;
}

// Guardar ventas en archivo
bool estacion::guardarVentasEnArchivo() {
    ofstream archivo("C:\\Users\\Lenovo\\Documents\\Desafio2\\ventas.txt", ios::app); // Modo append
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

// Cargar objetos desde un archivo
estacion* estacion::TXTobj(const string& rutaArchivo) {
    unsigned int count = contadorlineas(rutaArchivo); // Determina cuántas líneas tiene el archivo
    if (count == 0) {
        cout << "El archivo está vacío." << endl;
        return nullptr;
    }

    estacion* arrayEstaciones = new estacion[count]; // Crear arreglo dinámico
    string atributos[10]; // 10 atributos por estación
    string linea;
    unsigned int i = 0;

    ifstream archivo(rutaArchivo);
    if (!archivo.is_open()) {
        cout << "Error al abrir el archivo." << endl;
        return nullptr;
    }

    // Leer línea por línea del archivo
    while (getline(archivo, linea) && i < count) {
        unsigned int posInicio = 0, posDelim, index = 0;

        // Extraer los atributos separados por ';'
        while ((posDelim = linea.find(';', posInicio)) != string::npos && index < 10) {
            atributos[index] = linea.substr(posInicio, posDelim - posInicio);
            posInicio = posDelim + 1;
            index++;
        }

        // Validar que se han leído todos los atributos
        if (index != 10) {
            cout << "Error: Línea incompleta en el archivo." << endl;
            continue;  // Ignorar líneas mal formadas
        }

        // Crear y almacenar una estación en el arreglo
        arrayEstaciones[i] = estacion(
            atributos[0],                    // nombre
            stoi(atributos[1]),              // id
            atributos[2],                    // gerente
            atributos[3][0],                 // region
            stod(atributos[4]),              // latitud
            stod(atributos[5]),              // longitud
            atributos[6],                    // maquina
            stoi(atributos[7]),              // isla
            stoi(atributos[8]),              // activo
            stoi(atributos[9])               // numeroVentas
            );
        i++;
    }

    archivo.close();
    return arrayEstaciones;
}


// Guardar estación en archivo
void estacion::guardarTXT(const string& rutaArchivo) {
    ofstream archivo(rutaArchivo, ios::app); // Modo 'append' para agregar sin borrar
    if (!archivo.is_open()) {
        cout << "Error al abrir el archivo para guardar." << endl;
        return;
    }

    // Guardar los atributos separados por ';'
    archivo << nombre<< ';' << id << ';' << gerente << ';' << region << ';'
            << latitud << ';' << longitud << ';' << maquina << ';' << isla << ';'
            << activo << '\n';

    archivo.close();
}

// Método para eliminar una estación por ID
bool estacion::eliminarEstacion(unsigned int idEstacion) {

    string rutaArchivo = "C:\\Users\\Lenovo\\Documents\\Desafio2\\estaciones.txt";
    estacion* estaciones = TXTobj(rutaArchivo); // Cargar estaciones desde el archivo

    if (estaciones == nullptr) {
        cout << "No se pudieron cargar las estaciones desde el archivo." << endl;
        return false;
    }

    unsigned int totalEstaciones = contadorlineas(rutaArchivo);
    bool encontrado = false;

    // Crear un nuevo arreglo para almacenar las estaciones que no se eliminan
    estacion* nuevasEstaciones = new estacion[totalEstaciones - 1];
    unsigned int nuevoIndice = 0;

    // Recorrer las estaciones y copiar las que no son la que se va a eliminar
    for (unsigned int i = 0; i < totalEstaciones; i++) {
        if (estaciones[i].getId() != idEstacion) {
            nuevasEstaciones[nuevoIndice++] = estaciones[i]; // Copiar estación
        } else {
            encontrado = true; // Marca que se encontró y eliminó la estación
        }
    }

    // Guardar las estaciones restantes en el archivo
    ofstream archivo(rutaArchivo, ios::trunc); // Abrir en modo truncado para sobreescribir
    if (!archivo.is_open()) {
        cout << "Error al abrir el archivo para guardar." << endl;
        delete[] estaciones; // Liberar memoria
        delete[] nuevasEstaciones; // Liberar memoria
        return false;
    }

    for (unsigned int i = 0; i < nuevoIndice; i++) {
        archivo << nuevasEstaciones[i].getNombre() << ';'
                << nuevasEstaciones[i].getId() << ';'
                << nuevasEstaciones[i].getGerente() << ';'
                << nuevasEstaciones[i].getRegion() << ';'
                << nuevasEstaciones[i].getLatitud() << ';'
                << nuevasEstaciones[i].getLongitud() << ';'
                << nuevasEstaciones[i].getMaquina() << ';'
                << nuevasEstaciones[i].getIsla() << ';'
                << nuevasEstaciones[i].getActivo() << '\n';
    }

    archivo.close();

    delete[] estaciones;
    delete[] nuevasEstaciones;

    if (encontrado) {
        cout << "Estación eliminada exitosamente." << endl;
        return true;
    } else {
        cout << "Estación no encontrada." << endl;
        return false;
    }
}
