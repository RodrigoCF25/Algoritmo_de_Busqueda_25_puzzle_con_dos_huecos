//
//  SolucionPuzzle.cpp
//  Puzzle
//
//  Created by Rodri on 02/06/23.
//

#include "SolucionPuzzle.hpp"



PuzzleSolver::PuzzleSolver()
{
}
//---------------------------------------------------------------------------------------------------------------

PuzzleSolver::~PuzzleSolver()
{

}
//---------------------------------------------------------------------------------------------------------------




unsigned int PuzzleSolver::calcula_heuristica_a_la_meta(string nodo_actual, string meta)
{
    unsigned int heuristica_total = 0;
    
    int movimientos_horizontales_necesarios_para_que_el_elemento_llegue_su_posicion_de_la_meta = 0; //columnas
    int movimientos_verticales_necesarios_para_que_el_elemento_llegue_su_posicion_de_la_meta  = 0; //filas
    
    //La forma de calcular los desplazamientos para llegar a la fila meta es mas sencilla que para el caso de las columnas
    // simplemente debe seguirse la siguiente expresion:
    //abs( indice_en_el_string_meta/dimension_del_puzzle - indice_en_el_string_nodo_actual/dimension_del_puzzle)
    //Pongamos un escenario de un puzzle 3x3, los elementos de la primera fila {0,1,2} divididos entre 3 dan 0
    // los elementos de la ultima fila {6,7,8} dan 2, las restas entre los posibles resultados de estas divisiones
    //estan en el perfecto rango de posibles movimientos verticales {0,1,2}
    
    
   

    //La forma de calcular los desplazamientos para llegar a la columna de la meta se realiza de la sisguiente manera:
    //sabemos que todos los elementos que sean divisibles entre la dimension del puzzle estan en la primera columna
    // por lo que si al indice del elemento que tenemos le restamos el producto del numero de la fila en la que esta por la dimension del puzzle, conoceremos la columna.
    //Ejemplos: tenemos el siguiente puzzle 3x3 {{1,2,3},{4,5,6},{7,8,-1}} -> indices{{0,1,2},{3,4,5},{6,7,8}} en que columna estan 1,5,-1
    //Formula para calcular fila = indice_del_elemento_en_el_string /dimension_del_puzzle
    //Formula para calcular columna = abs( indice_del_elemento_en_el_string - (dimension_del_puzzle * fila_en_donde_esta_el_elemento))
    
    // Fila del 1 : 0/3 -> fila = 0
    //Columna del 1 : abs(0 - (3 * 0)) = abs(0 -0) -> columna =  0
    //Fila del 5 : 4/3 = 1 -> fila = 1
    //Columna del 5: abs(4 - (3 * 1)) - abs(4-3) -> columa = 1
    //Fila del -1 : 8/3 = 2 -> fila = 2
    //Columna del -1 = abs(8 - (3 * 2)) = abs(8 - 6) -> columna = 2
    
    
    
    int fila_en_la_que_esta_el_elemento_en_el_nodo_actual = 0;
    int fila_en_el_que_esta_el_elemento_en_la_meta = 0;
    int columna_en_la_que_esta_el_elemento_en_el_nodo_actual = 0;
    int columna_en_el_que_esta_el_elemento_en_la_meta = 0;
    

    
    for (int i = 0; i < nodo_actual.length();i++) //nodo actual tiene el puzzle en 1 string
    {
        for (int j = 0; j < meta.length();j++)
            if (nodo_actual[i] == meta[j])
            {
                if(nodo_actual[i] == entero_con_el_que_comienza_el_casteo)
                    break;
                
                fila_en_la_que_esta_el_elemento_en_el_nodo_actual = i/dimension;
                
                fila_en_el_que_esta_el_elemento_en_la_meta = j/dimension;
                movimientos_verticales_necesarios_para_que_el_elemento_llegue_su_posicion_de_la_meta = abs(fila_en_el_que_esta_el_elemento_en_la_meta - fila_en_la_que_esta_el_elemento_en_el_nodo_actual);

                columna_en_la_que_esta_el_elemento_en_el_nodo_actual = abs(i - (int)dimension * fila_en_la_que_esta_el_elemento_en_el_nodo_actual);
                
                columna_en_el_que_esta_el_elemento_en_la_meta = abs(j - (int)dimension * fila_en_el_que_esta_el_elemento_en_la_meta);
                
                movimientos_horizontales_necesarios_para_que_el_elemento_llegue_su_posicion_de_la_meta = abs(columna_en_el_que_esta_el_elemento_en_la_meta - columna_en_la_que_esta_el_elemento_en_el_nodo_actual);

                heuristica_total = heuristica_total + movimientos_verticales_necesarios_para_que_el_elemento_llegue_su_posicion_de_la_meta + movimientos_horizontales_necesarios_para_que_el_elemento_llegue_su_posicion_de_la_meta;
                break;
                
            }
        
    }
    
    return heuristica_total;
    
}




//------------------------------------------------------------------------------------------------------------------------------

//Si un solo hueco puede moverse en un movimiento
 
void PuzzleSolver::devuelve_vecinos(string nodo_actual, vector <tipo_nodo_informacion> &vecinos) const
{
    vecinos.clear();
    tipo_nodo_informacion informacion_del_vecino;
    char valor_de_los_huecos;
    char valor_en_la_otra_columna;
    char valor_en_la_otra_fila;
    
    valor_de_los_huecos = (char) entero_con_el_que_comienza_el_casteo;
    if (huecos.size() == 1)
    {
        
        for(int j = 0; j < nodo_actual.length();j++)
        {
            if(nodo_actual[j] == valor_de_los_huecos)
            {
                
                int fila_en_la_que_se_encuentra_el_hueco = j/dimension;
                int columna_en_la_que_se_encuentra_el_hueco = abs(j - (fila_en_la_que_se_encuentra_el_hueco * (int)dimension));
                
                if(columna_en_la_que_se_encuentra_el_hueco + 1 < dimension) //movimiento a la derecha
                {
                    informacion_del_vecino.nombre_del_nodo = nodo_actual;
                    valor_en_la_otra_columna = nodo_actual[j+1];
                    if(valor_en_la_otra_columna != valor_de_los_huecos)
                    {
                        informacion_del_vecino.nombre_del_nodo[j] = valor_en_la_otra_columna;
                        informacion_del_vecino.nombre_del_nodo[j+1] = valor_de_los_huecos;
                        vecinos.push_back(informacion_del_vecino);
                    }
                }
                
                if(columna_en_la_que_se_encuentra_el_hueco - 1 >= 0) //movimiento a la izquierda
                {
                    
                    informacion_del_vecino.nombre_del_nodo = nodo_actual;
                    valor_en_la_otra_columna = nodo_actual[j-1];
                    if(valor_en_la_otra_columna != valor_de_los_huecos)
                    {
                        informacion_del_vecino.nombre_del_nodo[j] = valor_en_la_otra_columna;
                        informacion_del_vecino.nombre_del_nodo[j-1] = valor_de_los_huecos;
                        vecinos.push_back(informacion_del_vecino);
                    }
                    
                    
                }
                
                if(fila_en_la_que_se_encuentra_el_hueco + 1 < dimension) //movimiento hacia abajo
                {
                    informacion_del_vecino.nombre_del_nodo = nodo_actual;
                    valor_en_la_otra_fila = nodo_actual[j+dimension];
                    if(valor_en_la_otra_fila != valor_de_los_huecos)
                    {
                        informacion_del_vecino.nombre_del_nodo[j] = valor_en_la_otra_fila;
                        informacion_del_vecino.nombre_del_nodo[j+dimension] = valor_de_los_huecos;
                        vecinos.push_back(informacion_del_vecino);
                    }
                    
                }
                
                if(fila_en_la_que_se_encuentra_el_hueco - 1 >= 0) //movimiento hacia arriba
                {
                    
                    informacion_del_vecino.nombre_del_nodo = nodo_actual;
                    valor_en_la_otra_fila = nodo_actual[j-dimension];
                    if(valor_en_la_otra_fila != valor_de_los_huecos)
                    {
                        informacion_del_vecino.nombre_del_nodo[j] = valor_en_la_otra_fila;
                        informacion_del_vecino.nombre_del_nodo[j-dimension] = valor_de_los_huecos;
                        vecinos.push_back(informacion_del_vecino);
                    }
                    
                }
                
                break;
            }
            
        }
    }
    
    else
    {
        
        
        for(int j = 0; j < nodo_actual.length();j++)
        {
            if(nodo_actual[j] == valor_de_los_huecos)
            {
                
                int fila_en_la_que_se_encuentra_el_hueco = j/dimension;
                int columna_en_la_que_se_encuentra_el_hueco = abs(j - (fila_en_la_que_se_encuentra_el_hueco * (int)dimension));
                
                if(columna_en_la_que_se_encuentra_el_hueco + 1 < dimension) //movimiento a la derecha
                {
                    informacion_del_vecino.nombre_del_nodo = nodo_actual;
                    valor_en_la_otra_columna = nodo_actual[j+1];
                    if(valor_en_la_otra_columna != valor_de_los_huecos)
                    {
                        informacion_del_vecino.nombre_del_nodo[j] = valor_en_la_otra_columna;
                        informacion_del_vecino.nombre_del_nodo[j+1] = valor_de_los_huecos;
                        vecinos.push_back(informacion_del_vecino);
                    }
                }
                
                if(columna_en_la_que_se_encuentra_el_hueco - 1 >= 0) //movimiento a la izquierda
                {
                    
                    informacion_del_vecino.nombre_del_nodo = nodo_actual;
                    valor_en_la_otra_columna = nodo_actual[j-1];
                    if(valor_en_la_otra_columna != valor_de_los_huecos)
                    {
                        informacion_del_vecino.nombre_del_nodo[j] = valor_en_la_otra_columna;
                        informacion_del_vecino.nombre_del_nodo[j-1] = valor_de_los_huecos;
                        vecinos.push_back(informacion_del_vecino);
                    }
                    
                    
                }
                
                if(fila_en_la_que_se_encuentra_el_hueco + 1 < dimension) //movimiento hacia abajo
                {
                    informacion_del_vecino.nombre_del_nodo = nodo_actual;
                    valor_en_la_otra_fila = nodo_actual[j+dimension];
                    if(valor_en_la_otra_fila != valor_de_los_huecos)
                    {
                        informacion_del_vecino.nombre_del_nodo[j] = valor_en_la_otra_fila;
                        informacion_del_vecino.nombre_del_nodo[j+dimension] = valor_de_los_huecos;
                        vecinos.push_back(informacion_del_vecino);
                    }
                    
                }
                
                if(fila_en_la_que_se_encuentra_el_hueco - 1 >= 0) //movimiento hacia arriba
                {
                    
                    informacion_del_vecino.nombre_del_nodo = nodo_actual;
                    valor_en_la_otra_fila = nodo_actual[j-dimension];
                    if(valor_en_la_otra_fila != valor_de_los_huecos)
                    {
                        informacion_del_vecino.nombre_del_nodo[j] = valor_en_la_otra_fila;
                        informacion_del_vecino.nombre_del_nodo[j-dimension] = valor_de_los_huecos;
                        vecinos.push_back(informacion_del_vecino);
                    }
                    
                }
                
                break;
            }
            
        }
        
        
        for(int j = (int)nodo_actual.length()-1; j >= 0;j--)
        {
            if(nodo_actual[j] == valor_de_los_huecos)
            {
                
                int fila_en_la_que_se_encuentra_el_hueco = j/dimension;
                int columna_en_la_que_se_encuentra_el_hueco = abs(j - (fila_en_la_que_se_encuentra_el_hueco * (int)dimension));
                
                if(columna_en_la_que_se_encuentra_el_hueco + 1 < dimension) //movimiento a la derecha
                {
                    informacion_del_vecino.nombre_del_nodo = nodo_actual;
                    valor_en_la_otra_columna = nodo_actual[j+1];
                    if(valor_en_la_otra_columna != valor_de_los_huecos)
                    {
                        informacion_del_vecino.nombre_del_nodo[j] = valor_en_la_otra_columna;
                        informacion_del_vecino.nombre_del_nodo[j+1] = valor_de_los_huecos;
                        vecinos.push_back(informacion_del_vecino);
                    }
                }
                
                if(columna_en_la_que_se_encuentra_el_hueco - 1 >= 0) //movimiento a la izquierda
                {
                    
                    informacion_del_vecino.nombre_del_nodo = nodo_actual;
                    valor_en_la_otra_columna = nodo_actual[j-1];
                    if(valor_en_la_otra_columna != valor_de_los_huecos)
                    {
                        informacion_del_vecino.nombre_del_nodo[j] = valor_en_la_otra_columna;
                        informacion_del_vecino.nombre_del_nodo[j-1] = valor_de_los_huecos;
                        vecinos.push_back(informacion_del_vecino);
                    }
                    
                    
                }
                
                if(fila_en_la_que_se_encuentra_el_hueco + 1 < dimension) //movimiento hacia abajo
                {
                    informacion_del_vecino.nombre_del_nodo = nodo_actual;
                    valor_en_la_otra_fila = nodo_actual[j+dimension];
                    if(valor_en_la_otra_fila != valor_de_los_huecos)
                    {
                        informacion_del_vecino.nombre_del_nodo[j] = valor_en_la_otra_fila;
                        informacion_del_vecino.nombre_del_nodo[j+dimension] = valor_de_los_huecos;
                        vecinos.push_back(informacion_del_vecino);
                    }
                    
                }
                
                if(fila_en_la_que_se_encuentra_el_hueco - 1 >= 0) //movimiento hacia arriba
                {
                    
                    informacion_del_vecino.nombre_del_nodo = nodo_actual;
                    valor_en_la_otra_fila = nodo_actual[j-dimension];
                    if(valor_en_la_otra_fila != valor_de_los_huecos)
                    {
                        informacion_del_vecino.nombre_del_nodo[j] = valor_en_la_otra_fila;
                        informacion_del_vecino.nombre_del_nodo[j-dimension] = valor_de_los_huecos;
                        vecinos.push_back(informacion_del_vecino);
                    }
                    
                }
                
                break;
            }
            
        }
        
    }
    
            
}



