#include <stdio.h>
#include <stdlib.h>

// Desafio Batalha Naval - Nível Mestre
// Este programa mantém o tabuleiro 10x10 e adiciona áreas de efeito
// para três habilidades especiais: cone, cruz e octaedro.
// O tabuleiro mostra 0 para água, 3 para navios e 5 para áreas afetadas.

#define BOARD_SIZE 10
#define SHIP_SIZE 3
#define ABILITY_SIZE 5
#define WATER 0
#define SHIP 3
#define EFFECT 5

int main(void) {
    // Tabuleiro 10x10 iniciado com água em todas as posições.
    int board[BOARD_SIZE][BOARD_SIZE] = {0};

    // Navios fixos de tamanho 3.
    int horizontalShip[SHIP_SIZE] = {SHIP, SHIP, SHIP};
    int verticalShip[SHIP_SIZE] = {SHIP, SHIP, SHIP};
    int diagonalDescShip[SHIP_SIZE] = {SHIP, SHIP, SHIP};
    int diagonalAscShip[SHIP_SIZE] = {SHIP, SHIP, SHIP};

    // Coordenadas iniciais para cada navio.
    int horizStartRow = 1;
    int horizStartCol = 1;
    int vertStartRow = 4;
    int vertStartCol = 4;
    int diagDescStartRow = 6;
    int diagDescStartCol = 0;
    int diagAscStartRow = 2;
    int diagAscStartCol = 7;

    int row, col, i;
    int validPlacement = 1;

    // Direções para cada tipo de navio.
    int directions[4][2] = {
        {0, 1},  // horizontal
        {1, 0},  // vertical
        {1, 1},  // diagonal descendente
        {-1, 1}  // diagonal ascendente
    };

    int startRows[4] = {horizStartRow, vertStartRow, diagDescStartRow, diagAscStartRow};
    int startCols[4] = {horizStartCol, vertStartCol, diagDescStartCol, diagAscStartCol};
    int *ships[4] = {horizontalShip, verticalShip, diagonalDescShip, diagonalAscShip};

    // Valida as posições e posiciona todos os navios no tabuleiro.
    for (i = 0; i < 4 && validPlacement; i++) {
        int dRow = directions[i][0];
        int dCol = directions[i][1];
        int currentRow = startRows[i];
        int currentCol = startCols[i];
        int part;

        // Valida cada parte do navio atual.
        for (part = 0; part < SHIP_SIZE; part++) {
            row = currentRow + part * dRow;
            col = currentCol + part * dCol;

            if (row < 0 || row >= BOARD_SIZE || col < 0 || col >= BOARD_SIZE) {
                printf("Erro: navio %d ultrapassa os limites do tabuleiro.\n", i + 1);
                validPlacement = 0;
                break;
            }

            if (board[row][col] != WATER) {
                printf("Erro: navio %d sobrepõe outro navio em (%d, %d).\n", i + 1, row, col);
                validPlacement = 0;
                break;
            }
        }

        // Insere o navio no tabuleiro se a validação passar.
        if (validPlacement) {
            for (part = 0; part < SHIP_SIZE; part++) {
                row = currentRow + part * dRow;
                col = currentCol + part * dCol;
                board[row][col] = ships[i][part];
            }
        }
    }

    // Matrizes de habilidade 5x5
    int cone[ABILITY_SIZE][ABILITY_SIZE] = {0};
    int cross[ABILITY_SIZE][ABILITY_SIZE] = {0};
    int octahedron[ABILITY_SIZE][ABILITY_SIZE] = {0};

    // Constante para o centro das matrizes de habilidade
    int abilityCenter = ABILITY_SIZE / 2;

    // Preenche as matrizes de habilidade com condicionais e loops aninhados.
    for (row = 0; row < ABILITY_SIZE; row++) {
        for (col = 0; col < ABILITY_SIZE; col++) {
            // Habilidade: cone apontando para baixo.
            if (row <= abilityCenter && abs(col - abilityCenter) <= row) {
                cone[row][col] = 1;
            } else {
                cone[row][col] = 0;
            }

            // Habilidade: cruz com ponto de origem no centro.
            if (row == abilityCenter || col == abilityCenter) {
                cross[row][col] = 1;
            } else {
                cross[row][col] = 0;
            }

            // Habilidade: octaedro vista frontal em forma de losango.
            if (abs(row - abilityCenter) + abs(col - abilityCenter) <= abilityCenter) {
                octahedron[row][col] = 1;
            } else {
                octahedron[row][col] = 0;
            }
        }
    }

    // Pontos de origem para as habilidades no tabuleiro.
    int coneOriginRow = 2;
    int coneOriginCol = 2;
    int crossOriginRow = 5;
    int crossOriginCol = 6;
    int octahedronOriginRow = 7;
    int octahedronOriginCol = 3;

    // Função de sobreposição das habilidades no tabuleiro.
    for (row = 0; row < ABILITY_SIZE; row++) {
        for (col = 0; col < ABILITY_SIZE; col++) {
            if (cone[row][col] == 1) {
                int boardRow = coneOriginRow + row - abilityCenter;
                int boardCol = coneOriginCol + col - abilityCenter;
                if (boardRow >= 0 && boardRow < BOARD_SIZE && boardCol >= 0 && boardCol < BOARD_SIZE) {
                    board[boardRow][boardCol] = EFFECT;
                }
            }

            if (cross[row][col] == 1) {
                int boardRow = crossOriginRow + row - abilityCenter;
                int boardCol = crossOriginCol + col - abilityCenter;
                if (boardRow >= 0 && boardRow < BOARD_SIZE && boardCol >= 0 && boardCol < BOARD_SIZE) {
                    board[boardRow][boardCol] = EFFECT;
                }
            }

            if (octahedron[row][col] == 1) {
                int boardRow = octahedronOriginRow + row - abilityCenter;
                int boardCol = octahedronOriginCol + col - abilityCenter;
                if (boardRow >= 0 && boardRow < BOARD_SIZE && boardCol >= 0 && boardCol < BOARD_SIZE) {
                    board[boardRow][boardCol] = EFFECT;
                }
            }
        }
    }

    if (validPlacement) {
        printf("Tabuleiro do Batalha Naval (0 = agua, 3 = navio, 5 = area de efeito):\n");

        for (row = 0; row < BOARD_SIZE; row++) {
            for (col = 0; col < BOARD_SIZE; col++) {
                printf("%d ", board[row][col]);
            }
            printf("\n");
        }
    }

    return validPlacement ? 0 : 1;
}
