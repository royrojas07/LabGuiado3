/* 
 * File:   Nodo.h
 * Author: alan.calderon
 */

#ifndef NODO_H
#define	NODO_H

#include <random>
#include <ostream>
using namespace std;

class Nodo {
public:
    // Representa un nodo de la red de computadores sobre la cual se aplica la simulación
    // de dispersión de virus.
    
    /* TIPO PÚBLICO DE ESTADOS DE VÉRTICES */
    enum E{ // representa el tipo de estados de la red de infección
        S, // representa un vértice susceptible de infección
        I, // representa un vértice infectado
        R, // representa un vértice resistente
    };
    
    Nodo();
    Nodo(const Nodo& orig);
    virtual ~Nodo();
    
    // EFE: retorna el valor del estado del nodo.
    E obtEstado() const;
        
    // MOD: *this.
    // EFE: cambia el estado del nodo a ne.
    void modEstado(E ne);

    // EFE: permite que n sea consumido por el flujo s mediante el operator<<.
    // NOTA: es una función externa a la clase que por hacer acceso
    //       a los atributos privados del nodo se debe declarar como friend.
    friend ostream& operator<<(ostream& s, const Nodo& n);
    
    // EFE: modifica *this con los valores de n.
    Nodo operator=(const Nodo& n) const;
    
private:
    E estado; // representa el estado del nodo
};

#endif	/* NODO_H */

