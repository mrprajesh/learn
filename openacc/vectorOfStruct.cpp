//~~~START:Fri, 16-Sep-2022, 14:25:49 IST
//~~~Author:Rajesh Pandian M | mrprajesh.co.in 
//~ nvc++ -acc -gpu=managed -Minfo=all vectorOfStruct.cpp -o vectorOfStruct.out && ./vectorOfStruct.out

#include <math.h>
#include <iostream>
using namespace std;
struct Point{
  double x;
  double y;
};
int main(int argc, char* argv[]){
  unsigned n = 1000;//  1 << 28;
  std::cout << "N:" << n << '\n';
  
   
  Point* p = (Point*) malloc (sizeof(Point) *n);
  double* d = (double*) malloc (sizeof(double) *n);
  
  for (unsigned i = 0; i < n; ++i) {
    p[i].x = i;
    p[i].y = i + 10;
  }
  for (unsigned i = 1; i < n; ++i) {
    //~ d[i] = sqrt( (p[i].x - p[i-1].x)*(p[i].x - p[i-1].x) + (p[i].y - p[i-1].y)*(p[i].y - p[i-1].y) );
    d[i] = atan2(2.3,3.3);
  }


  for (unsigned i = 0; i < 10; ++i) {
    std::cout<< i << " " << p[i].x << "--" << p[i].y << " " << d[i] << '\n';
  }
  
      
  
  #pragma acc data create(p[0:n],d[0:n]) copyout(p[0:n],d[0:n])  
  {
    #pragma acc parallel loop 
    for (unsigned i = 0; i < n; ++i) {
      p[i].x = i;
      p[i].y = i + 10;
    }
      
    //~ #pragma acc routine seq  
    #pragma acc parallel loop 
    for (unsigned i = 1; i < n; ++i) {
      //~ d[i] = sqrt( (p[i].x - p[i-1].x)*(p[i].x - p[i-1].x) + (p[i].y - p[i-1].y)*(p[i].y - p[i-1].y) );
      d[i] = atan2(2.3,3.3);                              
    }
  }
  
  for (unsigned i = 0; i < 10; ++i) {
    std::cout<< i << " " << p[i].x << "--" << p[i].y << " " << d[i] << '\n';
  }
        
  
  
  return 0;
}
