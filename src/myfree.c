#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include"../include/myfree.h"

void myfree(void* ptr) {
  
    size_t HEADER_BLK_SIZE = (sizeof(block_header))/4; 
    block_header* blk = ptr-(HEADER_BLK_SIZE)*4; 
    blk->alloc = 0; // le bloc n'est plus alloué
    block_header* next = blk + (blk->size)/4 + (HEADER_BLK_SIZE);

    if (next->alloc == 0) 
      blk->size += next->size + HEADER_BLK_SIZE*4; // si le bloc suivant est vide, on ajoute sa taille à celle de blk    

    if (blk != base_heap) { // si blk ne se trouve pas à la base du heap
      block_header* prev = base_heap; // à la fin de la boucle, prev sera le bloc précédent blk
      block_header* curr = prev + (prev->size)/4 + HEADER_BLK_SIZE; // à la fin de la boucle, curr sera égal à blk 

      while (curr != blk) {
	prev = curr;
	curr += (curr->size)/4 + HEADER_BLK_SIZE;
      }

      if (prev->alloc == 0)
	prev->size += blk->size + HEADER_BLK_SIZE*4; // si prev est n'est pas alloué, on ajoute la taille de blk à la taille de prev
    }
}
