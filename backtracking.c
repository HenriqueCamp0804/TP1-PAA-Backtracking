#include <stdio.h>
#include <stdbool.h>
#include "backtracking.h"
#include "mapa.h"

// Usando seus nomes de struct: 'Mapa' e 'Analise'
static bool movimentar(
    Mapa *mapa, Analise *analise,
    int linha, int coluna,
    int durabilidadeAtual, int pecasColetadas, int profundidadeAtual
){
    //MODO ANALISE
    #ifdef MODO_ANALISE
    // Usando seus nomes de variáveis: 'chamadaRecursiva', 'profundidadeMaxima'
    analise->chamadaRecursiva++;
    if(profundidadeAtual > analise->profundidadeMaxima){
        analise->profundidadeMaxima = profundidadeAtual;
    }
    #endif
    
    //Casos de falha
    //Sair dos limites
    if(linha<0 || linha >= mapa->altura || coluna < 0 || coluna >= mapa->largura){
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

    mapa->localVisitado[linha][coluna] = true; 

    char celulaAtual = mapa->matrizMapa[linha][coluna];
    if(celulaAtual == 'P'){
        pecasColetadas++;
        durabilidadeAtual += mapa->bonusPeca;
    }

    //Imprimir estado atual
    printf("Linha: %d, Coluna: %d; D: %d, pecas restantes: %d\n", linha+1, coluna+1,durabilidadeAtual,4-pecasColetadas);

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
    int proxDurabilidade = durabilidadeAtual;
    if(pecasColetadas < 4){
        proxDurabilidade -= mapa->custoMovimento;
    }
    
    //Movimentacoes Verticais
    if(celulaAtual == '|' || celulaAtual == '+' || celulaAtual == 'X' || celulaAtual == 'P'){
        if(movimentar(mapa,analise,linha + 1,coluna,proxDurabilidade,pecasColetadas,profundidadeAtual+1)){
            return true;
        }
        if(movimentar(mapa,analise,linha - 1,coluna,proxDurabilidade,pecasColetadas,profundidadeAtual+1)){
            return true;
        }
    }

    //Movimentacoes Horizontais
    if(celulaAtual == '-' || celulaAtual == '+' || celulaAtual == 'X' || celulaAtual == 'P' ){
        if(movimentar(mapa, analise, linha, coluna + 1, proxDurabilidade, pecasColetadas, profundidadeAtual + 1)){
            return true;
        }
        if(movimentar(mapa,analise,linha,coluna - 1, proxDurabilidade,pecasColetadas, profundidadeAtual + 1)){
            return true;
        }
    }


    mapa->localVisitado[linha][coluna] = false;
    return false;
}

// Usando seus nomes de função e structs
bool resolverLabirinto(Mapa *mapa,Analise *analise){
    analise->chamadaRecursiva = 0;
    analise->profundidadeMaxima = 0;

    return movimentar(mapa,analise,
    mapa->posInicial_linha,mapa->posInicial_coluna,
    mapa->durabilidadeInicial,0,0);
    
}