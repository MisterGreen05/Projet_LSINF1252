#include<stdio.h>
#include"mymalloc.h"

struct block_header{
  unsigned int size : 29,
               zero : 2,
               alloc : 1;
}

//void* mymalloc(size_t size){
//  printf("Hello\n");
//}
