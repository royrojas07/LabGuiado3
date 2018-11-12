/* 
 * File:   Grafo.h
 * Author: Alan
 *
 * Created on 5 de febrero de 2018, 05:49 PM
 */

#ifndef GRAFO_H
#define GRAFO_H

#include <fstream>
#include <vector>
#include <list>
#include <map>
#include <stack>
#include <algorithm>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
using namespace std;

#include "Nodo.h"
#include "GrafoGnr.h"

class Grafo {
    // Representa una red compleja con vértices de tipo Nodo.

public:
    /* CONSTRUCTORES */

    // DADOS:
    // N la cantidad de vértices o nodos.
    // K el promedio de adyacencias por vértice.
    
    // REQ: 0 < p < 1.
    // Construye un grafo con N vértices en el que el conjunto de
    // adyacencias se determina aleatoriamente utilizando p. Esto
    // implica que la probabilidad de que un arco exista entre 
    // cualesquiera dos vértices es igual a p.
    Grafo(int N, double p);
    
    // REQ: N >> K >> ln N >> 1.
    // REQ: 0 <= beta <= 1.
    // Construye un grafo con N vértices, cada uno con K adyacencias EN PROMEDIO,
    // siguiendo el algoritmo de Watts-Strogatz:
    // https://en.wikipedia.org/wiki/Watts%E2%80%93Strogatz_model
    Grafo(int N, int K, double beta);

    // Construye una red con base en los datos en el archivo.
    // El archivo debe ser de texto (extensión txt) con datos separados por comas.
    // En la primera línea aparecerá un entero que representa la cantidad N de vértices.
    // Los vértices se identifican con números de 0 a N-1.
    // Luego en cada línea aparecerán los índices de los vértices asociados o
    // adyacentes, a cada vértice: 0, 1...N-1.
    // NOTA: todos los vértices son inicializados con Nodo().
    Grafo(ifstream& archivo);

    // Construye una copia idéntica a orig.
    Grafo(const Grafo& orig);

    // Destructor
    ~Grafo();

    /* MÉTODOS OBSERVADORES BÁSICOS */

    // EFE: retorna true si 0 <= idVrt < N.
    // NOTA: idVrt significa "identificador de vértice".
    bool xstVrt(int idVrt) const;

    // REQ: 0 <= idVrtO < N && 0 <= idVrtD < N.
    // EFE: retorna true si existe adyacencia entre los vértices idVrtO e idVrtD.
    bool xstAdy(int idVrtO, int idVrtD) const;

    // REQ: 0 <= idVrt < N.
    // EFE: retorna en "rsp" los identificadores idVrtj de todos los vértices 
    // adyacentes a idVrt en el grafo.
    void obtIdVrtAdys(int idVrt, vector< int >& rsp) const;

    // REQ: 0 <= idVrt < N.
    // EFE: retorna la cantidad de vértices adyacentes a idVrt en el grafo.    
    int obtCntVrtAdys(int idVrt) const;

    // REQ: 0 <= idVrt < N.
    // EFE: retorna el vértice con índice idVrt.
    // NOTA: retorna por valor para que NO pueda ser modificado.
    Nodo operator[](int idVrt) const;

    // EFE: retorna el total de arcos o adyacencias en el grafo.
    int obtTotArc() const;

    // EFE: retorna el total de vértices en el grafo.
    int obtTotVrt() const;
    
    // EFE: retorna el total de nodos susceptibles en la red.
    int obtTotVrtSusceptibles() const;
    
    // EFE: retorna el total de nodos infectados en la red.
    int obtTotVrtInfectados() const;
    
    // EFE: retorna el total de nodos resistentes en la red.
    int obtTotVrtResistentes() const;

    /* MÉTODOS MODIFICADORES BÁSICOS */

    // REQ: 0 <= idVrt < N.
    // EFE: retorna el vértice con índice idVrt.
    // NOTA: retorna por referencia para que pueda ser modificado en el contexto
    // invocador.
    Nodo& operator[](int idVrt);
    
    /* MÉTODOS OBSERVADORES ESPECIALES */
    
    // REQ: 0 <= idVrt < N.
    // EFE: retorna el "local clustering coefficient" o coeficiente local de agrupamiento
    //      para el vértice indicado por idVrt.
    // La definición que aparece en: http://en.wikipedia.org/wiki/Clustering_coefficient
    // Sea c == obtCntVrtAdys(idVrt).
    // Entonces coeficienteLocalAgrupamiento(idVrt) == 2 * c / (c * (c - 1))
    double coeficienteLocalAgrupamiento(int idVrt) const;
   
    // EFE: retorna true si la sumatoria del coeficiente local de agrupamiento del 20% de
    //      los vértices con coeficiente más alto es mayor o igual a la sumatoria del
    //      coeficiente local de agrupamiento del 80% de los vértices con coeficiente más
    //      bajo.
    // NOTA: se basa en el principio de Paretto: https://en.wikipedia.org/wiki/Pareto_principle
    bool conformidadPareto() const;

private:

    GrafoGnr< Nodo > grf_nodos; // GrafoGnr especializado con Nodo
};

#endif /* GRAFO_H */
