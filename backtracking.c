#include <stdio.h>
#include <stdbool.h>
#include "backtracking.h"
#include "mapa.h"

static bool movimentar(
    Mapa *mapa, Analise *analise,
    int linha, int coluna,
    int durabilidadeAtual, int pecasColetadas, int profundidadeAtual
){
    //MODO ANALISE - SO SE FOR COMPILADO COM 'make ANALISE=1'
    #ifdef MODO_ANALISE
    analise->chamadaRecursiva++;
    if(profundidadeAtual > analise->profundidadeMaxima){
        analise->profundidadeMaxima = profundidadeAtual;
    }
    #endif
    
    //Casos de falha
    //Sair dos limites
    if(linha < 0 || linha >= mapa->altura || coluna < 0 || coluna >= mapa->largura){
        return false;
    }
    //Durabilidade acabar
    if(durabilidadeAtual <= 0){
        return false;
    }
    //Local onde nao pode passar "."
    if(mapa->matrizMapa[linha][coluna] == '.'){
        return false;
    }
    //Local ja foi visitado
    if(mapa->localVisitado[linha][coluna] == true){
        return false;
    }

    //Processar a célula atual
    //Marcar que a celula foi visitada (CORRIGIDO: = ao invés de ==)
    mapa->localVisitado[linha][coluna] = true;

    char celulaAtual = mapa->matrizMapa[linha][coluna];
    if(celulaAtual == 'P'){
        pecasColetadas++;
        durabilidadeAtual += mapa->bonusPeca;
    }

    //Imprimir estado atual
    printf("Linha: %d, Coluna: %d, Durabilidade: %d, Pecas restantes: %d\n", 
           linha+1, coluna+1, durabilidadeAtual, 4-pecasColetadas);

    //Encontra destino
    if(celulaAtual == 'F'){
        if(pecasColetadas >= 4){
            printf("\n#MENSAGEM FINAL\nA jornada sera finalizada sem mais desafios\n");
        }else{
            printf("\n#MENSAGEM FINAL\nA tripulacao finalizou sua jornada\n");
        }
        return true;
    }

    //Passo recursivo
    //Durabilidade para o proximo movimento
    int proxDurabilidade = durabilidadeAtual;
    //Se nao temos as 4 peças coletadas, durabilidade diminui
    if(pecasColetadas < 4){
        proxDurabilidade -= mapa->custoMovimento;
    }
    
    //Movimentos verticais (cima/baixo) - para | + X P
    if(celulaAtual == '|' || celulaAtual == '+' || celulaAtual == 'X' || celulaAtual == 'P'){
        if(movimentar(mapa, analise, linha + 1, coluna, proxDurabilidade, pecasColetadas, profundidadeAtual+1)){
            return true;
        }
        if(movimentar(mapa, analise, linha - 1, coluna, proxDurabilidade, pecasColetadas, profundidadeAtual+1)){
            return true;
        }
    }

    //Movimentos horizontais (esquerda/direita) - para - + X P
    if(celulaAtual == '-' || celulaAtual == '+' || celulaAtual == 'X' || celulaAtual == 'P'){
        if(movimentar(mapa, analise, linha, coluna + 1, proxDurabilidade, pecasColetadas, profundidadeAtual + 1)){
            return true;
        }
        if(movimentar(mapa, analise, linha, coluna - 1, proxDurabilidade, pecasColetadas, profundidadeAtual + 1)){
            return true;
        }
    }
    
    //Backtrack: desmarcar célula como visitada
    mapa->localVisitado[linha][coluna] = false;
    return false;
}

bool resolverLabirinto(Mapa *mapa, Analise *analise){
    analise->chamadaRecursiva = 0;
    analise->profundidadeMaxima = 0;

    return movimentar(mapa, analise,
                     mapa->posInicial_linha, mapa->posInicial_coluna,
                     mapa->durabilidadeInicial, 0, 0);
}