#ifndef ESCALONADOR_H
#define ESCALONADOR_H

// Define o tempo máximo de cada processo na CPU
#define QUANTUM 2 

#include "processos.h"
#include <stdio.h>

// Função que executa o ESCALONAMENTO Round-Robin
void executar_round_robin(PCB *processo) {
    
    if (processo->tempo_restante > 0) {
        processo->estado = EXECUTANDO;

        // Define quanto tempo o processo vai rodar nesta fatia
        int tempo_executado = (processo->tempo_restante >= QUANTUM) ? QUANTUM : processo->tempo_restante;
        
        printf("\033[0;33m  >>> CPU: Rodando PID %d | Restante: %ds\033[0m\n", processo->pid, processo->tempo_restante);
        
        // Deduz o tempo gasto do total restante
        processo->tempo_restante -= tempo_executado;
        
        if (processo->tempo_restante <= 0) {
            // Finaliza o processo se o tempo zerar
            processo->estado = ENCERRADO;
            printf("\033[0;32m      [ OK ] PID %d Finalizado!\033[0m\n", processo->pid);
        } 
        else {
            // Se ainda houver tempo, volta para a fila (Troca de Contexto)
            processo->estado = PRONTO;
            printf("      [ !! ] Quantum expirado. PID %d volta para a fila.\n", processo->pid);
        }
    }
}

#endif