//---------------------------------------------------------------------------------------------------------------

bool PuzzleSolver::busqueda_primero_el_mejor(const vector <vector <unsigned int>> pEstado_inicial, const vector <vector <unsigned int>> pEstado_final, int& nodo_encontrado)
{
    srand((unsigned int) time(NULL));
    arbol_de_busqueda.limpia_arbol();
    agenda.limpia_agenda();

    huecos.clear();
    nodo_encontrado = -1;



    unsigned int t1 = (unsigned int) clock(), t2 = 0;
    string inicio = "";
    string meta = "";
    int id_hueco = -1;
    
    dimension =  (unsigned int)pEstado_inicial[0].size();
    estado_inicial.clear();
    estado_inicial.assign(dimension, {});
    
    //A nuestro vector estado inicial le cambiamos los ceros por identificadores negativos
    for (unsigned int i = 0; i < pEstado_inicial.size();i++)
        for (unsigned int j = 0; j < pEstado_inicial[i].size();j++)
        {
            inicio  += (char) entero_con_el_que_comienza_el_casteo + pEstado_inicial[i][j];
            meta += (char) entero_con_el_que_comienza_el_casteo + pEstado_final[i][j];
            if(pEstado_inicial[i][j] == 0)
            {
                huecos.push_back(id_hueco);
                estado_inicial[i].push_back(id_hueco);
                id_hueco--;
                continue;
            }
            estado_inicial[i].push_back(pEstado_inicial[i][j]);
        }

    
    
    tipo_nodo_informacion nodo_raiz;
    nodo_raiz.nombre_del_nodo = inicio;
    nodo_raiz.costo_estimado = calcula_heuristica_a_la_meta(nodo_raiz.nombre_del_nodo,meta);
    nodo_raiz.numero_a_colocar = devuelve_numero_a_colocar_en_su_posicion(nodo_raiz.nombre_del_nodo, meta);

    arbol_de_busqueda.crea_arbol(nodo_raiz);
    Arbol_Binario arbol_binario = Arbol_Binario();
    arbol_binario.push(inicio,0);

    informacion_en_agenda informacion_para_la_agenda_del_nodo_raiz;

    informacion_para_la_agenda_del_nodo_raiz.nodo = 0;
    informacion_para_la_agenda_del_nodo_raiz.costo_estimado = nodo_raiz.costo_estimado;
    informacion_para_la_agenda_del_nodo_raiz.numero_a_colocar = nodo_raiz.numero_a_colocar;
    agenda.push_back(informacion_para_la_agenda_del_nodo_raiz);

    tipo_nodo_informacion informacion_del_hijo_a_adicionar;
    informacion_en_agenda informacion_del_nodo_hijo_para_la_agenda;
    unsigned int mejor_nodo = 0;
    unsigned int posicion_del_mejor_nodo = 0;
    unsigned int costo_estimado_del_mejor_nodo = 0;
    unsigned int costo_acumulado_del_mejor_nodo = 0;
    unsigned int numero_a_colocar_del_mejor_nodo = 0;
    vector<tipo_nodo_informacion> vecinos;

    while(!agenda.esta_vacia())
    {
        mejor_nodo = agenda[0].nodo;
        posicion_del_mejor_nodo = 0;
        costo_estimado_del_mejor_nodo = agenda[0].costo_estimado;
        costo_acumulado_del_mejor_nodo = agenda[0].costo_acumulado;
        numero_a_colocar_del_mejor_nodo = agenda[0].numero_a_colocar;
        for (unsigned int i = 1; i < agenda.size(); i++)
            if (costo_estimado_del_mejor_nodo > agenda[i].costo_estimado)
            {
                mejor_nodo = agenda[i].nodo;
                posicion_del_mejor_nodo = i;
                costo_estimado_del_mejor_nodo = agenda[i].costo_estimado;
                costo_acumulado_del_mejor_nodo = agenda[i].costo_acumulado;
                numero_a_colocar_del_mejor_nodo = agenda[i].numero_a_colocar;
            }
        
        for(unsigned int i = 0; i < agenda.size();i++)
            if(costo_estimado_del_mejor_nodo == agenda[i].costo_estimado && agenda[i].costo_acumulado < costo_acumulado_del_mejor_nodo)
            {
                mejor_nodo = agenda[i].nodo;
                posicion_del_mejor_nodo = i;
                costo_estimado_del_mejor_nodo = agenda[i].costo_estimado;
                costo_acumulado_del_mejor_nodo = agenda[i].costo_acumulado;
                numero_a_colocar_del_mejor_nodo = agenda[i].numero_a_colocar;
            }
        
        
        agenda.erase(posicion_del_mejor_nodo);
        
        
        
        
        if (arbol_de_busqueda[mejor_nodo].contenido.nombre_del_nodo == meta)
        {

            nodo_encontrado = mejor_nodo;
            t2 = (unsigned int)clock();
            cout << "Tiempo de busqueda: " << (double(t2 - t1) / CLOCKS_PER_SEC) << " segundos" << endl;
            return true;
        }

        vecinos.clear();
        devuelve_vecinos(arbol_de_busqueda[mejor_nodo].contenido.nombre_del_nodo, vecinos);
        

        for(unsigned int i = 0; i < vecinos.size();i++)
            if(!arbol_binario.push(vecinos[i].nombre_del_nodo,costo_acumulado_del_mejor_nodo+1))
            {
                vecinos.erase(vecinos.begin()+i);
                i--;
            }

        
        
        
        
        for(unsigned int i = 0; i < vecinos.size();i++)
        {
            informacion_del_hijo_a_adicionar.nombre_del_nodo = vecinos[i].nombre_del_nodo;
            informacion_del_hijo_a_adicionar.costo_acumulado = costo_acumulado_del_mejor_nodo + 1;
            informacion_del_hijo_a_adicionar.costo_estimado = calcula_heuristica_a_la_meta(informacion_del_hijo_a_adicionar.nombre_del_nodo,meta);
            informacion_del_hijo_a_adicionar.numero_a_colocar = devuelve_numero_a_colocar_en_su_posicion(informacion_del_hijo_a_adicionar.nombre_del_nodo, meta);
            arbol_de_busqueda.agrega_hijo_a_un_nodo_del_arbol(mejor_nodo, informacion_del_hijo_a_adicionar);
            informacion_del_nodo_hijo_para_la_agenda.nodo = arbol_de_busqueda.size() -1;
            informacion_del_nodo_hijo_para_la_agenda.costo_acumulado = informacion_del_hijo_a_adicionar.costo_acumulado;
            informacion_del_nodo_hijo_para_la_agenda.costo_estimado = informacion_del_hijo_a_adicionar.costo_estimado;
            informacion_del_nodo_hijo_para_la_agenda.costo_acumulado = informacion_del_hijo_a_adicionar.costo_acumulado;
            informacion_del_nodo_hijo_para_la_agenda.numero_a_colocar = informacion_del_hijo_a_adicionar.numero_a_colocar;
            agenda.push_back(informacion_del_nodo_hijo_para_la_agenda);
        }
        
        agenda.revisa_tamano_maximo_de_la_agenda();

        if (agenda.esta_vacia())
        {
            t2 = (unsigned int)clock();
            cout << "Tiempo de busqueda: " << (double(t2 - t1) / CLOCKS_PER_SEC) << " segundos" << endl;
            return nodo_encontrado != -1;
        }
        
    }


    t2 = (unsigned int)clock();
    cout << "Tiempo de busqueda: " << (double(t2 - t1) / CLOCKS_PER_SEC) << " segundos" << endl;


    return nodo_encontrado != -1;
}


