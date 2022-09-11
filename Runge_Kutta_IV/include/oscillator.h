#ifndef OSCILLATOR_
#define OSCILLATOR_
#include<stdlib.h>

/* Define struct for states. */
typedef struct estado {
    double x;
    double y;
    double z;
} estado;
/* Define struct for ks result. */
typedef struct RK4 {
    double k1;
    double k2; 
    double k3;
    double k4;
} RK4;

/* This function gets the derivatives for 
the system based on its initial states.
param@ system = gets the actual states for obtaining its derivatives. */
estado osciladorPrima(estado system);

void obtenerKs(RK4 *kFunctions, estado currentState, double h);
estado siguienteEstado(estado currentState, RK4 *kFunctions, double h);
estado *RK4Oscilador(estado estadoInicial, double h, int tMax, int *totalStates);
void exportarEstados(const char* filePath, estado* statesCalculated, int totalAmountStates);
#endif
