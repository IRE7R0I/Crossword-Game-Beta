#include <iostream>
#include <vector>
#include <cstring>
#include <string>
#include <stdlib.h>

using namespace std;

struct PARAMETRO{
    int id;
    int posFila;
    int posColumna;
    string palabra;
    string descripcion;
    char orientacion;
};

string convertirAMayusculas(string cad1) {
    for (size_t i = 0; i < cad1.length(); ++i) {
        cad1[i] = toupper(cad1[i]);
    }
    return cad1;
}

bool compararCadenas(string cad1, string cad2) {
    return convertirAMayusculas(cad1) == convertirAMayusculas(cad2);
}

void agregarPalabra(vector<PARAMETRO> &palabras, int id, int posFila, int posColumna, string palabra, string descripcion, char orientacion){
    palabras.push_back({id, posFila, posColumna, palabra, descripcion, orientacion});
    //cout << "Palabra agregada correctamente." << endl;
}

void mostrarPalabras(vector<PARAMETRO> &palabras){
    for (size_t i = 0; i < palabras.size(); i++){
        cout << "ID: " << palabras[i].id << " ,Pos: " << palabras[i].posFila << " - " << palabras[i].posColumna << ", Palabra: " << palabras[i].palabra << ", Descripcion: " << palabras[i].descripcion<<", Orientacion: " << palabras[i].orientacion <<endl;
    }
}

void mostrarCrucigrama(vector<vector<char>> cruci){
    for (size_t i = 0; i < cruci.size(); i++){
        for (size_t j = 0; j < cruci[i].size(); j++){
            char elemento = cruci[i][j];
            cout << elemento << " ";
        }
        cout << endl; // Salto de línea después de cada fila
    }
}

void eliminarPalabra(vector<PARAMETRO> &palabras, int id) {
    auto it = palabras.begin();
    while (it != palabras.end()) {
        if (it->id == id) {
            it = palabras.erase(it);
            cout << "Palabra eliminada correctamente." << endl;
            return;
        } else {
            ++it;
        }
    }
    cout << "No se encontró ninguna palabra con el ID especificado." << endl;
}


int elegirPorId(vector<PARAMETRO> palabras, char orientacion) {
    int eleccion;
    bool encontrado = false;
    do {
        cout << "\nElija por ID la descripcion de la palabra que quiera descubrir" << endl;
        if (orientacion == 'H') {
            for (size_t i = 0; i < palabras.size(); i++) {
                if (palabras[i].orientacion == 'H') {
                    cout << "ID: " << palabras[i].id << ", Descripcion: " << palabras[i].descripcion << endl;
                }
            }
        } else {
            for (size_t i = 0; i < palabras.size(); i++) {
                if (palabras[i].orientacion == 'V') {
                    cout << "ID: " << palabras[i].id << ", Descripcion: " << palabras[i].descripcion << endl;
                }
            }
        }
        cin >> eleccion;

        // Verificar si eleccion es un valor válido
        
        for (size_t i = 0; i < palabras.size(); i++) { //Hice todo esto porque si no me entraba en bucle infinito, al no encontrar el siguiente
            if (palabras[i].id == eleccion) {
                encontrado = true;
                break;
            }
        }
        if (!encontrado) {
            cout << "ID no válido. Intente nuevamente." << endl;
        }
    } while (!encontrado);

    for (size_t i = 0; i < palabras.size(); i++) {
        if (palabras[i].id == eleccion) {
            cout << "Se devuelve la posición " << i << " del ID seleccionado: " << eleccion << endl;
            return i;
        }
    }

    cout << "No se encontró ninguna palabra con el ID especificado." << endl;
    return -1; // Valor por defecto en caso de que no se encuentre ninguna palabra
}

bool reintentar(){
    char respuesta;
    cout<<"No era la respuesta correcta"<<endl;
    cout<<"Desea reintentar? Elija la opcion que corresponda"<<endl;
    cout<<"SI(s) - NO(n)"<<endl; 
    cin>>respuesta;
    respuesta = toupper(respuesta);
    return (respuesta != 'S');
}

void procedimientoHorizontal(vector<PARAMETRO> &palabras, vector<vector<char>> &crucigrama, int posPalabra){
    string respuesta;
    bool respuestaCorrecta = false;

    cout<<"\nSi adivina la palabra sera colocada en el crucigrama"<< endl;
    do{

        cout<<palabras[posPalabra].descripcion << endl;
        cin>>respuesta;
            
            if (compararCadenas(respuesta,palabras[posPalabra].palabra)){
            cout<<"Adivinaste!!!"<<endl;
            const char* palabraNueva = palabras[posPalabra].palabra.c_str();
                for (size_t i = 0; i < strlen(palabraNueva); i++){
                    crucigrama[palabras[posPalabra].posFila][palabras[posPalabra].posColumna + i] = palabraNueva[i];//De esta manera coloca cada letra en su posicion
                }
                eliminarPalabra(palabras, palabras[posPalabra].id);
                respuestaCorrecta = true;
                
            }   else {
                    respuestaCorrecta = reintentar();
            }
    }while (!respuestaCorrecta);
}

 

