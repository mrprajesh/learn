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
  vector<int> a(n);
  vector<int> b(n);
  vector<int> c(n);
  long sum = 0.0;
  
  #pragma acc data copyin(a,b), copyout(sum) 
  //~ #pragma acc data copy(a,b,c)
  {
  

    #pragma acc parallel loop reduction (+:sum)
    for (unsigned i = 0; i < n; ++i) {
      sum += a[i];
    }

  }
  
  
  //~ std::copy(c.begin(), c.begin() + 10, std::ostream_iterator<int>(std::cout, "\n"));
  std::cout << "Sum: " << sum << std::endl; 
  
  return 0;
}
