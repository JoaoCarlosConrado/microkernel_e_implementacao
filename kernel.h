#ifndef KERNEL_H_
#define KERNEL_H_

// códigos de retorno
#define SUCCESS 0
#define FAIL    1
#define REPEAT  2

// definição de constantes
#define POOL_SIZE 10
#define MIN_INT  -30000

// declaração de ponteiro de função
typedef char (*ptrFunc)(void);

// definição da estrutura de um processo
typedef struct {
    int deadline;
    int period;
    ptrFunc function;
} process;

// definição da estrutura do kernel
typedef struct {
    process pool[POOL_SIZE];
    int start;
    int end;
} kernel;

// protótipos das funções do kernel
char kernelInit(void);
char kernelAddProc(process* newProc);
void kernelLoop(void);
void kernelTick(void);

#endif // KERNEL_H_
