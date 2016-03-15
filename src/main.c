#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include"../include/mymalloc.h"
#include"../include/mycalloc.h"
#include"../include/myfree.h"

void main(){
    printf("%p", mymalloc(12));
}
