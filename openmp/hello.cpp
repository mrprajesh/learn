//~~~START:Fri, 02-Sep-2022, 12:48:21 IST
//~~~Author:Rajesh Pandian M | mrprajesh.co.in

#include <iostream>
#include <iterator>
#include <vector>
#include <stdio.h>
#include <omp.h>
#include <chrono>

using namespace std;

int main(int argc, char* argv[]) {
  unsigned n = 1 << 29;
  std::cout << "N:" << n << '\n';
  //~ vector<int> a(n);
  //~ vector<int> b(n);  ['o  //~ vector<int> c(n);
  
  int* a = (int*) malloc (sizeof(int) *n);
  int* b = (int*) malloc (sizeof(int) *n);
  int* c = (int*) malloc (sizeof(int) *n);
  
  unsigned long long int sum = 0.0;
  
 
  std::chrono::high_resolution_clock::time_point   start = std::chrono::high_resolution_clock::now();
 
  #pragma omp parallel
  {
  
    #pragma omp master
    printf("numThreads: %d\n", omp_get_num_threads());
 
    #pragma omp parallel for
    for (unsigned i = 0; i < n; ++i) {
      a[i] = i;
    }

    #pragma omp parallel for
    for (unsigned i = 0; i < n; ++i) {
      b[i] = n - i;
    }
    
    #pragma omp parallel for reduction (+:sum)
    for (unsigned i = 0; i < n; ++i) {
      c[i] = a[i] + 2 * b[i];
      sum += a[i];
    }

  }
  
  std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
  uint64_t elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
  double total_time = (double)(elapsed * 1.E-9 );  
  std::cout<< "TotalTime: " << total_time << " s\n";
  // PRINT VEC 
  //~ std::copy(c.begin(), c.begin() + 10, std::ostream_iterator<int>(std::cout, "\n"));
  
  for (unsigned i = 0; i < 10; ++i) {
    std::cout<< i << " " << c[i] << '\n';
  }
  std::cout << "Sum: " << sum << std::endl; 
  
  return 0;
}
