# TP1-PAA-Backtracking


## A Jornada do Expresso Interestelar
Universidade Federal de Viçosa - Campus Florestal - Curso: Ciência da Computação

Disciplina: Projeto e Análise de Algoritmos (PAA)

Alunos: Henrique Campos - 4673 / Davi de Souza - XXXX / Guilherme Gustavo - 5378 / Decio Cançado - 5782

Professor: Daniel Mendes Barbosa 

🚀 Sobre o Projeto

Este trabalho implementa uma solução em C para o problema do "Expresso Interestelar". O objetivo é encontrar um caminho viável através de uma "rodovia estelar" (representada por um mapa) para uma tripulação que precisa chegar a um planeta de festividades. A nave possui uma durabilidade limitada que diminui a cada movimento, mas que pode ser restaurada ao coletar peças espalhadas pelo cosmos.

O desafio central é gerenciar a durabilidade da nave para garantir que ela chegue ao destino final ('F') partindo do ponto inicial ('X'). O algoritmo foi desenvolvido utilizando obrigatoriamente a estratégia de backtracking para explorar todas as rotas possíveis de forma recursiva.

✨ Funcionalidades Principais

Solução com Backtracking: O algoritmo explora recursivamente os caminhos possíveis, retrocedendo quando encontra um beco sem saída (ex: durabilidade zerada, parede ou caminho já visitado).

Leitura de Arquivos: O programa é inicializado a partir de um arquivo de texto que define o mapa, as dimensões e os parâmetros da jornada (durabilidade inicial, custo de movimento e bônus de reparo).

Gerenciamento de Recursos: Controla a durabilidade da nave, que diminui a cada passo e aumenta ao coletar peças ('P').

Condição de Reparo Completo: Se a tripulação coleta as 4 peças necessárias, a durabilidade da nave para de diminuir.

Modo de Análise: O programa pode ser compilado em um "modo de análise" que contabiliza e exibe o número total de chamadas recursivas e a profundidade máxima de recursão alcançada durante a execução.

Execução Contínua: Permite ao usuário executar o programa com diferentes arquivos de entrada em sequência, sem precisar reiniciar.
