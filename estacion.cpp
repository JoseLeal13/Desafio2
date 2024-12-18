#include "estacion.h"
#include <iostream>
#include <ctime>
#include <sstream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

// Definición del constructor
estacion::estacion(string nombre, unsigned int id, string gerente, char region, double latitud,
                   double longitud, string maquina, unsigned short int isla, unsigned short int activo)
    : nombre(nombre), id(id), gerente(gerente), region(region), latitud(latitud), longitud(longitud),
    maquina(maquina), isla(isla), activo(activo), contadorSurtidores(0), contadorVentas(0), capacidadVentas(5) {

   /* srand(static_cast<unsigned int>(time(0)));
    for(unsigned short int i=0;i<2;i++){
     unsigned int numeroAleatorio = rand() % 10001 + 20000;
     surtidores[i]=numeroAleatorio;
     surtidorActivo[i]=true;
    }*/
    //contadorSurtidores=2;
    ventas = new Venta[capacidadVentas]; // Inicializa el arreglo dinámico para ventas
}
estacion::estacion() : nombre(""),id(0),gerente(""),region('N'),latitud(0.0f),longitud(0.0f),
    maquina(""),isla(0),activo(0),contadorSurtidores(0),contadorVentas(0),capacidadVentas(5){
    ventas = new Venta[capacidadVentas];
}

// Destructor
estacion::~estacion() {
    delete[] ventas; // Liberar el arreglo de objetos Venta
}


// Getters

void estacion::getsurtidores(){
    for(unsigned short i=0;i<contadorSurtidores;i++){
        cout<<"surtidor de la estacion: "<<id <<" es "<<surtidores[i]<<endl;
    }
    }
unsigned short int estacion:: getcantsurti()const{
    return contadorSurtidores;
}


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
unsigned int estacion:: getIdsurt(unsigned int idsurtidor){
    for (unsigned short int i=0;i<contadorSurtidores;i++){
        if(surtidores[i]==idsurtidor){
            return i;
        }
    }

    cout<<"el surtidor no existe en esta estacion"<<endl;
    return -2;
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
void estacion::agregarSurtidor(unsigned short int idSurtidor, bool activo, unsigned short int ventas) {
    if (contadorSurtidores < 12) {  // Verificar que no exceda la capacidad
        surtidores[contadorSurtidores] = idSurtidor;  // Almacenar el ID del surtidor
        surtidorActivo[contadorSurtidores] = activo;  // Almacenar el estado del surtidor
        ventaSurtidor[contadorSurtidores] = ventas;  // Almacenar las ventas del surtidor
        contadorSurtidores++;  // Incrementar el contador
    } else {
        cerr << "No se pueden agregar más surtidores a esta estación." << endl;
    }
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
                              string documentoCliente, double monto, unsigned short int id, unsigned int est) {
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
    unsigned int idSurtidor = surtidores[id];
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
    return;
}


// Guardar ventas en archivo
bool estacion::guardarVentasEnArchivo() {
    ofstream archivo("C:\\Users\\juan david\\Documents\\desafioII\\ventas.txt", ios::app); // Modo append
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
                << ventas[i].monto << " | "
                << ventas[i].id << " | "
                << ventas[i].est << endl;
    }

    archivo.close();
   // cout << "Ventas guardadas exitosamente." << endl;
    return true;
}

