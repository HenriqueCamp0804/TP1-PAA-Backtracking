#ifndef MAPA_H
#define MAPA_H

#include <stdbool.h> 

// Estrutura para armazenar todos os dados do jogo

typedef struct{
    int altura;
    int largura;
    int durabilidadeInicial; //D
    int custoMovimento; //D'
    int bonusPeca; //A
    int posInicial_coluna; 
    int posInicial_linha;
    char **matrizMapa; //matriz para o mapa
    bool **localVisitado; // matriz para marcar os lugares que ja foram visitados

} Mapa;

//Funcoes
Mapa *carregarMapa(const char *nome_arquivo);
void liberarMapa(Mapa *mapa);
void imprimirMapa(Mapa *mapa); //opcional, para ajudar a testar

#endif 