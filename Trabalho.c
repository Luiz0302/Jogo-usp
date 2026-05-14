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

    printf("\n=========== Cartas no Baralho (Embaralhadas) ===========\n");
    
    for(i = 0; i < 44; i++)
    {
        printf("Valor: %d - ", baralho[i].valor);

        if(baralho[i].naipe == 0)
        {
            printf("Espadas\n");
        }
        else if(baralho[i].naipe == 1)
        {
            printf("Paus\n");
        }
        else if(baralho[i].naipe == 2)
        {
            printf("Ouros\n");
        }
        else if(baralho[i].naipe == 3)
        {
            printf("Copas\n");
        }
    } //mostrar cartas


    // --- Interface inicial ---
    printf("=========== Bem-vindo à Masmorra! =========== \n");
    printf("Sobreviva ás 10 salas ou sucumba tentando.\n");

    // Status do player
    printf("=========== Status do Player ===========\n");
    printf("HP: %d\n", hp);
    printf("Força da Arma Equipada: %d\n", arma_equipada); 
    printf("Limite de Armas: %d\n", limite_arma);
    printf("Pulo de sala: %d\n", pode_skip);

    // --- Finalização do jogo ---
    if (hp <= 0) // Tem que add condição de vitória, mas como não tem nada, vamo se virar com o hp
    {
        printf("========= Game Over! ========= \n Você foi consumido pela masmorra \n");
    }
    else
    {
        printf("=========== Parabéns! =========== \n Você derrotou a masmorra \n");
    }

    return 0;
}