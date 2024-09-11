#include "kernel.h"

//armazena as referências dos processos
static process* pool [POOL_SIZE];

int start;
int end;
//inicializa o kernel
char kernelInit(void) {
    start=0;
    end=0;
    return SUCCESS;
}

//adiciona os processos no pool
char kernelAddProc(process* func) {
    //adiciona processo somente se houver espaço livre
    //o fim nunca pode coincidir com o início
    if(((end+1)%POOL_SIZE) != start) {
        //adiciona o novo processo e agenda para executar 
        func->deadline += func->period;
        pool [end] = func;
        end = (end+1)%POOL_SIZE;
       return SUCCESS; //sucesso
   }
   return FAIL; //falha
}

void kernelLoop(void) {
    unsigned int count;
    unsigned int next;
    process* tempProc;
    
    for(;;) {
        if (start != end) {
            // Procura a próxima função a ser executada com base no tempo
            count = (start + 1) % POOL_SIZE;
            next = start;
            while (count != end) {
                if ((pool[count]->deadline) < (pool[next]->deadline)) {
                    next = count;
                }
                count = (count + 1) % POOL_SIZE; // Próximo processo
            }
            // Troca o processo de menor tempo com o primeiro (trocando ponteiros)
            tempProc = pool[next];
            pool[next] = pool[start];
            pool[start] = tempProc;
            
            while (pool[start]->deadline > 0) {
                // Executa a função do processo
            }
            switch (pool[start]->function()) {
                case REPEAT:
                    kernelAddProc(pool[start]);
                    break;
                case FAIL:
                    break;
                default:
                    break;
            }
            // Inicia o próximo processo
            start = (start + 1) % POOL_SIZE; // Próximo processo
        }
    }
}

void kernelTick(void) {
    int proc;
    proc = start;
    while(proc!=end) {
        if ((pool[proc]->deadline)>(MIN_INT)) {
            pool[proc]->deadline--;
        }
        proc = (proc+1)%POOL_SIZE;
    }
}