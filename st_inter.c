#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Estrutura da carta
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

int main() {
    // Baralho com 5 cartas
    Carta baralho[5] = {
        {"Minas Gerais", "MG01", "Belo Horizonte", 21322, 586513.98, 682.786, 3, 0},
        {"Bahia", "BA02", "Salvador", 14850, 564760.42, 305.321, 5, 1},
        {"Acre", "AC03", "Rio Branco", 880, 164123.04, 16.476, 1, 0},
        {"Santa Catarina", "SC04", "Florianópolis", 8058, 95730.69, 349.275, 2, 0},
        {"Distrito Federal", "DF27", "Brasília", 3055, 5779.99, 265.847, 4, 0}
    };

    // Sorteio das cartas
    srand(time(NULL));
    int i1 = rand() % 5;
    int i2;
    do {
        i2 = rand() % 5;
    } while (i2 == i1);

    Carta jogador1 = baralho[i1];
    Carta jogador2 = baralho[i2];

    // Exibir carta do Jogador 1
    printf("=== Carta do Jogador 1 ===\n");
    printf("Estado: %s\n", jogador1.estado);
    printf("Cidade: %s\n", jogador1.cidade);
    printf("População: %d mil\n", jogador1.populacao);
    printf("Área: %.2f km²\n", jogador1.area);
    printf("PIB: %.2f bi\n", jogador1.PIB);
    printf("Pontos turísticos: %d\n", jogador1.pontos_turisticos);
    printf("===========================\n\n");

    // Jogador escolhe o atributo
    int opcao;
    printf("Escolha o atributo para comparar:\n");
    printf("1 - População\n");
    printf("2 - Área\n");
    printf("3 - PIB\n");
    printf("4 - Pontos turísticos\n");
    printf("Digite sua escolha: ");
    scanf("%d", &opcao);

    // Comparar com carta do Jogador 2
    printf("\n=== Carta do Jogador 2 ===\n");
    printf("Estado: %s\n", jogador2.estado);
    printf("Cidade: %s\n", jogador2.cidade);
    printf("População: %d mil\n", jogador2.populacao);
    printf("Área: %.2f km²\n", jogador2.area);
    printf("PIB: %.2f bi\n", jogador2.PIB);
    printf("Pontos turísticos: %d\n", jogador2.pontos_turisticos);
    printf("===========================\n\n");

    switch (opcao) {
        case 1:
            if (jogador1.populacao > jogador2.populacao)
                printf("Jogador 1 venceu!\n");
            else if (jogador2.populacao > jogador1.populacao)
                printf("Jogador 2 venceu!\n");
            else
                printf("Empate!\n");
            break;
        case 2:
            if (jogador1.area > jogador2.area)
                printf("Jogador 1 venceu!\n");
            else if (jogador2.area > jogador1.area)
                printf("Jogador 2 venceu!\n");
            else
                printf("Empate!\n");
            break;
        case 3:
            if (jogador1.PIB > jogador2.PIB)
                printf("Jogador 1 venceu!\n");
            else if (jogador2.PIB > jogador1.PIB)
                printf("Jogador 2 venceu!\n");
            else
                printf("Empate!\n");
            break;
        case 4:
            if (jogador1.pontos_turisticos > jogador2.pontos_turisticos)
                printf("Jogador 1 venceu!\n");
            else if (jogador2.pontos_turisticos > jogador1.pontos_turisticos)
                printf("Jogador 2 venceu!\n");
            else
                printf("Empate!\n");
            break;
        default:
            printf("Opção inválida!\n");
    }

    return 0;
}
