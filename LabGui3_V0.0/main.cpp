/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: Alan
 *
 * Created on 11 de septiembre de 2018, 05:36 PM
 */

#include <iostream>
using namespace std;

#include "Grafo.h"
#include "Simulador.h"
#include "Nodo.h"
/*
 * 
 */
int main(int argc, char** argv) {
    cout << "Bienvenido al simulador de dispersión de virus." << endl;
    cout << "Ingrese el nombre del archivo de experimentos: ";
    string nombreExperimentos;
    cin >> nombreExperimentos;
    cout << endl;
    ifstream archivoExperimentos( nombreExperimentos.c_str() );
    if( archivoExperimentos.fail() ){
        cout << "El archivo " << nombreExperimentos << " de extensión .txt no existe.";
        return 0;
    }
    
    Grafo grafo(0,0);
    int N, K, repeticiones,construccion, num = 1;
    double parametrosSimulacion[5], p;
    double comprobaciones[] = {0.0, 0.1, 0.0, 0.1, 1.0};
    string nombreRedEntrada;
    string salidaExperimento = "Salida_Experimento" + to_string(num) + ".txt";
    while( !archivoExperimentos.eof() ){
        salidaExperimento = "Salida_Experimento" + to_string(num) + ".txt";
        ofstream salida( salidaExperimento.c_str() );
        for( int i = 0; i < 5; i++ ){
            archivoExperimentos >> parametrosSimulacion[i];
            if( (i == 1 || i == 3 ) && !(parametrosSimulacion[i] <= comprobaciones[i]) ){
                cout << "El valor vsc o rc tomado de " << nombreExperimentos << " no se encuentra en el rango apropiado para hacer una comparacion con netlogoweb.org" << endl;
            } else if( i == 4 && !(parametrosSimulacion[i] <= comprobaciones[i]) ){
                cout << "El valor grc tomado de " << nombreExperimentos << " no se encuentra en el rango apropiado." << endl;
            }
        }
        archivoExperimentos >> repeticiones;
        archivoExperimentos >> construccion;
        archivoExperimentos.get();
        if( construccion == 2 ){
            archivoExperimentos >> nombreRedEntrada;
            ifstream archivo( nombreRedEntrada.c_str() );
            Grafo grafo1( archivo );
            grafo = grafo1;
        } else {
            archivoExperimentos >> N;
            if( construccion == 1 ){
                archivoExperimentos >> K;
                archivoExperimentos >> p;
                Grafo grafo1( N, K, p );
                grafo = grafo1;
            } else {
                archivoExperimentos >> p;
                Grafo grafo1( N, p );
                grafo = grafo1;
            }
        }
        for( int i = 0; i < repeticiones; i++ ){
            if( construccion == 2 ){
                Simulador simulador( grafo );
                simulador.iniciarSimulacion( parametrosSimulacion[0], parametrosSimulacion[1], parametrosSimulacion[2], parametrosSimulacion[3], parametrosSimulacion[4] );
                simulador.simular();
            } else if( construccion == 1 ){
                Simulador simulador( grafo );
                simulador.iniciarSimulacion( parametrosSimulacion[0], parametrosSimulacion[1], parametrosSimulacion[2], parametrosSimulacion[3], parametrosSimulacion[4] );
                simulador.simular();
            } else {
                Simulador simulador( grafo );
                simulador.iniciarSimulacion( parametrosSimulacion[0], parametrosSimulacion[1], parametrosSimulacion[2], parametrosSimulacion[3], parametrosSimulacion[4] );
                simulador.simular();
            }
            
            salida << "-----------------------------------------" << endl;
            salida << "Simulación " << i+1 << endl;
            salida << "-----------------------------------------" << endl;
            ifstream recibo( "salidaSimulacion.txt" );
            string temporal;
            while( !recibo.eof() ){
                while( recibo.peek() != '\n' && !recibo.eof() ){
                    recibo >> temporal;
                    salida << temporal << " ";
                }
                recibo.get();
                salida << endl;
            }
            recibo.close();
        }
        salida.close();
        remove( "salidaSimulacion.txt" );
        cout << "Se ha producido la " << salidaExperimento << endl;
        num++;
    }
    
    return 0;
}