// Vitor Rodrigues da Mata
#define _GNU_SOURCE
#include <sched.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <assert.h>
#include <sys/syscall.h>
#include <errno.h>
#include <string.h> 

void loop_infinito() {
    long int cont = 0, r = 1;

    while (cont < 600000000) {
        r += (1045550234 + 10000000000) * 9988;
        cont += 1;
    }
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Uso: %s <cpu_number> <rt_priority>\n", argv[0]);
        return 1;
    }

    int cpu = atoi(argv[1]);
    int rtprio = atoi(argv[2]);
    int max, min;
    cpu_set_t c;

    // Limites de prioridade para SCHED_RR
    max = sched_get_priority_max(SCHED_RR);
    min = sched_get_priority_min(SCHED_RR);

    if (min == -1 || max == -1) {
        perror("sched_get_priority_*");
        return 1;
    }

    if (rtprio < min || rtprio > max) {
        fprintf(stderr, "Erro: prioridade fora do intervalo permitido (%d - %d)\n", min, max);
        return 1;
    }

    // Define a política de escalonamento SCHED_RR com a prioridade escolhida
    struct sched_param sp;
    sp.sched_priority = rtprio;

    if (sched_setscheduler(0, SCHED_RR, &sp) == -1) {
        fprintf(stderr, "Erro ao configurar SCHED_RR: %s\n", strerror(errno));
        return 1;
    } else {
        printf("OK: processo configurado em SCHED_RR com prioridade %d\n", rtprio);
    }

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

