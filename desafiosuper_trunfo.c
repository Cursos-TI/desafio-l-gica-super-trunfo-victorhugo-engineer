#include <stdio.h>
#include <string.h>

typedef struct {
    char estado;               // Letra de A a H
    char codigo[4];            // Ex: A01
    char nome[50];             // Nome da cidade
    unsigned long int populacao;
    float area;
    float pib;
    int pontos_turisticos;
    float densidade;           // populacao / area
    float pib_per_capita;      // pib / populacao
} Carta;

// Função para cadastrar uma carta
void cadastrarCarta(Carta *carta, int numero) {
    printf("Cadastro da Carta %d:\n", numero);
    printf("Estado (A-H): ");
    scanf(" %c", &carta->estado);

    printf("Código da carta (Ex: A01): ");
    scanf("%3s", carta->codigo);

    printf("Nome da cidade: ");
    scanf(" %[^\n]", carta->nome);

    printf("População: ");
    scanf("%lu", &carta->populacao);

    printf("Área (km²): ");
    scanf("%f", &carta->area);

    printf("PIB (bilhões de reais): ");
    scanf("%f", &carta->pib);

    printf("Número de pontos turísticos: ");
    scanf("%d", &carta->pontos_turisticos);

    // Cálculos
    carta->densidade = carta->populacao / carta->area;
    carta->pib_per_capita = carta->pib * 1e9 / carta->populacao;  // pib em reais, então * 1e9
    printf("\n");
}

// Função para exibir uma carta
void exibirCarta(const Carta *carta, int numero) {
    printf("Carta %d:\n", numero);
    printf("Estado: %c\n", carta->estado);
    printf("Código: %s\n", carta->codigo);
    printf("Nome da Cidade: %s\n", carta->nome);
    printf("População: %lu\n", carta->populacao);
    printf("Área: %.2f km²\n", carta->area);
    printf("PIB: %.2f bilhões de reais\n", carta->pib);
    printf("Número de Pontos Turísticos: %d\n", carta->pontos_turisticos);
    printf("Densidade Populacional: %.2f hab/km²\n", carta->densidade);
    printf("PIB per Capita: %.2f reais\n", carta->pib_per_capita);
    printf("\n");
}

// Nível Novato: Cadastro e exibição
void nivelNovato(Carta cartas[]) {
    printf("=== Nível Novato: Cadastro e Exibição ===\n\n");
    cadastrarCarta(&cartas[0], 1);
    cadastrarCarta(&cartas[1], 2);

    printf("Cartas cadastradas:\n\n");
    exibirCarta(&cartas[0], 1);
    exibirCarta(&cartas[1], 2);
}

// Função auxiliar para comparar e exibir resultado de um atributo
// retorna 1 se carta1 vence, 0 se carta2 vence, -1 empate
int compararAtributo(float val1, float val2, int menor_vence) {
    if (val1 == val2) return -1;
    if (menor_vence) {
        return (val1 < val2) ? 1 : 0;
    } else {
        return (val1 > val2) ? 1 : 0;
    }
}

