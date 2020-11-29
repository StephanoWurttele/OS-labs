#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<pthread.h>

#define MAX 1000000
#define FACTOR ( MAX/2 )
#define N 100000000
#define N_THREADS 4

volatile int points_in_circle;
pthread_mutex_t lock;

void* generate_random(void *v){
  double x = 0;
  double y = 0;
  double temp = 0;
  srand (time(NULL));
  for(int i = 0; i < N/N_THREADS ; ++i ){
    int num = (rand() % MAX) + 1.0;
    x = (double) (num - FACTOR) / FACTOR;
    num = (rand() % MAX) + 1.0;
    y = (double) (num - FACTOR) / FACTOR;
    temp = y < 0 ? y*(-1) : y;
    if(temp <= sqrt(1-pow(x,2))){
      pthread_mutex_lock(&lock);
      ++points_in_circle;
      pthread_mutex_unlock(&lock);
    }
  }
}

int main(){
  pthread_t threads[N_THREADS];
  for(int i = 0; i < N_THREADS; ++i){
    pthread_create(&threads[i], NULL, generate_random, NULL);
  }
  for(int i = 0; i < N_THREADS; ++i){
    pthread_join(threads[i], NULL);
  }
  printf("%f", 4.0 * points_in_circle / N);
  return 0;
}
