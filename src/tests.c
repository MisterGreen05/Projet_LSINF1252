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


typedef struct block_header{
  unsigned int size : 29,
               zero : 2,
               alloc : 1;
} block_header;

/* La fonction d'initialisation
 * initialise un bloc en memoire via mymalloc et on realise les tests dessus
 */
int init_suite1(void) { return 0; }

int clean_suite1(void) { return 0; }

/*verifie si le premier appel de mymalloc renvoie un pointeur différent de NULL*/
void test_mymalloc1(void){
  CU_ASSERT_PTR_NOT_NULL(mymalloc(128));
}

/*verifie si deux blocs consécutifs sont situés à la bonne adresse*/
void test_mymalloc2(void){
  char* i = (char*)mymalloc(24);
  unsigned int inc = 28;
  char* ii = (char*)mymalloc(24);
  i = i + inc;  /*i devrait être a l'adresse de ii*/
  CU_ASSERT_EQUAL(i,ii);
}

/*verifie que malloc renvoie NULL si on demande d'allouer un bloc plus grand
 *que la taille du heap
 */
void test_mymalloc3(void){
  int* a = (int*)mymalloc(12); //initialisation du heap
  CU_ASSERT_PTR_NULL(mymalloc(HEAP_TOTAL_SIZE+30)); //plus grand que le heap
}

/*verifie si les données du bloc sont bien initialisés à zero */
void test_mycalloc1(void){
  char* b = (char*)mycalloc(32);
  CU_ASSERT_FALSE(*b); //verifie si la valeur de b est zero
}

/*verifie si le premier appel de mycalloc renvoie un pointeur différent de NULL*/
void test_mycalloc2(void){
  CU_ASSERT_PTR_NOT_NULL(mycalloc(128));
}

/*verifie si free met bien le champ alloc du bloc à 0*/
void test_myfree1(void){
  char* c = (char*)mycalloc(32);
  myfree(c);
  CU_ASSERT_EQUAL(((block_header*)c)->alloc, 0);
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

    /*Mesure de temps via clock() pour un block de 5210 bytes avec mymalloc*/
    clock_t clk;
    clk = clock();
    int* i = (int*)mymalloc(5120);
    clk = clock() - clk;
    double exec_time_mymalloc = ((double)clk)/CLOCKS_PER_SEC;
    printf("Le temps pris pour allouer un bloc de 5120 bytes par mymalloc est de %f\n", exec_time_mymalloc);

    /*Mesure de temps via clock() pour un block de 5210 bytes avec malloc*/
    clock_t clkk;
    clkk = clock();
    int* ii = (int*)malloc(5120);
    clkk = clock() - clkk;
    double exec_time_malloc = ((double)clkk)/CLOCKS_PER_SEC;
    printf("Le temps pris pour allouer un bloc de 5120 bytes par malloc est de %f\n", exec_time_malloc);

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
    if(NULL == CU_add_test(pSuite, "vérifie si le premier appel de mymalloc renvoie un pointeur différent de NULL", test_mymalloc1) ||
      NULL == CU_add_test(pSuite, "vérifie si deux blocs consécutifs sont situés à la bonne adresse", test_mymalloc2) ||
      NULL == CU_add_test(pSuite, "verifie que malloc renvoie NULL si on demande d’allouer un bloc plus grand que la taille du heap", test_mymalloc3) ||
      NULL == CU_add_test(pSuite, "vérifie si les données du bloc sont bien initialisés à zero", test_mycalloc1) ||
      NULL == CU_add_test(pSuite, "verifie si le premier appel de mycalloc renvoie un pointeur différent de NULL", test_mycalloc2) ||
      NULL == CU_add_test(pSuite, "verifie si free met bien le champ alloc du bloc à 0", test_myfree1)
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
