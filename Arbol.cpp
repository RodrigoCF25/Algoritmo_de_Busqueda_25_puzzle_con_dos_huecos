//
//  Arbol.cpp
//  Puzzle
//
//  Created by Rodri on 02/06/23.
//

#include "Arbol.hpp"

using  namespace::std;


Arbol::Arbol()
{

}

Arbol::~Arbol()
{

}

void Arbol::crea_arbol(tipo_nodo_informacion contenido)
{
    tipo_nodo_del_arbol nodo;
    nodo.contenido = contenido;
    nodo.nivel_de_profundidad = 0;
    nodo.padre = -1;
    arbol.push_back(nodo);
}

void Arbol::agrega_hijo_a_un_nodo_del_arbol(int padre, tipo_nodo_informacion contenido)
{
    tipo_nodo_del_arbol nodo;
    nodo.contenido = contenido;
    nodo.nivel_de_profundidad = arbol[padre].nivel_de_profundidad + 1;
    nodo.padre = padre;
    arbol.push_back(nodo);
    arbol[padre].hijos.push_back((unsigned int)arbol.size() - 1);
}

void Arbol::push_back(tipo_nodo_del_arbol nodo)
{
    arbol.push_back(nodo);
}



void Arbol::imprime_arbol() const
{
    for (unsigned int i = 0; i < arbol.size(); i++)
    {
        cout << "Nodo: " << i << " Padre: " << arbol[i].padre << " Nivel de profundidad: " << arbol[i].nivel_de_profundidad << " Nombre: " << arbol[i].contenido.nombre_del_nodo << " Costo acumulado: " << arbol[i].contenido.costo_acumulado << endl;
    }
}

void Arbol::limpia_arbol()
{
    arbol.clear();
}


bool Arbol::esta_un_nodo_en_ancestros(unsigned int nodo_actual, string nombre_del_nodo) const
{
    int temporal = arbol[nodo_actual].padre;
    while (temporal != -1) {
        if (arbol[temporal].contenido.nombre_del_nodo == nombre_del_nodo)
            return true;
        temporal = arbol[temporal].padre;
    }
    return false;
}
 


unsigned int Arbol::size() const
{
    return (unsigned int)arbol.size();
}


tipo_nodo_del_arbol Arbol::operator [] (unsigned int indice) const
{
    return arbol[indice];
}


void Arbol::erase(unsigned int indice)
{
    arbol.erase(arbol.begin() + indice);
}



string Arbol::devuelve_la_ruta_encontrada(int nodo_encontrado) const
{
    vector<unsigned int> temporal;
    string ruta = "";
    temporal.clear();

    float costo_acumulado = 0.0f;

    
    costo_acumulado += arbol[nodo_encontrado].contenido.costo_acumulado;

    while (nodo_encontrado != -1)
    {
        temporal.push_back(nodo_encontrado);
        nodo_encontrado = arbol[nodo_encontrado].padre;
    }


    

    for (int i = (int)temporal.size() - 1; i >= 0; i--)
    {
        
        ruta = ruta + "->" + arbol[temporal[i]].contenido.nombre_del_nodo;
    }

    ruta = ruta + "  costo total = " + to_string(costo_acumulado);

    return ruta;
    
}

