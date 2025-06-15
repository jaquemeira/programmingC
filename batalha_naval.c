#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define TAM 10

// Estado das células
#define AGUA 0
#define NAVIO 1
#define ACERTADO 2
#define ERROU 3
#define AREA_ESP 4

// Protótipos
void inicializarTabuleiro(int tab[TAM][TAM]);
void imprimirTabuleiro(int tab[TAM][TAM], int ocultarNavios);
void posicionarNavio(int tab[TAM][TAM]);
void atacar(int tab[TAM][TAM], int *pontuacao);
void aplicarHabilidade(int tab[TAM][TAM]);
void aplicarCruz(int tab[TAM][TAM], int x, int y);
void aplicarCone(int tab[TAM][TAM], int x, int y);
void aplicarOctaedro(int tab[TAM][TAM], int x, int y, int raio);

int main() {
    int jogador1[TAM][TAM], jogador2[TAM][TAM];
    int turno = 1, fim = 0;
    int pontos1 = 0, pontos2 = 0;

    inicializarTabuleiro(jogador1);
    inicializarTabuleiro(jogador2);

    printf("=== POSICIONAMENTO DE NAVIOS ===\n\n");
    printf("Jogador 1, posicione seus navios:\n");
    posicionarNavio(jogador1);

    printf("\nJogador 2, posicione seus navios:\n");
    posicionarNavio(jogador2);

    while (!fim) {
        printf("\n=== TURNO DO JOGADOR %d ===\n", turno);
        if (turno == 1) {
            printf("\nTABULEIRO DO ADVERSÁRIO:\n");
            imprimirTabuleiro(jogador2, 1);
            atacar(jogador2, &pontos1);
            aplicarHabilidade(jogador2);
            turno = 2;
        } else {
            printf("\nTABULEIRO DO ADVERSÁRIO:\n");
            imprimirTabuleiro(jogador1, 1);
            atacar(jogador1, &pontos2);
            aplicarHabilidade(jogador1);
            turno = 1;
        }

        if (pontos1 >= 5) {
            printf("\n>>> JOGADOR 1 VENCEU! <<<\n");
            fim = 1;
        } else if (pontos2 >= 5) {
            printf("\n>>> JOGADOR 2 VENCEU! <<<\n");
            fim = 1;
        }
    }

    return 0;
}

// Funções
void inicializarTabuleiro(int tab[TAM][TAM]) {
    for (int i = 0; i < TAM; i++)
        for (int j = 0; j < TAM; j++)
            tab[i][j] = AGUA;
}

void imprimirTabuleiro(int tab[TAM][TAM], int ocultarNavios) {
    printf("   ");
    for (int j = 0; j < TAM; j++) printf("%2d ", j);
    printf("\n");

    for (int i = 0; i < TAM; i++) {
        printf("%2d ", i);
        for (int j = 0; j < TAM; j++) {
            if (tab[i][j] == AGUA) printf("[~]");
            else if (tab[i][j] == NAVIO && ocultarNavios) printf("[~]");
            else if (tab[i][j] == NAVIO) printf("[N]");
            else if (tab[i][j] == ACERTADO) printf("[X]");
            else if (tab[i][j] == ERROU) printf("[o]");
            else if (tab[i][j] == AREA_ESP) printf("[*]");
        }
        printf("\n");
    }
}

void posicionarNavio(int tab[TAM][TAM]) {
    int x, y, direcao;

    for (int k = 0; k < 2; k++) {
        printf("Digite linha, coluna e direcao (1-H, 2-V, 3-Diag): ");
        scanf("%d %d %d", &x, &y, &direcao);

        int podeColocar = 1;
        for (int i = 0; i < 3; i++) {
            int nx = x, ny = y;
            if (direcao == 1) ny += i;
            else if (direcao == 2) nx += i;
            else if (direcao == 3) { nx += i; ny += i; }

            if (nx >= TAM || ny >= TAM || tab[nx][ny] != AGUA) {
                podeColocar = 0;
                break;
            }
        }

        if (podeColocar) {
            for (int i = 0; i < 3; i++) {
                int nx = x, ny = y;
                if (direcao == 1) ny += i;
                else if (direcao == 2) nx += i;
                else if (direcao == 3) { nx += i; ny += i; }
                tab[nx][ny] = NAVIO;
            }
        } else {
            printf("Posicaoo invalida. Tente novamente.\n");
            k--;
        }
    }
}

void atacar(int tab[TAM][TAM], int *pontuacao) {
    int x, y;
    printf("Digite a posicao para atacar: ");
    scanf("%d %d", &x, &y);

    if (x < 0 || x >= TAM || y < 0 || y >= TAM) {
        printf("Coordenada invalida.\n");
        return;
    }

    if (tab[x][y] == NAVIO) {
        tab[x][y] = ACERTADO;
        (*pontuacao)++;
        printf(">> ACERTOU!\n");
    } else if (tab[x][y] == AGUA) {
        tab[x][y] = ERROU;
        printf(">> Agua...\n");
    } else {
        printf(">> Já atacado.\n");
    }
}

void aplicarHabilidade(int tab[TAM][TAM]) {
    int x, y, tipo;
    printf("Deseja usar habilidade? (1-Sim / 0-Não): ");
    int usar;
    scanf("%d", &usar);
    if (!usar) return;

    printf("Digite posicao central da habilidade (linha coluna): ");
    scanf("%d %d", &x, &y);
    printf("Escolha a habilidade:\n");
    printf("1 - Cruz | 2 - Cone | 3 - Octaedro\n");
    scanf("%d", &tipo);

    switch (tipo) {
        case 1: aplicarCruz(tab, x, y); break;
        case 2: aplicarCone(tab, x, y); break;
        case 3: aplicarOctaedro(tab, x, y, 2); break;
        default: printf("Tipo invalido.\n");
    }
}

void aplicarCruz(int tab[TAM][TAM], int x, int y) {
    for (int i = 0; i < TAM; i++) {
        if (tab[i][y] == AGUA) tab[i][y] = AREA_ESP;
        if (tab[x][i] == AGUA) tab[x][i] = AREA_ESP;
    }
}

void aplicarCone(int tab[TAM][TAM], int x, int y) {
    for (int i = -1; i <= 1; i++) {
        for (int j = 1; j <= 3; j++) {
            int nx = x - j;
            int ny = y + i * j;
            if (nx >= 0 && ny >= 0 && ny < TAM && tab[nx][ny] == AGUA)
                tab[nx][ny] = AREA_ESP;
        }
    }
}

void aplicarOctaedro(int tab[TAM][TAM], int x, int y, int raio) {
    for (int dx = -raio; dx <= raio; dx++) {
        for (int dy = -raio; dy <= raio; dy++) {
            if (abs(dx) + abs(dy) <= raio) {
                int nx = x + dx;
                int ny = y + dy;
                if (nx >= 0 && nx < TAM && ny >= 0 && ny < TAM && tab[nx][ny] == AGUA)
                    tab[nx][ny] = AREA_ESP;
            }
        }
    }
}

