#include <stdio.h>

#define ARRAYSIZE 17
#define NUMTHREADS 4

/* puts i^2 into array positions i=start to stop-1 */
void* squarer(int start, int stop, int* array) {
  int i;

  for (i=start; i<stop; i++) {
    array[i]=i*i;
  }

  return NULL;
}

int main(void) {
  int array[ARRAYSIZE];
  int i, start, stop;
  /*
        this has the effect of rounding up the number of tasks
        per thread, which is useful in case ARRAYSIZE does not
        divide evenly by NUMTHREADS.
  */
  int tasksPerThread=(ARRAYSIZE+NUMTHREADS-1)/NUMTHREADS;

  /* Do the loop in NUMTHREADS pieces */
  for (i=0; i<NUMTHREADS; i++) {
    start=i*tasksPerThread;
    stop=(i+1)*tasksPerThread;
    /* if the tasks do not divide evenly, we could have stop too big. Check and fix. */
    if (stop>ARRAYSIZE) {
      stop=ARRAYSIZE;
    }
    squarer(start, stop, array);
  }

  /* Display Result */
  for (i=0; i<ARRAYSIZE; i++) {
    printf("%d ", array[i]);
  }
  printf("\n");

  return 0;
}