//-----------------------------------------------------------------------------------------------------------------


bool PuzzleSolver::busqueda_primero_el_mejor(string archivo,string archivo_solucion, int& nodo_encontrado)
{
    srand((unsigned int) time(NULL));
    arbol_de_busqueda.limpia_arbol();
    agenda.limpia_agenda();

    huecos.clear();
    nodo_encontrado = -1;


    unsigned int t1 = (unsigned int) clock(), t2 = 0;
    string inicio = "";
    string meta = "";


    
    estado_inicial.clear();
    vector < vector <int>> estado_final = lee_archivo(archivo);
    
    if(estado_final.size() != 0)
    {
        dimension =  (unsigned int)estado_inicial[0].size();
        int id_hueco = -1;
        
        //A nuestro vector estado inicial le cambiamos los ceros por identificadores negativos
        //A nuestro vector estado inicial le cambiamos los ceros por identificadores negativos
        for (unsigned int i = 0; i < estado_inicial.size();i++)
            for (unsigned int j = 0; j < estado_inicial[i].size();j++)
            {
                inicio  += (char) entero_con_el_que_comienza_el_casteo + estado_inicial[i][j];
                meta += (char) entero_con_el_que_comienza_el_casteo + estado_final[i][j];
                if(estado_inicial[i][j] == 0)
                {
                    huecos.push_back(id_hueco);
                    estado_inicial[i][j] = id_hueco;
                    id_hueco--;
                    continue;
                }
            }

        
        
        tipo_nodo_informacion nodo_raiz;
        nodo_raiz.nombre_del_nodo = inicio;
        nodo_raiz.costo_estimado = calcula_heuristica_a_la_meta(nodo_raiz.nombre_del_nodo,meta);
        nodo_raiz.numero_a_colocar = devuelve_numero_a_colocar_en_su_posicion(inicio, meta);
        
        arbol_de_busqueda.crea_arbol(nodo_raiz);
        Arbol_Binario arbol_binario = Arbol_Binario();
        arbol_binario.push(inicio,0);
        
        informacion_en_agenda informacion_para_la_agenda_del_nodo_raiz;
        
        informacion_para_la_agenda_del_nodo_raiz.nodo = 0;
        informacion_para_la_agenda_del_nodo_raiz.costo_estimado = nodo_raiz.costo_estimado;
        informacion_para_la_agenda_del_nodo_raiz.numero_a_colocar = nodo_raiz.numero_a_colocar;
        agenda.push_back(informacion_para_la_agenda_del_nodo_raiz);
        
        tipo_nodo_informacion informacion_del_hijo_a_adicionar;
        informacion_en_agenda informacion_del_nodo_hijo_para_la_agenda;
        unsigned int mejor_nodo = 0;
        unsigned int posicion_del_mejor_nodo = 0;
        unsigned int costo_estimado_del_mejor_nodo = 0;
        unsigned int costo_acumulado_del_mejor_nodo = 0;
        unsigned int numero_a_colocar_del_mejor_nodo = 0;
        vector<tipo_nodo_informacion> vecinos;
        
        while(!agenda.esta_vacia())
        {
            mejor_nodo = agenda[0].nodo;
            posicion_del_mejor_nodo = 0;
            costo_estimado_del_mejor_nodo = agenda[0].costo_estimado;
            costo_acumulado_del_mejor_nodo = agenda[0].costo_acumulado;
            numero_a_colocar_del_mejor_nodo = agenda[0].numero_a_colocar;
            for (unsigned int i = 1; i < agenda.size(); i++)
                if (costo_estimado_del_mejor_nodo > agenda[i].costo_estimado)
                {
                    mejor_nodo = agenda[i].nodo;
                    posicion_del_mejor_nodo = i;
                    costo_estimado_del_mejor_nodo = agenda[i].costo_estimado;
                    costo_acumulado_del_mejor_nodo = agenda[i].costo_acumulado;
                    numero_a_colocar_del_mejor_nodo = agenda[i].numero_a_colocar;
                }
            
            for(unsigned int i = 0; i < agenda.size();i++)
                if(costo_estimado_del_mejor_nodo == agenda[i].costo_estimado && agenda[i].costo_acumulado < costo_acumulado_del_mejor_nodo)
                {
                    mejor_nodo = agenda[i].nodo;
                    posicion_del_mejor_nodo = i;
                    costo_estimado_del_mejor_nodo = agenda[i].costo_estimado;
                    costo_acumulado_del_mejor_nodo = agenda[i].costo_acumulado;
                    numero_a_colocar_del_mejor_nodo = agenda[i].numero_a_colocar;
                }
            

                
            
            agenda.erase(posicion_del_mejor_nodo);
            
            
            
            
            if (arbol_de_busqueda[mejor_nodo].contenido.nombre_del_nodo == meta)
            {
                nodo_encontrado = mejor_nodo;
                t2 = (unsigned int)clock();
                double tiempo = (double(t2 - t1) / CLOCKS_PER_SEC);
                cout << "Tiempo de busqueda: " << tiempo << " segundos" << endl;
                escribe_en_archivo(archivo_solucion, tiempo, nodo_encontrado);
                return true;
            }
            
            vecinos.clear();
            devuelve_vecinos(arbol_de_busqueda[mejor_nodo].contenido.nombre_del_nodo, vecinos);
            

            for(unsigned int i = 0; i < vecinos.size();i++)
                if(!arbol_binario.push(vecinos[i].nombre_del_nodo,costo_acumulado_del_mejor_nodo + 1))
                {
                    vecinos.erase(vecinos.begin()+i);
                    i--;
                }
            
            
            
            
            for(unsigned int i = 0; i < vecinos.size();i++)
            {
                informacion_del_hijo_a_adicionar.costo_acumulado = costo_acumulado_del_mejor_nodo + 1;
                informacion_del_hijo_a_adicionar.nombre_del_nodo = vecinos[i].nombre_del_nodo;
                informacion_del_hijo_a_adicionar.costo_estimado = calcula_heuristica_a_la_meta(informacion_del_hijo_a_adicionar.nombre_del_nodo,meta);
                informacion_del_hijo_a_adicionar.numero_a_colocar = devuelve_numero_a_colocar_en_su_posicion(informacion_del_hijo_a_adicionar.nombre_del_nodo, meta);
                arbol_de_busqueda.agrega_hijo_a_un_nodo_del_arbol(mejor_nodo, informacion_del_hijo_a_adicionar);
                informacion_del_nodo_hijo_para_la_agenda.nodo = arbol_de_busqueda.size() -1;
                informacion_del_nodo_hijo_para_la_agenda.costo_acumulado = informacion_del_hijo_a_adicionar.costo_acumulado;
                informacion_del_nodo_hijo_para_la_agenda.costo_estimado = informacion_del_hijo_a_adicionar.costo_estimado;
                informacion_del_nodo_hijo_para_la_agenda.numero_a_colocar = informacion_del_hijo_a_adicionar.numero_a_colocar;
                agenda.push_back(informacion_del_nodo_hijo_para_la_agenda);
            }
            
            agenda.revisa_tamano_maximo_de_la_agenda();
            
            if (agenda.esta_vacia())
            {
                t2 = (unsigned int)clock();
                cout << "Tiempo de busqueda: " << (double(t2 - t1) / CLOCKS_PER_SEC) << " segundos" << endl;
                return nodo_encontrado != -1;
            }
            
        }
        
    }
    t2 = (unsigned int)clock();
    cout << "Tiempo de busqueda: " << (double(t2 - t1) / CLOCKS_PER_SEC) << " segundos" << endl;
    return nodo_encontrado != -1;
}








//--------------------------------------------------------------------------------------------------------------------




//---------------------------------------------------------------------------------------------------------------

