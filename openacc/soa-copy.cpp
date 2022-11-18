//~~~START:Wed, 28-Sep-2022, 12:48:39 IST
//~~~Author:Rajesh Pandian M | mrprajesh.co.in 
#include <bits/stdc++.h>
using namespace std;
struct SoA{
    vector <int>    A;
    vector <double> B;
    vector <float>  C;
    SoA(size_t n){
        A.resize(n);
        B.resize(n);
        C.resize(n);
        
        #pragma data create(A[:n],B[:n],C[:n])
        #pragma acc parallel loop
        for (size_t ii=0; ii < n; ++ii){
          A[ii] = 10 * ii; 
          B[ii] = 200 * ii;
          C[ii] = 3000 * ii;
        }
          
    }
};
int main(int argc, char* argv[]){
  
  size_t n = 10;
  SoA soa(n);
  
  #pragma acc parallel loop
  for(size_t ii=0 ; ii < n; ++ii){
    soa.A[ii] += 1;
    soa.B[ii] += 2;
    soa.C[ii] += 3;
  }
  
  for (auto &c : soa.C)
    std::cout<< c << '\n';
  return 0;
}
