#include <stdio.h>
#include <stdlib.h>
#include "processos.h"
#include "memoria.h"
#include "escalonador.h"

int main() {
    inicializar_memoria();
    
    FILE *file = fopen("processos.txt", "r");
    if (!file) {
        printf("\033[0;31mErro ao abrir arquivo processos.txt\033[0m\n");
        return 1;
    }

    PCB fila[20];
    int total_processos = 0;

    while (fscanf(file, "%d | %d %d %d", 
                  &fila[total_processos].pid, 
                  &fila[total_processos].burst_time, 
                  &fila[total_processos].tamanho, 
                  &fila[total_processos].prioridade) != EOF) {
        
        fila[total_processos].tempo_restante = fila[total_processos].burst_time;
        fila[total_processos].estado = NOVO;
        fila[total_processos].base_memoria = -1;
        total_processos++;
    }
    fclose(file);

    int tempo_global = 0;
    int concluidos = 0;

    printf("\n\033[1;36m=== INICIANDO SIMULACAO MINI-SO ===\033[0m\n");

    while (concluidos < total_processos) {
        printf("\n----------------------------------------------------");
        printf("\n  INSTANTE: %ds | CONCLUIDOS: %d/%d", tempo_global, concluidos, total_processos);
        printf("\n----------------------------------------------------\n");

        for (int i = 0; i < total_processos; i++) {
            
            // Tenta alocar se o processo for NOVO
            if (fila[i].estado == NOVO) {
                int base = alocar_memoria(fila[i].pid, fila[i].tamanho);
                if (base != -1) {
                    fila[i].base_memoria = base;
                    fila[i].estado = PRONTO;
                    printf("  [ MEM ] PID %d alocado (Pos: %d)\n", fila[i].pid, base);
                }
            }

            // Executa se estiver PRONTO
            if (fila[i].estado == PRONTO && fila[i].tempo_restante > 0) {
                executar_round_robin(&fila[i]);
                tempo_global += QUANTUM;

                if (fila[i].estado == ENCERRADO) {
                    desalocar_memoria(fila[i].pid);
                    concluidos++;
                }
                imprimir_mapa_memoria();
            }
        }
    }

    printf("\n\033[1;32m=== SIMULACAO CONCLUIDA COM SUCESSO :D ===\033[0m\n");
    return 0;
}