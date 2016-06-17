#include <stdio.h>
#define ARRAYSIZE 17

int main(void) {
  int array[ARRAYSIZE];
  int i;

  /* puts i^2 into array positions i=0 to ARRAYSIZE-1 */
  for (i=0; i<ARRAYSIZE; i++) {
    array[i]=i*i;
  }

  /* Display Result */
  for (i=0; i<ARRAYSIZE; i++) {
    printf("%d ", array[i]);
  }
  printf("\n");

  return 0;
}
