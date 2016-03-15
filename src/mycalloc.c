/*Author : Gilles Mottiat and Singh Aman */

#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include"mycalloc.h"

typedef struct block_header{
  unsigned int size : 29,
               zero : 2,
               alloc : 1;
} block_header;


void* mycalloc(size_t size){
    /*block memory by mymalloc*/
    void* blk = mymalloc(size);
    char* ptr = (char*)blk;
    unsigned int i;
    unsigned int ALIGNED_PAYLOAD_SIZE = ((((((unsigned int)size)-1)>>2)<<2)+4);
    
    /*Travel the block memory by ptr and we initialize every bits to 0*/
    for(i=0 ; i<ALIGNED_PAYLOAD_SIZE ; i++){
        (*(ptr+i)) = 0;
    }
    
    /*return the blk and every value set to O*/
    
    return blk;
}
