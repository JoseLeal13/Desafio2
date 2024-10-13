
#ifndef tank_h
#define tank_h
#include <string>
using namespace std;
class tank
{
private:
    unsigned int id;
    unsigned short int combustibles[3];
    unsigned short int total;
    unsigned short int activo;

public:
    //contructor
    //----------------
    tank(unsigned int id_,unsigned short int regular_,unsigned short int premiun_,unsigned short int ecoextra_,unsigned short int activo_);
    //----------------

    //metodos
    //---------
        //funcion para pasar los txt a objetos
    void mostrar();     //mostrar los valores de los atributos
    void modcombustible(unsigned short int tcombustible,unsigned short int cant);//metodo para modificar los atributos
    int getrest(unsigned short int tcombustibles);     //metodo que retorna el restante de combustible de un objeto
    friend ostream& operator<<(ostream& os, const tank& tank); //funcion amiga(puede acceder a los atributos de cualquier objeto)
    static tank* objetos();
};

#endif // tank_h

