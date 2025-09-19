//Vitor Rodrigues da Mata
#define _GNU_SOURCE
#include <sched.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <assert.h>
#include <sys/syscall.h>




void loop_infinito(){
 long int cont = 0, r = 1;
  
  while(cont < 600000000){
     r += 1;
     cont +=1;
  }
};


int main() {
  
  int cpu = 0; //CPU 0
  cpu_set_t c; 
  

  CPU_ZERO(&c);  // adiciona a CPU   
  CPU_SET(cpu, &c);  // seta a cpu 0
  
  if (sched_setaffinity(0, sizeof(cpu_set_t), &c) == -1) {  //0 pois especifica que sera executado sobre o processo atual
        perror("Erro ao setar a afinidade");
        return 1;
    }
   
 
  
  
   
  loop_infinito();
  
  return EXIT_SUCCESS;


}
