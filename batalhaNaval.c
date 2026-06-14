#include <stdio.h>

// Desafio Batalha Naval - Nível Novato
// Este programa inicializa um tabuleiro 10x10 e posiciona dois navios:
// um navio horizontal e um navio vertical. O tabuleiro mostra 0 para água
// e 3 para a posição de cada parte do navio.

#define BOARD_SIZE 10
#define SHIP_SIZE 3
#define WATER 0
#define SHIP 3

int main(void) {
    // Tabuleiro 10x10 iniciado com zeros (água)
    int board[BOARD_SIZE][BOARD_SIZE] = {0};

    // Vetores que representam os dois navios de tamanho fixo 3
    int horizontalShip[SHIP_SIZE] = {SHIP, SHIP, SHIP};
    int verticalShip[SHIP_SIZE] = {SHIP, SHIP, SHIP};

    // Coordenadas de início definidas diretamente no código
    // O navio horizontal começa na linha 1, coluna 1.
    int horizStartRow = 1;
    int horizStartCol = 1;

    // O navio vertical começa na linha 4, coluna 4.
    int vertStartRow = 4;
    int vertStartCol = 4;

    int row, col, i, j;
    int validPlacement = 1;
    int overlap = 0;

    // Validação do navio horizontal dentro dos limites do tabuleiro
    if (horizStartRow < 0 || horizStartRow >= BOARD_SIZE ||
        horizStartCol < 0 || horizStartCol + SHIP_SIZE > BOARD_SIZE) {
        printf("Erro: coordenadas do navio horizontal invalidas.\n");
        validPlacement = 0;
    }

    // Validação do navio vertical dentro dos limites do tabuleiro
    if (vertStartCol < 0 || vertStartCol >= BOARD_SIZE ||
        vertStartRow < 0 || vertStartRow + SHIP_SIZE > BOARD_SIZE) {
        printf("Erro: coordenadas do navio vertical invalidas.\n");
        validPlacement = 0;
    }

    // Verifica se as posições do navio horizontal e vertical se sobrepõem
    if (validPlacement) {
        for (i = 0; i < SHIP_SIZE && !overlap; i++) {
            int horizRow = horizStartRow;
            int horizCol = horizStartCol + i;

            for (j = 0; j < SHIP_SIZE && !overlap; j++) {
                int vertRow = vertStartRow + j;
                int vertCol = vertStartCol;

                if (horizRow == vertRow && horizCol == vertCol) {
                    overlap = 1;
                }
            }
        }

        if (overlap) {
            printf("Erro: navios sobrepostos. Escolha coordenadas diferentes.\n");
            validPlacement = 0;
        }
    }

    // Se a posição for válida, copia o valor 3 do vetor do navio para o tabuleiro
    if (validPlacement) {
        for (i = 0; i < SHIP_SIZE; i++) {
            board[horizStartRow][horizStartCol + i] = horizontalShip[i];
        }

        for (i = 0; i < SHIP_SIZE; i++) {
            board[vertStartRow + i][vertStartCol] = verticalShip[i];
        }

        printf("Tabuleiro do Batalha Naval (0 = agua, 3 = navio):\n");

        // Exibe o tabuleiro completo utilizando loops aninhados
        for (row = 0; row < BOARD_SIZE; row++) {
            for (col = 0; col < BOARD_SIZE; col++) {
                printf("%d ", board[row][col]);
            }
            printf("\n");
        }
    }

    return validPlacement ? 0 : 1;
}
