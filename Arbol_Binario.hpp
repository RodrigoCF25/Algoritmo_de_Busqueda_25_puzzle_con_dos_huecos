//
//  Arbol_Binario.hpp
//  Puzzle
//
//  Created by Rodri on 02/06/23.
//



#ifndef Arbol_Binario_hpp
#define Arbol_Binario_hpp

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std;



struct Nodo
{
    string value = "";
    string costo_acumulado = "0";
    string pDer = "";
    string pIzq = "";
};




class Arbol_Binario
{
public:
    Arbol_Binario(void);
    ~Arbol_Binario();
    bool push(string pValue, unsigned int pCosto_acumulado); // true, es que logro meterlo; false, es que no lo metio porque ya estaba en el arbol
    void repr();
    void clear();
    
private:
    vector <Nodo> arbol_binario;
    
};

#endif /* Arbol_Binario_hpp */