bool PuzzleSolver::busqueda_A_ESTRELLA(const vector <vector <unsigned int>> pEstado_inicial, const vector <vector <unsigned int>> pEstado_final, int& nodo_encontrado)
{
    srand((unsigned int) time(NULL));
    arbol_de_busqueda.limpia_arbol();
    agenda.limpia_agenda();
    huecos.clear();
    nodo_encontrado = -1;



    unsigned int t1 = (unsigned int) clock(), t2 = 0;
    string inicio = "";
    string meta = "";
    int id_hueco = -1;
    
    dimension =  (unsigned int)pEstado_inicial[0].size();
    estado_inicial.clear();
    estado_inicial.assign(dimension, {});
    
    //A nuestro vector estado inicial le cambiamos los ceros por identificadores negativos
    for (unsigned int i = 0; i < pEstado_inicial.size();i++)
        for (unsigned int j = 0; j < pEstado_inicial[i].size();j++)
        {
            inicio  += (char) entero_con_el_que_comienza_el_casteo + pEstado_inicial[i][j];
            meta += (char) entero_con_el_que_comienza_el_casteo + pEstado_final[i][j];
            if(pEstado_inicial[i][j] == 0)
            {
                huecos.push_back(id_hueco);
                estado_inicial[i].push_back(id_hueco);
                id_hueco--;
                continue;
            }
            estado_inicial[i].push_back(pEstado_inicial[i][j]);
        }

    
    
    tipo_nodo_informacion nodo_raiz;
    nodo_raiz.nombre_del_nodo = inicio;
    nodo_raiz.costo_estimado = calcula_heuristica_a_la_meta(nodo_raiz.nombre_del_nodo,meta);
    nodo_raiz.numero_a_colocar = devuelve_numero_a_colocar_en_su_posicion(nodo_raiz.nombre_del_nodo, meta);

    arbol_de_busqueda.crea_arbol(nodo_raiz);
    Arbol_Binario arbol_binario = Arbol_Binario();
    arbol_binario.push(inicio,0);

    informacion_en_agenda informacion_para_la_agenda_del_nodo_raiz;

    informacion_para_la_agenda_del_nodo_raiz.nodo = 0;
    informacion_para_la_agenda_del_nodo_raiz.costo_estimado = nodo_raiz.costo_estimado;
    informacion_para_la_agenda_del_nodo_raiz.numero_a_colocar = nodo_raiz.numero_a_colocar;
    agenda.push_back(informacion_para_la_agenda_del_nodo_raiz);

    tipo_nodo_informacion informacion_del_hijo_a_adicionar;
    informacion_en_agenda informacion_del_nodo_hijo_para_la_agenda;
    unsigned int mejor_nodo = 0;
    unsigned int posicion_del_mejor_nodo = 0;
    unsigned int costo_estimado_del_mejor_nodo = 0;
    unsigned int costo_acumulado_del_mejor_nodo = 0;
    unsigned int numero_a_colocar_del_mejor_nodo = 0;
    int meta_temporal = -1;
    vector<tipo_nodo_informacion> vecinos;

    while(!agenda.esta_vacia())
    {
        mejor_nodo = agenda[0].nodo;
        posicion_del_mejor_nodo = 0;
        costo_estimado_del_mejor_nodo = agenda[0].costo_estimado;
        costo_acumulado_del_mejor_nodo = agenda[0].costo_acumulado;
        numero_a_colocar_del_mejor_nodo = agenda[0].numero_a_colocar;
        for (unsigned int i = 1; i < agenda.size(); i++)
        {
            if (costo_estimado_del_mejor_nodo + costo_acumulado_del_mejor_nodo > agenda[i].costo_estimado + agenda[i].costo_acumulado)
            {
                mejor_nodo = agenda[i].nodo;
                posicion_del_mejor_nodo = i;
                costo_estimado_del_mejor_nodo = agenda[i].costo_estimado;
                costo_acumulado_del_mejor_nodo = agenda[i].costo_acumulado;
                numero_a_colocar_del_mejor_nodo = agenda[i].numero_a_colocar;
            }
        }
        
        
        agenda.erase(posicion_del_mejor_nodo);
        
        
        
        
        if (arbol_de_busqueda[mejor_nodo].contenido.nombre_del_nodo == meta)
        {
            if (meta_temporal == -1)
                meta_temporal = mejor_nodo;
            else if (arbol_de_busqueda[meta_temporal].contenido.costo_acumulado >
                arbol_de_busqueda[mejor_nodo].contenido.costo_acumulado)
                meta_temporal = mejor_nodo;
            for (unsigned int i = 0; i < agenda.size(); i++)
                if (agenda[i].costo_acumulado >=
                    arbol_de_busqueda[meta_temporal].contenido.costo_acumulado)
                {
                    agenda.erase(i);
                    i--;
                }
            
            if(agenda.esta_vacia())
            {
                nodo_encontrado = meta_temporal;
                t2 = (unsigned int)clock();
                cout << "Tiempo de busqueda: " << (double(t2 - t1) / CLOCKS_PER_SEC) << " segundos" << endl;
                return true;
            }
        }

        vecinos.clear();
        devuelve_vecinos(arbol_de_busqueda[mejor_nodo].contenido.nombre_del_nodo, vecinos);
        
        
        

        for(unsigned int i = 0; i < vecinos.size();i++)
            if(!arbol_binario.push(vecinos[i].nombre_del_nodo,costo_acumulado_del_mejor_nodo+1))
            {
                vecinos.erase(vecinos.begin()+i);
                i--;
            }


        for(unsigned int i = 0; i < vecinos.size();i++)
        {
            informacion_del_hijo_a_adicionar.nombre_del_nodo = vecinos[i].nombre_del_nodo;
            informacion_del_hijo_a_adicionar.costo_acumulado = costo_acumulado_del_mejor_nodo + 1;
            if (meta_temporal != -1)
                if (informacion_del_hijo_a_adicionar.costo_acumulado > arbol_de_busqueda[meta_temporal].contenido.costo_acumulado)
                    continue;
            informacion_del_hijo_a_adicionar.costo_estimado = calcula_heuristica_a_la_meta(informacion_del_hijo_a_adicionar.nombre_del_nodo,meta);
            informacion_del_hijo_a_adicionar.numero_a_colocar = devuelve_numero_a_colocar_en_su_posicion(informacion_del_hijo_a_adicionar.nombre_del_nodo, meta);
            arbol_de_busqueda.agrega_hijo_a_un_nodo_del_arbol(mejor_nodo, informacion_del_hijo_a_adicionar);
            informacion_del_nodo_hijo_para_la_agenda.nodo = arbol_de_busqueda.size() -1;
            informacion_del_nodo_hijo_para_la_agenda.costo_acumulado = informacion_del_hijo_a_adicionar.costo_acumulado;
            informacion_del_nodo_hijo_para_la_agenda.costo_estimado = informacion_del_hijo_a_adicionar.costo_estimado;
            informacion_del_nodo_hijo_para_la_agenda.costo_acumulado = informacion_del_hijo_a_adicionar.costo_acumulado;
            informacion_del_nodo_hijo_para_la_agenda.numero_a_colocar = informacion_del_hijo_a_adicionar.numero_a_colocar;
            agenda.push_back(informacion_del_nodo_hijo_para_la_agenda);
        }
        
        agenda.revisa_tamano_maximo_de_la_agenda();

        if (agenda.esta_vacia())
        {
            nodo_encontrado = meta_temporal;
            t2 = (unsigned int)clock();
            cout << "Tiempo de busqueda: " << (double(t2 - t1) / CLOCKS_PER_SEC) << " segundos" << endl;
            return nodo_encontrado != -1;
        }
        
    }

    nodo_encontrado = meta_temporal;
    t2 = (unsigned int)clock();
    cout << "Tiempo de busqueda: " << (double(t2 - t1) / CLOCKS_PER_SEC) << " segundos" << endl;


    return nodo_encontrado != -1;
}


//-----------------------------------------------------------------------------------------------------------------


bool PuzzleSolver::busqueda_A_ESTRELLA(string archivo,string archivo_solucion, int& nodo_encontrado)
{
    srand((unsigned int) time(NULL));
    arbol_de_busqueda.limpia_arbol();
    agenda.limpia_agenda();

    huecos.clear();
    nodo_encontrado = -1;
    int meta_temporal = -1;


    unsigned int t1 = (unsigned int) clock(), t2 = 0;
    string inicio = "";
    string meta = "";


    
    estado_inicial.clear();
    vector < vector <int>> estado_final = lee_archivo(archivo);
    
    if(estado_final.size() != 0)
    {
        dimension =  (unsigned int)estado_inicial[0].size();
        int id_hueco = -1;
        
        //A nuestro vector estado inicial le cambiamos los ceros por identificadores negativos
        //A nuestro vector estado inicial le cambiamos los ceros por identificadores negativos
        for (unsigned int i = 0; i < estado_inicial.size();i++)
            for (unsigned int j = 0; j < estado_inicial[i].size();j++)
            {
                inicio  += (char) entero_con_el_que_comienza_el_casteo + estado_inicial[i][j];
                meta += (char) entero_con_el_que_comienza_el_casteo + estado_final[i][j];
                if(estado_inicial[i][j] == 0)
                {
                    huecos.push_back(id_hueco);
                    estado_inicial[i][j] = id_hueco;
                    id_hueco--;
                    continue;
                }
            }
        
        
        
        tipo_nodo_informacion nodo_raiz;
        nodo_raiz.nombre_del_nodo = inicio;
        nodo_raiz.costo_estimado = calcula_heuristica_a_la_meta(nodo_raiz.nombre_del_nodo,meta);
        nodo_raiz.numero_a_colocar = devuelve_numero_a_colocar_en_su_posicion(inicio, meta);
        
        
        arbol_de_busqueda.crea_arbol(nodo_raiz);
        Arbol_Binario arbol_binario = Arbol_Binario();
        arbol_binario.push(inicio,0);
        
        informacion_en_agenda informacion_para_la_agenda_del_nodo_raiz;
        
        informacion_para_la_agenda_del_nodo_raiz.nodo = 0;
        informacion_para_la_agenda_del_nodo_raiz.costo_estimado = nodo_raiz.costo_estimado;
        informacion_para_la_agenda_del_nodo_raiz.numero_a_colocar = nodo_raiz.numero_a_colocar;
        agenda.push_back(informacion_para_la_agenda_del_nodo_raiz);
        
        tipo_nodo_informacion informacion_del_hijo_a_adicionar;
        informacion_en_agenda informacion_del_nodo_hijo_para_la_agenda;
        unsigned int mejor_nodo = 0;
        unsigned int posicion_del_mejor_nodo = 0;
        unsigned int costo_estimado_del_mejor_nodo = 0;
        unsigned int costo_acumulado_del_mejor_nodo = 0;
        unsigned int numero_a_colocar_del_mejor_nodo = 0;
        vector<tipo_nodo_informacion> vecinos;
        
        while(!agenda.esta_vacia())
        {
            mejor_nodo = agenda[0].nodo;
            posicion_del_mejor_nodo = 0;
            costo_estimado_del_mejor_nodo = agenda[0].costo_estimado;
            costo_acumulado_del_mejor_nodo = agenda[0].costo_acumulado;
            numero_a_colocar_del_mejor_nodo = agenda[0].numero_a_colocar;
            

            for (unsigned int i = 1; i < agenda.size(); i++)
            {
                if (costo_estimado_del_mejor_nodo + costo_acumulado_del_mejor_nodo > agenda[i].costo_estimado + agenda[i].costo_acumulado)
                {
                    mejor_nodo = agenda[i].nodo;
                    posicion_del_mejor_nodo = i;
                    costo_estimado_del_mejor_nodo = agenda[i].costo_estimado;
                    costo_acumulado_del_mejor_nodo = agenda[i].costo_acumulado;
                    numero_a_colocar_del_mejor_nodo = agenda[i].numero_a_colocar;
                }
            }
            
            agenda.erase(posicion_del_mejor_nodo);
            
            
            
            if (arbol_de_busqueda[mejor_nodo].contenido.nombre_del_nodo == meta)
            {
                if (meta_temporal == -1)
                    meta_temporal = mejor_nodo;
                else if (arbol_de_busqueda[meta_temporal].contenido.costo_acumulado >
                         arbol_de_busqueda[mejor_nodo].contenido.costo_acumulado)
                    meta_temporal = mejor_nodo;
                for (unsigned int i = 0; i < agenda.size(); i++)
                    if (agenda[i].costo_acumulado >=
                        arbol_de_busqueda[meta_temporal].contenido.costo_acumulado)
                    {
                        agenda.erase(i);
                        i--;
                    }
                
                
                if(agenda.esta_vacia())
                {
                    nodo_encontrado = meta_temporal;
                    t2 = (unsigned int)clock();
                    double tiempo = (double(t2 - t1) / CLOCKS_PER_SEC);
                    cout << "Tiempo de busqueda: " << tiempo << " segundos" << endl;
                    escribe_en_archivo(archivo_solucion, tiempo, nodo_encontrado);
                    return true;
                }
            }
            
            
            vecinos.clear();
            devuelve_vecinos(arbol_de_busqueda[mejor_nodo].contenido.nombre_del_nodo, vecinos);
            
            
            
            
            for(unsigned int i = 0; i < vecinos.size();i++)
                if(!arbol_binario.push(vecinos[i].nombre_del_nodo,costo_acumulado_del_mejor_nodo+1))
                {
                    vecinos.erase(vecinos.begin()+i);
                    i--;
                }
            
            
            for(unsigned int i = 0; i < vecinos.size();i++)
            {
                informacion_del_hijo_a_adicionar.nombre_del_nodo = vecinos[i].nombre_del_nodo;
                informacion_del_hijo_a_adicionar.costo_acumulado = costo_acumulado_del_mejor_nodo + 1;
                if (meta_temporal != -1)
                    if (informacion_del_hijo_a_adicionar.costo_acumulado > arbol_de_busqueda[meta_temporal].contenido.costo_acumulado)
                        continue;
                informacion_del_hijo_a_adicionar.costo_estimado = calcula_heuristica_a_la_meta(informacion_del_hijo_a_adicionar.nombre_del_nodo,meta);
                arbol_de_busqueda.agrega_hijo_a_un_nodo_del_arbol(mejor_nodo, informacion_del_hijo_a_adicionar);
                informacion_del_nodo_hijo_para_la_agenda.nodo = arbol_de_busqueda.size() -1;
                informacion_del_nodo_hijo_para_la_agenda.costo_acumulado = informacion_del_hijo_a_adicionar.costo_acumulado;
                informacion_del_nodo_hijo_para_la_agenda.costo_estimado = informacion_del_hijo_a_adicionar.costo_estimado;
                informacion_del_nodo_hijo_para_la_agenda.costo_acumulado = informacion_del_hijo_a_adicionar.costo_acumulado;
                informacion_del_nodo_hijo_para_la_agenda.numero_a_colocar = informacion_del_hijo_a_adicionar.numero_a_colocar;
                agenda.push_back(informacion_del_nodo_hijo_para_la_agenda);
            }
            
            agenda.revisa_tamano_maximo_de_la_agenda();
            
            if (agenda.esta_vacia())
            {
                nodo_encontrado = meta_temporal;
                t2 = (unsigned int)clock();
                double tiempo = (double(t2 - t1) / CLOCKS_PER_SEC);
                cout << "Tiempo de busqueda: " << tiempo << " segundos" << endl;
                escribe_en_archivo(archivo_solucion, tiempo, nodo_encontrado);
                
                return nodo_encontrado != -1;
            }
            
        }
        
        nodo_encontrado = meta_temporal;
        t2 = (unsigned int)clock();
        double tiempo = (double(t2 - t1) / CLOCKS_PER_SEC);
        cout << "Tiempo de busqueda: " << tiempo << " segundos" << endl;
        escribe_en_archivo(archivo_solucion, tiempo, nodo_encontrado);
    }
        
    return nodo_encontrado != -1;
}





