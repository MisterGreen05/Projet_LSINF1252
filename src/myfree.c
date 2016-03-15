#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include"../include/myfree.h"

void myfree(void *ptr){
  printf("Hello\n");
}
