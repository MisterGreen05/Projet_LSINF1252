/*Author : Gilles Mottiat and Singh Aman */

#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include"../include/mycalloc.h"

typedef struct block_header{
  unsigned int size : 29,
               zero : 2,
               alloc : 1;
} block_header;


void* mycalloc(size_t size){

    /*On alloue un block mémoire via mymalloc*/
    void* blk = mymalloc(size);
    if (blk == NULL)
      return NULL;

    /*On utilise un pointeur qui se trouve à l'adresse du bloc*/
    char* ptr = (char*)blk;
    unsigned int i;
    unsigned int ALIGNED_PAYLOAD_SIZE = ((((((unsigned int)size)-1)>>2)<<2)+4);

    /*On parcourt le bloc memoire de ptr et on intialise les bytes a 0*/
    for(i=0 ; i<ALIGNED_PAYLOAD_SIZE ; i++){
        (*(ptr+i)) = 0;
    }

    /*On retourne blk ton les données on été initialisées à O*/
    return blk;
}
