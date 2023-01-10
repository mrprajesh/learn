
// nvc++ -g -acc -gpu=managed -Minfo=all dev-ptr-sample.cpp -o dev-ptr-sample.out && ./dev-ptr-sample.out
// nvc++ -acc=multicore -Minfo=all dev-ptr-sample.cpp -o dev-ptr-sample.out && ./dev-ptr-sample.out

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <openacc.h> //acc_* functions

void saxpy(int n, float a, float *restrict x, float *restrict y) {
#pragma acc kernels deviceptr(x, y)
  {
    for (int i = 0; i < n; i++) {
      y[i] += a * x[i];
    }
  }
}
void set(int n, float val, float *restrict arr) {
#pragma acc kernels deviceptr(arr)
  {
    for (int i = 0; i < n; i++) {
      arr[i] = val;
    }
  }
}

int main(int argc, char **argv) {
  float *x, *y, tmp;
  int n = 1 << 20;

  x = (float*)acc_malloc((size_t)n * sizeof(float));
  y = (float*)acc_malloc((size_t)n * sizeof(float));

  set(n, 1.0f, x);
  set(n, 0.0f, y);

  saxpy(n, 2.0, x, y);
  acc_memcpy_from_device(&tmp, y, (size_t)sizeof(float));
  printf("%f\n", tmp);
  acc_free(x);
  acc_free(y);
  return 0;
}