//--------------------------------------------------------------------------------------------------------------------



unsigned int PuzzleSolver:: devuelve_numero_a_colocar_en_su_posicion(string nodo_actual,string meta)
{
    unsigned int numero_a_colocar = 0;
    
    for (int i = 0; i < nodo_actual.length();i++)
        if(nodo_actual[i]!=meta[i])
            return numero_a_colocar = i + 1;
    
    return numero_a_colocar;
}


//--------------------------------------------------------------------------------------------------------------------




unsigned int PuzzleSolver::nuevo_calcula_heuristica_a_la_meta(string nodo_actual, string meta, unsigned int  numero_a_colocar_en_su_posicion) const
{
    unsigned int heuristica_total = 0;
    
    int movimientos_horizontales_necesarios_para_que_el_elemento_llegue_su_posicion_de_la_meta = 0; //columnas
    int movimientos_verticales_necesarios_para_que_el_elemento_llegue_su_posicion_de_la_meta  = 0; //filas
    
    //La forma de calcular los desplazamientos para llegar a la fila meta es mas sencilla que para el caso de las columnas
    // simplemente debe seguirse la siguiente expresion:
    //abs( indice_en_el_string_meta/dimension_del_puzzle - indice_en_el_string_nodo_actual/dimension_del_puzzle)
    //Pongamos un escenario de un puzzle 3x3, los elementos de la primera fila {0,1,2} divididos entre 3 dan 0
    // los elementos de la ultima fila {6,7,8} dan 2, las restas entre los posibles resultados de estas divisiones
    //estan en el perfecto rango de posibles movimientos verticales {0,1,2}
    
    
   

    //La forma de calcular los desplazamientos para llegar a la columna de la meta se realiza de la sisguiente manera:
    //sabemos que todos los elementos que sean divisibles entre la dimension del puzzle estan en la primera columna
    // por lo que si al indice del elemento que tenemos le restamos el producto del numero de la fila en la que esta por la dimension del puzzle, conoceremos la columna.
    //Ejemplos: tenemos el siguiente puzzle 3x3 {{1,2,3},{4,5,6},{7,8,-1}} -> indices{{0,1,2},{3,4,5},{6,7,8}} en que columna estan 1,5,-1
    //Formula para calcular fila = abs(indice_del_elemento_en_el_string /dimension_del_puzzle)
    //Formula para calcular columna = abs( indice_del_elemento_en_el_string - (dimension_del_puzzle * fila_en_donde_esta_el_elemento))
    
    // Fila del 1 : 0/3 -> fila = 0
    //Columna del 1 : abs(0 - (3 * 0)) = abs(0 -0) -> columna =  0
    //Fila del 5 : 4/3 = 1 -> fila = 1
    //Columna del 5: abs(4 - (3 * 1)) - abs(4-3) -> columa = 1
    //Fila del -1 : 8/3 = 2 -> fila = 2
    //Columna del -1 = abs(8 - (3 * 2)) = abs(8 - 6) -> columna = 2
    
    int indice_del_numero_a_colocar_en_el_nodo_actual = -1;
    
    int fila_en_la_que_esta_el_elemento_en_el_nodo_actual = 0;
    int columna_en_la_que_esta_el_elemento_en_el_nodo_actual = 0;
    
    
    int fila_en_la_que_esta_el_elemento_en_la_meta = 0;
    int columna_en_la_que_esta_el_elemento_en_la_meta = 0;
    
    int fila_en_la_que_esta_el_numero_a_colocar_en_el_nodo_actual = 0;
    int columna_en_la_que_esta_el_numero_a_colocar_en_el_nodo_actual = 0;


    
    
    vector<int> indices_de_huecos_en_el_nodo_actual;
    
    if(huecos.size() == 1)
    {
        
        for(int i = 0; i < nodo_actual.length();i++)
        {
            if((int)nodo_actual[i] <= (entero_con_el_que_comienza_el_casteo + numero_a_colocar_en_su_posicion) && nodo_actual[i] != (char)entero_con_el_que_comienza_el_casteo)
            {
                if((int)nodo_actual[i] == entero_con_el_que_comienza_el_casteo + numero_a_colocar_en_su_posicion)
                {
                    indice_del_numero_a_colocar_en_el_nodo_actual = i;
                    fila_en_la_que_esta_el_numero_a_colocar_en_el_nodo_actual = (indice_del_numero_a_colocar_en_el_nodo_actual)/ dimension;
                    
                    columna_en_la_que_esta_el_numero_a_colocar_en_el_nodo_actual = abs(indice_del_numero_a_colocar_en_el_nodo_actual - ((int)dimension * fila_en_la_que_esta_el_numero_a_colocar_en_el_nodo_actual));
                }
                
                fila_en_la_que_esta_el_elemento_en_el_nodo_actual = i/dimension;
                
                columna_en_la_que_esta_el_elemento_en_el_nodo_actual = abs(i - ((int)dimension * fila_en_la_que_esta_el_elemento_en_el_nodo_actual));
                
                
                
                for(int j = 0; j < nodo_actual.length();j++)
                {
                    if(nodo_actual[i] == meta[j])
                    {
                        fila_en_la_que_esta_el_elemento_en_la_meta = j/dimension;
                        columna_en_la_que_esta_el_elemento_en_la_meta = abs(j - ((int)dimension * fila_en_la_que_esta_el_elemento_en_la_meta));
                        break;
                    }
                    
                }
                
                
                
                movimientos_verticales_necesarios_para_que_el_elemento_llegue_su_posicion_de_la_meta = abs(fila_en_la_que_esta_el_elemento_en_la_meta - fila_en_la_que_esta_el_elemento_en_el_nodo_actual);
                
                
                movimientos_horizontales_necesarios_para_que_el_elemento_llegue_su_posicion_de_la_meta = abs(columna_en_la_que_esta_el_elemento_en_la_meta - columna_en_la_que_esta_el_elemento_en_el_nodo_actual);
                
                heuristica_total = heuristica_total + movimientos_verticales_necesarios_para_que_el_elemento_llegue_su_posicion_de_la_meta + movimientos_horizontales_necesarios_para_que_el_elemento_llegue_su_posicion_de_la_meta;
                
            }
            
            if((int)nodo_actual[i] == entero_con_el_que_comienza_el_casteo)
                indices_de_huecos_en_el_nodo_actual.push_back(i);
        }
    }
    
    else
    {
        for(int i = 0; i < nodo_actual.length();i++)
        {
            if((int)nodo_actual[i] <= (entero_con_el_que_comienza_el_casteo + numero_a_colocar_en_su_posicion + 1) && nodo_actual[i] != (char)entero_con_el_que_comienza_el_casteo)
            {
                if((int)nodo_actual[i] == entero_con_el_que_comienza_el_casteo + numero_a_colocar_en_su_posicion)
                {
                    indice_del_numero_a_colocar_en_el_nodo_actual = i;
                    fila_en_la_que_esta_el_numero_a_colocar_en_el_nodo_actual = (indice_del_numero_a_colocar_en_el_nodo_actual)/ dimension;
                    
                    columna_en_la_que_esta_el_numero_a_colocar_en_el_nodo_actual = abs(indice_del_numero_a_colocar_en_el_nodo_actual - ((int)dimension * fila_en_la_que_esta_el_numero_a_colocar_en_el_nodo_actual));
                }
                
                fila_en_la_que_esta_el_elemento_en_el_nodo_actual = i/dimension;
                
                columna_en_la_que_esta_el_elemento_en_el_nodo_actual = abs(i - ((int)dimension * fila_en_la_que_esta_el_elemento_en_el_nodo_actual));
                
                
                
                for(int j = 0; j < nodo_actual.length();j++)
                {
                    if(nodo_actual[i] == meta[j])
                    {
                        fila_en_la_que_esta_el_elemento_en_la_meta = j/dimension;
                        columna_en_la_que_esta_el_elemento_en_la_meta = abs(j - ((int)dimension * fila_en_la_que_esta_el_elemento_en_la_meta));
                        break;
                    }
                    
                }
                
                
                
                movimientos_verticales_necesarios_para_que_el_elemento_llegue_su_posicion_de_la_meta = abs(fila_en_la_que_esta_el_elemento_en_la_meta - fila_en_la_que_esta_el_elemento_en_el_nodo_actual);
                
                
                movimientos_horizontales_necesarios_para_que_el_elemento_llegue_su_posicion_de_la_meta = abs(columna_en_la_que_esta_el_elemento_en_la_meta - columna_en_la_que_esta_el_elemento_en_el_nodo_actual);
                
                heuristica_total = heuristica_total + movimientos_verticales_necesarios_para_que_el_elemento_llegue_su_posicion_de_la_meta + movimientos_horizontales_necesarios_para_que_el_elemento_llegue_su_posicion_de_la_meta;
                
            }
            
            if((int)nodo_actual[i] == entero_con_el_que_comienza_el_casteo)
                indices_de_huecos_en_el_nodo_actual.push_back(i);
        }
    }
    
    for(unsigned int i = 0; i  < indices_de_huecos_en_el_nodo_actual.size();i++)
    {
        
        fila_en_la_que_esta_el_elemento_en_el_nodo_actual = indices_de_huecos_en_el_nodo_actual[i]/dimension;
        columna_en_la_que_esta_el_elemento_en_el_nodo_actual = abs(indices_de_huecos_en_el_nodo_actual[i]  - ((int)dimension * fila_en_la_que_esta_el_elemento_en_el_nodo_actual));
        
        movimientos_verticales_necesarios_para_que_el_elemento_llegue_su_posicion_de_la_meta = abs(fila_en_la_que_esta_el_numero_a_colocar_en_el_nodo_actual - fila_en_la_que_esta_el_elemento_en_el_nodo_actual);
        
        movimientos_horizontales_necesarios_para_que_el_elemento_llegue_su_posicion_de_la_meta = abs(columna_en_la_que_esta_el_numero_a_colocar_en_el_nodo_actual - columna_en_la_que_esta_el_elemento_en_el_nodo_actual);
        
        heuristica_total = heuristica_total + movimientos_verticales_necesarios_para_que_el_elemento_llegue_su_posicion_de_la_meta + movimientos_horizontales_necesarios_para_que_el_elemento_llegue_su_posicion_de_la_meta;
        
        
    }
    
    return heuristica_total;
    
}



