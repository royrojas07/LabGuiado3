///*
// * To change this license header, choose License Headers in Project Properties.
// * To change this template file, choose Tools | Templates
// * and open the template in the editor.
// */
//
///* 
// * File:   main.cpp
// * Author: Alan
// *
// * Created on 11 de septiembre de 2018, 05:36 PM
// */
//
//#include <iostream>
//using namespace std;
//
//#include "Grafo.h"
//#include "Simulador.h"
//#include "Nodo.h"
///*
// * 
// */
//int main(int argc, char** argv) {
//    cout << "Bienvenido al simulador de dispersión de virus." << endl;
//    cout << "Ingrese el nombre del archivo de experimentos: ";
//    string nombreExperimentos;
//    cin >> nombreExperimentos;
//    cout << endl;
//    ifstream archivoExperimentos( nombreExperimentos.c_str() );
//    if( archivoExperimentos.fail() ){
//        cout << "El archivo " << nombreExperimentos << " de extensión .txt no existe.";
//        return 0;
//    }
//    
//    Grafo grafo(0,0);
//    int N, K, repeticiones,construccion, num = 1;
//    double parametrosSimulacion[5], p;
//    double comprobaciones[] = {0.0, 0.1, 0.0, 0.1, 1.0};
//    string nombreRedEntrada;
//    string salidaExperimento = "Salida_Experimento" + to_string(num) + ".txt";
//    while( !archivoExperimentos.eof() ){
//        salidaExperimento = "Salida_Experimento" + to_string(num) + ".txt";
//        ofstream salida( salidaExperimento.c_str() );
//        for( int i = 0; i < 5; i++ ){
//            archivoExperimentos >> parametrosSimulacion[i];
//            if( (i == 1 || i == 3 ) && !(parametrosSimulacion[i] <= comprobaciones[i]) ){
//                cout << "El valor vsc o rc tomado de " << nombreExperimentos << " no se encuentra en el rango apropiado para hacer una comparacion con netlogoweb.org" << endl;
//            } else if( i == 4 && !(parametrosSimulacion[i] <= comprobaciones[i]) ){
//                cout << "El valor grc tomado de " << nombreExperimentos << " no se encuentra en el rango apropiado." << endl;
//            }
//        }
//        archivoExperimentos >> repeticiones;
//        archivoExperimentos >> construccion;
//        archivoExperimentos.get();
//        if( construccion == 2 ){
//            archivoExperimentos >> nombreRedEntrada;
//            ifstream archivo( nombreRedEntrada.c_str() );
//            Grafo grafo1( archivo );
//            grafo = grafo1;
//        } else {
//            archivoExperimentos >> N;
//            if( construccion == 1 ){
//                archivoExperimentos >> K;
//                archivoExperimentos >> p;
//                Grafo grafo1( N, K, p );
//                grafo = grafo1;
//            } else {
//                archivoExperimentos >> p;
//                Grafo grafo1( N, p );
//                grafo = grafo1;
//            }
//        }
//        for( int i = 0; i < repeticiones; i++ ){
//            if( construccion == 2 ){
//                Simulador simulador( grafo );
//                simulador.iniciarSimulacion( parametrosSimulacion[0], parametrosSimulacion[1], parametrosSimulacion[2], parametrosSimulacion[3], parametrosSimulacion[4] );
//                simulador.simular();
//            } else if( construccion == 1 ){
//                Simulador simulador( grafo );
//                simulador.iniciarSimulacion( parametrosSimulacion[0], parametrosSimulacion[1], parametrosSimulacion[2], parametrosSimulacion[3], parametrosSimulacion[4] );
//                simulador.simular();
//            } else {
//                Simulador simulador( grafo );
//                simulador.iniciarSimulacion( parametrosSimulacion[0], parametrosSimulacion[1], parametrosSimulacion[2], parametrosSimulacion[3], parametrosSimulacion[4] );
//                simulador.simular();
//            }
//            
//            salida << "-----------------------------------------" << endl;
//            salida << "Simulación " << i+1 << endl;
//            salida << "-----------------------------------------" << endl;
//            ifstream recibo( "salidaSimulacion.txt" );
//            string temporal;
//            while( !recibo.eof() ){
//                while( recibo.peek() != '\n' && !recibo.eof() ){
//                    recibo >> temporal;
//                    salida << temporal << " ";
//                }
//                recibo.get();
//                salida << endl;
//            }
//            recibo.close();
//        }
//        salida.close();
//        remove( "salidaSimulacion.txt" );
//        cout << "Se ha producido la " << salidaExperimento << endl;
//        num++;
//    }
//    
//    return 0;
//}

