//
//  Arbol.hpp
//  Puzzle
//
//  Created by Rodri on 02/06/23.
//

#ifndef Arbol_hpp
#define Arbol_hpp

#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct tipo_nodo_informacion //Guarda: Nombre_del_nodo(identificador) y el costo acumulado (vital para el camino a escoger en weighted graph)
{
    string nombre_del_nodo = "";
    unsigned int costo_acumulado = 0;
    unsigned int costo_estimado = 0;
    unsigned int numero_a_colocar = 1;
};


struct tipo_nodo_del_arbol //Guarda la informacion interna del nodo, quien es su padre y quienes sus hijos
{
    tipo_nodo_informacion contenido;
    unsigned int nivel_de_profundidad = 0;
    int padre = -1;
    vector<int> hijos;
};


class Arbol //Clase que se encarga de manejar el arbol de b�squeda
{
public:
    Arbol();
    ~Arbol();
    void crea_arbol(tipo_nodo_informacion contenido);
    void agrega_hijo_a_un_nodo_del_arbol(int padre, tipo_nodo_informacion contenido);
    void push_back(tipo_nodo_del_arbol nodo);
    void imprime_arbol() const;
    void limpia_arbol();
    bool esta_un_nodo_en_ancestros(unsigned int nodo_actual, string nombre_del_nodo) const;
    string devuelve_la_ruta_encontrada(int nodo_encontrado) const;
    unsigned int size() const;
    tipo_nodo_del_arbol operator [] (unsigned int indice) const;
    void erase(unsigned int indice);
    


private:

    vector <tipo_nodo_del_arbol> arbol;
};


#endif /* Arbol_hpp */
