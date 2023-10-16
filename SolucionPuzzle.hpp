//
//  SolucionPuzzle.hpp
//  Puzzle
//
//  Created by Rodri on 02/06/23.
//



#ifndef SolucionPuzzle_hpp
#define SolucionPuzzle_hpp

#include "SolucionPuzzle.hpp"
#include "Arbol_Binario.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>
#include "Arbol.hpp"
#include "Agenda.hpp"




using namespace::std;

#pragma warning(disable : 6011)




class PuzzleSolver //Clase que se encarga de ejecutar los algoritmos de b�squedas en cualquier grafo
{
public:
    PuzzleSolver();
    ~PuzzleSolver();
    bool busqueda_primero_el_mejor(const vector <vector <unsigned int>> pEstado_inicial, const vector <vector <unsigned int>> pEstado_final, int& nodo_encontrado);
    bool busqueda_primero_el_mejor(string archivo,string archivo_solucion, int& nodo_encontrado);
    

    
    bool busqueda_A_ESTRELLA(const vector <vector <unsigned int>> pEstado_inicial,const vector <vector <unsigned int>> pEstado_final, int& nodo_encontrado);
    bool busqueda_A_ESTRELLA(string archivo,string archivo_solucion, int& nodo_encontrado);
    
    
    
    bool busqueda_nueva(vector <vector <unsigned int>> pEstado_inicial, int& nodo_encontrado);
    bool busqueda_nueva(string archivo,string archivo_solucion, int& nodo_encontrado);
    
    string devuelve_la_ruta_encontrada(int nodo_encontrado);
    
    
private:
    unsigned int dimension;
    int entero_con_el_que_comienza_el_casteo = 64; //Sirve para convertir los numeros a char y ternlos como el alfabeto en minusuculas
    vector < vector <int>> estado_inicial; //Es el conjunto de numeros pasados por el usuario y con un cierto orden
    Arbol arbol_de_busqueda;
    Agenda agenda;
    vector <int> huecos; //Guarda los id que debe otorgarle a los huecos cuando son 2

    
    //Para busqueda nueva
    unsigned int devuelve_numero_a_colocar_en_su_posicion(string nodo_actual,string meta); //revisa cual es el numero que deberia trabajarse en acomodar
    unsigned int nuevo_calcula_heuristica_a_la_meta(string nodo_actual, string meta, unsigned int  numero_a_colocar_en_su_posicion) const; // Heuristica que asegura que los numeros anteriores al
    //que se va a colocar ahora estan en su lugar, la heuristica del numero a colocar y su posterior a su lugar en la meta y la heuristica de los huecos al numero a colocar


    //Primero el mejor y A*
    unsigned int calcula_heuristica_a_la_meta(string nodo_actual, string meta); //Heuristica Manhattan, los huecos se ignoran
    void devuelve_vecinos(string nodo_actual, vector <tipo_nodo_informacion> &vecinos) const;
    //los huecos se mueven 1 a la vez, 1 nodo : 4 vecinos max; 2: 8 max


    //Lectura y escritura
    vector < vector < int>> lee_archivo(string &archivo); // devuelve el estado final, el inicio se almacena en el atributo estado_inicial
    void escribe_en_archivo(string &archivo, double tiempo, int  nodo_encontrado);
};



#endif /* SolucionPuzzle_hpp */