// Nível Aventureiro: Comparação com escolha de um atributo (fixa no código)
void nivelAventureiro(Carta cartas[]) {
    printf("=== Nível Aventureiro: Comparação por um atributo ===\n\n");

    // Escolha do atributo para comparar (mudar aqui para testar)
    // Opções: 1-População, 2-Área, 3-PIB, 4-Densidade, 5-PIB per capita, 6-Pontos turísticos
    int atributo = 1; // Exemplo: comparar população (alterar conforme desejado)

    const char* nome_atributo;
    float val1, val2;
    int menor_vence = 0;

    switch(atributo) {
        case 1:
            nome_atributo = "População";
            val1 = (float) cartas[0].populacao;
            val2 = (float) cartas[1].populacao;
            menor_vence = 0;
            break;
        case 2:
            nome_atributo = "Área";
            val1 = cartas[0].area;
            val2 = cartas[1].area;
            menor_vence = 0;
            break;
        case 3:
            nome_atributo = "PIB";
            val1 = cartas[0].pib;
            val2 = cartas[1].pib;
            menor_vence = 0;
            break;
        case 4:
            nome_atributo = "Densidade Populacional";
            val1 = cartas[0].densidade;
            val2 = cartas[1].densidade;
            menor_vence = 1; // menor vence
            break;
        case 5:
            nome_atributo = "PIB per Capita";
            val1 = cartas[0].pib_per_capita;
            val2 = cartas[1].pib_per_capita;
            menor_vence = 0;
            break;
        case 6:
            nome_atributo = "Número de Pontos Turísticos";
            val1 = (float) cartas[0].pontos_turisticos;
            val2 = (float) cartas[1].pontos_turisticos;
            menor_vence = 0;
            break;
        default:
            printf("Atributo inválido.\n");
            return;
    }

    printf("Comparação de cartas (Atributo: %s):\n\n", nome_atributo);
    printf("Carta 1 - %s (%c): %.2f\n", cartas[0].nome, cartas[0].estado, val1);
    printf("Carta 2 - %s (%c): %.2f\n", cartas[1].nome, cartas[1].estado, val2);

    int resultado = compararAtributo(val1, val2, menor_vence);
    if (resultado == -1) {
        printf("Resultado: Empate!\n");
    } else if (resultado == 1) {
        printf("Resultado: Carta 1 (%s) venceu!\n", cartas[0].nome);
    } else {
        printf("Resultado: Carta 2 (%s) venceu!\n", cartas[1].nome);
    }
    printf("\n");
}

