/* 
 * File:   Nodo.cpp
 * Author: alan.calderon
 * 
 * Created on 24 de octubre de 2016, 06:00 PM
 */

#include "Nodo.h"

Nodo::Nodo() : estado(S) {
}

Nodo::Nodo(const Nodo& orig) : estado(orig.estado) {
}

Nodo::~Nodo() {
}

Nodo::E Nodo::obtEstado() const {
    return estado;
}

void Nodo::modEstado(E ne) {
    estado = ne;
}

ostream& operator<<(ostream& s, const Nodo& n) {

}

Nodo Nodo::operator=(const Nodo& n) const{
    
}