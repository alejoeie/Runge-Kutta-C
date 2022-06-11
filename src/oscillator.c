#include "include/oscillator.h"
#include <stdio.h>

estado osciladorPrima(estado system){
    double a = 10.0;
    double b = 4.85;
    double c = 10.0;
    estado derivative; 
    derivative.x = a * (b*system.y - system.x);
    derivative.y = c*system.x-(system.x * system.z);
    derivative.z = (system.x * system.y) - (4.85 * system.z);
    return derivative;
}

void obtenerKs(RK4 *kFunctions, estado currentState, double h){
    RK4 kx;
    RK4 ky;
    RK4 kz;
    estado intermedio;

    intermedio = osciladorPrima(currentState);
    kx.k1 = intermedio.x;
    ky.k1 = intermedio.y;
    kz.k1 = intermedio.z;

    intermedio.x = currentState.x + 0.5 * (kx.k1) * h;
    intermedio.y = currentState.y + 0.5 * (ky.k1) * h;
    intermedio.z = currentState.z + 0.5 * (kz.k1) * h;
    intermedio = osciladorPrima(intermedio);

    kx.k2 = intermedio.x;
    ky.k2 = intermedio.y;
    kz.k2 = intermedio.z;

    intermedio.x = currentState.x + 0.5 * (kx.k2) * h;
    intermedio.y = currentState.y + 0.5 * (ky.k2) * h;
    intermedio.z = currentState.z + 0.5 * (kz.k2) * h;

    intermedio = osciladorPrima(intermedio);
    kx.k3 = intermedio.x;
    ky.k3 = intermedio.y;
    kz.k3 = intermedio.z;
    intermedio.x = currentState.x + (kx.k3) * h;
    intermedio.y = currentState.y + (ky.k3) * h;
    intermedio.z = currentState.z + (kz.k3) * h;
    intermedio = osciladorPrima(intermedio);
    kx.k4 = intermedio.x;
    ky.k4 = intermedio.y;
    kz.k4 = intermedio.z;

    kFunctions[0] = kx;
    kFunctions[1] = ky;
    kFunctions[2] = kz;
}

estado siguienteEstado(estado currentState, RK4 *kFunctions, double h){
    estado nextState;
    nextState.x = currentState.x + 0.1667 * ((kFunctions[0].k1) + 2 * (kFunctions[0].k2) + 2 * (kFunctions[0].k3) + (kFunctions[0].k4)) * h;
    nextState.y = currentState.y + 0.1667 * ((kFunctions[1].k1) + 2 * (kFunctions[1].k2) + 2 * (kFunctions[1].k3) + (kFunctions[1].k4)) * h;
    nextState.z = currentState.z + 0.1667 * ((kFunctions[2].k1) + 2 * (kFunctions[2].k2) + 2 * (kFunctions[2].k3) + (kFunctions[2].k4)) * h;
    return nextState;
}

estado *RK4Oscilador(estado estadoInicial, double h, int tMax, int *totalStates){
    double amount_states = tMax/h;
    *totalStates = amount_states;
    estado estActual = estadoInicial;
    estado *estadoAllocate;
    estadoAllocate = malloc(amount_states*sizeof(estado));
    RK4* vars = malloc(3*sizeof(RK4));
    for (int i; i < amount_states; i++){
        estadoAllocate[i] = estActual;
        obtenerKs(vars, estActual, h);
        estActual = siguienteEstado(estActual, vars, h);
    }
    free(vars);
    return estadoAllocate;
}

void exportarEstados(const char* filePath, estado* statesCalculated, int totalAmountStates){
    FILE* fptr;

    fptr = fopen(filePath, "w");
    double dimx;
    double dimy;
    double dimz;
    if (fptr){
        for (int i=0; i < totalAmountStates; i++){
            dimx = statesCalculated[i].x;
            dimy = statesCalculated[i].y;
            dimz = statesCalculated[i].z;

            fprintf(fptr, "%.4f, %.4f, %.4f\n", dimx, dimy, dimz);
        }
        fclose(fptr);
    }
    else{
        printf("No files were found");
    }

}
