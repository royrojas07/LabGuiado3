/* 
 * File:   Simulador.h
 * Author: Alan
 *
 * Created on 2 de abril de 2015, 06:46 PM
 */

#ifndef SIMULADOR_H
#define	SIMULADOR_H


using namespace std;

#include "Grafo.h"
#include "Nodo.h"


class Simulador {
    // Representa el proceso de simulación de la infección en la red de computadoras.
    
public:
    
    // EFE: Construye un simulador que transformará al grafo g.
    Simulador(Grafo& g);

    // Destruye a *this retornando toda la memoria asignada dinámicamente.
    ~Simulador();


    // REQ: el grafo asociado (el pasado al constructor) esté bien construido.
    // MOD: el grafo asociado.    
    // EFE: inicializa el simulador con los siguientes parámetros:
    //      ios o initial-outbreak-size [1..N], N cantidad de vértices: cantidad
    //           de vértices contagiados al comienzo de la simulación.
    //      vsc o virus-spread-chance [0..0.1]: probabilidad de contagio.
    //      vcf o virus-check-frecuency [1..20]: frecuencia de chequeo antivirus.
    //      rc o recovery-chance [0..0.1]: probabilidad de eliminación de infección.
    //      grc o gain-resistance-chance [0..1]: probabilidad de generar resistencia.   
    void iniciarSimulacion(int ios, double vsc, int vcf, double rc, double grc);
    
    // REQ: el grafo asociado (el pasado al constructor) esté bien construido.
    // MOD: el grafo asociado.
    // EFE: aplica al grafo asociado una transformación con base en las reglas de 
    //      la simulación especificadas.
    void simular();

private:
    Grafo& grafo;
    int ios;
    double vsc;
    int vcf;
    double rc;
    double grc;
};

#endif	/* SIMULADOR_H */

