//~~~START:Fri, 23-Dec-2022, 15:16:21 IST
//~~~Author:Rajesh Pandian M | mrprajesh.co.in
//~ nvc++ -acc -gpu=managed -Minfo=all       acc-vs-omp.cpp -o acc-vs-omp.out && ./acc-vs-omp.out
//~ nvc++ -acc=multicore -Minfo=all -fopenmp acc-vs-omp.cpp -o acc-vs-omp.out && ./acc-vs-omp.out
//~ nvc++  acc-vs-omp.cpp -o acc-vs-omp.out && ./acc-vs-omp.out
//~ g++    acc-vs-omp.cpp -o acc-vs-omp.out && ./acc-vs-omp.out

#include <iostream>
#include <chrono>

using namespace std;

int main(int argc, char* argv[]) {
  unsigned n = 1 << 30;
  std::cout << "N:" << n << '\n';

  
  int* a = (int*) malloc (sizeof(int) *n);

  unsigned long long int sum = 0.0;
  
  // START TIMER
  std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();


  #pragma acc parallel loop copyin(a) 
  //~ #pragma acc parallel loop async(1)
  for (unsigned i = 0; i < n; ++i) {
    a[i] = i;
  }

  #pragma acc parallel loop reduction (+:sum)
  for (unsigned i = 0; i < n; ++i) {
    a[i] = a[i]*2;
    sum += a[i];
  }


  for (unsigned i = 0; i < 10; ++i) {
    std::cout<< i << " " << a[i] << '\n';
  }
  
  // END TIMER
  std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
  uint64_t elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
  double total_time_seconds = (double)(elapsed * 1.E-9 );
  std::cout<< "Time:" << total_time_seconds << '\n';
  
  std::cout << "Sum: " << sum << std::endl; 
  
  return 0;
}
