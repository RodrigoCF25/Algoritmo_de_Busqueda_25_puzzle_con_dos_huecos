//
//  main.cpp
//  Puzzle
//
//  Created by Rodri on 02/06/23.
//

#include <iostream>
#include <string>
#include "SolucionPuzzle.hpp"


#define RutaPuzzle1 "Puzzle1.csv"
#define RutaPuzzle2 "Puzzle2.csv"
#define RutaPuzzle3 "Puzzle3.csv"
#define RutaPuzzle4 "Puzzle4.csv"
#define RutaPuzzle5 "Puzzle5.csv"
#define RutaPuzzle6 "Puzzle6.csv"
#define RutaPuzzle7 "Puzzle7.csv"
#define RutaPuzzle8 "Puzzle8.csv"

#define RutaSolPuzzle1 "Solucion1.txt"
#define RutaSolPuzzle2 "Solucion2.txt"
#define RutaSolPuzzle3 "Solucion3.txt"
#define RutaSolPuzzle4 "Solucion4.txt"
#define RutaSolPuzzle5 "Solucion5.txt"
#define RutaSolPuzzle6 "Solucion6.txt"
#define RutaSolPuzzle7 "Solucion7.txt"
#define RutaSolPuzzle8 "Solucion8.txt"

using namespace std;

int main(int argc, const char* argv[]) {


    PuzzleSolver solver = PuzzleSolver();

    int nodo_encontrado;
    string ruta = "";
    vector <vector <unsigned int>> inicio = { {0,0,23,22,21},{20,19,18,17,16},{15,14,13,12,11},{10,9,8,7,6},{5,4,3,2,1} };
    vector <vector<unsigned int>> final = { {1,2,3,4,5},{6,7,8,9,10},{11,12,13,14,15},{16,17,18,19,20},{21,22,23,0,0} };

    /*
    cout << "Busqueda primero el mejor " << endl;

    if (solver.busqueda_primero_el_mejor(inicio, final, nodo_encontrado))
    {

        ruta = solver.devuelve_la_ruta_encontrada(nodo_encontrado);
        cout << ruta << endl;
    }

    cout << "----------------------------------------------" << endl;
    */
    
    
    cout << "Puzzle 5x5 2 huecos" << endl;
    if (solver.busqueda_nueva(inicio, nodo_encontrado))
    {

        ruta = solver.devuelve_la_ruta_encontrada(nodo_encontrado);
        cout << ruta << endl;
    }
    
    cout << "----------------------------------------------" << endl;
    

    
    
    cout << "ARCHIVOS PRIMERO EL MEJOR" << endl;
    
    //solver.busqueda_primero_el_mejor(RutaPuzzle1, RutaSolPuzzle1, nodo_encontrado);
    //solver.busqueda_primero_el_mejor(RutaPuzzle2, RutaSolPuzzle2, nodo_encontrado);
    //solver.busqueda_primero_el_mejor(RutaPuzzle3, RutaSolPuzzle3, nodo_encontrado);
    //solver.busqueda_primero_el_mejor(RutaPuzzle4, RutaSolPuzzle4, nodo_encontrado);
    //solver.busqueda_primero_el_mejor(RutaPuzzle5, RutaSolPuzzle5, nodo_encontrado);
    //solver.busqueda_primero_el_mejor(RutaPuzzle6, RutaSolPuzzle6, nodo_encontrado);
    //solver.busqueda_primero_el_mejor(RutaPuzzle7, RutaSolPuzzle7, nodo_encontrado);
    
     

    cout << endl << "--------------------------------------------" << endl;
          
    
    cout << "ARCHIVOS BUSQUEDA NUEVA" << endl;

    solver.busqueda_nueva(RutaPuzzle1, RutaSolPuzzle1, nodo_encontrado);
    solver.busqueda_nueva(RutaPuzzle2, RutaSolPuzzle2, nodo_encontrado);
    solver.busqueda_nueva(RutaPuzzle3, RutaSolPuzzle3, nodo_encontrado);
    solver.busqueda_nueva(RutaPuzzle4, RutaSolPuzzle4, nodo_encontrado);
    solver.busqueda_nueva(RutaPuzzle5, RutaSolPuzzle5, nodo_encontrado);
    solver.busqueda_nueva(RutaPuzzle6, RutaSolPuzzle6, nodo_encontrado);
    solver.busqueda_nueva(RutaPuzzle7, RutaSolPuzzle7, nodo_encontrado);
    solver.busqueda_nueva(RutaPuzzle8, RutaSolPuzzle8, nodo_encontrado);
    
    cout << endl << "--------------------------------------------" << endl;
    
    
    cout << "ARCHIVOS A ESTRELLA" << endl;

    //solver.busqueda_A_ESTRELLA(RutaPuzzle1, RutaSolPuzzle1, nodo_encontrado);
    //solver.busqueda_A_ESTRELLA(RutaPuzzle2, RutaSolPuzzle2, nodo_encontrado);
    //solver.busqueda_A_ESTRELLA(RutaPuzzle3, RutaSolPuzzle3, nodo_encontrado);
    //solver.busqueda_A_ESTRELLA(RutaPuzzle4, RutaSolPuzzle4, nodo_encontrado);
    //solver.busqueda_A_ESTRELLA(RutaPuzzle5, RutaSolPuzzle5, nodo_encontrado);
    //solver.busqueda_A_ESTRELLA(RutaPuzzle6, RutaSolPuzzle6, nodo_encontrado);
    
    
    
    


    return 0;
}
