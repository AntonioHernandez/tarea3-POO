#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>

using namespace std;

#define MAX_PROFESORES 2
#define ALTA 1
#define BAJA 2
#define CONSULTA 3
#define CAMBIO 4
#define BUSQUEDA 5
#define SALIR 6
#define TAMANO_NOMBRE 50
#define TAMANO_RFC 13

typedef struct{
    int anio;
    int mes;
    int dia;
}Fecha;

typedef struct{
    int codigo;
    char nombre[TAMANO_NOMBRE+1];
    char rfc[TAMANO_RFC+1]; //13 caracteres más el caracter '\0'
    float salario;
    Fecha fechaNacimiento;
    bool libre;
}Persona;

Persona profesores[MAX_PROFESORES];

void limpiarRegistro(int indice);
void inicializarPrograma();
void modificarRegistroProfesor(int indice);
bool elRegistroTieneDatos(int indice);
void mostrarProfesor(int indice);
void darDeAltaProfesor();
void darDeBajaProfesor();
void consultarProfesor();
void cambiarDatosDeProfesor();
void buscarProfesor();
void mostrarMenu();

int main()
{
    bool continuaPrograma=true;
    int opcion;
    inicializarPrograma();
    do{
        mostrarMenu();
        cin>>opcion;
        switch(opcion){
            case ALTA:darDeAltaProfesor();break;
            case BAJA:darDeBajaProfesor();break;
            case CONSULTA:consultarProfesor();break;
            case CAMBIO:cambiarDatosDeProfesor();break;
            case BUSQUEDA:buscarProfesor();break;
            case SALIR:continuaPrograma=false;break;
            default:cout<<"Opcion no valida!"<<endl;
        }
    }while(continuaPrograma);
    return 0;
}

void limpiarRegistro(int indice){
    int i=indice;
    profesores[i].codigo=0;
    strcpy(profesores[i].nombre,"");
    strcpy(profesores[i].rfc,"");
    profesores[i].salario=0;
    profesores[i].fechaNacimiento.anio=0;
    profesores[i].fechaNacimiento.mes=0;
    profesores[i].fechaNacimiento.dia=0;
    profesores[i].libre=true;
}

void inicializarPrograma(){
    int i;
    for(i=0;i<MAX_PROFESORES;i++){
        limpiarRegistro(i);
    }
}

void modificarRegistroProfesor(int indice){
    int i=indice;
    cout<<"Provee datos para el registro"<<i<<endl;
    cout<<"Codigo:";
    cin>>profesores[i].codigo;
    cout<<"Nombre:";
    getchar();
    gets(profesores[i].nombre);
    cout<<"RFC:";
    gets(profesores[i].rfc);
    cout<<"Salario:";
    cin>>profesores[i].salario;
    cout<<"*Fecha nacimiento*"<<endl<<"Anio: ";
    cin>>profesores[i].fechaNacimiento.anio;
    cout<<"Mes: ";
    cin>>profesores[i].fechaNacimiento.mes;
    cout<<"Dia: ";
    cin>>profesores[i].fechaNacimiento.dia;
    profesores[i].libre=false;
}

void darDeAltaProfesor(){
    bool hayEspacioLibre;
    int i;
    cout<<"ALTA DE NUEVO PROFESOR"<<endl<<endl;
    hayEspacioLibre=false;
    for(i=0;i<MAX_PROFESORES;i++){
        if (profesores[i].libre){
            hayEspacioLibre=true;
            break;
        }
        //else seguir buscando un espacio libre
    }
    if (hayEspacioLibre){
        modificarRegistroProfesor(i);
    }
    else{
        cout<<"No hay mas espacio para captura"<<endl<<endl;
    }
    system("PAUSE()");
}

