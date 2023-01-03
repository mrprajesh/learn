//~~~START:Fri, 09-Sep-2022, 14:02:15 IST
//~~~Author:Rajesh Pandian M | mrprajesh.co.in 
//~ nvc++ -acc -gpu=managed -Minfo=all mutiple-reduction.cpp -o mutiple-reduction.out && ./mutiple-reduction.out

#include <iostream>
#include <chrono>
using namespace std;
int main(int argc, char* argv[]){
  
  unsigned n = 1 << 10;
  
  int* a = (int*) malloc (sizeof(int) *n);
  long long int sum = 0; // IDENTITY
  //~ long long int sum2 = 0; // IDENTITY
  long long int prod = 1; // IDENTITY

  
  auto start = std::chrono::high_resolution_clock::now();

  #pragma acc data create(a) copy(sum,prod) //copyin(sum,prod) copyout(sum,prod) 
  {
  
    #pragma acc parallel loop  
    for(size_t ii=0; ii < n ; ++ii){
      a[ii] = 2;
    }
    
    //~ #pragma acc parallel loop  reduction(+:sum), reduction(+:sum2)
    //~ for(size_t ii=0; ii < n ; ++ii) {
      //~ sum+=a[ii];
      //~ sum2+=a[ii];
    //~ }
    
    #pragma acc parallel loop  reduction(+:sum) reduction(*:prod)
    for(size_t ii=0; ii < n ; ++ii) {
      sum+=a[ii];
      prod*=a[ii];
    }
    
  }
  auto end = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> diff = end - start;
  
  std::cout << "Time: " << diff.count() << " s\n";
  std::cout<< "Sum  :" << sum << '\n';
  //~ std::cout<< "Sum2 :" << sum2 << '\n';
  std::cout<< "Prod :" << prod << '\n';
  
  return 0;
}
