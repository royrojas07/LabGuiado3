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
#include <chrono>
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

    vector< Vrt<T> > vectorVrts; // vector de vértices
};

template < typename T >
GrafoGnr< T >::GrafoGnr(int N, double p){
     vectorVrts.resize( N, Vrt<T>() );
    unsigned int seed = chrono::system_clock::now().time_since_epoch().count();
    default_random_engine generator(seed);
    uniform_int_distribution<int> distribution(0, 9999);
    double random;
    for( int i = 0; i < N; i++ ){
        for( int j = i+1; j < N; j++ ){
            random = (double)(distribution(generator))/10000.0;
            if( random <= p ){
                vectorVrts[i].lstAdy.push_back( j );
                vectorVrts[j].lstAdy.push_back( i );
            }
        }
    }
}

template < typename T >
GrafoGnr< T >::GrafoGnr(int N, int K, double beta){
    vectorVrts.resize( N );
    for( int n = 0; n < N; n++ ){
        Vrt<T> vrt;
        vectorVrts[n] = vrt;
    }
    
    //ANILLO
    int iz;
    int dr;
    for( int n = 0; n < N; n++ ){
        iz = n;
        dr = n;
        for( int j = 0; j < K; j++ ){
            if( j < K/2 ){
                iz--;
                if( iz < 0 )
                    iz = N-1;
                vectorVrts[n].lstAdy.push_back(iz);
            } else {
                dr++;
                if( dr > N-1 )
                    dr = 0;
                vectorVrts[n].lstAdy.push_back(dr);
            }
        }
    }
    
    //REALAMBRAMIENTO
    unsigned int seed = chrono::system_clock::now().time_since_epoch().count();
    default_random_engine generator(seed);
    uniform_int_distribution<int> distribution(0, 9999);
    uniform_int_distribution<int> distribution1(0, N-1);
    double nodRand;
    bool nodRandValido;
    double proRand;
    int limInferior;
    int limSuperior;
    list<int>::iterator itParaInsert;
    for( int n = 0; n < N; n++ ){
        limInferior = n+1;
        limSuperior = n+K/2;
        if( N <= limInferior ){
            limInferior -= N;
            limSuperior -= N;
        }
        itParaInsert = vectorVrts[n].lstAdy.begin();
        while( !(limInferior <= *itParaInsert && *itParaInsert <= limSuperior) )
            itParaInsert++;
        for( int i = K/2; i < K; i++ ){
            proRand = (double)(distribution(generator))/10000;
            if( proRand <= beta ){
                nodRand = distribution1(generator);
                nodRandValido = false;
                while( !nodRandValido ){
                    nodRandValido = true;
                    for( list<int>::const_iterator t = vectorVrts[n].lstAdy.begin(); t != vectorVrts[n].lstAdy.end(); t++ ){
                        if( *t == nodRand || nodRand == n ){
                            nodRandValido = false;
                            t = --(vectorVrts[n].lstAdy.end());
                        }
                    }
                    if( !nodRandValido )
                        nodRand = (rand()%N);
                }
                vectorVrts[nodRand].lstAdy.push_back(n);
                vectorVrts[*itParaInsert].lstAdy.remove(n);
                *itParaInsert = nodRand;
                itParaInsert++;
            }
        }
    }
}

template < typename T >
GrafoGnr< T >::GrafoGnr(ifstream& archivo){
    string cantNodos;
    getline( archivo, cantNodos );
    int nodos = atoi( cantNodos.c_str() );
    int c;
    vectorVrts.resize( nodos );
    for( int i = 0; i < nodos; i++ ){
        Vrt<T> vertice;
        vectorVrts[i] =  vertice;
    }
    for( int i = 0; i < nodos; i++ ){
        while( archivo.peek() != '\n' && !archivo.eof() ){
            archivo >> c;
            vectorVrts[i].lstAdy.push_back(c);
            archivo.get();
        }
        archivo.get();
    }
    archivo.close();
}

