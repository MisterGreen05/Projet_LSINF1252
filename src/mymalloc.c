/*Author : Gilles Mottiat and Singh Aman */

#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include"../include/mymalloc.h"

typedef struct block_header{
  unsigned int size : 29,
               zero : 2,
               alloc : 1;
} block_header;

void* base_heap = NULL;
unsigned int HEAP_TOTAL_SIZE = 0; 

void* mymalloc(size_t size){

  size_t HEADER_BLK_SIZE = sizeof(block_header)/4; //taille du header
  int j = (int)size;
  for (; j%4!=0;j++);
  size_t BLK_SIZE = (size_t)j; // BLK_SIZE est un multiple de 4
    
    if(!base_heap){ // 1er appel à mymalloc : on initialise le heap et on alloue le premier bloc
      HEAP_TOTAL_SIZE = (BLK_SIZE)*1024; // taille totale du heap 
      base_heap = sbrk(HEAP_TOTAL_SIZE); // base du heap
      void* end_heap = sbrk(0);

      if(base_heap == (void*)-1 || end_heap == (void*)-1) { // si on ne peut pas étendre le heap 
        return NULL;
      }

      block_header* first_blk = base_heap; //premier bloc
      first_blk->size = BLK_SIZE;
      first_blk->zero = 2;
      first_blk->alloc = 1;

      return first_blk + HEADER_BLK_SIZE;
    }

    // si l'espace demandé est plus grand que la taille du heap
    else if (HEAP_TOTAL_SIZE < BLK_SIZE + HEADER_BLK_SIZE*4) {
      return NULL;
    }

    else{
      block_header* ptr = base_heap;
      block_header* best = NULL;
      unsigned int i = 0;

      // parcourt le heap avec base_heap comme point de départ      
      while(i<HEAP_TOTAL_SIZE){
	
        // si le bloc est déjà alloué on passe au suivant 
        if(ptr->alloc == 1){ //&& (ptr->size != 0)){          
          ptr += (ptr->size)/4 + HEADER_BLK_SIZE;
        }

	      /*si le bloc a pile la taille demandée ou que sa taille vaut zéro
	      on renvoie directement l'adresse de ce bloc*/
	      else if(ptr->size == BLK_SIZE+HEADER_BLK_SIZE || ptr->size==0){
	        ptr->alloc = 1;
	        ptr->size = BLK_SIZE; 
	        return ptr + HEADER_BLK_SIZE; 
      	}

	      /*si la taille du bloc est assez grande et qu'elle est plus petite
	      que celle de best ou que best n'a pas encore de valeur*/
	      else if(ptr->size > BLK_SIZE+4*HEADER_BLK_SIZE && (ptr->size < best->size || best == NULL)) {
	        best = ptr;
	      }
	
	      else {
	        ptr += ptr->size/4 + HEADER_BLK_SIZE;
	      }
	    
	    i+= ptr->size;
	    
      }

    // si on a pas trouvé de bloc libre de taille suffisante on renvoie NULL
    if(best==NULL){
	     return NULL;
    }
      
    else{
	    best->size = BLK_SIZE;
	    best->alloc = 1;
	    return best + best->size/4;
    }
  }
}
