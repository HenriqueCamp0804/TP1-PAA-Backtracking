#include <stdio.h>
#include <stdlib.h>
#include "mapa.h"

//Funcao para ler o arquivo e construir a matriz do mapa
Mapa *carregarMapa(const char *nome_arquivo){
    FILE *arquivo = fopen(nome_arquivo, "r");
    if(arquivo == NULL){
        perror("Erro ao abrir o arquivo\n");
        return NULL;
    }

    //Alocar o mapa
    Mapa *mapa = malloc(sizeof(Mapa));
    if(mapa == NULL){
        perror("Erro ao alocar memoria para o mapa");
        fclose(arquivo);
        return NULL;
    }

    //Leitura dos parametros (Durabilidade, Custo de movimento e Bonus de peca)
    if(fscanf(arquivo, "%d %d %d", &mapa->durabilidadeInicial, &mapa->custoMovimento, &mapa->bonusPeca) != 3){
        fprintf(stderr, "Erro: Falha ao ler os parametros do mapa(D, D', A) do arquivo.\n");
        free(mapa);
        fclose(arquivo);
        return NULL;
    }
    
    //Leitura das dimensões (Altura e largura)
    if(fscanf(arquivo, "%d %d", &mapa->altura, &mapa->largura) != 2){
        fprintf(stderr, "Erro: Falha ao ler as dimensoes do mapa(altura e largura).\n");
        free(mapa);
        fclose(arquivo);
        return NULL;
    }


    //Verificar se as dimensoes sao validas (> 0)
    if(mapa->altura <= 0 || mapa->largura <= 0){
        fprintf(stderr, "Erro: Dimensoes de mapa (%dx%d) invalidas.\n", mapa->altura, mapa->largura);
        free(mapa);
        fclose(arquivo);
        return NULL;
    }

    //Alocacao dinamica matrizes
    mapa->matrizMapa = malloc(mapa->altura * sizeof(char*));
    mapa->localVisitado = malloc(mapa->altura * sizeof(bool*));

    if(mapa->matrizMapa == NULL || mapa->localVisitado == NULL){
        perror("Erro ao alocar arrays de ponteiros das matrizes.\n");
        free(mapa->matrizMapa);
        free(mapa->localVisitado);
        free(mapa);
        fclose(arquivo);
        return NULL;
    }

    for (int i = 0; i < mapa->altura; i++){
        //Alocar memoria para cada linha
        mapa->matrizMapa[i] = malloc(mapa->largura * sizeof(char));
        mapa->localVisitado[i] = malloc(mapa->largura * sizeof(bool));
        //Se a alocacao de alguma linha falhar, apaga tudo
        if(mapa->matrizMapa[i] == NULL || mapa->localVisitado[i] == NULL){
            perror("Erro ao alocar linha das matrizes");
            //Apagar todas as linhas que ja foram alocadas ate i
            for(int k=0;k<i;k++){
                free(mapa->matrizMapa[k]);
                free(mapa->localVisitado[k]);
            }
            //Liberar espaco dos arrays
            free(mapa->matrizMapa);
            free(mapa->localVisitado);

            free(mapa);
            fclose(arquivo);
            return NULL;
        }
    }

    //Leitura do mapa e preenchimento das matrizes
    bool encontrarX = false;
    for(int i=0;i<mapa->altura;i++){
        for(int j=0;j<mapa->largura;j++){
            char c;
            //Ler caractere por caractere 
            do{
                c = fgetc(arquivo);
                if(c == EOF){
                    fprintf(stderr,"Erro: Fim inesperado de arquivo.\n");
                    liberarMapa(mapa);
                    fclose(arquivo);
                    return NULL;
                }
            }while (c == '\n' || c == '\r');
            
            //Armazenar o caractere lido na matriz do mapa
            mapa->matrizMapa[i][j] = c;

            //Inicializar matriz de visitados como falso
            mapa->localVisitado[i][j] = false;
            
            //Se encontrar o "X", salva a posicao inicial
            if(c == 'X'){
                mapa->posInicial_linha = i;
                mapa->posInicial_coluna = j;
                encontrarX = true;
            }
        } 
    }

    //Verificacao se 'X' foi encontrado
    if(!encontrarX){
        fprintf(stderr, "Erro: O ponto de partida nao foi encontrado.\n");
        liberarMapa(mapa);
        fclose(arquivo);
        return NULL;
    }

    fclose(arquivo);
    return mapa;
}

//Implementar funcao de liberarMapa e ImprimirMapa