//---------------------------------------------------------------------------------------------------------------

bool PuzzleSolver::busqueda_nueva(vector <vector <unsigned int>> pEstado_inicial, int& nodo_encontrado)
{
    
    arbol_de_busqueda.limpia_arbol();
    agenda.limpia_agenda();
    huecos.clear();
    nodo_encontrado = -1;


    unsigned int t1 = (unsigned int) clock(), t2 = 0;
    string inicio = "";
    string meta = "";
    
    int id_hueco = -1;
    
    dimension =  (unsigned int)pEstado_inicial[0].size();
    estado_inicial.clear();
    estado_inicial.assign(dimension, {});
    
    
    for (unsigned int i = 0; i < pEstado_inicial.size();i++)
        for (unsigned int j = 0; j < pEstado_inicial[i].size();j++)
        {
            inicio  += (char) entero_con_el_que_comienza_el_casteo + pEstado_inicial[i][j];
            if(pEstado_inicial[i][j] == 0)
            {
                huecos.push_back(id_hueco);
                estado_inicial[i].push_back(id_hueco);
                id_hueco--;
                continue;
            }
            estado_inicial[i].push_back(pEstado_inicial[i][j]);
        }
    
    
    
    for(unsigned int i = 1; i <= dimension*dimension;i++)
        meta += (char)(entero_con_el_que_comienza_el_casteo + i);
    
    for(int i = (int) meta.length() - 1; i>meta.length() - 1 - huecos.size();i--)
        meta[i] = (char)(entero_con_el_que_comienza_el_casteo);
    

    

    unsigned int numero_a_colocar_en_su_posicion =  devuelve_numero_a_colocar_en_su_posicion(inicio, meta);
    unsigned int nuevo_numero_a_colocar_en_su_posicion = numero_a_colocar_en_su_posicion;


    tipo_nodo_informacion nodo_raiz;
    nodo_raiz.nombre_del_nodo = inicio;
    nodo_raiz.costo_estimado = nuevo_calcula_heuristica_a_la_meta(nodo_raiz.nombre_del_nodo,meta,numero_a_colocar_en_su_posicion);
    nodo_raiz.numero_a_colocar = numero_a_colocar_en_su_posicion;
    arbol_de_busqueda.crea_arbol(nodo_raiz);
    Arbol_Binario arbol_binario = Arbol_Binario();
    arbol_binario.push(inicio,0);

    informacion_en_agenda informacion_para_la_agenda_del_nodo_raiz;

    informacion_para_la_agenda_del_nodo_raiz.nodo = 0;
    informacion_para_la_agenda_del_nodo_raiz.costo_estimado = nodo_raiz.costo_estimado;
    informacion_para_la_agenda_del_nodo_raiz.numero_a_colocar = numero_a_colocar_en_su_posicion;
    agenda.push_back(informacion_para_la_agenda_del_nodo_raiz);

    tipo_nodo_informacion informacion_del_hijo_a_adicionar;
    informacion_en_agenda informacion_del_nodo_hijo_para_la_agenda;
    unsigned int mejor_nodo = 0;
    unsigned int posicion_del_mejor_nodo = 0;
    unsigned int costo_estimado_del_mejor_nodo = 0;
    unsigned int costo_acumulado_del_mejor_nodo = 0;
    vector<tipo_nodo_informacion> vecinos;

    
    while(!agenda.esta_vacia())
    {
        mejor_nodo = agenda[0].nodo;
        posicion_del_mejor_nodo = 0;
        costo_estimado_del_mejor_nodo = agenda[0].costo_estimado;
        for (unsigned int i = 1; i < agenda.size(); i++)
            if (costo_estimado_del_mejor_nodo > agenda[i].costo_estimado)
            {
                mejor_nodo = agenda[i].nodo;
                posicion_del_mejor_nodo = i;
                costo_estimado_del_mejor_nodo = agenda[i].costo_estimado;
                costo_acumulado_del_mejor_nodo = agenda[i].costo_acumulado;
            }

        
        for(unsigned int i = 0; i < agenda.size();i++)
            if(costo_estimado_del_mejor_nodo == agenda[i].costo_estimado && agenda[i].costo_acumulado < costo_acumulado_del_mejor_nodo)
            {
                mejor_nodo = agenda[i].nodo;
                posicion_del_mejor_nodo = i;
                costo_estimado_del_mejor_nodo = agenda[i].costo_estimado;
                costo_acumulado_del_mejor_nodo = agenda[i].costo_acumulado;
            }
        
        
        
        
        nuevo_numero_a_colocar_en_su_posicion = agenda[posicion_del_mejor_nodo].numero_a_colocar;
        agenda.erase(posicion_del_mejor_nodo);
        
        if(nuevo_numero_a_colocar_en_su_posicion > numero_a_colocar_en_su_posicion)
        {
            numero_a_colocar_en_su_posicion = nuevo_numero_a_colocar_en_su_posicion;
            
            
            for(unsigned int i = 0; i < agenda.size();i++)
                if(agenda[i].numero_a_colocar < numero_a_colocar_en_su_posicion)
                {
                    agenda.erase(i);
                    i--;
                }
            arbol_binario.clear();
        }

        
        if (arbol_de_busqueda[mejor_nodo].contenido.nombre_del_nodo == meta)
        {
            
            nodo_encontrado = mejor_nodo;
            t2 = (unsigned int)clock();
            cout << "Tiempo de busqueda: " << (double(t2 - t1) / CLOCKS_PER_SEC) << " segundos" << endl;
            return true;
        }

        vecinos.clear();
        devuelve_vecinos(arbol_de_busqueda[mejor_nodo].contenido.nombre_del_nodo, vecinos);
        

        
        for(unsigned int i = 0; i < vecinos.size();i++)
            if(!arbol_binario.push(vecinos[i].nombre_del_nodo, costo_acumulado_del_mejor_nodo + 1) || arbol_de_busqueda.esta_un_nodo_en_ancestros(mejor_nodo, vecinos[i].nombre_del_nodo))
            {
                vecinos.erase(vecinos.begin()+i);
                i--;
            }
        
        
        
        
        for(unsigned int i = 0; i < vecinos.size();i++)
        {

            informacion_del_hijo_a_adicionar.nombre_del_nodo = vecinos[i].nombre_del_nodo;
            informacion_del_hijo_a_adicionar.costo_acumulado = arbol_de_busqueda[mejor_nodo].contenido.costo_acumulado + 1;
            informacion_del_hijo_a_adicionar.costo_estimado = nuevo_calcula_heuristica_a_la_meta(informacion_del_hijo_a_adicionar.nombre_del_nodo,meta,numero_a_colocar_en_su_posicion);
            informacion_del_hijo_a_adicionar.numero_a_colocar = devuelve_numero_a_colocar_en_su_posicion(vecinos[i].nombre_del_nodo, meta);
            arbol_de_busqueda.agrega_hijo_a_un_nodo_del_arbol(mejor_nodo, informacion_del_hijo_a_adicionar);
            informacion_del_nodo_hijo_para_la_agenda.nodo = arbol_de_busqueda.size() -1;
            informacion_del_nodo_hijo_para_la_agenda.costo_acumulado = informacion_del_hijo_a_adicionar.costo_acumulado;
            informacion_del_nodo_hijo_para_la_agenda.costo_estimado = informacion_del_hijo_a_adicionar.costo_estimado;
            informacion_del_nodo_hijo_para_la_agenda.numero_a_colocar = informacion_del_hijo_a_adicionar.numero_a_colocar;
            
            agenda.push_back(informacion_del_nodo_hijo_para_la_agenda);
        }
        
        agenda.revisa_tamano_maximo_de_la_agenda();
        

        if (agenda.esta_vacia())
        {
            t2 = (unsigned int)clock();
            cout << "Tiempo de busqueda: " << (double(t2 - t1) / CLOCKS_PER_SEC) << " segundos" << endl;
            return nodo_encontrado != -1;
        }
        
    }


    t2 = (unsigned int)clock();
    cout << "Tiempo de busqueda: " << (double(t2 - t1) / CLOCKS_PER_SEC) << " segundos" << endl;


    return nodo_encontrado != -1;
    
    
    
    return false;
}

