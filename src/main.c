#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<time.h>
#include<stdlib.h>
#include<string.h>
#include"../include/mymalloc.h"
#include"../include/mycalloc.h"
#include"../include/myfree.h"

int main(int argc, char* argv[]){
  int i;
  printf("\n");
  printf("******************************************************************************* \n");
  printf("*Voulez vous realisez un test de performance ou executer les tests unitaires ?* \n");
  printf("*Pour un test de performance mettez 1 et faites enter.                        * \n");
  printf("*Pour executer les tests unitaires mettez 2 et faites enter.                  * \n");
  printf("******************************************************************************* \n");
  scanf("%d", &i);

  if (i == 1){
    printf("Vous avez choisi les mesures de performances : \n");
    clock_t clk;
    clk = clock();
    int* i = (int*)mymalloc(64);
    clk = clock() - clk;
    double exec_time_mymalloc = ((double)clk)/CLOCKS_PER_SEC;
    printf("Le temps pris pour allouer un bloc de 64 bytes par mymalloc est de %f\n", exec_time_mymalloc);

    clock_t clkk;
    clkk = clock();
    int* ii = (int*)malloc(64);
    clkk = clock() - clkk;
    double exec_time_malloc = ((double)clkk)/CLOCKS_PER_SEC;
    printf("Le temps pris pour allouer un bloc de 64 bytes par malloc est de %f\n", exec_time_malloc);
  }
  else if (i == 2){
    printf("tests\n");
  }
  else{
    printf("Erreur, veuillez choisir 1 ou 2\n");
    return EXIT_FAILURE;
  }
}
