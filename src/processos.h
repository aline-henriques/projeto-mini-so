#ifndef PROCESSOS_H
#define PROCESSOS_H

// Define os estados do processo no ciclo de vida do SO
typedef enum { 
    NOVO,        // Criado, aguardando memória
    PRONTO,      // Na RAM, aguardando CPU
    EXECUTANDO,  // Em execução na CPU
    ENCERRADO    // Finalizado, memória liberada
} Estado;

// Estrutura que armazena os dados de controle do processo (PCB)
typedef struct {
    int pid;             // ID único do processo
    int burst_time;      // Tempo total de CPU necessário
    int tempo_restante;  // Tempo que falta para terminar
    int prioridade;      // Prioridade do processo
    int tamanho;         // Espaço ocupado na RAM (bytes)
    int base_memoria;    // Posição inicial no array da RAM
    Estado estado;       // Estado atual do processo
} PCB;

#endif