//~~~START:Fri, 16-Sep-2022, 15:38:26 IST
//~~~Author:Rajesh Pandian M | mrprajesh.co.in 
//~ nvc++ -acc -gpu=managed -Minfo=all sqrt-acc.cpp -o sqrt-acc.out && ./sqrt-acc.out
#include <math.h>
#include <iostream>
using namespace std;
int main(int argc, char* argv[]){
  int n = 100000;
  double* d = (double*) malloc (sizeof(double) *n);
  double* s = (double*) malloc (sizeof(double) *n);
  
  #pragma acc data create(d[:n], s[:n]) copyout(s[:n])  
  {
    #pragma acc parallel loop 
    for (unsigned i = 0; i < n; ++i) {
      d[i] = i;
    }
      
    #pragma acc parallel loop 
    for (unsigned i = 1; i < n; ++i) {
      s[i] = round(sqrt(d[i]));
    }
  }
  
  for (unsigned i = 0; i < 10; ++i) {
    std::cout<< i << ": " << s[i] << '\n';
  }
  return 0;
}
