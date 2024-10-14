
#ifndef tank_h
#define tank_h
#include <string>
using namespace std;
class tank
{
private:
    unsigned int id;
    float combustibles[3];
    float total;
    unsigned short int activo;

public:
    //contructor
    //----------------
    tank();
    tank(unsigned int id_,float regular_,float premiun_,float ecoextra_,unsigned short int activo_);
    //----------------

    //Metodos
        //funcion para pasar los txt a objetos
    void gettank();     //mostrar los valores de los atributos
    void settank(unsigned short int tcombustible,unsigned short int cant);//metodo para modificar los atributos
    int getrest(unsigned short int tcombustibles);     //metodo que retorna el restante de combustible de un objeto
    void GuardarTank();//Este metodo es para guardar los objetos a un txt
    friend ostream& operator<<(ostream& os, const tank& tank); //funcion amiga(puede acceder a los atributos de cualquier objeto)
    static unsigned int contadorlineas();       //contar las lineas del archivo
    static tank* TXTobj(const string& rutaArchivo);                      //pasar el txt a objetos de clase tank
    static void Saveobj(tank* array,tank obj,const string& archivo);           //guardar los objetos a un archivo
};

#endif // tank_h

