#ifndef tank_h
#define tank_h
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;
class tank
{
private:
    unsigned int id;
    float combustibles[3];
    float precios[3];
    float total;
    unsigned short int activo;

public:
    //contructor  Sobrecargas
    //----------------
    tank();
    tank(unsigned int id_,float regular_,float premiun_,float ecoextra_,
         float pr,float pp,float peco,unsigned short int activo_);
    tank(unsigned int id_,unsigned short int activo_);
    //----------------
    //destructor
    ~tank();
    //----------------


    //Metodos
    void getprice();    //muestra los precios
    unsigned int Getid()const;//muestra el id del objeto
    unsigned short int Getact()const;//muestra si la estacion esta activa o no
    void gettank();     //mostrar los valores de los atributos
    void settank(unsigned short int tcombustible,unsigned short int cant);//metodo para modificar los atributos
    void setactivo(unsigned short int activid);       //modificar el estado del tanque
    int getrest(unsigned short int tcombustibles);     //metodo que retorna el restante de combustible de un objeto
    void GuardarTank();//Este metodo es para guardar los objetos a un txt
    void setprecios(float pr,float pp,float peco); //modificar los precios de un objeto
    friend ostream& operator<<(ostream& os, const tank& tank); //funcion amiga(puede acceder a los atributos de cualquier objeto)
    static unsigned int contadorlineas();       //contar las lineas del archivo
    static tank* TXTobj(const string& rutaArchivo);                      //pasar el txt a objetos de clase tank
    static void Saveobj(tank* array,tank obj,const string& archivo);           //guardar los objetos a un archivo



};

#endif // tank_h