//---------------------------------------------------------------------------------------------------------

vector < vector < int>> PuzzleSolver::lee_archivo(string &archivo)
{
    string linea_capturada = "";
    ifstream file(archivo);
    bool division_encontrada = false;
    vector <vector<int>> estado_final;
    if (file.is_open())
    {
        
        while (getline(file, linea_capturada))
        {
            string numero = "";
            stringstream linea_csv(linea_capturada);
            
            vector <int> fila;
            if(division_encontrada == false) //Llenar el estado inicial (atributo de la clase)
            {
                while (getline(linea_csv,numero, ','))
                {
                    
                    if(isdigit(numero[0]))
                        fila.push_back(stoi(numero));
                    else
                    {
                        division_encontrada = true;
                        break;
                    }
                }
                if(division_encontrada == false)
                    estado_inicial.push_back(fila);
                
            }
            else //Llenar el estado final (variable local a retornar)
            {
                while (getline(linea_csv,numero, ','))
                {
                   
                    fila.push_back(stoi(numero));
                }
                
                estado_final.push_back(fila);
            }
            
        }
        file.close();
    }
    return estado_final;
}


//---------------------------------------------------------------------------------------------------------

void PuzzleSolver::escribe_en_archivo(string &archivo, double tiempo, int  nodo_encontrado)
{
    
    vector< int> temporal;
    string ruta = "";
    temporal.clear();

    
    unsigned int costo_acumulado = 0;

 

    while (nodo_encontrado != -1)
    {
        costo_acumulado++;
        temporal.push_back(nodo_encontrado);
        nodo_encontrado = arbol_de_busqueda[nodo_encontrado].padre;
    }
    
    costo_acumulado--;//Por el estado_inicial

    vector <string> estados;
    
    //Tenemos los strings en el orden yendo del inicio a la meta
    for(int i = (int)temporal.size()-1; i >= 0;i--)
        estados.push_back(arbol_de_busqueda[temporal[i]].contenido.nombre_del_nodo);
    

    //Como probablemente el usuario haya puesto 2 numeros negativos diferentes para los huecos, hay que convertir los 0´s en esos numeros
    
    if(huecos.size() == 2)
    {
        unsigned int posicion_anterior_hueco1 = 0;
        unsigned int posicion_anterior_hueco2 = 0;
        vector<char> estado_anterior;
        vector<char> estado_actual;

        
        //Primero hagamos el cambio en el primer nodo
        
        
        for(unsigned int i = 0; i < estado_inicial.size();i++)
            for(unsigned int j = 0; j < estado_inicial[i].size();j++)
                estado_anterior.push_back((char) (entero_con_el_que_comienza_el_casteo +  estado_inicial[i][j]));
        
        estados[0] = "";
        //Obtenemos las posiciones de los huecos
        for(unsigned int i = 0;  i < estado_anterior.size();i++)
        {
            estados[0] += estado_anterior[i];
            if(estado_anterior[i] == (char) entero_con_el_que_comienza_el_casteo + huecos[0])
                posicion_anterior_hueco1 = i;

            if(estado_anterior[i] == (char) entero_con_el_que_comienza_el_casteo + huecos[1])
                posicion_anterior_hueco2 = i;
            
        }
        
        //Ya tenemos un punto de referencia, ahora podemos modificar los demás estados
        
        for(unsigned int i = 1; i < estados.size();i++)
        {
            estado_actual.clear();
            //Agarramos el string en el vector de char estado actual
            for(unsigned int j = 0; j < estados[i].length();j++)
                estado_actual.push_back(estados[i][j]);
            
            if(estado_actual[posicion_anterior_hueco1] == (char) entero_con_el_que_comienza_el_casteo) //Si hay un cero todavia en esa poscion, significa que el hueco 1 no se movió y el 2 sí
            {
                estado_actual[posicion_anterior_hueco1] = (char)entero_con_el_que_comienza_el_casteo + huecos[0]; //Convertimos el cero en el hueco1 que paso el usuario
                
                for(unsigned int j = 0; j < estado_actual.size();j++)
                    if(estado_actual[j] == (char) entero_con_el_que_comienza_el_casteo)
                    {
                        estado_actual[j] = (char) entero_con_el_que_comienza_el_casteo + huecos[1];
                        posicion_anterior_hueco2 = j;
                        break;
                    }
            }
            
            else if(estado_actual[posicion_anterior_hueco2] == (char)entero_con_el_que_comienza_el_casteo)//Si hay un cero todavia en esa poscion, significa que el hueco 2 no se movió y el 1 sí

            {
                estado_actual[posicion_anterior_hueco2] = (char)entero_con_el_que_comienza_el_casteo + huecos[1]; //Convertimos el cero en el hueco2 que paso el usuario
                
                for(unsigned int j = 0; j < estado_actual.size();j++)
                    if(estado_actual[j] == (char) entero_con_el_que_comienza_el_casteo)
                    {
                        estado_actual[j] = (char) entero_con_el_que_comienza_el_casteo + huecos[0];
                        posicion_anterior_hueco1 = j;
                        break;
                    }
            }
            
            estados[i] = "";
            
            for(unsigned int j = 0; j < estado_actual.size();j++)
                estados[i] += estado_actual[j];
            
            estado_anterior = estado_actual;
            
        }
        
    }
    
    ofstream file(archivo);
    
    if (file.is_open())
    {
        
        file << "Tiempo: " << tiempo << " segundos" << endl;

        file << "Tamano del arbol: " << arbol_de_busqueda.size() << " nodos" << endl;
        file << "Tamano maximo de agenda: " << agenda.obten_tamano_maximo_de_la_agenda() << " nodos" << endl;
       
        file << "Costo acumulado: " << costo_acumulado << endl;
        
        for (int i = 0; i < estados.size(); i++)
        {
            for(int j = 0; j < estados[i].length();j++)
            {
                
                if ((j + 1) % dimension != 0)
                    file << to_string(((int)estados[i][j]) - entero_con_el_que_comienza_el_casteo) + "\t";
                else
                    file << ruta + to_string((int)estados[i][j] - entero_con_el_que_comienza_el_casteo) + "\n";
                
            }
            file << endl << endl;
        }
        
    }
    


    
}


