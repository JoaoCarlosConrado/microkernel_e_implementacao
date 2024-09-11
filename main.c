#include <stdio.h>
#include <pthread.h>
#include <unistd.h>  // Para usar sleep
#include "kernel.h"
// Funções de exemplo para os processos
char processFunc1(void) {
    printf("Executando processo 1\n");
    return REPEAT;
}

char processFunc2(void) {
    printf("Executando processo 2\n");
    return SUCCESS;
}

char processFunc3(void) {
    printf("Executando processo 3\n");
    return REPEAT;
}

// Funções das threads
void* kernelLoopThread(void* arg) {
    kernelLoop();  // Roda indefinidamente
    return NULL;
}

void* kernelTickThread(void* arg) {
    while (1) {
        kernelTick();  // Simula o tick do sistema
        usleep(1000000);  // Aguarda 100ms (0.1 segundos) entre ticks (ajustável)
    }
    return NULL;
}

int main(void) {
    // Inicializa o kernel
    kernelInit();

    // Cria processos de exemplo
    process proc1 = { .deadline = 10, .period = 5, .function = processFunc1 };
    process proc2 = { .deadline = 15, .period = 10, .function = processFunc2 };
    process proc3 = { .deadline = 20, .period = 15, .function = processFunc3 };

    // Adiciona os processos ao kernel
    kernelAddProc(&proc1);
    kernelAddProc(&proc2);
    kernelAddProc(&proc3);

    // Declarando as threads
    pthread_t threadLoop;
    pthread_t threadTick;

    // Cria a thread para rodar kernelLoop
    pthread_create(&threadLoop, NULL, kernelLoopThread, NULL);
    
    // Cria a thread para rodar kernelTick
    pthread_create(&threadTick, NULL, kernelTickThread, NULL);

    // Espera indefinidamente pelas threads (na prática, elas nunca vão terminar)
    pthread_join(threadLoop, NULL);
    pthread_join(threadTick, NULL);

    return 0;
}