#include <stdlib.h>
#include <iostream>
#include <string>
#include "Grafo.h"
#include "Simulador.h"
using namespace std;

void testArchivoTexto() {
    ifstream archivo( "redPeq.txt" );
    Grafo grafo(archivo);
    archivo.open("redPeq.txt");
    string cantNodos;
    getline( archivo, cantNodos );
    int totalNodos = atoi( cantNodos.c_str() );
    int temp=0; 
    int count=0;
    int i=0; 
    int totalArcos = 0;
    bool adyPorVrt = true;
    while( !(archivo.eof()) ){
        while( archivo.peek() != '\n' && !archivo.eof() ){
            archivo >> temp;
            count++;
            totalArcos++;
            archivo.get();
        }
        if( count != grafo.obtCntVrtAdys( i ) && count != 0 ){
            adyPorVrt = false;
            break;
        } else {
            i++;
        }
        archivo.get();
        count=0; 
    }
    if( (grafo.obtTotVrt() != totalNodos) || (grafo.obtTotArc() != totalArcos/2) || !adyPorVrt ) {
        std::cout << "%TEST_FAILED% time=0 testname=testGrafo3 (newsimpletest1) testPorArchivo redPeq" << std::endl;
    }

    archivo.close();
    archivo.open( "redMed.txt" );
    Grafo grafo2(archivo);
    archivo.open( "redMed.txt" );
    getline( archivo, cantNodos );
    totalNodos = atoi( cantNodos.c_str() );
    count = 0;
    i = 0;
    totalArcos = 0;
    adyPorVrt = true;
    while( !archivo.eof() ){
        while( archivo.peek() != '\n' && !archivo.eof() ){
            archivo >> temp;
            count++;
            totalArcos++;
            archivo.get();
        }
        if( count != grafo2.obtCntVrtAdys( i ) && count != 0 ){
            adyPorVrt = false;
            break;
        } else{
            i++;
        }
        archivo.get();
        count = 0;
    }
    if( (grafo2.obtTotVrt() != totalNodos) || (grafo2.obtTotArc() != totalArcos/2) || !adyPorVrt ) {
        std::cout << "%TEST_FAILED% time=0 testname=testGrafo3 (newsimpletest1) testPorArchivo redMed" << std::endl;
    }

    archivo.close();
    archivo.open( "redGrande.txt" );
    Grafo grafo3(archivo);
    archivo.open( "redGrande.txt" );
    getline( archivo, cantNodos );
    totalNodos = atoi( cantNodos.c_str() );
    count = 0;
    i = 0;
    totalArcos = 0;
    adyPorVrt = true;
    while( !archivo.eof() ){
        while( archivo.peek() != '\n' && !archivo.eof() ){
            archivo >> temp;
            count++;
            totalArcos++;
            archivo.get();
        }
        if( count != grafo3.obtCntVrtAdys( i ) && count != 0 ){
            adyPorVrt = false;
            break;
        } else{
            i++;}
        archivo.get();
        count = 0;
    }
    if( (grafo3.obtTotVrt() != totalNodos) || (grafo3.obtTotArc() != totalArcos/2) || !adyPorVrt ) {
        std::cout << "%TEST_FAILED% time=0 testname=testGrafo3 (newsimpletest1) testPorArchivo redGrande" << std::endl;
    }
}

