#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

int size;
int* array;

int recursive_fib( int pos ){
  if(pos <= 1){
    *(array+pos) = pos;
    return pos;
  }
  *(array+pos) = recursive_fib(pos-1) + recursive_fib(pos-2);
  return *(array+pos);
}


void* generate_fib(void *args){
  recursive_fib(size);
}

int main(int argc, char *argv[]){
  int i = 0;
  size = atoi(argv[1]);
  pthread_t thread;
  array = calloc(size, sizeof(int));
  pthread_create(&thread, NULL, generate_fib, NULL);
  pthread_join(thread, NULL);
  for ( i = 0; i < size+1; i++ )
    printf("Element %d = %d\n", i+1, *(array+i) );
  free(array);
  return 0;
}