template < typename T >
GrafoGnr< T >::GrafoGnr(const GrafoGnr< T >& orig){
    vectorVrts.resize( orig.obtTotVrt() );
    for( int i = 0; i < orig.obtTotVrt(); i++ ){
        Vrt<T> vertice( orig[i] );
        vectorVrts[i] = vertice;
        vectorVrts[i].lstAdy = orig.vectorVrts[i].lstAdy;
    }
}

template < typename T >
GrafoGnr< T >::~GrafoGnr(){
}

template < typename T >
bool GrafoGnr< T >::xstVrt(int idVrt) const{
    bool result = false;
    if( 0 <= idVrt && idVrt < vectorVrts.size() )
        result = true;
    return result;
}

template < typename T >
bool GrafoGnr< T >::xstAdy(int idVrtO, int idVrtD) const{
    int i =idVrtO;
    int j=idVrtD;
    bool func =false;
    list<int>::const_iterator recor = vectorVrts[i].lstAdy.begin();
    list<int>::const_iterator fin = vectorVrts[i].lstAdy.end();
    while(recor!=fin){
        if(*recor==j){
            func=true;
            recor=fin;
        }
        if(recor != fin){
            recor++;
        }
    }
    return func;
}

template < typename T >
void GrafoGnr< T >::obtIdVrtAdys(int idVrt, vector< int >& rsp) const{
    list<int>::const_iterator i = vectorVrts[idVrt].lstAdy.begin();
    list<int>::const_iterator end = vectorVrts[idVrt].lstAdy.end();
    rsp.resize( vectorVrts[idVrt].lstAdy.size() );
    int j = 0;
    while( i != end ){
        rsp[j] = *i;
        i++;
        j++;
    }
}

template < typename T >
int GrafoGnr< T >::obtCntVrtAdys(int idVrt) const{
    int tam = vectorVrts[idVrt].lstAdy.size();
    return tam;
}

template < typename T >
T GrafoGnr< T >::operator[](int idVrt) const{
    return vectorVrts[idVrt].t;
}

template < typename T >
int GrafoGnr< T >::obtTotArc() const{
    int total=0;
    int N=obtTotVrt();
    for( int i = 0; i < N; i++ ){
        total += vectorVrts[i].lstAdy.size();
    }
    total /= 2;
    return total;
}

template < typename T >
int GrafoGnr< T >::obtTotVrt() const{
    return vectorVrts.size();
}

template < typename T >
T& GrafoGnr< T >::operator[](int idVrt){
    return vectorVrts[idVrt].t;
}

template < typename T >
double GrafoGnr< T >::coeficienteLocalAgrupamiento(int idVrt) const{
    int nodo=idVrt;
    double resul=0;
    double cuenta=0;
    vector<int> nodos;
    obtIdVrtAdys(nodo,nodos);
    int tamano = nodos.size();
    
    for(int i=0;i<tamano;i++){
        for(int j=0;j<tamano;j++){
            if( xstAdy(nodos[i], nodos[j])){
                cuenta++;
            }
        }
    }
    cuenta=cuenta/2;
    int vrtAdyNodo = obtCntVrtAdys(nodo);
    double den=( vrtAdyNodo*(vrtAdyNodo - 1) );
    resul= ( 2*(cuenta) )/den;
    if(tamano==1){
        resul=0;
    }
    
    return resul;
}

template < typename T >
bool GrafoGnr< T >::conformidadPareto() const{
    vector<double> coe;
    int tamano=(vectorVrts.size());
    coe.resize( tamano );
    int i=0;
    while(i < tamano){
        coe[i] = coeficienteLocalAgrupamiento(i);
        i++;
    }

    sort( coe.begin(), coe.end(), greater<double>() );

    double cmenor=(vectorVrts.size())*0.20;
    i=0;
    double may = 0.0;
    double men = 0.0;
    while(i<(coe.size())){
    if (i<cmenor){
        men=men+coe[i];
    }else{
        may=may+coe[i];
    }
        i++;
    }
    if(men>=may){
        return true;
    }else{
        return false;
    }
}

#endif /* GRAFOGNR_H */
