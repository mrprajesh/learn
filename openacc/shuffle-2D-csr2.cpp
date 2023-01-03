//~~~START:Mon, 02-Jan-2023, 16:26:44 IST
//~~~Author:Rajesh Pandian M | mrprajesh.co.in
//~ nvc++ -acc -gpu=managed -Minfo=all shuffle-2D-csr2.cpp -o shuffle-2D-csr2.out && ./shuffle-2D-csr2.out
// ERROR: NVC++-S-1061-Procedures called in a compute region must have acc routine information 
//~ nvc++ -acc=multicore -Minfo=all -fopenmp shuffle-2D-csr2.cpp -o shuffle-2D-csr2.out && ./shuffle-2D-csr2.out
// OKAY!
#include <iostream>
#include <random> //default rand in shuffle
#include <algorithm> // shuffle
#include <cstring> // memset

using namespace std;

void convert_VecOfVec_to_CSR(const vector<vector<int>> &a, int* &offset, int* &value){
  
  
  int aSize = a.size();
  offset = new int[aSize +1];
  int totalSize = 0;
  
  offset[0] = 0;
  
  for(int i=0, endI = a.size() ; i < endI ; ++i ){     // finds total size and set offsets
    totalSize += (int)a[i].size();
    offset[i+1] = totalSize ; //offset[i]+a[i].size();
  }
  
  //~ value = (int *) malloc(sizeof(int)*totalSize); // Allocates
  value = new int[totalSize];
  
  for(int i=0, k=0, endI = a.size() ; i < endI ; ++i ){     // k=0
    //~ std::cout<< i << ':';
    for(int j=0, endJ = a[i].size() ; j < endJ ; ++j, ++k) { // k++
       value[k] = a[i][j];
       //~ std::cout<< a[i][j] << ' ';
     }
     //~ std::cout<< '\n';
  }
}

void randInit_Print(vector<vector<int>> &a){
for (unsigned i = 0, endI =a.size(); i < endI; ++i) {
    a[i].resize(rand() % 10 + 1); // +1 ensure at least one element
    std::cout<< i << ':';
    for(int j=0, endJ = a[i].size(); j < endJ; ++j){
      a[i][j]= j +1;
      std::cout<< a[i][j] << ' ';
    }
    std::cout<< '\n';
  }  
}
void printCSR(int *offset, int* value, int n){
   
   for (int i = 0; i < n; ++i) {
    std::cout<< i << ':';
    for(int j=offset[i], end = offset[i+1]; j < end; ++j)
      std::cout<< value[j] << ' ';
    std::cout<< '\n';
  }
}

void shuffleIt(int *&offset, int* &value, int n){
  //~ #pragma data copy(offset,value)
  //~ #pragma acc parallel loop
  #pragma acc routine(shuffle) seq
  for (int i = 0; i < n; ++i) {
    std::shuffle(value+offset[i], value+offset[i+1] ,std::default_random_engine(rand()));
  }
    
}
int main(int argc, char* argv[]) {
  int n = 10;
  srand(time(0));
  
  std::cout << "N:" << n << '\n';
  
  vector<vector<int>> a(n);
  
  randInit_Print(a); // Randomly populate values!
  
  int* offset;
  int* value;
  
  convert_VecOfVec_to_CSR(a, offset, value);

  // PRINT OFFSET
  //~ std::cout<< "OFFSET:" << '\n';
  //~ for(int i=0; i < n; ++i)
    //~ std::cout<< offset[i+1] << ' ';
  //~ std::cout<<  '\n';  
  
  shuffleIt(offset, value, n);
  
  std::cout<< '\n';
  printCSR(offset, value, n);
  

  return 0;
}
