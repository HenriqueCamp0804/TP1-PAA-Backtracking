#ifndef BACKTRACKING_H
#define BACKTRACKING_H

#include "mapa.h"

typedef struct{
    long long chamadaRecursiva;
    int profundidadeMaxima;
} Analise;

bool resolverLabirinto(Mapa *mapa, Analise *analise);

#endif //BACKTRACKING.H