//--------------------------------------------------------------------------------------------------------
bool PuzzleSolver::busqueda_nueva(string archivo, string archivo_solucion, int& nodo_encontrado)
{
    
    arbol_de_busqueda.limpia_arbol();
    agenda.limpia_agenda();

    huecos.clear();
    nodo_encontrado = -1;

  
    
    
    unsigned int t1 = (unsigned int) clock(), t2 = 0;
    string inicio = "";
    string meta = "";
    
    estado_inicial.clear();
    
    vector <vector <int>> estado_final_comprueba_lectura = lee_archivo(archivo);
    
    if(estado_final_comprueba_lectura.size() != 0)
    {
        dimension =  (unsigned int)estado_inicial[0].size();
        int id_hueco = -1;
        
        //A nuestro vector estado inicial le cambiamos los ceros por identificadores negativos
        for (unsigned int i = 0; i < estado_inicial.size();i++)
        {
            for (unsigned int j = 0; j < estado_inicial[i].size();j++)
            {
                inicio  += (char) entero_con_el_que_comienza_el_casteo + estado_inicial[i][j];
                if(estado_inicial[i][j] == 0)
                {
                    huecos.push_back(id_hueco);
                    estado_inicial[i][j] = id_hueco;
                    id_hueco--;
                    continue;
                }
            }
            
        }
        
        
        for(unsigned int i = 1; i <= dimension*dimension;i++)
            meta += (char)(entero_con_el_que_comienza_el_casteo + i);
        
        for(int i = (int) meta.length() - 1; i>meta.length() - 1 - huecos.size();i--)
            meta[i] = (char)(entero_con_el_que_comienza_el_casteo);
        
        
        
        
        unsigned int numero_a_colocar_en_su_posicion =  devuelve_numero_a_colocar_en_su_posicion(inicio, meta);
        unsigned int nuevo_numero_a_colocar_en_su_posicion = numero_a_colocar_en_su_posicion;
        
        
        tipo_nodo_informacion nodo_raiz;
        nodo_raiz.nombre_del_nodo = inicio;
        nodo_raiz.costo_estimado = nuevo_calcula_heuristica_a_la_meta(nodo_raiz.nombre_del_nodo,meta,numero_a_colocar_en_su_posicion);
        nodo_raiz.numero_a_colocar = numero_a_colocar_en_su_posicion;
        arbol_de_busqueda.crea_arbol(nodo_raiz);
        Arbol_Binario arbol_binario = Arbol_Binario();
        arbol_binario.push(inicio,0);
        
        informacion_en_agenda informacion_para_la_agenda_del_nodo_raiz;
        
        informacion_para_la_agenda_del_nodo_raiz.nodo = 0;
        informacion_para_la_agenda_del_nodo_raiz.costo_estimado = nodo_raiz.costo_estimado;
        informacion_para_la_agenda_del_nodo_raiz.numero_a_colocar = numero_a_colocar_en_su_posicion;
        agenda.push_back(informacion_para_la_agenda_del_nodo_raiz);
        
        tipo_nodo_informacion informacion_del_hijo_a_adicionar;
        informacion_en_agenda informacion_del_nodo_hijo_para_la_agenda;
        unsigned int mejor_nodo = 0;
        unsigned int posicion_del_mejor_nodo = 0;
        unsigned int costo_estimado_del_mejor_nodo = 0;
        unsigned int costo_acumulado_del_mejor_nodo = 0;
        vector<tipo_nodo_informacion> vecinos;
        
        
        while(!agenda.esta_vacia())
        {
            mejor_nodo = agenda[0].nodo;
            posicion_del_mejor_nodo = 0;
            costo_estimado_del_mejor_nodo = agenda[0].costo_estimado;
            for (unsigned int i = 1; i < agenda.size(); i++)
                if (costo_estimado_del_mejor_nodo > agenda[i].costo_estimado)
                {
                    mejor_nodo = agenda[i].nodo;
                    posicion_del_mejor_nodo = i;
                    costo_estimado_del_mejor_nodo = agenda[i].costo_estimado;
                    costo_acumulado_del_mejor_nodo = agenda[i].costo_acumulado;
                }
            
            for(unsigned int i = 0; i < agenda.size();i++)
                if(costo_estimado_del_mejor_nodo == agenda[i].costo_estimado && agenda[i].costo_acumulado < costo_acumulado_del_mejor_nodo)
                {
                    mejor_nodo = agenda[i].nodo;
                    posicion_del_mejor_nodo = i;
                    costo_estimado_del_mejor_nodo = agenda[i].costo_estimado;
                    costo_acumulado_del_mejor_nodo = agenda[i].costo_acumulado;
                }
            
            nuevo_numero_a_colocar_en_su_posicion = agenda[posicion_del_mejor_nodo].numero_a_colocar;
            agenda.erase(posicion_del_mejor_nodo);
            
            
            if(nuevo_numero_a_colocar_en_su_posicion > numero_a_colocar_en_su_posicion)
            {
                numero_a_colocar_en_su_posicion = nuevo_numero_a_colocar_en_su_posicion;
                
                for(unsigned int i = 0; i < agenda.size();i++)
                    if(agenda[i].numero_a_colocar < numero_a_colocar_en_su_posicion)
                    {
                        agenda.erase(i);
                        i--;
                    }
                arbol_binario.clear();
            }
            
            
            if (arbol_de_busqueda[mejor_nodo].contenido.nombre_del_nodo == meta)
            {
                nodo_encontrado = mejor_nodo;
                t2 = (unsigned int)clock();
                double tiempo = (double(t2 - t1) / CLOCKS_PER_SEC);
                cout << "Tiempo de busqueda: " << tiempo << " segundos" << endl;
                escribe_en_archivo(archivo_solucion, tiempo, nodo_encontrado);
                return true;
            }
            
            vecinos.clear();
            devuelve_vecinos(arbol_de_busqueda[mejor_nodo].contenido.nombre_del_nodo, vecinos);
            
            
            
            for(unsigned int i = 0; i < vecinos.size();i++)
                if(arbol_de_busqueda.esta_un_nodo_en_ancestros(mejor_nodo, vecinos[i].nombre_del_nodo) || !arbol_binario.push(vecinos[i].nombre_del_nodo,costo_acumulado_del_mejor_nodo+1))
                {
                    vecinos.erase(vecinos.begin()+i);
                    i--;
                }
            
            
            
            
            
            for(unsigned int i = 0; i < vecinos.size();i++)
            {
                informacion_del_hijo_a_adicionar.nombre_del_nodo = vecinos[i].nombre_del_nodo;
                informacion_del_hijo_a_adicionar.costo_acumulado = costo_acumulado_del_mejor_nodo + 1;
                informacion_del_hijo_a_adicionar.costo_estimado = nuevo_calcula_heuristica_a_la_meta(informacion_del_hijo_a_adicionar.nombre_del_nodo,meta,numero_a_colocar_en_su_posicion);
                informacion_del_hijo_a_adicionar.numero_a_colocar = devuelve_numero_a_colocar_en_su_posicion(vecinos[i].nombre_del_nodo, meta);
                arbol_de_busqueda.agrega_hijo_a_un_nodo_del_arbol(mejor_nodo, informacion_del_hijo_a_adicionar);
                informacion_del_nodo_hijo_para_la_agenda.nodo = arbol_de_busqueda.size() -1;
                informacion_del_nodo_hijo_para_la_agenda.costo_acumulado = informacion_del_hijo_a_adicionar.costo_acumulado;
                informacion_del_nodo_hijo_para_la_agenda.costo_estimado = informacion_del_hijo_a_adicionar.costo_estimado;
                informacion_del_nodo_hijo_para_la_agenda.numero_a_colocar = informacion_del_hijo_a_adicionar.numero_a_colocar;
                
                agenda.push_back(informacion_del_nodo_hijo_para_la_agenda);
            }
            
            agenda.revisa_tamano_maximo_de_la_agenda();
            if (agenda.esta_vacia())
            {
                t2 = (unsigned int)clock();
                cout << "Tiempo de busqueda: " << (double(t2 - t1) / CLOCKS_PER_SEC) << " segundos" << endl;
                return nodo_encontrado != -1;
            }
            
        }
        
        
        t2 = (unsigned int)clock();
        cout << "Tiempo de busqueda: " << (double(t2 - t1) / CLOCKS_PER_SEC) << " segundos" << endl;
    }

    return nodo_encontrado != -1;

}



//----------------------------------------------------------------------------------------------------------
string PuzzleSolver::devuelve_la_ruta_encontrada(int nodo_encontrado)
{
    vector< int> temporal;
    string ruta = "";
    temporal.clear();

    
    unsigned int costo_acumulado = 0;

 

    while (nodo_encontrado != -1)
    {
        costo_acumulado++;
        temporal.push_back(nodo_encontrado);
        nodo_encontrado = arbol_de_busqueda[nodo_encontrado].padre;
    }
    costo_acumulado--;//Por el estado_inicial

    vector <string> estados;
    
    for(int i = (int)temporal.size()-1; i >= 0;i--)
        estados.push_back(arbol_de_busqueda[temporal[i]].contenido.nombre_del_nodo);
    

  
    //Hay que diferenciar los huecos para la persona
    if(huecos.size() == 2)
    {
        unsigned int posicion_anterior_hueco1 = 0;
        unsigned int posicion_anterior_hueco2 = 0;
        vector<char> estado_anterior;
        vector<char> estado_actual;

        
        //Primero hagamos el cambio en el primer nodo
        
        
        for(unsigned int i = 0; i < estado_inicial.size();i++)
            for(unsigned int j = 0; j < estado_inicial[i].size();j++)
                estado_anterior.push_back((char) (entero_con_el_que_comienza_el_casteo +  estado_inicial[i][j]));
        
        estados[0] = "";
        //Obtenemos las posiciones de los huecos
        for(unsigned int i = 0;  i < estado_anterior.size();i++)
        {
            estados[0] += estado_anterior[i];
            if(estado_anterior[i] == (char) entero_con_el_que_comienza_el_casteo + huecos[0])
                posicion_anterior_hueco1 = i;

            if(estado_anterior[i] == (char) entero_con_el_que_comienza_el_casteo + huecos[1])
                posicion_anterior_hueco2 = i;
            
        }
        
        //Ya tenemos un punto de referencia, ahora podemos modificar los demás estados
        
        for(unsigned int i = 1; i < estados.size();i++)
        {
            estado_actual.clear();
            //Agarramos el string en el vector de char estado actual
            for(unsigned int j = 0; j < estados[i].length();j++)
                estado_actual.push_back(estados[i][j]);
            
            if(estado_actual[posicion_anterior_hueco1] == (char) entero_con_el_que_comienza_el_casteo) //Si hay un cero todavia en esa poscion, significa que el hueco 1 no se movió y el 2 sí
            {
                estado_actual[posicion_anterior_hueco1] = (char)entero_con_el_que_comienza_el_casteo + huecos[0]; //Convertimos el cero en el hueco1 que paso el usuario
                
                for(unsigned int j = 0; j < estado_actual.size();j++)
                    if(estado_actual[j] == (char) entero_con_el_que_comienza_el_casteo)
                    {
                        estado_actual[j] = (char) entero_con_el_que_comienza_el_casteo + huecos[1];
                        posicion_anterior_hueco2 = j;
                        break;
                    }
            }
            
            else if(estado_actual[posicion_anterior_hueco2] == (char)entero_con_el_que_comienza_el_casteo)//Si hay un cero todavia en esa poscion, significa que el hueco 2 no se movió y el 1 sí

            {
                estado_actual[posicion_anterior_hueco2] = (char)entero_con_el_que_comienza_el_casteo + huecos[1]; //Convertimos el cero en el hueco2 que paso el usuario
                
                for(unsigned int j = 0; j < estado_actual.size();j++)
                    if(estado_actual[j] == (char) entero_con_el_que_comienza_el_casteo)
                    {
                        estado_actual[j] = (char) entero_con_el_que_comienza_el_casteo + huecos[0];
                        posicion_anterior_hueco1 = j;
                        break;
                    }
            }
            
            estados[i] = "";
            
            for(unsigned int j = 0; j < estado_actual.size();j++)
                estados[i] += estado_actual[j];
            
            estado_anterior = estado_actual;
            
        }
        
    }
    
    for (int i = 0; i < estados.size(); i++)
    {
        for(int j = 0; j < estados[i].length();j++)
        {
            
            if ((j + 1) % dimension != 0)
            {
                ruta = ruta + to_string(((int)estados[i][j]) - entero_con_el_que_comienza_el_casteo) + "\t";
            }
            else
            {
                ruta = ruta + to_string((int)estados[i][j] - entero_con_el_que_comienza_el_casteo) + "\n";
            }
            
        }
        ruta = ruta + "\n";
    }
    

    cout << "Tamano del arbol: " << arbol_de_busqueda.size() << " nodos" << endl;
    cout << "Tamano maximo de agenda: " << agenda.obten_tamano_maximo_de_la_agenda() << " nodos" << endl;

    
    cout << "costo total: " << costo_acumulado << endl;
    ruta = ruta + "costo total = " + to_string(costo_acumulado);
    

    return ruta;

}