void testPorCopia() {
    ifstream archivo( "redPeq.txt" );
    Grafo orig(archivo);
    Grafo grafo1(orig);
    bool func=true;
    int contador =(orig.obtTotVrt())-1;
    if((orig.obtTotVrt()!=grafo1.obtTotVrt()))
    {
        func=false;
    }
    while( contador >= 0 ){
        if(orig.obtCntVrtAdys(contador)!=grafo1.obtCntVrtAdys(contador))
        {
            func=false;
            contador=-1;
        }
        contador=contador-1;
    }
    if(orig.obtTotArc()!=grafo1.obtTotArc())
    {
        func=false;
    }
    if (func ==false) {
        std::cout << "%TEST_FAILED% time=0 testname=ConstructorPorCopia (newsimpletest1) Por copia redPeq" << std::endl;
    }

    //segunda prueba
    archivo.open( "redMed.txt" );
    Grafo orig2(archivo);
    Grafo grafo2(orig2);
    func=true;
    contador =(orig2.obtTotVrt())-1;
    if((orig2.obtTotVrt()!=grafo2.obtTotVrt()))
    {
        func=false;
    }
    while( contador >= 0 ){
        if(orig2.obtCntVrtAdys(contador)!=grafo2.obtCntVrtAdys(contador))
        {
            func=false;
            contador=-1;
        }
        contador=contador-1;
    }
    if(orig2.obtTotArc()!=grafo2.obtTotArc())
    {
        func=false;
    }
    if (func ==false) {
        std::cout << "%TEST_FAILED% time=0 testname=ConstructorPorCopia (newsimpletest1) Por copia redMed" << std::endl;
    }

    //tercera prueba
    archivo.open( "redGrande.txt" );
    Grafo orig3(archivo);
    Grafo grafo3(orig3);
    func=true;
    contador =(orig3.obtTotVrt())-1;
    if((orig3.obtTotVrt()!=grafo3.obtTotVrt()))
    {
        func=false;
    }
    while( contador >= 0 ){
        if(orig3.obtCntVrtAdys(contador)!=grafo3.obtCntVrtAdys(contador))
        {
            func=false;
            contador=-1;
        }
        contador=contador-1;
    }
    if(orig3.obtTotArc()!=grafo3.obtTotArc())
    {
        func=false;
    }
    if (func ==false) {
        std::cout << "%TEST_FAILED% time=0 testname=ConstructorPorCopia (newsimpletest1) Por copia redGrande" << std::endl;
    }
}

void testRedesAleatorias(){
    int N = 100;
    double p = 0.2;
    double promedTotArc = 0;
    int cantVrt = 0;
    for( int i = 0; i < 100; i++ ){
        Grafo grafo(N, p);
        promedTotArc = promedTotArc + grafo.obtTotArc();
        cantVrt =cantVrt+grafo.obtTotVrt();
    }
    promedTotArc = promedTotArc / 100;
    cantVrt = cantVrt / 100;
    double norma = p*N*(N-1)/2;
    double segun = N*p;
    if( !( promedTotArc <= norma + segun && norma - segun <= promedTotArc ) || cantVrt != N ){
        std::cout << "%TEST_FAILED% time=0 testname=testGrafo (newsimpletest1) Redes Aleatorias(100 Nodos)" << std::endl;
    }

    N = 1000;
    p = 0.4;
    promedTotArc = 0;
    cantVrt = 0;
    for( int i = 0; i < 100; i++ ){
        cout << i << endl;
        Grafo grafo(N, p);
        promedTotArc += grafo.obtTotArc();
        cantVrt += grafo.obtTotVrt();
    }
    promedTotArc = promedTotArc / 100;
    cantVrt = cantVrt / 100;
    norma = p*N*(N-1)/2;
    segun = N*p;
    if( !( promedTotArc < norma + segun && norma - segun < promedTotArc ) || cantVrt != N ){
        std::cout << "%TEST_FAILED% time=0 testname=testGrafo (newsimpletest1) Redes Aleatorias(1000 Nodos)" << std::endl;
    }

    N = 10000;
    p = 0.4;
    promedTotArc = 0;
    cantVrt = 0;
    for( int i = 0; i < 100; i++ ){
        cout << i << endl;
        Grafo grafo(N, p);
        promedTotArc += grafo.obtTotArc();
        cantVrt += grafo.obtTotVrt();
    }
    promedTotArc = promedTotArc / 100;
    cantVrt = cantVrt / 100;
    norma = p*N*(N-1)/2;
    segun = N*p;
    if( !( promedTotArc < norma + segun && norma - segun < promedTotArc ) || cantVrt != N ){
        std::cout << "%TEST_FAILED% time=0 testname=testGrafo (newsimpletest1) Redes Aleatorias(10000 Nodos)" << std::endl;
    }
}
void testConformidadPareto() {
    bool func=false;
    ifstream archivo1( "redPeq.txt" );
    Grafo grafo1(archivo1);
    bool result1 = grafo1.conformidadPareto();
    if ( result1 != true ){
        std::cout << "%TEST_FAILED% time=0 testname=testConformidadPareto (newsimpletest1) pareto redPeq" << std::endl;
    }

    ifstream archivo3( "redGrande.txt" );
    Grafo grafo3(archivo3);
    bool result3 = grafo3.conformidadPareto();
    if ( result3 != true ){
        std::cout << "%TEST_FAILED% time=0 testname=testConformidadPareto (newsimpletest1) pareto redGrande" << std::endl;
    }
}

