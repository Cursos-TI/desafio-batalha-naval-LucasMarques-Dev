#include <stdio.h>

// Desafio Batalha Naval - Nível Aventureiro
// Este programa inicializa um tabuleiro 10x10 e posiciona quatro navios:
// dois navios em orientação horizontal/vertical e dois navios em orientação diagonal.
// O tabuleiro mostra 0 para água e 3 para cada parte de navio.

#define BOARD_SIZE 10
#define SHIP_SIZE 3
#define WATER 0
#define SHIP 3

int main(void) {
    // Tabuleiro 10x10 iniciado com água em todas as posições.
    int board[BOARD_SIZE][BOARD_SIZE] = {0};

    // Vetores que representam navios de tamanho fixo 3.
    int horizontalShip[SHIP_SIZE] = {SHIP, SHIP, SHIP};
    int verticalShip[SHIP_SIZE] = {SHIP, SHIP, SHIP};
    int diagonalDescShip[SHIP_SIZE] = {SHIP, SHIP, SHIP};
    int diagonalAscShip[SHIP_SIZE] = {SHIP, SHIP, SHIP};

    // Coordenadas iniciais para cada navio definidas diretamente no código.
    int horizStartRow = 1;
    int horizStartCol = 1;

    int vertStartRow = 4;
    int vertStartCol = 4;

    int diagDescStartRow = 6; // diagonal crescente: row e col aumentam juntos
    int diagDescStartCol = 0;

    int diagAscStartRow = 2; // diagonal decrescente: row diminui e col aumenta
    int diagAscStartCol = 7;

    int row, col, i;
    int validPlacement = 1;

    // Valida e posiciona um navio com direção fixa
    // dRow e dCol definem o deslocamento para cada parte do navio.
    int directions[4][2] = {
        {0, 1},  // horizontal
        {1, 0},  // vertical
        {1, 1},  // diagonal descendente
        {-1, 1}  // diagonal ascendente
    };

    int startRows[4] = {horizStartRow, vertStartRow, diagDescStartRow, diagAscStartRow};
    int startCols[4] = {horizStartCol, vertStartCol, diagDescStartCol, diagAscStartCol};

    int *ships[4] = {horizontalShip, verticalShip, diagonalDescShip, diagonalAscShip};

    // Processo de validação e posicionamento para cada navio
    for (i = 0; i < 4 && validPlacement; i++) {
        int dRow = directions[i][0];
        int dCol = directions[i][1];
        int currentRow = startRows[i];
        int currentCol = startCols[i];
        int part;

        for (part = 0; part < SHIP_SIZE; part++) {
            row = currentRow + part * dRow;
            col = currentCol + part * dCol;

            // Verifica limites do tabuleiro
            if (row < 0 || row >= BOARD_SIZE || col < 0 || col >= BOARD_SIZE) {
                printf("Erro: navio %d ultrapassa os limites do tabuleiro.\n", i + 1);
                validPlacement = 0;
                break;
            }

            // Verifica sobreposição de navios
            if (board[row][col] != WATER) {
                printf("Erro: navio %d sobrepõe outro navio em (%d, %d).\n", i + 1, row, col);
                validPlacement = 0;
                break;
            }
        }

        // Se passou nas validações, insere o navio no tabuleiro
        if (validPlacement) {
            for (part = 0; part < SHIP_SIZE; part++) {
                row = currentRow + part * dRow;
                col = currentCol + part * dCol;
                board[row][col] = ships[i][part];
            }
        }
    }

    if (validPlacement) {
        printf("Tabuleiro do Batalha Naval (0 = agua, 3 = navio):\n");

        // Exibe o tabuleiro completo com espaçamento para facilitar a visualização
        for (row = 0; row < BOARD_SIZE; row++) {
            for (col = 0; col < BOARD_SIZE; col++) {
                printf("%d ", board[row][col]);
            }
            printf("\n");
        }
    }

    return validPlacement ? 0 : 1;
}
