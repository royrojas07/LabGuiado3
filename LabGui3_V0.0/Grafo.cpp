#include "Grafo.h"

Grafo::Grafo(int N, double p) : grf_nodos(N, p) {

}

Grafo::Grafo(ifstream& archivo) : grf_nodos(archivo) {

}

Grafo::Grafo(const Grafo& orig) : grf_nodos(orig.grf_nodos) {

}

Grafo::~Grafo() {
}

bool Grafo::xstVrt(int idVrt) const {

}

bool Grafo::xstAdy(int idVrtO, int idVrtD) const {

}

void Grafo::obtIdVrtAdys(int idVrt, vector< int >& rspRetornar) const {

}

int Grafo::obtCntVrtAdys(int idVrt) const {

}

Nodo Grafo::operator[](int idVrt) const {

}

int Grafo::obtTotArc() const {

}

int Grafo::obtTotVrt() const {

}

int Grafo::obtTotVrtSusceptibles() const {

}

int Grafo::obtTotVrtInfectados() const {

}

int Grafo::obtTotVrtResistentes() const {

}

Nodo& Grafo::operator[](int idVrt) {

}

double Grafo::coeficienteLocalAgrupamiento(int idVrt) const {

}

bool Grafo::conformidadPareto() const {

}

