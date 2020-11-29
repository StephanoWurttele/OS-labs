#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<pthread.h>

#define MAX 1000000
#define FACTOR ( MAX/2 )
#define N 100000000

volatile int points_in_circle;

void* generate_random(void *v){
  double x = 0;
  double y = 0;
  double temp = 0;
  srand (time(NULL));
  for(int i = 0; i < N ; ++i ){
    int num = (rand() % MAX) + 1.0;
    x = (double) (num - FACTOR) / FACTOR;
    num = (rand() % MAX) + 1.0;
    y = (double) (num - FACTOR) / FACTOR;
    temp = y < 0 ? y*(-1) : y;
    if(temp <= sqrt(1-pow(x,2))) ++points_in_circle;
  }
}


int main(){
  pthread_t thread;
  pthread_create(&thread, NULL, generate_random, NULL);
  pthread_join(thread, NULL);
  printf("%f", 4.0 * points_in_circle / N);
  return 0;
}
