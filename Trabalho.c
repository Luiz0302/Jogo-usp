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
    
    // Vetor para saber se a carta da mesa ja foi usada (1 tá livre, 0 já foi)
    int mesa_disponivel[4] = {1, 1, 1, 1}; 
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
    
    // Guarda o valor do ultimo monstro que a arma bateu para validar a regra de quebra
    int ultimo_monstro = 0; 

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
        baralho[i].decay = 3; // Mantendo a estrutura padrão de preenchimento
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
    int fim_baralho = 44; // Guarda o final do vetor para empurrar cartas se pular sala
    int opcao;

    printf("=========== Bem-vindo à Masmorra =========== \n");
    printf("\nSobreviva às 10 salas ou sucumba tentando.\n");

    // Compra as 4 primeiras cartas para comecar a mesa
    for(i = 0; i < 4; i++) {
        mesa[i] = baralho[topo_baralho];
        topo_baralho++;
        mesa_disponivel[i] = 1;
    }

    // Loop principal roda enquanto tiver vida e cartas no deck
    while (topo_baralho <= fim_baralho && hp > 0) {
        printf("\n=========== Sala %d ===========\n", sala_atual);
        printf("HP: %d | Arma: %d\n", hp, arma_equipada);
        printf("As cartas que voce tem na sala são:\n");

        // Mostra o status atual das cartas na mesa
        for(i = 0; i < 4; i++) {
            if (mesa_disponivel[i] == 1) {
                printf("Carta %d -> Valor: %d - ", i + 1, mesa[i].valor);
                if(mesa[i].naipe == 0) printf("Espadas (Monstro)\n");
                else if(mesa[i].naipe == 1) printf("Paus (Monstro)\n");
                else if(mesa[i].naipe == 2) printf("Ouros (Arma)\n");
                else if(mesa[i].naipe == 3) printf("Copas (Poção)\n");
            } else {
                printf("Carta %d -> [RESOLVIDA]\n", i + 1);
            }
        }

        // Menu da sala
        printf("\nO que deseja fazer?\n");
        printf("1 Enfrentar a sala\n");
        printf("2 Pular esta sala (Disponível: %d)\n", pode_skip);
        printf("Escolha: ");
        scanf("%d", &opcao);

        // Validando jogadas erradas
        if (opcao != 1 && (opcao != 2 || pode_skip == 0)) {
            printf("\n[ERRO] Opção inválida! Tente de novo.\n");
        }
        
        // Logica para pular a sala jogando as cartas pro final
        else if (opcao == 2 && pode_skip == 1) {
            printf("\nVocê decidiu pular a sala\n");
            
            for(i = 0; i < 4; i++) {
                if (mesa_disponivel[i] == 1) {
                    baralho[fim_baralho] = mesa[i];
                    fim_baralho++;
                }
            }
            pode_skip = 0; 
            sala_atual++;

            // Puxa mais 4 cartas novas
            for(i = 0; i < 4; i++) {
                mesa[i] = baralho[topo_baralho];
                topo_baralho++;
                mesa_disponivel[i] = 1;
            }
        }
        
        // Logica para resolver as 3 cartas uma por uma
        else if (opcao == 1) {
            printf("\nVocê decidiu enfrentar a sala\n");
            
            int cartas_resolvidas = 0;
            int ja_usou_pocao = 0;

            // Roda o loop interno controlando estritamente pelas variaveis (sem break)
            while (cartas_resolvidas < 3 && hp > 0) {
                int escolha = 0;
                printf("\nEscolha uma carta de 1 a 4 para resolver [%d de 3]: ", cartas_resolvidas + 1);
                scanf("%d", &escolha);

                // Tratando erros de escolha do usuario
                if (escolha < 1 || escolha > 4 || mesa_disponivel[escolha - 1] == 0) {
                    printf("[ERRO] Essa carta não está disponível!\n");
                } else {
                    int idx = escolha - 1;
                    mesa_disponivel[idx] = 0; 
                    cartas_resolvidas++;

                    // Logica de Combate (Espadas ou Paus)
                    if (mesa[idx].naipe == 0 || mesa[idx].naipe == 1) {
                        printf("[COMBATE] Monstro valor %d!\n", mesa[idx].valor);
                        
                        // Checa se a arma ainda e valida (regra do monstro menor)
                        if (arma_equipada > 0 && (ultimo_monstro == 0 || mesa[idx].valor < ultimo_monstro)) {
                            int diferenca_dano = mesa[idx].valor - arma_equipada;
                            
                            if (diferenca_dano > 0) {
                                hp = hp - diferenca_dano;
                                printf("Você usou sua arma e sofreu %d de dano (diferença resolvida).\n", diferenca_dano);
                            } else {
                                printf("Sua arma é forte o suficiente! Você não sofreu nenhum dano nesta carta.\n");
                            }
                            ultimo_monstro = mesa[idx].valor; 
                        } else {
                            if (arma_equipada > 0) {
                                printf("Sua arma travou/quebrou nesse monstro ");
                            }
                            hp = hp - mesa[idx].valor;
                            printf("Tomou o dano inteiro do monstro: %d\n", mesa[idx].valor);
                        }
                    }
                    
                    // Logica para equipar Arma (Ouros)
                    else if (mesa[idx].naipe == 2) {
                        arma_equipada = mesa[idx].valor;
                        ultimo_monstro = 0; // Nova arma limpa a restrição anterior
                        printf(" Nova arma equipada. Força: %d\n", arma_equipada);
                    }
                    
                    // Logica da Poção (Copas)
                    else if (mesa[idx].naipe == 3) {
                        if (ja_usou_pocao == 0) {
                            hp = hp + mesa[idx].valor;
                            if (hp > 20) {
                                hp = 20; 
                            }
                            ja_usou_pocao = 1; 
                            printf("Curado. Seu HP subiu para %d\n", hp);
                        } else {
                            printf("Você só pode usar uma poção por rodada. Essa foi perdida.\n");
                        }
                    }
                }
            }

            // Preparando a proxima sala guardando a 4ª carta que sobrou
            if (hp > 0) {
                pode_skip = 1; 
                sala_atual++;

                struct Carta sobrou;
                for(i = 0; i < 4; i++) {
                    if (mesa_disponivel[i] == 1) {
                        sobrou = mesa[i];
                    }
                }

                // Monta a mesa da rodada seguinte com a que sobrou + 3 novas
                mesa[0] = sobrou;
                mesa_disponivel[0] = 1;

                for(i = 1; i < 4; i++) {
                    if (topo_baralho < fim_baralho) {
                        mesa[i] = baralho[topo_baralho];
                        topo_baralho++;
                        mesa_disponivel[i] = 1;
                    } else {
                        mesa_disponivel[i] = 0; 
                    }
                }
            }
        }
    }

    // --- Finalização do jogo ---
    printf("\n=============================================\n");
    if (hp <= 0) 
    {
        printf("========= Game Over ========= \nVocê foi consumido pela masmorra.\n");
    }
    else
    {
        printf("=========== Parabéns =========== \nVocê derrotou a masmorra\n");
    }
    return 0;
}