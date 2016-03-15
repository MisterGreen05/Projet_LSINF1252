/*Author : Gilles Mottiat and Singh Aman */

#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include"mymalloc.h"

typedef struct block_header{
  unsigned int size : 29,
               zero : 2,
               alloc : 1;
} block_header;

static char* base_heap = NULL;
unsigned int HEAP_TOTAL_SIZE = 0; /*proportional to the 1st call of mymalloc*/

void* mymalloc(size_t size){

  unsigned int HEADER_BLK_SIZE = sizeof(block_header); /*size header*/
  unsigned int ALIGNED_PAYLOAD_SIZE = ((((((unsigned int)size)-1)>>2)<<2)+4); /*payload rounded for alignement*/
  unsigned int BLK_SIZE = (HEADER_BLK_SIZE) + (ALIGNED_PAYLOAD_SIZE); /*total block size (header + rounded payload)*/

    /*1st call of mymalloc : initialize the heap and allocate the 1st block*/

    if(!base_heap){

      /*heap initialize*/
      HEAP_TOTAL_SIZE = ((BLK_SIZE)*1024);
      base_heap = (char*)sbrk(HEAP_TOTAL_SIZE);
      char* end_heap = base_heap + (HEAP_TOTAL_SIZE);

      /*if sbrk does not work*/
      if(base_heap == (char*)-1 || end_heap == (char*)-1) {
        return NULL;
      }

      /*otherwise allocate the 1st block*/
      block_header* first_blk = (block_header*) base_heap;
      first_blk->size = BLK_SIZE;
      first_blk->zero = 2;
      first_blk->alloc = 1;

      /*adress 1st block*/
      return ( ((char*)first_blk) + (HEADER_BLK_SIZE) );
    }

    /*second call of mymalloc : find a block in the heap and allocate*/

    else{
      block_header* ptr = (block_header*)base_heap;
      unsigned int i = 0;

      /*travel the heap, starting point is the base_heap*/
      while(i<HEAP_TOTAL_SIZE){

        /*1st case : if the block is allocate we go to the next one*/
        if(ptr->alloc == 1 && (ptr->size != 0)){
          i = i + (ptr->size);
          ptr = (block_header*)((char*)ptr + ptr->size);
        }

        /*second case : if the block is free we allocate one and it was not allocate before*/
        else if (ptr->alloc == 0 && (ptr->size == 0)){
          i = i + (BLK_SIZE);

          ptr->size = BLK_SIZE;
          ptr->zero = 2;
          ptr->alloc = 1;

          return ( ((char*)ptr) + (HEADER_BLK_SIZE) );
        }

        /*third case : if the block is free, was allocate before, but is not big enough, jump to the next one*/
        else if (ptr->alloc == 0 && (ptr->size != 0) && ptr->size< BLK_SIZE){
          i = i + (ptr->size);
          ptr = (block_header*)((char*)ptr + ptr->size);
        }

        /*fourth case : if the block is free, was allocate before and is big enough, we allocate one*/
        else if (ptr->alloc == 0 && (ptr->size != 0) && ptr->size>BLK_SIZE){
          i = i + (BLK_SIZE);

          ptr->size = BLK_SIZE;
          ptr->zero = 2;
          ptr->alloc = 1;

          return ( ((char*)ptr) + (HEADER_BLK_SIZE) );
        }

        /*fifth case : if it did not find one*/
        else{
          return NULL;
        }

      }
    }
}
/*test
void main(){
  printf("%p\n", mymalloc(12));
  printf("%p\n", mymalloc(16));
  printf("%p\n", mymalloc(20));
  printf("%p\n", mymalloc(24));
  printf("%p\n", mymalloc(28));

}*/
