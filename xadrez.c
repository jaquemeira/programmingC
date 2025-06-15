#include <stdio.h>
#include <stdlib.h>

#define TAM 8

void inicializarTabuleiro(char tabuleiro[TAM][TAM]) {
    for (int i = 0; i < TAM; i++)
        for (int j = 0; j < TAM; j++)
            tabuleiro[i][j] = ' ';
}

void mostrarTabuleiro(char tabuleiro[TAM][TAM]) {
    printf("  ");
    for (int i = 0; i < TAM; i++) printf("%d ", i);
    printf("\n");

    for (int i = 0; i < TAM; i++) {
        printf("%d ", i);
        for (int j = 0; j < TAM; j++) {
            printf("%c ", tabuleiro[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void moverTorre(int x, int y, char tabuleiro[TAM][TAM]) {
    for (int i = 0; i < TAM; i++) {
        tabuleiro[i][y] = '*';
        tabuleiro[x][i] = '*';
    }
    tabuleiro[x][y] = 'T';
}

void moverBispo(int x, int y, char tabuleiro[TAM][TAM]) {
    int i = x, j = y;
    while (i >= 0 && j >= 0) tabuleiro[i--][j--] = '*';
    i = x; j = y;
    while (i >= 0 && j < TAM) tabuleiro[i--][j++] = '*';
    i = x; j = y;
    while (i < TAM && j >= 0) tabuleiro[i++][j--] = '*';
    i = x; j = y;
    while (i < TAM && j < TAM) tabuleiro[i++][j++] = '*';
    tabuleiro[x][y] = 'B';
}

void moverRainha(int x, int y, char tabuleiro[TAM][TAM]) {
    moverTorre(x, y, tabuleiro);
    moverBispo(x, y, tabuleiro);
    tabuleiro[x][y] = 'R';
}

void moverCavalo(int x, int y, char tabuleiro[TAM][TAM]) {
    int mov[8][2] = {
        {-2, -1}, {-2, +1}, {-1, -2}, {-1, +2},
        {+1, -2}, {+1, +2}, {+2, -1}, {+2, +1}
    };
    for (int i = 0; i < 8; i++) {
        int nx = x + mov[i][0];
        int ny = y + mov[i][1];
        if (nx >= 0 && nx < TAM && ny >= 0 && ny < TAM)
            tabuleiro[nx][ny] = '*';
    }
    tabuleiro[x][y] = 'C';
}

void moverBispoRecursivo(int x, int y, char tabuleiro[TAM][TAM]) {
    if (x < 0 || x >= TAM || y < 0 || y >= TAM) return;
    if (tabuleiro[x][y] != ' ') return;
    tabuleiro[x][y] = '*';
    moverBispoRecursivo(x - 1, y - 1, tabuleiro);
    moverBispoRecursivo(x - 1, y + 1, tabuleiro);
    moverBispoRecursivo(x + 1, y - 1, tabuleiro);
    moverBispoRecursivo(x + 1, y + 1, tabuleiro);
}

int main() {
    char tabuleiro[TAM][TAM];
    int opcao, x, y;

    do {
        inicializarTabuleiro(tabuleiro);

        printf("=== JOGO DE XADREZ EM C ===\n");
        printf("Escolha a peça para movimentar:\n");
        printf("1 - Torre\n");
        printf("2 - Bispo\n");
        printf("3 - Rainha\n");
        printf("4 - Cavalo\n");
        printf("5 - Bispo (recursivo)\n");
        printf("0 - Sair\n");
        printf("Opcao: ");
        scanf("%d", &opcao);

        if (opcao == 0) break;

        printf("Digite a posição (linha e coluna): ");
        scanf("%d %d", &x, &y);

        if (x < 0 || x >= TAM || y < 0 || y >= TAM) {
            printf("Posição inválida!\n\n");
            continue;
        }

        switch (opcao) {
            case 1:
                moverTorre(x, y, tabuleiro);
                break;
            case 2:
                moverBispo(x, y, tabuleiro);
                break;
            case 3:
                moverRainha(x, y, tabuleiro);
                break;
            case 4:
                moverCavalo(x, y, tabuleiro);
                break;
            case 5:
                tabuleiro[x][y] = 'b';
                moverBispoRecursivo(x - 1, y - 1, tabuleiro);
                moverBispoRecursivo(x - 1, y + 1, tabuleiro);
                moverBispoRecursivo(x + 1, y - 1, tabuleiro);
                moverBispoRecursivo(x + 1, y + 1, tabuleiro);
                break;
            default:
                printf("Opcao inválida!\n");
        }

        mostrarTabuleiro(tabuleiro);
    } while (1);

    printf("Fim do jogo!\n");
    return 0;
}
