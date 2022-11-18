//~~~START:Fri, 02-Sep-2022, 12:48:21 IST
//~~~Author:Rajesh Pandian M | mrprajesh.co.in

#include <iostream>
#include <iterator>
#include <vector>
#include <stdio.h>

using namespace std;

int main(int argc, char* argv[]) {
  unsigned n = 1 << 28;
  std::cout << "N:" << n << '\n';
  //~ vector<int> a(n);
  //~ vector<int> b(n);
  //~ vector<int> c(n);
  
  int* a = (int*) malloc (sizeof(int) *n);
  int* b = (int*) malloc (sizeof(int) *n);
  int* c = (int*) malloc (sizeof(int) *n);
  
  unsigned long long int sum = 0.0;
  
  #pragma acc data copyin(a,b)  
  //~ #pragma acc data copy(a,b,c)
  {
  
    #pragma acc parallel loop 
    //~ #pragma acc parallel loop async(1)
    for (unsigned i = 0; i < n; ++i) {
      a[i] = i;
    }

    //~ #pragma acc parallel loop 
    #pragma acc parallel loop async(2)
    for (unsigned i = 0; i < n; ++i) {
      b[i] = n - i;
    }
    
    #pragma acc wait
    
    #pragma acc parallel loop reduction (+:sum)
    for (unsigned i = 0; i < n; ++i) {
      c[i] = a[i] + 2 * b[i];
      sum += a[i];
    }

  }
  
  // PRINT VEC 
  //~ std::copy(c.begin(), c.begin() + 10, std::ostream_iterator<int>(std::cout, "\n"));
  
  for (unsigned i = 0; i < 10; ++i) {
    std::cout<< i << " " << c[i] << '\n';
  }
  std::cout << "Sum: " << sum << std::endl; 
  
  return 0;
}
