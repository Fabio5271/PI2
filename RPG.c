#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "labirinto.h"
#include "montanha.h"
#include "vulcao.h"
// #include "dragao.h"

#define NUM_NODES 8

int game_path[8][8];
int curr_ep = 1;

void ep_start_msg(){
    if (curr_ep == 1){
        printf(labr_start);
    }
    if (curr_ep == 2){
        printf(mount_start);
    }
    if (curr_ep == 3){
        printf(volc_start);
    }
    // if (curr_ep == 4){
    //     printf(volc_start);
    // }
}

void ep_end_msg(){
    if (curr_ep == 1){
        printf(labr_end);
    }
    if (curr_ep == 2){
        printf(mount_end);
    }
    if (curr_ep == 3){
        printf(volc_end);
    }
    // if (curr_ep == 4){
    //     printf(volc_end);
    // }
}

void game_path_init(int ep_num){
    switch (ep_num){
        case 1:
            memcpy(game_path, labr_path, sizeof(labr_path));
            break;
        case 2:
            memcpy(game_path, mount_path, sizeof(mount_path));
            break;
        case 3:
            memcpy(game_path, volc_path, sizeof(volc_path));
            break;
        // case 4:
        //     memcpy(game_path, drag_path, sizeof(drag_path));
        //     break;
    }
}

void death_msg(int orig, int dest){
    if (curr_ep == 1){
        l_death_msg(orig, dest);
    }
    if (curr_ep == 2){
        m_death_msg(orig, dest);
    }
    if (curr_ep == 3){
        v_death_msg(orig, dest);
    }
    // if (curr_ep == 4){
    //     d_death_msg(orig, dest);
    // }
}

void node_msg(int orig, int dest){
    if (curr_ep == 1){
        l_node_msg(orig, dest);
    }
    if (curr_ep == 2){
        m_node_msg(orig, dest);
    }
    if (curr_ep == 3){
        v_node_msg(orig, dest);
    }
    // if (curr_ep == 4){
    //     d_node_msg(orig, dest);
    // }
}

int check_death(int path[], int num_nodes){
    if (game_path[path[num_nodes - 2]][path[num_nodes - 1]] != 2){ // Verifica se o caminho escolhido não tem a relação 2 (morte)
        return 0;
    }
    death_msg(path[num_nodes - 2] + 1, path[num_nodes - 1] + 1); // Manda as mensagens de morte usando os índices + 1, pra facilitar colocar cada caso na função
    printf("Voltando pro começo...\n");
    return 1;
}

int main(){
    // memcpy(game_path, labr_path, sizeof(labr_path));
    // int current_node = 0;            // Começa na entrada do labirinto
    // int *path = malloc(sizeof(int)); // Armazena o caminho escolhido pelo usuário
    // int nodes_in_path = 1;           // Número de nós no caminho, começa com um (a entrada)
    // path[0] = current_node;

    printf("Bem-vindo ao RPG do FUSCAO\n");
    printf("Você é um herói destemido que recebe uma missão do grande sábio da sua terra: matar um terrível dragão que aterroriza o reino.\n");
    printf(" Mas, antes de enfrentar o dragão, você precisa coletar uma série de equipamentos mágicos.Boa sorte!");
    printf("O primeiro item que você precisa é a Espada da Tormenta. Dizem que ela esta dentro de labirinto perigoso, que é cheio de armadilhas mortais e monstros hostis.\n");
    printf("O caminho pelo labirinto é complicado e você precisa escolher cuidadosamente qual caminho seguir para evitar as armadilhas e derrotar os monstros.");

    while (curr_ep < 4){ 
        ep_start_msg();
        game_path_init(curr_ep);
        int current_node = 0;            // Começa na entrada do labirinto
        int *path = malloc(sizeof(int)); // Armazena o caminho escolhido pelo usuário
        int nodes_in_path = 1;           // Número de nós no caminho, começa com um (a entrada)
        path[0] = current_node;

        // Enquanto não chegar no objetivo
        while (current_node != NUM_NODES - 1) {
            printf("\nVocê está no nó %d.\n", current_node + 1);
            printf("Para onde você quer ir?\n");

            // Mostra os caminhos disponíveis
            for (int i = 0; i < NUM_NODES; i++) {
                if (game_path[current_node][i] != 0) {
                    printf("%d. Nó %d\n", i + 1, i + 1);
                }
            }

            int choice;
            scanf("%d", &choice);
            if (choice < 1 || choice > NUM_NODES || game_path[current_node][choice - 1] == 0) {
                printf("Opção inválida. Tente novamente.\n");
                continue;
            }

            // Aloca mais memória pros nós novos
            path = realloc(path, (nodes_in_path + 1) * sizeof(int));
            path[nodes_in_path++] = choice - 1;
            current_node = choice - 1;

            // Reinicia o jogo se morrer
            if (check_death(path, nodes_in_path) == 1) {
                current_node = 0;
                free(path);                      // Reinicializar path
                int *path = malloc(sizeof(int)); // Reinicializar path
                path[0] = current_node;          // Reinicializar path
                nodes_in_path = 1;
            }
        }
        ep_end_msg();
        curr_ep++;
        free(path);
    }
    printf("\nParabéns! Você terminou o jogo!\n");
    // if (path){
    //     free(path);
    // }
    return EXIT_SUCCESS;
}