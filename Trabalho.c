#include <stdio.h>
#include <locale.h>
#include <stdlib.h> 
#include <time.h>   

// Estrutura do baralho 
struct Carta {
    int valor;
    int naipe;
};

int main() {
    setlocale(LC_ALL, "portuguese");
    srand(time(NULL));   //Pra usar a aleatoriedade do rand 

    // --- Definições do Baralho e da Mesa ---
    struct Carta baralho[44];
    struct Carta mesa[4];
    int i = 0;
    int valor;
    int aleatorio;
    struct Carta temp;

    // --- Informações player ---
    int hp = 20;
    int arma_equipada = 0;
    int limite_arma = 1;
    int skip_sala = 0;
    int pode_skip = 1;

    // --- Preenchimento do Baralho ---
    for(valor = 2; valor <= 14; valor++)
    {
        baralho[i].valor = valor;
        baralho[i].naipe = 0;
        i++;
    }     // Espadas

    for(valor = 2; valor <= 14; valor++)
    {
        baralho[i].valor = valor;
        baralho[i].naipe = 1;
        i++;
    }     // Paus

    for(valor = 2; valor <= 10; valor++)
    {
        baralho[i].valor = valor;
        baralho[i].naipe = 2;
        i++;
    }     //Ouros

    for(valor = 2; valor <= 10; valor++)
    {
        baralho[i].valor = valor;
        baralho[i].naipe = 3;
        i++;
    }     // Copas

    // --- Embaralhar  ---
    for(i = 0; i <= 43; i++)
    {
        aleatorio = rand() % 44;
        temp = baralho[i];
        baralho[i] = baralho[aleatorio];
        baralho[aleatorio] = temp;
    } //embaralhar.


    // --- Variáveis para ajudar a controlar o jogo ---
    int sala_atual = 1;
    int topo_baralho = 0;
    int opcao;

    printf("=========== Bem-vindo à Masmorra =========== \n");
    printf("\nSobreviva às 10 salas ou sucumba tentando.\n");

    // --- Loop Principal ---
    for (sala_atual = 1; sala_atual <= 10 && hp > 0; sala_atual++) 
    {
        printf("\n=========== Sala %d/10 ===========\n", sala_atual);
        printf("HP: %d | Arma: %d\n", hp, arma_equipada);
        printf("As cartas que voce tem na sala são:\n");

        // Puxa 4 cartas do baralho e já mostra na tela
        for(i = 0; i < 4; i++) 
        {
            mesa[i] = baralho[topo_baralho];
            topo_baralho++;

            printf("Carta %d -> Valor: %d - ", i + 1, mesa[i].valor);
            if(mesa[i].naipe == 0) printf("Espadas (Monstro)\n");
            else if(mesa[i].naipe == 1) printf("Paus (Monstro)\n");
            else if(mesa[i].naipe == 2) printf("Ouros (Arma)\n");
            else if(mesa[i].naipe == 3) printf("Copas (Poção)\n");
        }

        // Menu da sala
        printf("\nO que deseja fazer?\n");
        printf("1 Enfrentar a sala\n");
        printf("2 Pular esta sala (Disponível: %d)\n", pode_skip);
        printf("Escolha: ");
        scanf("%d", &opcao);

        if (opcao == 2 && pode_skip == 1) {
            printf("\nVocê decidiu pular a sala\n");
            pode_skip = 0; // Gasta o pulo
            continue;      // Ainda n tem o combate então ta pulando pro próximo turno
        }
        
        printf("\nVocê decidiu enfrentar a sala\n");

        pode_skip = 1; // Recupera o pulo pro jogador usar na próxima sala
    }

    // --- Finalização do jogo ---
    if (hp <= 0) 
    {
        printf("========= Game Over ========= \nVocê foi consumido pela masmorra.\n");
    }
    else
    {
        printf("=========== Parabéns =========== \nVocê derrotou a masmorra\n");
    }
    // lepo lepo
    return 0;
}