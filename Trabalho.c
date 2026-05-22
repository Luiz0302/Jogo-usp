#include <stdio.h>
#include <locale.h>
#include <stdlib.h> 
#include <time.h>   

struct Carta {
    int valor;
    int naipe; // 0: Espadas, 1: Paus, 2: Ouros, 3: Copas
};

int main() {
    setlocale(LC_ALL, "portuguese");
    srand(time(NULL)); 

    // Com o tamanho do baralho sendo 100 evita problemas com cartas extras que vão sobrar
    struct Carta baralho[100]; 
    struct Carta mesa[4];
    int mesa_disponivel[4] = {1, 1, 1, 1}; 
    
    int i = 0;
    int valor;
    int aleatorio;
    struct Carta temp;

    // Status do Player
    int hp = 20;
    int arma_equipada = 0;
    int ultimo_monstro = 0; // Guarda o valor do ultimo monstro pra regra de quebra da arma
    int pode_skip = 1; 
    
    // Inicialização do Baralho 
    for(valor = 2; valor <= 14; valor++) {
        baralho[i].valor = valor;
        baralho[i].naipe = 0; // Espadas
        i++;
    }
    for(valor = 2; valor <= 14; valor++) {
        baralho[i].valor = valor;
        baralho[i].naipe = 1; // Paus
        i++;
    }
    for(valor = 2; valor <= 10; valor++) {
        baralho[i].valor = valor;
        baralho[i].naipe = 2; // Ouros
        i++;
    }
    for(valor = 2; valor <= 10; valor++) {
        baralho[i].valor = valor;
        baralho[i].naipe = 3; // Copas
        i++;
    }

    // Embaralhamento
    for(i = 0; i <= 43; i++) {
        aleatorio = rand() % 44;
        temp = baralho[i];
        baralho[i] = baralho[aleatorio];
        baralho[aleatorio] = temp;
    }

    int sala_atual = 1;
    int topo_baralho = 0;
    int fim_baralho = 44; 
    int opcao;

    printf("=========== Bem-vindo à Masmorra =========== \n");
    printf("\nSobreviva às salas ou sucumba tentando.\n");

    // Compra inicial
    for(i = 0; i < 4; i++) {
        mesa[i] = baralho[topo_baralho];
        topo_baralho++;
        mesa_disponivel[i] = 1;
    }

    // Loop principal do jogo
    while (hp > 0 && (mesa_disponivel[0] || mesa_disponivel[1] || mesa_disponivel[2] || mesa_disponivel[3])) {
        printf("\n=========== Sala %d ===========\n", sala_atual);
        printf("HP: %d/20 | Arma: %d\n", hp, arma_equipada);
        printf("Cartas na mesa:\n");

        for(i = 0; i < 4; i++) {
            if (mesa_disponivel[i]) {
                printf("  Carta %d -> Valor %d de ", i + 1, mesa[i].valor);
                if(mesa[i].naipe == 0) printf("Espadas (Monstro)\n");
                else if(mesa[i].naipe == 1) printf("Paus (Monstro)\n");
                else if(mesa[i].naipe == 2) printf("Ouros (Arma)\n");
                else if(mesa[i].naipe == 3) printf("Copas (Poção)\n");
            } else {
                printf("  Carta %d\n", i + 1);
            }
        }

        printf("\nO que vai fazer?\n");
        printf("1 Enfrentar a sala\n");
        printf("2 Pular sala (Disponível: %d)\n", pode_skip);
        printf("Escolha: ");
        scanf("%d", &opcao);

        if (opcao != 1 && (opcao != 2 || !pode_skip)) {
            printf("\n! Opção inválida ou skip indisponível!\n");
            continue;
        }
        
        // Mecânica de Skip 
        if (opcao == 2 && pode_skip) {
            printf("\nVocê se acovardou e correu.\n");
            for(i = 0; i < 4; i++) {
                if (mesa_disponivel[i]) {
                    baralho[fim_baralho] = mesa[i];
                    fim_baralho++;
                }
            }
            pode_skip = 0; 
            sala_atual++;

            // Compra nova mesa completa
            for(i = 0; i < 4; i++) {
                if (topo_baralho < fim_baralho) {
                    mesa[i] = baralho[topo_baralho];
                    topo_baralho++;
                    mesa_disponivel[i] = 1;
                } else {
                    mesa_disponivel[i] = 0;
                }
            }
        }
        // Enfrentar a sala 
        else if (opcao == 1) {
            printf("\nPrepare-se para o combate...\n");
            
            int cartas_resolvidas = 0;
            int ja_usou_pocao = 0;
            int cartas_na_mesa = 0;

            for(i = 0; i < 4; i++) {
                if (mesa_disponivel[i]) cartas_na_mesa++;
            }
            
            int limite_resolucao = (cartas_na_mesa < 3) ? cartas_na_mesa : 3;

            while (cartas_resolvidas < limite_resolucao && hp > 0) {
                int escolha = 0;
                printf("\nEscolha uma carta (1 a 4) para interagir [%d/%d]: ", cartas_resolvidas + 1, limite_resolucao);
                scanf("%d", &escolha);

                if (escolha < 1 || escolha > 4 || !mesa_disponivel[escolha - 1]) {
                    printf("[!] Carta inválida ou já resolvida.\n");
                    continue;
                }

                int idx = escolha - 1;
                mesa_disponivel[idx] = 0; 
                cartas_resolvidas++;

                // Lógica dos Monstros
                if (mesa[idx].naipe == 0 || mesa[idx].naipe == 1) {
                    printf(" MONSTRO Força %d\n", mesa[idx].valor);
                    
                    // Verifica se a arma defende
                    if (arma_equipada > 0 && (ultimo_monstro == 0 || mesa[idx].valor < ultimo_monstro)) {
                        int dano_recebido = mesa[idx].valor - arma_equipada;
                        if (dano_recebido > 0) {
                            hp -= dano_recebido;
                            printf("Sua arma absorveu parte do impacto Tomou %d de dano.\n", dano_recebido);
                        } else {
                            printf("Defesa perfeita! A arma tancou o monstro sem sofrer dano.\n");
                        }
                        ultimo_monstro = mesa[idx].valor; 
                    } else {
                        if (arma_equipada > 0) {
                            printf("    [!] Sua arma não serve contra esse monstro!\n");
                        }
                        hp -= mesa[idx].valor;
                        printf("    Sem defesa! Tomou %d de dano direto.\n", mesa[idx].valor);
                    }
                }
                // Lógica Arma 
                else if (mesa[idx].naipe == 2) {
                    arma_equipada = mesa[idx].valor;
                    ultimo_monstro = 0; // Reset do histórico de quebra
                    printf(" -> [ARMA] Equipou uma arma de força %d.\n", arma_equipada);
                }
                // Lógica Poção 
                else if (mesa[idx].naipe == 3) {
                    if (!ja_usou_pocao) {
                        hp += mesa[idx].valor;
                        if (hp > 20) hp = 20; 
                        ja_usou_pocao = 1; 
                        printf(" -> [POÇÃO] Curado! HP atual: %d\n", hp);
                    } else {
                        printf(" -> [POÇÃO] Efeito desperdiçado! Só é permitido uma poção por sala.\n");
                    }
                }
            }

            // Transição de sala
            if (hp > 0) {
                pode_skip = 1; 
                sala_atual++;

                struct Carta sobrou;
                int achou_sobra = 0;

                for(i = 0; i < 4; i++) {
                    if (mesa_disponivel[i]) {
                        sobrou = mesa[i];
                        achou_sobra = 1;
                    }
                }

                // Reseta estados da mesa antiga
                for(i = 0; i < 4; i++) mesa_disponivel[i] = 0;

                // Repovoa a mesa
                int start_idx = 0;
                if (achou_sobra) {
                    mesa[0] = sobrou;
                    mesa_disponivel[0] = 1;
                    start_idx = 1;
                }

                for(i = start_idx; i < 4; i++) {
                    if (topo_baralho < fim_baralho) {
                        mesa[i] = baralho[topo_baralho];
                        topo_baralho++;
                        mesa_disponivel[i] = 1;
                    }
                }
            }
        }
    }

    printf("\n====================================\n");
    if (hp <= 0) {
        printf("========= Game Over ========= \nVocê foi consumido pela masmorra.\n");
    } else {
        printf("=========== Parabéns =========== \nVocê derrotou a masmorra\n");
    }

    return 0;
}