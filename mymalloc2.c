#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>


typedef struct block_header{
  unsigned int size : 29,
               zero : 2,
               alloc : 1;
} block_header;

static void* base_heap = NULL;
size_t HEAP_TOTAL_SIZE = 0;

void mymalloc(size_t size)
{
    size_t HEADER_BLK_SIZE = sizeof(block_header);
    size_t ALIGNED_PAYLOAD_SIZE = (((((size)-1)>>2)<<2)+4);
    size_t BLK_SIZE = (HEADER_BLK_SIZE + ALIGNED_PAYLOAD_SIZE);

    if(!base_heap){
      base_heap = sbrk(0);
      void* end_heap = sbrk(HEAP_TOTAL_SIZE);
      HEAP_TOTAL_SIZE = ((BLK_SIZE)*1024);

      if(base_heap == (void*)-1 || end_heap == (void*)-1) {
        return NULL;
      }

      block_header* blk = (block_header*)base_heap;
      blk->size = (unsigned int)(BLK_SIZE);
      blk->zero = 2;
      blk->alloc = 1;

      block_header* freeblk = base_heap + (BLK_SIZE);
      freeblk->size = (unsigned int)((HEAP_TOTAL_SIZE) - (BLK_SIZE));
      freeblk->zero = 2;
      freeblk->alloc = 0;

      return blk + (HEADER_BLK_SIZE);
      /* debug
      printf("%p\n",blk);
      printf("%u\n",blk->size);
      printf("%u\n",blk->alloc);
      printf("%u\n",freeblk->size);
      printf("%u\n",freeblk->alloc);
      printf("%p\n", blk + (HEADER_BLK_SIZE));
      */
    }

    else if (size >= HEAP_TOTAL_SIZE){
      return NULL;
    }

    else{
      block_header* new = (block_header*)base_heap;
      size_t i = 0;
      while(i<HEAP_TOTAL_SIZE){
        if(new->alloc == 1)
      }
    }
}
    /*
        else {
            block_header* ptr = base_heap;
            size_t i = 0;
            while(i < HEAP_EXTEND_SIZE) { // Travel the heap
                if(ptr->alloc == 1) { // If it's allocated, then we go to the next block
                    ptr = (unsigned char*)ptr + (size_t)ptr->size;
                    i += (size_t)(ptr->size);
                }
                else if(ptr->alloc == 0 && ptr->size >= BLK_SIZE) { // If it's free and big enough
                    if (ptr->size == BLK_SIZE){
                        ptr->alloc = 1;
                        return (unsigned char*)ptr + HEADER_BLK_SIZE;
                    }
                    else {
                        block_header* freeblk = ptr + (size_t)(ptr->size);
                        freeblk->size = ptr->size - (unsigned int)(BLK_SIZE);
                        freeblk->zero = 2;
                        freeblk->alloc = 0;
                        ptr->size = BLK_SIZE;
                        ptr->alloc = 1;
                        return (unsigned char*)ptr + HEADER_BLK_SIZE;
                    }
                }
                else { // It's not big enough, so we go to the next block
                    ptr = (unsigned char*)ptr + (size_t)(ptr->size);
                    i += (size_t)(ptr->size);
                }
            }
            return NULL; // If nothing works
        }
}
*/
/*
void myfree(void* ptr) {
    size_t HEADER_BLK_SIZE = sizeof(block_header);
    if (ptr == base_heap+HEADER_BLK_SIZE){
        if ((base_heap+(base_heap->size))->alloc==0){
            base_heap->alloc = 0;
            base_heap->size += (base_heap+(base_heap->size))->size;
        }
        else
            base_heap->alloc = 0;
    }
    else {
        void* a = base_heap+(base_heap->size);
        void* b = base_heap;
        while (a != ptr - HEADER_BLK_SIZE){
            a += a->size;
            b += b->size;
        }
        if (b->alloc == 0) {
            if ((ptr - HEADER_BLK_SIZE + (ptr - HEADER_BLK_SIZE)->size)->alloc == 0) {
                b->size += a->size + (a+a->size)->size;
            }
            else {
                b->size += a->size;
            }
        }
        else {
            if ((ptr - HEADER_BLK_SIZE + (ptr - HEADER_BLK_SIZE)->size)->alloc == 0) {
                a->size += (a+a->size)->size;
                a->alloc = 0;
            }
            else {
                a->alloc = 0;
            }
        }

    }
}

*/
void main(){
  mymalloc(12);

  mymalloc(16);
/*
  int* iii = (int*)mymalloc(20);
  printf("pointeur iii : %p\n", iii);
/*
  int* iiii = (int*)mymalloc(24);
  printf("pointeur iiii : %p\n", iiii);

  int* iiiii = (int*)mymalloc(28);
  printf("pointeur iiiii : %p\n", iiiii);

  int* iiiiii = (int*)mymalloc(32);
  printf("pointeur iiiiii : %p\n", iiiiii);

  int* iiiiiii = (int*)mymalloc(36);
  printf("pointeur iiiiiii : %p\n", iiiiiii);

  int* iiiiiiii = (int*)mymalloc(40);
  printf("pointeur iiiiiiii : %p\n", iiiiiiii);
  */
}
