#include <stdio.h>
#include <stdlib.h>
#include "mapa.h"
#include "backtracking.h"

int main(){
    char nomeArquivo[100];
    char continuar;

    do{
        printf("\n===========================================\n");
        printf("A Jornada do Expresso Interestelar\n");
        printf("=============================================\n");
        printf("Digite o nome do arquivo de entrada:\n");
        scanf("%s",nomeArquivo);

        Analise analise; 
        Mapa *mapa = carregarMapa(nomeArquivo);
        if(mapa == NULL){
            fprintf(stderr,"Falha ao carregar o jogo. Verificar o arquivo de entrada.\n");

        } else{
            printf("-------Iniciando Jornada-------\n");
            bool buscaSolucao = resolverLabirinto(mapa, &analise);
            printf("--------Fim da Jornada----------\n");

            if(!buscaSolucao){
                printf("\nApesar da bravura a tripulacao falhou em sua jornada\n");
            }

            #ifdef MODO ANALISE
            printf("\n====================================\n");
            printf("|            MODO ANALISE             |\n");
            printf("======================================\n");
            printf("Total de chamadas recursivas: %lld\n", analise.chamadaRecursiva);
            printf("Profundidade maxima de recursao: %d\n",analise.profundidadeMaxima);
            printf("======================================\n");
            #endif

            liberarMapa(mapa);

        }
        printf("Deseja executar com outro arquivo? (s/n): ");
        scanf(" %c", &continuar);


    } while (continuar == 's' || continuar == 'S');
    printf("\nEncerrando o programa.\n");
    return 0;
}