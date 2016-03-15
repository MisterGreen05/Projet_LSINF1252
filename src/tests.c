#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<errno.h>
#include<unistd.h>
#include<time.h>
#include<string.h>
#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>

#include"../include/mymalloc.h"
#include"../include/mycalloc.h"
#include"../include/myfree.h"

/* pointeur utilisé pour les tests*/
static char *ptr = NULL;

/* La fonction d'initialisation
 * initialise un bloc en memoire via mymalloc et on realise les tests dessus
 */
int init_suite1(void) { return 0; }
int clean_suite1(void) { return 0; }

void test_mymalloc1(void){

}
void test_mymalloc2(void){

}
void test_mycalloc1(void){

}
void test_mycalloc2(void){

}
void test_myfree1(void){

}
void test_myfree2(void){

}



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
    printf("Vous avez choisi les tests unitaires : \n");
    /* Initialisation de la suite de tests */
    CU_pSuite pSuite = NULL;

    if(CUE_SUCCESS != CU_initialize_registry())
      return CU_get_error();

    /* Ajout de la suite au registre */
    pSuite = CU_add_suite("Suite de tests pour le projet 1", init_suite1, clean_suite1);
      if (NULL == pSuite) {
        CU_cleanup_registry();
        return CU_get_error();
      }

      /*Ajout des tests à la suite.*/
    if(NULL == CU_add_test(pSuite, "Test si le pointeur est du type void", test_mymalloc1) ||
      NULL == CU_add_test(pSuite, "Test si la taille est effectivement la taille demande", test_mymalloc2) ||
      NULL == CU_add_test(pSuite, "Test si le pointeur est du type void", test_mycalloc1) ||
      NULL == CU_add_test(pSuite, "Test si le pointeur est bien initialiser a 0", test_mycalloc2) ||
      NULL == CU_add_test(pSuite, "Test si le block a bien ete vide", test_myfree1) ||
      NULL == CU_add_test(pSuite, "Test si ", test_myfree2)
      ) {
       CU_cleanup_registry();
       return CU_get_error();
    }

    /* Execution des tests l'un a la suite des autreset on nettoie la mémoire utilisée par CUnit */
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();

  }

  else{
    printf("Erreur, veuillez choisir 1 ou 2\n");
    return EXIT_FAILURE;
  }

}
