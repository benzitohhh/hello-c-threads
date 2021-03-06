#include <pthread.h>
#include <stdio.h>

#define ARRAYSIZE 17
#define NUMTHREADS 4

struct ThreadData {
  int start, stop;
  int* array;
};

/* puts i^2 into array positions i=start to stop-1 */
void* squarer(struct ThreadData* td) {

  pthread_t id = pthread_self();
  printf("current thread: %p\n", id);
  
  struct ThreadData* data=(struct ThreadData*) td;
  int start=data->start;
  int stop=data->stop;
  int* array=data->array;
  int i;

  for (i=start; i<stop; i++) {
    array[i]=i*i;
  }
  printf("finished thread: %p\n", id);
  return NULL;
}

int main(void) {
  int array[ARRAYSIZE];
  pthread_t thread[NUMTHREADS];
  struct ThreadData data[NUMTHREADS];
  int i;
  /*
        this has the effect of rounding up the number of tasks
        per thread, which is useful in case ARRAYSIZE does not
        divide evenly by NUMTHREADS.
  */
  int tasksPerThread=(ARRAYSIZE+NUMTHREADS-1)/NUMTHREADS;

  /* Divide work for threads, prepare parameters */
  for (i=0; i<NUMTHREADS; i++) {
    data[i].start=i*tasksPerThread;
    data[i].stop=(i+1)*tasksPerThread;
    data[i].array=array;
  }
  /* the last thread must not go past the end of the array */
  data[NUMTHREADS-1].stop=ARRAYSIZE;

  /* Launch Threads */
  for (i=0; i<NUMTHREADS; i++) {
    pthread_create(&thread[i] /* id of created thread will be stored here */, NULL, (void *(*)(void*))squarer, &data[i]);
  }

  /* Wait for Threads to Finish */
  for (i=0; i<NUMTHREADS; i++) {
    printf("Joining thread %d\n", i);
    pthread_join(thread[i], NULL); // suspends execution of this thread, until target thread has terminated

    // So in this case here...
    // join(0) call will block until thread[0] has terminated.
    // then join join(1) call will block until thread[1] has terminated.
    // etc....
  }

  /* Display Result */
  for (i=0; i<ARRAYSIZE; i++) {
    printf("%d ", array[i]);
  }
  printf("\n");

  return 0;
}