bool elRegistroTieneDatos(int indice){
    bool tieneDatos=false;
    if ((indice>=0)&&(indice<MAX_PROFESORES)){
        if (profesores[indice].libre){
            cout<<endl<<"Registro sin datos"<<endl;
        }
        else{
            tieneDatos=true;
        }
    }
    else{
        cout<<endl<<"No existe ese numero de registro"<<endl;
    }
    return tieneDatos;
    system("PAUSE()");
}

void mostrarProfesor(int indice){
    int i=indice;
    cout<<"Registro" <<i<<":"<<endl;
    cout<<"Codigo="<<profesores[i].codigo<<endl;
    cout<<"Nombre="<<profesores[i].nombre<<endl;
    cout<<"RFC="<<profesores[i].rfc<<endl;
    cout<<"Salario="<<profesores[i].salario<<endl;
    cout<<"Fecha nacimiento="<<profesores[i].fechaNacimiento.anio<<"/"<<
    profesores[i].fechaNacimiento.mes<<"/"<<profesores[i].fechaNacimiento.dia<<endl;
}

void darDeBajaProfesor(){
    int i;
    char opcion;
    cout<<"BAJA DE PROFESOR\n\n";
    cout<<"Indica el numero de registro a eliminar (0 a "<<MAX_PROFESORES-1<<"): ";
    cin>>i;
    if (elRegistroTieneDatos(i)){
        mostrarProfesor(i);
        cout<<"Estas seguro de eliminar el registro (s/n)?";
        getchar();
        cin>>opcion;
        if (opcion=='S' || opcion=='s'){
            limpiarRegistro(i);
            cout<<"Registro eliminado!"<<endl;
        }
        else{
            cout<<"Registro conservado!"<<endl;
        }
    }
    //elRegistroTieneDatos() imprime en caso falso
    system("PAUSE()");
}

void consultarProfesor(){
    int i;
    cout<<"CONSULTA DE UN PROFESOR"<<endl<<endl;
    cout<<"Indica el numero de registro a consultar (0 a "<<MAX_PROFESORES-1<<"): ";
    cin>>i;
    if (elRegistroTieneDatos(i)){
        mostrarProfesor(i);
    }
    //elRegistroTieneDatos() imprime en caso falso
    system("PAUSE()");
}

void cambiarDatosDeProfesor(){
    int i;
    cout<<"CAMBIO DE DATOS DE UN PROFESOR"<<endl<<endl;
    cout<<"Indica el numero de registro a modificar (0 a "<<MAX_PROFESORES-1<<": ";
    cin>>i;
    if (elRegistroTieneDatos(i)){
        mostrarProfesor(i);
        modificarRegistroProfesor(i);
    }
    //elRegistroTieneDatos() imprime en caso falso
    system("PAUSE()");
}

void buscarProfesor(){
    char buscado[TAMANO_NOMBRE+1];
    char* patron;
    int i,encontrados;
    cout<<"BUSQUEDA DE PROFESOR"<<endl<<endl;
    cout<<"Indica el nombre del profesor: ";
    getchar();
    gets(buscado);
    encontrados=0;
    for(i=0;i<MAX_PROFESORES;i++){
        patron=strstr(profesores[i].nombre,buscado);
        if (patron!=NULL){
            mostrarProfesor(i);
            encontrados++;
        }
        //else seguir buscando
    }
    if (encontrados){
        cout<<"Se encontro "<<encontrados<<" registro(s) con la palabra buscada"<<endl;
    }
    else{
        cout<<"No se encontro algun registro con la palabra buscada"<<endl;
    }
    system("PAUSE()");
}

void mostrarMenu(){
    system("CLS");
    cout<<"*REGISTRO DE PROFESORES*"<<endl;
    cout<<endl<<"1. Alta de nuevo profesor"<<endl;
    cout<<"2. Baja de profesor"<<endl;
    cout<<"3. Consulta de un profesor"<<endl;
    cout<<"4. Cambio de datos de un profesor"<<endl;
    cout<<"5. Busqueda de profesor"<<endl;
    cout<<"6. Salir"<<endl;
    cout<<"Opcion: ";
}