// Nível Mestre: Comparação por 2 atributos escolhidos pelo usuário
void nivelMestre(Carta cartas[]) {
    printf("=== Nível Mestre: Comparação por dois atributos ===\n\n");

    // Menu para escolher o primeiro atributo
    int escolha1 = 0, escolha2 = 0;
    int valido = 0;

    while(!valido) {
        printf("Escolha o primeiro atributo para comparar:\n");
        printf("1 - População\n");
        printf("2 - Área\n");
        printf("3 - PIB\n");
        printf("4 - Densidade Populacional\n");
        printf("5 - PIB per Capita\n");
        printf("6 - Número de Pontos Turísticos\n");
        printf("Opção: ");
        scanf("%d", &escolha1);

        if (escolha1 >= 1 && escolha1 <= 6) {
            valido = 1;
        } else {
            printf("Opção inválida, tente novamente.\n\n");
        }
    }

    valido = 0;
    while(!valido) {
        printf("\nEscolha o segundo atributo para comparar (diferente do primeiro):\n");
        printf("1 - População\n");
        printf("2 - Área\n");
        printf("3 - PIB\n");
        printf("4 - Densidade Populacional\n");
        printf("5 - PIB per Capita\n");
        printf("6 - Número de Pontos Turísticos\n");
        printf("Opção: ");
        scanf("%d", &escolha2);

        if (escolha2 >= 1 && escolha2 <= 6 && escolha2 != escolha1) {
            valido = 1;
        } else {
            printf("Opção inválida, tente novamente.\n\n");
        }
    }

    // Função para pegar nome e valor de atributo
    char nome1[30], nome2[30];
    float c1_val1, c2_val1, c1_val2, c2_val2;
    int menor_vence1 = 0, menor_vence2 = 0;

    // Atributo 1
    switch(escolha1) {
        case 1: strcpy(nome1, "População"); c1_val1 = (float) cartas[0].populacao; c2_val1 = (float) cartas[1].populacao; menor_vence1=0; break;
        case 2: strcpy(nome1, "Área"); c1_val1 = cartas[0].area; c2_val1 = cartas[1].area; menor_vence1=0; break;
        case 3: strcpy(nome1, "PIB"); c1_val1 = cartas[0].pib; c2_val1 = cartas[1].pib; menor_vence1=0; break;
        case 4: strcpy(nome1, "Densidade Populacional"); c1_val1 = cartas[0].densidade; c2_val1 = cartas[1].densidade; menor_vence1=1; break;
        case 5: strcpy(nome1, "PIB per Capita"); c1_val1 = cartas[0].pib_per_capita; c2_val1 = cartas[1].pib_per_capita; menor_vence1=0; break;
        case 6: strcpy(nome1, "Número de Pontos Turísticos"); c1_val1 = (float) cartas[0].pontos_turisticos; c2_val1 = (float) cartas[1].pontos_turisticos; menor_vence1=0; break;
    }

    // Atributo 2
    switch(escolha2) {
        case 1: strcpy(nome2, "População"); c1_val2 = (float) cartas[0].populacao; c2_val2 = (float) cartas[1].populacao; menor_vence2=0; break;
        case 2: strcpy(nome2, "Área"); c1_val2 = cartas[0].area; c2_val2 = cartas[1].area; menor_vence2=0; break;
        case 3: strcpy(nome2, "PIB"); c1_val2 = cartas[0].pib; c2_val2 = cartas[1].pib; menor_vence2=0; break;
        case 4: strcpy(nome2, "Densidade Populacional"); c1_val2 = cartas[0].densidade; c2_val2 = cartas[1].densidade; menor_vence2=1; break;
        case 5: strcpy(nome2, "PIB per Capita"); c1_val2 = cartas[0].pib_per_capita; c2_val2 = cartas[1].pib_per_capita; menor_vence2=0; break;
        case 6: strcpy(nome2, "Número de Pontos Turísticos"); c1_val2 = (float) cartas[0].pontos_turisticos; c2_val2 = (float) cartas[1].pontos_turisticos; menor_vence2=0; break;
    }

    printf("\nComparando cartas:\n");
    printf("Carta 1: %s (%c)\n", cartas[0].nome, cartas[0].estado);
    printf("Carta 2: %s (%c)\n\n", cartas[1].nome, cartas[1].estado);

    printf("Atributo 1: %s\n", nome1);
    printf("  Carta 1: %.2f\n", c1_val1);
    printf("  Carta 2: %.2f\n\n", c2_val1);

    printf("Atributo 2: %s\n", nome2);
    printf("  Carta 1: %.2f\n", c1_val2);
    printf("  Carta 2: %.2f\n\n", c2_val2);

    // Comparação individual dos atributos
    int res1 = compararAtributo(c1_val1, c2_val1, menor_vence1);
    int res2 = compararAtributo(c1_val2, c2_val2, menor_vence2);

    // Soma dos valores (regra geral: somar valores originais, não invertidos)
    float soma_carta1 = c1_val1 + c1_val2;
    float soma_carta2 = c2_val1 + c2_val2;

    printf("Soma dos atributos:\n");
    printf("  Carta 1: %.2f\n", soma_carta1);
    printf("  Carta 2: %.2f\n\n", soma_carta2);

    if (soma_carta1 == soma_carta2) {
        printf("Resultado: Empate!\n");
    } else {
        printf("Resultado: Carta %s venceu!\n", (soma_carta1 > soma_carta2) ? "1" : "2");
    }

    printf("\n");
}

int main() {
    Carta cartas[2];

    // Menu principal
    int opcao;
    do {
        printf("=== Super Trunfo - Menu Principal ===\n");
        printf("1 - Nível Novato (Cadastro e Exibição)\n");
        printf("2 - Nível Aventureiro (Comparação 1 Atributo)\n");
        printf("3 - Nível Mestre (Comparação 2 Atributos)\n");
        printf("0 - Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        printf("\n");

        switch(opcao) {
            case 1:
                nivelNovato(cartas);
                break;
            case 2:
                if (cartas[0].codigo[0] == '\0' || cartas[1].codigo[0] == '\0') {
                    printf("Cadastre as cartas primeiro no nível Novato.\n\n");
                } else {
                    nivelAventureiro(cartas);
                }
                break;
            case 3:
                if (cartas[0].codigo[0] == '\0' || cartas[1].codigo[0] == '\0') {
                    printf("Cadastre as cartas primeiro no nível Novato.\n\n");
                } else {
                    nivelMestre(cartas);
                }
                break;
            case 0:
                printf("Saindo do programa. Até mais!\n");
                break;
            default:
                printf("Opção inválida! Tente novamente.\n\n");
        }
    } while(opcao != 0);

    return 0;
}
