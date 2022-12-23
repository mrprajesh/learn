//~~~START: Thu, 01-Dec-2022, 16:50:57 IST
//~~~Author:Rajesh Pandian M | mrprajesh.co.in
//~ nvc++ -acc -gpu=managed -Minfo=all shuffle-on-gpu.cpp -o shuffle-on-gpu.out && ./shuffle-on-gpu.out

#include <iostream>
#include <iterator>
#include <vector>
#include <stdio.h>
#include <chrono>

#include <thrust/device_vector.h>
#include <thrust/host_vector.h>
#include <thrust/device_ptr.h>

using namespace std;

int main(int argc, char* argv[]) {
  unsigned N = 1 << 29;
  std::cout << "N:" << N << '\n';
  
  //~ int* a = (int*) malloc (sizeof(int) *N);
  //~ int* b = (int*) malloc (sizeof(int) *N);
  //~ int* c = (int*) malloc (sizeof(int) *N);
  
  thrust::host_vector a(N);
  thrust::host_vector b(N);
  thrust::host_vector c(N);
  
  
  unsigned long long int sum = 0.0;

  auto start = std::chrono::high_resolution_clock::now();


  #pragma acc data create(a,b)  
  
  {
  
    #pragma acc parallel loop 
    //~ #pragma acc parallel loop async(1)
    for (unsigned i = 0; i < N; ++i) {
      a[i] = i;
    }

    //~ #pragma acc parallel loop 
    #pragma acc parallel loop async(2)
    for (unsigned i = 0; i < N; ++i) {
      b[i] = N - i;
    }
    
    #pragma acc wait
    
    #pragma acc parallel loop reduction (+:sum)
    for (unsigned i = 0; i < N; ++i) {
      c[i] = a[i] + 2 * b[i];
      sum += a[i];
    }

  }
  
  // PRINT VEC 
  //~ std::copy(c.begin(), c.begin() + 10, std::ostream_iterator<int>(std::cout, "\N"));
  auto end = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> diff = end - start;  
  std::cout << "Time: " << diff.count() << " s\n";
  
  
  for (unsigned i = 0; i < 10; ++i) {
    std::cout<< i << " " << c[i] << '\n';
  }
  std::cout << "Sum: " << sum << std::endl; 
  
  return 0;
}
