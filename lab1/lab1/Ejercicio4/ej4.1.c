#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>
#include <unistd.h>

int size;
int* array;
sem_t semaphore;
sem_t semaphore2;


void* generate_fib(void *args){
  int init = 0;
  for(init; init < size; ++init){
    if (init <= 1){
      *(array+init) = init;
    }
    else{
      *(array+init) = *(array+init-1) + *(array+init-2);
    }
    printf("Adding element\n");
    sem_post(&semaphore);
    sem_wait(&semaphore2);
  }
}

int main(int argc, char *argv[]){
  int i = 0;
  size = atoi(argv[1]);
  pthread_t thread;
  array = calloc(size, sizeof(int));
  sem_init(&semaphore, 0, 0);
  sem_init(&semaphore2, 0, 0);
  pthread_create(&thread, NULL, generate_fib, NULL);
  for(i; i < size; ++i){
    sem_wait(&semaphore);
    printf("Element %d = %d\n", i+1, *(array+i) );
    sem_post(&semaphore2);
  }
  pthread_join(thread, NULL);
  free(array);
  return 0;
}

