/* 
 * File:   Simulador.cpp
 * Author: Alan
 * 
 * Created on 2 de abril de 2015, 06:46 PM
 */

#include "Simulador.h"

Simulador::Simulador(Grafo& g): grafo(g) {
    
}

Simulador::~Simulador() {
    
}

void Simulador::iniciarSimulacion(int ios, double vsc, int vcf, double rc, double grc){
    this->ios = ios;
    this->vsc = vsc;
    this->vcf = vcf;
    this->rc = rc;
    this->grc = grc;
    
    vector<int> porInfectar;
    porInfectar.resize( ios );
    int cantNodos = grafo.obtTotVrt();
    bool noInfectado;
    unsigned int seed = chrono::system_clock::now().time_since_epoch().count();
    default_random_engine generator(seed);
    uniform_int_distribution<int> distribution(0, cantNodos-1);
    for( int i = 0; i < ios; i++ ){
        int random = rand()%cantNodos;
        noInfectado = false;
        while( !noInfectado ){
            noInfectado = true;
            for( int j = 0; j < porInfectar.size(); j++ ){
                if( random == porInfectar[j] ){
                    noInfectado = false;
                    j = porInfectar.size();
                }
                if( !noInfectado ){
                    random = distribution(generator);
                }
            }
        }
        porInfectar[i] = random;
        grafo[random].modEstado( Nodo::I );
    }
}

void Simulador::simular() {
    unsigned int seed = chrono::system_clock::now().time_since_epoch().count();
    default_random_engine generator(seed);
    uniform_int_distribution<int> distribution(0, 9999);
    
    int N = grafo.obtTotVrt();
    int S, R, I;
    int tic = 1;
    ofstream salida( "salidaSimulacion.txt" );
    bool hayInfectado = true;
    vector<pair<int, Nodo::E>> porModificar;
    vector<int> vecinosDeInfectado;
    double randInfeccion, randRecovery, randResistencia, porcentajeS, porcentajeR, porcentajeI, promedioS, promedioR, promedioI;
    while( hayInfectado ){
        S = 0;
        R = 0;
        I = 0;
        for( int i = 0; i < N; i++ ){
            if( grafo[i].obtEstado() == Nodo::E::I ){
                grafo.obtIdVrtAdys( i, vecinosDeInfectado );
                for( int j = 0; j < vecinosDeInfectado.size(); j++ ){
                   if( grafo[vecinosDeInfectado[j]].obtEstado() == Nodo::E::S ){
                       randInfeccion = (double)distribution(generator)/10000;
                        if( randInfeccion <= vsc ){
                            pair<int, Nodo::E> par(vecinosDeInfectado[j], Nodo::E::I);
                            if( find( porModificar.begin(), porModificar.end(), par ) == porModificar.end() ){
                                porModificar.push_back( par );
                            }
                        }
                   }
                }
                if( (tic % vcf) == 0 ){
                    randRecovery = (double)distribution(generator)/10000;
                    if( randRecovery <= rc ){
                        pair<int, Nodo::E> par(i, Nodo::E::S);
                        porModificar.push_back( par );
                        randResistencia = (double)distribution(generator)/10000;
                        if( randResistencia <= grc ){
                            porModificar.pop_back();
                            pair<int, Nodo::E> par(i, Nodo::E::R);
                            porModificar.push_back( par );
                        }
                    }
                }
                vecinosDeInfectado.clear();
            }
        }
        
        for( int i = 0; i < porModificar.size(); i++ )
            grafo[porModificar[i].first].modEstado( porModificar[i].second );
        porModificar.clear();
        
        for( int j = 0; j < N; j++ ){
            if( grafo[j].obtEstado() == Nodo::E::I ){
                I++;
            } else if( grafo[j].obtEstado() == Nodo::E::R ){
                R++;
            } else {
                S++;
            }
        }
        
        promedioS = (((double)S/N)*100.0)/10.0;
        promedioR = (((double)R/N)*100.0)/10.0;
        promedioI = (((double)I/N)*100.0)/10.0;
        porcentajeS = ((double)S/N)*100.0;
        porcentajeR = ((double)R/N)*100.0;
        porcentajeI = ((double)I/N)*100.0;
        salida << "************************************************************" << endl;
        salida << "Tic: " << tic << ":" << endl;
        salida << "Promedio de Nodos Susceptibles: " << promedioS << " de 10. " << "Porcentaje de Nodos Susceptibles: " << porcentajeS << "%. Cantidad de Nodos Susceptibles: " << S << "." << endl;
        salida << "Promedio de Nodos Resistentes: " << promedioR << " de 10. " << "Porcentaje de Nodos Resistentes: " << porcentajeR << "%. Cantidad de Nodos Resistentes: " << R << "." << endl;
        salida << "Promedio de Nodos Infectados: " << promedioI << " de 10. " << "Porcentaje de Nodos Infectados: " << porcentajeI << "%. Cantidad de Nodos Infectados: " << I << "." << endl;
        
        hayInfectado = false;
        for( int i = 0; i < N; i++ ){
            if( grafo[i].obtEstado() == Nodo::E::I ){
                hayInfectado = true;
                i = N;
            }
        }
        
        tic++;
    }
    
    salida << "Cantidades FINALES en S y R:" << endl;
    salida << "Promedio de Nodos Susceptibles: " << promedioS << " de 10. " << "Porcentaje de Nodos Susceptibles: " << porcentajeS << "%. Cantidad de Nodos Susceptibles: " << S << "." << endl;
    salida << "Promedio de Nodos Resistentes: " << promedioR << " de 10. " << "Porcentaje de Nodos Resistentes: " << porcentajeR << "%. Cantidad de Nodos Resistentes: " << R << "." << endl;
    salida << "Cantidad de tics necesarios para establizar la red: " << tic-1 << "." << endl;
    salida << "****************************************************************" << endl;
    salida.close();
}