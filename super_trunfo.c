#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// 1. Definição da estrutura da carta
typedef struct {
    char estado[30];
    char cod_carta[10];
    char cidade[30];
    int populacao;
    float area;
    float PIB;
    int pontos_turisticos;
    int super_trunfo;
} Carta;

// 2. Função principal
int main() {
    // 3. Baralho com cartas
    Carta baralho[5] = {
        {"Minas Gerais", "MG01", "Belo Horizonte", 21322, 586513.98, 682.786, 3, 0},
        {"Bahia", "BA02", "Salvador", 14850, 564760.42, 305.321, 5, 1},
        {"Acre", "AC03", "Rio Branco", 880, 164123.04, 16.476, 1, 0},
        {"Santa Catarina", "SC04", "Florianópolis", 8058, 95730.69, 349.275, 2, 0},
        {"Distrito Federal", "DF27", "Brasília", 3055, 5779.99, 265.847, 4, 0}
    };

    // 4. Sorteio de cartas
    srand(time(NULL));
    int i1 = rand() % 5;
    int i2;
    do {
        i2 = rand() % 5;
    } while (i2 == i1);

    Carta jogador1 = baralho[i1];
    Carta jogador2 = baralho[i2];

    // 5. Mostrar cartas sorteadas
    printf("Jogador 1: %s (%s)\n", jogador1.estado, jogador1.cod_carta);
    printf("Jogador 2: %s (%s)\n\n", jogador2.estado, jogador2.cod_carta);

    // 6. Escolha de atributo
    int opcao;
    printf("Escolha o atributo para comparar:\n");
    printf("1. Populacao\n2. Area\n3. PIB\n4. Pontos turisticos\n");
    scanf("%d", &opcao);

    // 7. Comparação
    switch (opcao) {
        case 1:
            printf(jogador1.populacao > jogador2.populacao ? "Jogador 1 venceu!\n" :
                   jogador2.populacao > jogador1.populacao ? "Jogador 2 venceu!\n" : "Empate!\n");
            break;
        case 2:
            printf(jogador1.area > jogador2.area ? "Jogador 1 venceu!\n" :
                   jogador2.area > jogador1.area ? "Jogador 2 venceu!\n" : "Empate!\n");
            break;
        case 3:
            printf(jogador1.PIB > jogador2.PIB ? "Jogador 1 venceu!\n" :
                   jogador2.PIB > jogador1.PIB ? "Jogador 2 venceu!\n" : "Empate!\n");
            break;
        case 4:
            printf(jogador1.pontos_turisticos > jogador2.pontos_turisticos ? "Jogador 1 venceu!\n" :
                   jogador2.pontos_turisticos > jogador1.pontos_turisticos ? "Jogador 2 venceu!\n" : "Empate!\n");
            break;
        default:
            printf("Atributo inválido!\n");
    }

    return 0;
}