// Mostrar ventas
void estacion::mostrarVentas() {
    guardarVentasEnArchivo();

    ifstream archivo("C:\\Users\\juan david\\Documents\\desafioII\\ventas.txt");

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



//Método para cargar staciones desde un archivos
estacion* estacion::TXTobj(const string& rutaArchivo, const string& rutaSurtidores) {
    ifstream archivo(rutaArchivo);
    if (!archivo.is_open()) {
        cerr << "Error al abrir el archivo de estaciones: " << rutaArchivo << endl;
        return nullptr;
    }

    // Contamos las líneas del archivo para saber cuántas estaciones hay.
    unsigned int count = contadorlineas(rutaArchivo);
    estacion* arrayEstaciones = new estacion[count];  // Array dinámico de estaciones.

    string linea;
    unsigned int i = 0;
    while (getline(archivo, linea) && i < count) {
        istringstream ss(linea);
        string nombre, gerente, maquina, regionStr;
        int id;
        double latitud, longitud;
        unsigned short isla, activo;

        // Extraemos los atributos del archivo separados por ';'.
        getline(ss, nombre, ';');
        ss >> id; ss.ignore();
        getline(ss, gerente, ';');
        getline(ss, regionStr, ';');
        char region = regionStr[0];  // Convertimos el string a char.
        ss >> latitud; ss.ignore();
        ss >> longitud; ss.ignore();
        getline(ss, maquina, ';');
        ss >> isla; ss.ignore();
        ss >> activo;

        // Creamos la estación y la agregamos al array.
        arrayEstaciones[i++] = estacion(nombre, id, gerente, region, latitud, longitud, maquina, isla, activo);
    }
    archivo.close();

    // Cargar surtidores y asociarlos con las estaciones.
    unsigned short numSurtidores;
    surtidor* surtidores = TXTsurtidor(rutaSurtidores, numSurtidores);
    if (surtidores!=nullptr) {
        for (unsigned int j = 0; j < numSurtidores; j++) {
            for (unsigned short int k = 0; k < count; k++) {
                if (arrayEstaciones[k].getId() == surtidores[j].idEstacion) {
                    cout<<"dentro del ciclo2"<<endl;
                    arrayEstaciones[k].agregarSurtidor(surtidores[j].idSurtidor, surtidores[j].activo, surtidores[j].ventas);
                }
            }
        }
        delete[] surtidores;  // Liberamos la memoria de los surtidores.
    }

    cout << "Estaciones cargadas correctamente." << endl;
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
    archivo << nombre<< ';'
            << id << ';'
            << gerente << ';'
            << region << ';'
            << latitud << ';'
            << longitud << ';'
            << maquina << ';'
            << isla << ';'
            << activo << '\n';
    cout << "Estación guardada exitosamente." << endl;
    archivo.close();
}


void estacion::guardarTXT(estacion* array, estacion obj, const string& rutaArchivo) {
    unsigned short int tam=contadorlineas(rutaArchivo);
    ofstream archivo(rutaArchivo);
    if (!archivo.is_open()) {
        cout << "Error al abrir el archivo para guardar." << endl;
        return;
    }
    for (unsigned short int i=0;i<tam;i++){
        if(array[i].getId()!=obj.getId()){
        // Guardar los atributos separados por ';'
            archivo << array[i].getNombre()<< ';' <<array[i].getId() << ';' << array[i].getGerente()<< ';'
                <<array[i].getRegion() << ';'<< array[i].getLatitud() << ';' << array[i].getLongitud() <<
            ';' << array[i].getMaquina() << ';' << array[i].getIsla()<< ';'
            << array[i].getActivo() << '\n';
        }
    }
    if(obj.getActivo()==1){
        archivo <<obj.getNombre()<< ';' <<obj.getId() << ';' << obj.getGerente()<< ';'
                <<obj.getRegion() << ';'<< obj.getLatitud() << ';' << obj.getLongitud() <<
            ';' <<obj.getMaquina() << ';' << obj.getIsla()<< ';'
                << obj.getActivo() << '\n';
    }
    archivo.close();
    cout<<"archivo cerrado"<<endl;
    return;
}

void estacion::guardarTXT(estacion* array, const string& rutaArchivo) {
    unsigned short int tam=contadorlineas(rutaArchivo);
    ofstream archivo(rutaArchivo);
    if (!archivo.is_open()) {
        cout << "Error al abrir el archivo para guardar." << endl;
        return;
    }
    for (unsigned short int i=0;i<tam;i++){
            // Guardar los atributos separados por ';'
            archivo << array[i].getNombre()<< ';' <<array[i].getId() << ';' << array[i].getGerente()<< ';'
                    <<array[i].getRegion() << ';'<< array[i].getLatitud() << ';' << array[i].getLongitud() <<
                ';' << array[i].getMaquina() << ';' << array[i].getIsla()<< ';'
                    << array[i].getActivo() << '\n';
    }
    archivo.close();
    cout<<"archivo cerrado"<<endl;
    return;
}

void estacion::guardarSurtidoresTXT(const string& rutaArchivo) {
    ofstream archivo(rutaArchivo, ios::app); // Modo 'append' para agregar sin borrar
    if (!archivo.is_open()) {
        cout << "Error al abrir el archivo para guardar los surtidores." << endl;
        return;
    }

    // Guardar la información de los surtidores
    for (unsigned short int i = 0; i < contadorSurtidores; ++i) {
        archivo << id << ";"  // ID de la estación
                << surtidores[i] << ";"  // ID del surtidor
                << surtidorActivo[i] << ";"  // Estado del surtidor
                << ventaSurtidor[i] << endl;  // Ventas del surtidor
    }

    archivo.close();
    cout << "Surtidores guardados exitosamente." << endl;
    return;
}


void estacion::guardarSurtidoresTXT(estacion* array,const string& rutaArchivo){
    unsigned short int tam=estacion::contadorlineas("C:\\Users\\juan david\\Documents\\desafioII\\surtidora.txt");
    ofstream archivo(rutaArchivo);
    if (!archivo.is_open()) {
        cout << "Error al abrir el archivo para guardar los surtidores." << endl;
        return;
    }

    // Guardar la información de los surtidores
    for(unsigned short int j=0;j<tam;j++){
        for (unsigned short int i = 0; i < array[j].contadorSurtidores; ++i) {
            archivo << array[j].id << ";"  // ID de la estación
                    << array[j].surtidores[i] << ";"  // ID del surtidor
                    << array[j].surtidorActivo[i] << ";"  // Estado del surtidor
                    << array[j].ventaSurtidor[i] << endl;  // Ventas del surtidor
        }
    }


    archivo.close();
    cout << "Surtidores guardados exitosamente." << endl;
    return;
}

surtidor* estacion::TXTsurtidor(const string& rutaArchivo, unsigned short& count) {
    ifstream archivo(rutaArchivo);
    if (!archivo.is_open()) {
        cerr << "Error al abrir el archivo de surtidores: " << rutaArchivo << endl;
        return nullptr;
    }

    count = contadorlineas(rutaArchivo);
    surtidor* arraySurtidores = new surtidor[count];  // Array dinámico de surtidores.

    string linea;
    unsigned int i = 0;
    while (getline(archivo, linea) && i < count) {
        istringstream ss(linea);
        unsigned idSurtidor, idEstacion;
        bool activo;
        double ventas;
        // Extraemos los atributos del archivo separados por ';'.
        ss >> idEstacion; ss.ignore();  // Leer idEstacion
        ss >> idSurtidor; ss.ignore();   // Leer idSurtidor
        ss >> activo; ss.ignore();        // Leer estado activo (true/false)
        ss >> ventas;                     // Leer ventas como unsigned short

        // Creamos el surtidor y lo agregamos al array.
        arraySurtidores[i++] = surtidor{idEstacion, idSurtidor, activo, ventas}; // Asignando valores leídos.
    }
    archivo.close();

    cout << "Surtidores cargados correctamente." << endl;
    return arraySurtidores;
}

void estacion::getVentas(){
    unsigned short int ventas = 0;
    unsigned short int sumatoria = 0;
    for (unsigned short int i=0; i < contadorSurtidores; i++){
        ventas = ventaSurtidor[i];
        sumatoria = sumatoria + ventas;
    }
    cout << "la estacion " << nombre << " a relizado " << sumatoria << " ventas" << endl;
    return;
}
