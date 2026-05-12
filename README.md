# Simulador de Gerência de Processos e Memória (Mini-SO)

**Equipe:** Aline Henriques e Mirna Lustosa 
**Disciplina:** Infraestrutura de Software | Prof. Monique Soares

## 1. Visão Geral
Este projeto é um simulador de sistema operacional que demonstra a interação entre o escalonamento de CPU e a gerência de memória RAM. 
O objetivo é aplicar conceitos de multiprogramação, onde o sistema deve admitir processos, gerenciar o espaço em memória e distribuir o tempo de processamento de forma justa entre as tarefas.

## 2. Tecnologias e Algoritmos
*   **Escalonamento de CPU:** Round-Robin (Quantum = 2). Garante que todos os processos recebam atenção da CPU em fatias de tempo iguais.
*   **Gerência de Memória:** First-Fit. Alocação contígua onde o sistema busca o primeiro bloco de memória livre que comporte o tamanho do processo.
*   **Estrutura de Controle:** Bloco de Controle de Processo (PCB).

---

## 3. Arquitetura do Sistema e Funções

O projeto está dividido de forma modular para facilitar a manutenção e organização:

### 📂 `processos.h`
Este arquivo define as estruturas de dados fundamentais do sistema.

*   **`Estado (enum)`**: Define os estados do processo: `NOVO`, `PRONTO`, `EXECUTANDO` e `ENCERRADO`.
*   **`PCB (struct)`**: Armazena todos os metadados do processo, como PID, tempo total, tempo restante, prioridade, tamanho e sua posição na memória (base).

### 📂 `memoria.h`
Este arquivo é responsável pela simulação física da memória RAM (vetor de 1024 bytes).

*   **`inicializar_memoria()`**: Limpa a RAM (preenche com 0) ao iniciar o sistema.
*   **`alocar_memoria(pid, tamanho)`**: Implementa o algoritmo **First-Fit**. Percorre o vetor buscando um espaço livre contíguo. Retorna o endereço inicial ou -1 se não houver espaço.
*   **`desalocar_memoria(pid)`**: Varre a RAM e libera todos os blocos ocupados pelo processo identificado pelo PID.
*   **`imprimir_mapa_memoria()`**: Gera um log visual da ocupação da RAM para acompanhamento da simulação.

### 📂 `escalonador.h`
Este arquivo contém a lógica de processamento da CPU.

*   **`executar_round_robin(PCB *processo)`**: Executa o processo pelo tempo do Quantum ou pelo seu tempo restante. Gerencia a transição de estados e realiza a "troca de contexto" simulada, movendo o processo de volta para o estado de PRONTO se ele não finalizar.

### 📂 `main.c`
Este arquivo é o núcleo do simulador.

*   **Leitura de Arquivo**: Carrega os dados de `processos.txt` e inicializa a fila de PCBs.
*   **Clock do Sistema**: Controla o tempo global da simulação.
*   **Loop de Execução**: Coordena a tentativa de alocação de novos processos na RAM e chama o escalonador para os processos que já estão prontos.

---

## 4. Como Executar

1.  Certifique-se de que o arquivo `processos.txt` está no mesmo diretório.
2.  Compile o código:
    ```bash
    gcc main.c -o mini-so
    ```
3.  Execute o programa:
    ```bash
    ./mini-so
    ```

## 5. Exemplo de Entrada (`processos.txt`)
O arquivo deve seguir o padrão: `PID | Burst_Time RAM Prioridade`
```text
1 | 10 120 1
2 | 4 80 2
3 | 6 200 1
```