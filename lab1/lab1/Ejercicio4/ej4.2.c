#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include <sys/syscall.h>
#include <linux/futex.h>
#include <sys/syscall.h>
#include <unistd.h>

int size;
int* array;
int flag = 0;
int* fut = &flag;

int futex_wait(void *addr, int val1) {
  return syscall(SYS_futex, addr, FUTEX_WAIT, 
                 val1, NULL, NULL, 0);
}

int futex_wake(void *addr, int n) {
    return syscall(SYS_futex, addr, FUTEX_WAKE, 
                   n, NULL, NULL, 0);
}

void* generate_fib(void *args){
  int init = 0;
  for(init; init < size; ++init){
    futex_wait(fut, 1);
    if (init <= 1){
      *(array+init) = init;
    }
    else{
      *(array+init) = *(array+init-1) + *(array+init-2);
    }
    printf("Adding element\n");
    flag = 1;
    futex_wake(fut, 1);
  }
}

int main(int argc, char *argv[]){
  int i = 0;
  size = atoi(argv[1]);
  pthread_t thread;
  array = calloc(size, sizeof(int));
  pthread_create(&thread, NULL, generate_fib, NULL);
  for(i; i < size; ++i){
    futex_wait(fut, 0);
    printf("Element %d = %d\n", i+1, *(array+i) );
    flag = 0;
    futex_wake(fut, 1);
  }
  pthread_join(thread, NULL);
  free(array);
  return 0;
}

