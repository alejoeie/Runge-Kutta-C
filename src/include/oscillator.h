#ifndef OSCILLATOR_
#define OSCILLATOR_
#include<stdlib.h>

/* */
typedef struct estado {
    double x;
    double y;
    double z;
} estado;

typedef struct RK4 {
    double k1;
    double k2; 
    double k3;
    double k4;
} RK4;

estado osciladorPrima(estado system);
void obtenerKs(RK4 *kFunctions, estado currentState, double h);
estado siguienteEstado(estado currentState, RK4 *kFunctions, double h);
estado *RK4Oscilador(estado estadoInicial, double h, int tMax, int *totalStates);
void exportarEstados(const char* filePath, estado* statesCalculated, int totalAmountStates);
#endif
