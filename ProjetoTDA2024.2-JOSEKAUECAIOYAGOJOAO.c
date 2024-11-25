/* Faça um algoritmo que funcione como um jogo da velha para dois jogadores, e que permita marcar posições no tabuleiro 3x3 alternadamente com os símbolos "X" e "O". O programa deve perguntar ao jogador qual posição ele quer marcar, sendo que a resposta deverá ser dois números inteiros, um para a linha e outro para a coluna, indicando a posição desejada. Depois de informada a posição escolhida, o programa deve verificar se ela está disponível no tabuleiro e atualizá-lo. De posse dessas informações, o algoritmo deverá verificar se houve vitória ou empate e mostrar, como saída, o resultado da partida.
#Planejamento:
O quê? Criar um programa que permita dois jogadores jogarem uma partida de jogo da velha, mostrando o tabuleiro, registrando as jogadas e anunciando o vencedor ou um empate.
Como? O algoritmo deve receber do teclado uma coluna e uma linha do jogador correspondente e deve alternar entre os jogadores 1 e 2. Ele também deve verificar se cada posição está disponível e imprimir o tabuleiro na tela. A cada jogada, o algoritmo deve checar se houve vitória ou empate (se estiver cheio). No fim, deve exibir o resultado da partida.
Algoritmo:
ENTRADA - Ler os dois nomes dos jogadores e armazená-los em variáveis. Definir o jogador inicial como jogador 1.

PROCESSAMENTO - Enquanto não houver empate nem ganhador, deve-se mostrar o tabuleiro na tela, ler a linha e a coluna escolhidas pelo jogador da vez; Verificar se é uma coordenada válida e está vazia ou passa do tamanho do tabuleiro; Caso True, marcar a posição com o símbolo do jogador da vez; Pedir a linha e a coluna do próximo jogador. Por fim, verificar se há um vencedor comparando os valores da diagonal, horizontal e vertical; Caso todas as posições forem preenchidas ("dar velha"), indicar empate.

SAÍDA -  Mostrar o tabuleiro final na tela; Anunciar o vencedor ou informar que houve empate; Perguntar se os jogadores desejam jogar novamente.
*/

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

// Função para imprimir a matriz
void imprimirTABULEIRO(char **tabuleiro) {
    int i, j;
    printf("\n   0   1   2");
    for (i = 0; i < 3; i++) {
        printf("\n%d ", i);
        for (j = 0; j < 3; j++) {
            printf(" %c ", tabuleiro[i][j]);
            if (j < 2) printf("|");
        }
        if (i < 2) printf("\n  ---|---|---");
    }
    printf("\n");
}

// Função para verificar se há um vencedor
int verificarVENCEDOR(char **tabuleiro) {
    int i;
    // Verificando as linhas
    for (i = 0; i < 3; i++) {
        if (tabuleiro[i][0] == tabuleiro[i][1] && tabuleiro[i][1] == tabuleiro[i][2] && tabuleiro[i][0] != ' ') {
            return 1;
        }
        // Verificando as colunas
        if (tabuleiro[0][i] == tabuleiro[1][i] && tabuleiro[1][i] == tabuleiro[2][i] && tabuleiro[0][i] != ' ') {
            return 1;
        }
    }
    // Verificando as diagonais
    if (tabuleiro[0][0] == tabuleiro[1][1] && tabuleiro[1][1] == tabuleiro[2][2] && tabuleiro[0][0] != ' ') {
        return 1;
    }
    if (tabuleiro[0][2] == tabuleiro[1][1] && tabuleiro[1][1] == tabuleiro[2][0] && tabuleiro[0][2] != ' ') {
        return 1;
    }
    return 0;
}

// Função para verificar se houve empate
int verificarEMPATE(char **tabuleiro) {
    int i, j;
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            if (tabuleiro[i][j] == ' ') {
                return 0; // Ainda há jogadas possíveis
            }
        }
    }
    return 1; // Tabuleiro cheio, empate
}

typedef struct jogadores {
    char jogador1[50];
    char jogador2[50];
} t_JOGADORES;

typedef struct menu {
    t_JOGADORES jogadores;
} t_MENU;

int main() {
    setlocale(LC_ALL, "Portuguese");

    int linha, coluna, i, j;
    int jogadorAtual = 1; // Começa com o jogador 1
    char jogarNovamente;
    t_MENU menu;

    do {
        // Obter os nomes dos jogadores
        printf("DIGITE O NOME PARA JOGADOR1: ");
        scanf("%[^\n]", menu.jogadores.jogador1);
        getchar();

        printf("DIGITE O NOME PARA JOGADOR2: ");
        scanf("%[^\n]", menu.jogadores.jogador2);
        getchar();

        // Alocando dinamicamente o tabuleiro
        char **tabuleiro = (char **)malloc(3 * sizeof(char *));
        for (i = 0; i < 3; i++) {
            tabuleiro[i] = (char *)malloc(3 * sizeof(char));
            for (j = 0; j < 3; j++) {
                tabuleiro[i][j] = ' ';
            }
        }

        // Iniciar o loop do jogo
        while (1) {
            imprimirTABULEIRO(tabuleiro);

            if (jogadorAtual == 1) {
                printf("\n%s, DIGITE O NÚMERO DA LINHA E DA COLUNA PARA MARCAR (X): ", menu.jogadores.jogador1);
            } else {
                printf("\n%s, DIGITE O NÚMERO DA LINHA E DA COLUNA PARA MARCAR (O): ", menu.jogadores.jogador2);
            }

            if (scanf("%d %d", &linha, &coluna) != 2 || linha < 0 || linha > 2 || coluna < 0 || coluna > 2) {
                printf("Coordenadas inválidas! Tente novamente.\n");
                while (getchar() != '\n'); // Limpa o buffer
                continue;
            }

            if (tabuleiro[linha][coluna] == ' ') {
                tabuleiro[linha][coluna] = (jogadorAtual == 1) ? 'X' : 'O';
                jogadorAtual = (jogadorAtual == 1) ? 2 : 1;
            } else {
                printf("A POSIÇÃO JÁ ESTÁ OCUPADA! TENTE NOVAMENTE.\n");
                continue;
            }

            // Verifica se há um vencedor
            if (verificarVENCEDOR(tabuleiro)) {
                imprimirTABULEIRO(tabuleiro);
                printf("\n%s VENCEU!\n", (jogadorAtual == 2) ? menu.jogadores.jogador1 : menu.jogadores.jogador2);
                break;
            }

            // Verifica se houve empate
            if (verificarEMPATE(tabuleiro)) {
                imprimirTABULEIRO(tabuleiro);
                printf("\nO JOGO TERMINOU EM EMPATE!\n");
                break;
            }
        }

        // Liberação de memória
        for (i = 0; i < 3; i++) {
            free(tabuleiro[i]);
        }
        free(tabuleiro);

        printf("Deseja jogar novamente? (s/n): ");
        scanf(" %c", &jogarNovamente);
        getchar();
    } while (jogarNovamente == 's' || jogarNovamente == 'S');

    printf("Obrigado por jogar!\n");
    return 0;
}
