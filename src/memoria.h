
#ifndef MEMORIA_H
#define MEMORIA_H

#define TAMANHO_RAM 1024
#include <stdio.h>

int ram[TAMANHO_RAM]; 

// Limpa toda a memória ao iniciar o sistema
void inicializar_memoria() {
    for (int i = 0; i < TAMANHO_RAM; i++) {
        ram[i] = 0;
    }
}

// Implementa o algoritmo First-Fit para alocação contígua
int alocar_memoria(int pid, int tamanho) {
    int espacos_livres = 0;
    for (int i = 0; i < TAMANHO_RAM; i++) {
        if (ram[i] == 0) {
            espacos_livres++;
            if (espacos_livres == tamanho) {
                int inicio = i - tamanho + 1;
                for (int j = inicio; j <= i; j++) {
                    ram[j] = pid;
                }
                return inicio;
            }
        } else {
            espacos_livres = 0;
        }
    }
    return -1;
}

// Libera as posições ocupadas pelo processo na RAM
void desalocar_memoria(int pid) {
    for (int i = 0; i < TAMANHO_RAM; i++) {
        if (ram[i] == pid) ram[i] = 0;
    }
}

// Representação visual da RAM
void imprimir_mapa_memoria() {
    printf("\n  [ MAPA DE MEMORIA RAM ]\n  |");
    for (int i = 0; i < TAMANHO_RAM; i += 32) {
        if (ram[i] == 0) printf(" - "); // Espaço livre
        else printf("\033[0;34m%2d \033[0m", ram[i]); // PID
    }
    printf("|\n");
}

#endif