void testPequenosMundos(){
    int N = 4500;
    int K = 10;
    double beta = 0.9;
    Grafo grafo(N, K, beta);
    if( !grafo.conformidadPareto() ) {
        std::cout << "%TEST_FAILED% time=0 testname=testGrafo2 (newsimpletest1) message=error Pequenos Mundos" << std::endl;
    }

    N = 5000;
    K = 10;
    beta = 0.8;
    Grafo grafo2(N, K, beta);
    if( !grafo2.conformidadPareto() ) {
        std::cout << "%TEST_FAILED% time=0 testname=testGrafo2 (newsimpletest1) message=error Pequenos Mundos" << std::endl;
    }

    N = 3500;
    K = 10;
    beta = 0.9;
    Grafo grafo3(N, K, beta);
    if( !grafo3.conformidadPareto() ) {
        std::cout << "%TEST_FAILED% time=0 testname=testGrafo2 (newsimpletest1) message=error Pequenos Mundos" << std::endl;
    }
}

void testCoeficienteLocalAgrupamiento() {
    ifstream archivo( "redPeq.txt" );
    Grafo orig(archivo);
    double coeficienteNodo5 = orig.coeficienteLocalAgrupamiento(4);
    double calculoManual = (double)2/15;
    if( coeficienteNodo5 != calculoManual ){
        std::cout << "%TEST_FAILED% time=0 testname=testCoeficienteLocalAgrupamiento (newsimpletest1) coeficienteLocal para Nodo4" << std::endl;
    }

    double coeficienteNodo6 = orig.coeficienteLocalAgrupamiento(5);
    calculoManual = (double)1/2;
    if( coeficienteNodo6 != calculoManual ){
        cout << coeficienteNodo6 << endl;
        std::cout << "%TEST_FAILED% time=0 testname=testCoeficienteLocalAgrupamiento (newsimpletest1) coeficienteLocal para Nodo5" << std::endl;
    }

    double coeficienteNodo10 = orig.coeficienteLocalAgrupamiento(9);
    calculoManual = (double)1/10;
    if( coeficienteNodo10 != calculoManual ){
        cout << coeficienteNodo10 << endl;
        std::cout << "%TEST_FAILED% time=0 testname=testCoeficienteLocalAgrupamiento (newsimpletest1) coeficienteLocal para Nodo9" << std::endl;
    }
}

int main(int argc, char** argv) {
    cout << "Prueba a constructor por archivo iniciada" << endl;
    testArchivoTexto();
    cout << "Prueba a constructor por archivo finalizada" << endl;

    cout << "Prueba a constructor por copia iniciada" << endl;
    testPorCopia();
    cout << "Prueba a constructor por copia finalizada" << endl;

    cout << "Prueba a constructor de pequeños mundos iniciada" << endl;
    testPequenosMundos();
    cout << "Prueba a constructor de pequeños mundos finalizada" << endl;

    cout << "Prueba a constructor de redes aleatorias iniciada" << endl;
    //testRedesAleatorias();
    cout << "Prueba a constructor de redes aleatorias finalizada" << endl;

    cout << "Prueba a conformidad pareto iniciada" << endl;
    testConformidadPareto();
    cout << "Prueba a conformidad pareto finalizada" << endl;

    cout << "Prueba a coeficiente local iniciada" << endl;
    testCoeficienteLocalAgrupamiento();
    cout << "Prueba a coeficiente local finalizada" << endl;

    return (EXIT_SUCCESS);
}