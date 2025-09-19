// Vitor Rodrigues da Mata
#define _GNU_SOURCE
#include <sched.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <assert.h>
#include <sys/syscall.h>


void loop_infinito() {
    long int cont = 0, r = 1;

    while (cont < 600000000) {
        r += (1045550234 + 10000000000) * 9988;
        cont += 1;
    }
}

int main() {
    int cpu = 0; //CPU 0
    cpu_set_t c;

  

    // Define afinidade de CPU
    CPU_ZERO(&c);
    CPU_SET(cpu, &c);

    if (sched_setaffinity(0, sizeof(cpu_set_t), &c) == -1) {
        perror("Erro ao setar afinidade de CPU");
        return 1;
    }

    // Executa a carga de trabalho
    loop_infinito();

    return EXIT_SUCCESS;
}