void procedimientoVertical(vector<PARAMETRO> &palabras, vector<vector<char>> &crucigrama, int posPalabra){
    string respuesta;
    bool respuestaCorrecta = false;

    cout<<"\nSi adivina la palabra sera colocada en el crucigrama"<<endl;
    do{

        cout<< palabras[posPalabra].descripcion << endl;
        cin>> respuesta;
            if (compararCadenas(respuesta,palabras[posPalabra].palabra)){
            cout<<"Adivinaste!!!"<< endl;
            const char* palabraNueva = palabras[posPalabra].palabra.c_str();
                for (size_t i = 0; i < strlen(palabraNueva); i++){
                    crucigrama[palabras[posPalabra].posFila + i][palabras[posPalabra].posColumna] = palabraNueva[i];//De esta manera coloca cada letra en su posicion
                }
                eliminarPalabra(palabras, palabras[posPalabra].id);
                respuestaCorrecta = true;
            }   else {
                    respuestaCorrecta = reintentar();    
            }
    }while(!respuestaCorrecta);
}

void adivinarPalabra(vector<PARAMETRO> &palabras, vector<vector<char>> &crucigrama){
    string respuesta;
    char orientacion;
    int posPalabra;

    cout <<"\nElija la palabra que quiera adivinar"<< endl;

    cout<<"Que orientacion quiere elegir: HORIZONTAL(H) O VERTICAL(V)"<<endl;
    do{
        cout<<"Elija el caracter que corresponda"<<endl;
        cin>>orientacion;
        orientacion = toupper(orientacion);
    }while(orientacion != 'H' && orientacion != 'V');

    posPalabra = elegirPorId(palabras, orientacion);//Numero de ID

    if(orientacion == 'H'){
        procedimientoHorizontal(palabras, crucigrama, posPalabra);

    } else {
        procedimientoVertical(palabras, crucigrama, posPalabra);

    }

}


void iniciarCrucigrama(vector<vector<char>> &crucigrama, vector<PARAMETRO> &palabras){
    crucigrama = {
    {'-','-','-','-','-','-','-','-','-','-','-','-','-','-','-'},
    {'-','-','-','-','-','-','-','-','-','-','-','-','-','-','-'},
    {'-','-','-','-','-','-','-','-','-','-','-','-','-','-','-'},
    {'-','-','-','-','-','-','-','-','-','-','-','-','-','-','-'},
    {'-','-','-','-','-','-','-','-','-','-','-','-','-','-','-'},
    {'-','-','-','-','-','-','-','-','-','-','-','-','-','-','-'},
    {'-','-','-','-','-','-','-','-','-','-','-','-','-','-','-'},
    {'-','-','-','-','-','-','-','-','-','-','-','-','-','-','-'},
    {'-','-','-','-','-','-','-','-','-','-','-','-','-','-','-'},
    {'-','-','-','-','-','-','-','-','-','-','-','-','-','-','-'},
    {'-','-','-','-','-','-','-','-','-','-','-','-','-','-','-'},
    {'-','-','-','-','-','-','-','-','-','-','-','-','-','-','-'},
    {'-','-','-','-','-','-','-','-','-','-','-','-','-','-','-'}};

    agregarPalabra(palabras, 1, 0, 1, "COMILLA", "Simple o doble",'H');
    agregarPalabra(palabras, 2, 0, 10, "DATOS", "Simples o compuestos",'H');
    agregarPalabra(palabras, 3, 2, 8, "FALSO", "No se cumple",'H');
    agregarPalabra(palabras, 4, 3, 0, "VALOR", "Pertenece a un conjunto",'H');
    agregarPalabra(palabras, 5, 4, 6, "RESERVADA", "Palabra con significado especial",'H');
    agregarPalabra(palabras, 6, 8, 2, "ESTRUCTURADO", "Compuesto",'H');
    agregarPalabra(palabras, 7, 10, 1, "BOOLEANO", "Lógico",'H');
    agregarPalabra(palabras, 8, 10, 10, "REAL", "Tipo de dato numérico",'H');
    agregarPalabra(palabras, 9, 12, 3, "ENUMERADO", "Tipo de dato no estándar",'H');


    agregarPalabra(palabras, 10, 0, 1, "CARACTER", "Tipo de dato simple",'V');
    agregarPalabra(palabras, 11, 2, 3, "COMPUESTO", "Estructurado",'V');
    agregarPalabra(palabras, 12, 1, 9, "CADENA", "Tipo de dato compuesto",'V');
    agregarPalabra(palabras, 13, 4, 11, "VERDADERO", "Valor lógico",'V');
    agregarPalabra(palabras, 14, 0, 14, "SUBRANGO", "Tipo de dato no estándar",'V');
}

void iniciarJuego(vector<vector<char>> &crucigrama, vector<PARAMETRO> &palabras){

    cout<<"BIENVENIDO AL JUEGO DEL CRUCIGRAMA V1.0"<<endl;
    
    mostrarCrucigrama(crucigrama);

    while(palabras.size() > 0){
        adivinarPalabra(palabras, crucigrama);
        //system("cls");
        mostrarCrucigrama(crucigrama);
    }

    cout<<"GANASTE!"<<endl;
}


int main(int argc, char *argv[]){

    vector<vector<char>> crucigramaParcial;
    vector<PARAMETRO> palabrasParametro;

    iniciarCrucigrama(crucigramaParcial, palabrasParametro);
    iniciarJuego(crucigramaParcial, palabrasParametro);

}
