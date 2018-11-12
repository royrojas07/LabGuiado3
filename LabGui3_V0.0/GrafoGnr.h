/* 
 * File:   GrafoGnr.h
 * Author: Alan
 *
 * Created on 5 de febrero de 2018, 05:49 PM
 */

#ifndef GRAFOGNR_H
#define GRAFOGNR_H

#include <fstream>
#include <vector>
#include <list>
#include <map>
#include <stack>
#include <algorithm>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
using namespace std;

template < typename T >
class GrafoGnr {
    // Representa una red compleja genérica con vértices de tipo T.
	/* Supuestos sobre el tipo T:
         * T() está definido.
         * T(const T&) está definido.
         * T operator=(const T& t) está definido.
         * friend ostream& operator<<(ostream& o, const T& t) plantilla de operador sobrecargado.
         */


public:
    /* CONSTRUCTORES */

    // DADOS:
    // N la cantidad de vértices o nodos.
    // K el promedio de adyacencias por vértice.
    
    // REQ: 0 < p < 1.
    // Construye un GrafoGnr con N vértices en el que el conjunto de
    // adyacencias se determina aleatoriamente utilizando p. Esto
    // implica que la probabilidad de que un arco exista entre 
    // cualesquiera dos vértices es igual a p.
    GrafoGnr(int N, double p);
    
    // REQ: N >> K >> ln N >> 1.
    // REQ: 0 <= beta <= 1.
    // Construye un GrafoGnr con N vértices, cada uno con K adyacencias EN PROMEDIO,
    // siguiendo el algoritmo de Watts-Strogatz:
    // https://en.wikipedia.org/wiki/Watts%E2%80%93Strogatz_model
    GrafoGnr(int N, int K, double beta);

    // Construye una red con base en los datos en el archivo.
    // El archivo debe ser de texto (extensión txt) con datos separados por comas.
    // En la primera línea aparecerá un entero que representa la cantidad N de vértices.
    // Los vértices se identifican con números de 0 a N-1.
    // Luego en cada línea aparecerán los índices de los vértices asociados o
    // adyacentes, a cada vértice: 0, 1...N-1.
    // NOTA: todos los vértices son inicializados con T().
    GrafoGnr(ifstream& archivo);

    // Construye una copia idéntica a orig.
    GrafoGnr(const GrafoGnr< T >& orig);

    // Destructor
    ~GrafoGnr();

    /* MÉTODOS OBSERVADORES BÁSICOS */

    // EFE: retorna true si 0 <= idVrt < N.
    // NOTA: idVrt significa "identificador de vértice".
    bool xstVrt(int idVrt) const;

    // REQ: 0 <= idVrtO < N && 0 <= idVrtD < N.
    // EFE: retorna true si existe adyacencia entre los vértices idVrtO e idVrtD.
    bool xstAdy(int idVrtO, int idVrtD) const;

    // REQ: 0 <= idVrt < N.
    // EFE: retorna en "rsp" los identificadores idVrtj de todos los vértices 
    // adyacentes a idVrt en el GrafoGnr.
    void obtIdVrtAdys(int idVrt, vector< int >& rsp) const;

    // REQ: 0 <= idVrt < N.
    // EFE: retorna la cantidad de vértices adyacentes a idVrt en el GrafoGnr.    
    int obtCntVrtAdys(int idVrt) const;

    // REQ: 0 <= idVrt < N.
    // EFE: retorna el vértice con índice idVrt.
    // NOTA: retorna por valor para que NO pueda ser modificado.
    T operator[](int idVrt) const;

    // EFE: retorna el total de arcos o adyacencias en el GrafoGnr.
    int obtTotArc() const;

    // EFE: retorna el total de vértices en el GrafoGnr.
    int obtTotVrt() const;

    /* MÉTODOS MODIFICADORES BÁSICOS */

    // REQ: 0 <= idVrt < N.
    // EFE: retorna el vértice con índice idVrt.
    // NOTA: retorna por referencia para que pueda ser modificado en el contexto
    // invocador.
    T& operator[](int idVrt);
    
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

    template < typename TT >
    struct Vrt {
        TT t;
        list< int > lstAdy;

        Vrt() : t(), lstAdy() {
        }; // constructor estándar de Vrt

        Vrt(const TT& tt) : t(tt), lstAdy() {
        }; // constructor con dato de vértice

        Vrt(const Vrt& vrt) : t(vrt.t), lstAdy(vrt.lstAdy) {
        }; // constructor de copias de Vrt
    };

    vector< T > vectorVrts; // vector de vértices
};

template < typename T >
GrafoGnr< T >::GrafoGnr(int N, double p){
}

template < typename T >
GrafoGnr< T >::GrafoGnr(int N, int K, double beta){
}

template < typename T >
GrafoGnr< T >::GrafoGnr(ifstream& archivo){
}

template < typename T >
GrafoGnr< T >::GrafoGnr(const GrafoGnr< T >& orig){
}

template < typename T >
GrafoGnr< T >::~GrafoGnr(){
}

template < typename T >
bool GrafoGnr< T >::xstVrt(int idVrt) const{
}

template < typename T >
bool GrafoGnr< T >::xstAdy(int idVrtO, int idVrtD) const{
}

template < typename T >
void GrafoGnr< T >::obtIdVrtAdys(int idVrt, vector< int >& rsp) const{
}

template < typename T >
int GrafoGnr< T >::obtCntVrtAdys(int idVrt) const{
}

template < typename T >
T GrafoGnr< T >::operator[](int idVrt) const{
}

template < typename T >
int GrafoGnr< T >::obtTotArc() const{
}

template < typename T >
int GrafoGnr< T >::obtTotVrt() const{
}

template < typename T >
T& GrafoGnr< T >::operator[](int idVrt){
}

template < typename T >
double GrafoGnr< T >::coeficienteLocalAgrupamiento(int idVrt) const{
    
}

template < typename T >
bool GrafoGnr< T >::conformidadPareto() const{
    
}

#endif /* GRAFOGNR_H */
