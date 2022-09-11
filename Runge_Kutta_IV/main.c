#include "include/oscillator.h"
#include <stdio.h>
int main(int argc, char const *argv[])
{
    estado estadoInicial;
    estadoInicial.x = 2.3; 
    estadoInicial.y = -1.3;
    estadoInicial.z = 10.0;

    double paso = 0.01;
    double tMax = 100;
    // estado derivada = osciladorPrima(estadoInicial);

    printf("Imprimiendo funcion principal");
    int size;

    estado* estados = RK4Oscilador(estadoInicial, paso, tMax, &size);

    exportarEstados("salida.txt", estados, size);
    
    free(estados);

    return 0;
}
