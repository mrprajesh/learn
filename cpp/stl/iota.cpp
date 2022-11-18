//~~~START:Wed, 21-Sep-2022, 16:34:33 IST
//~~~Author:Rajesh Pandian M | mrprajesh.co.in 
#include <bits/stdc++.h>
using namespace std;
void print(const vector<int>& a){
  std::copy(a.begin(), a.end(),std::ostream_iterator<int>(std::cout, " ")); std::cout<< std::endl; //#include <iterator> //ostream_iterator  
}
int main(int argc, char* argv[]){
  vector<int> a(10);
  // Third arg is a must. It is begin of the sequence.
  std::iota(a.begin(),a.end(),0);  print(a);  //  0  1  2  3  4  5  6  7  8  9 
  std::iota(a.begin(),a.end(),20); print(a);  // 20 21 22 23 24 25 26 27 28 29
  return 0;
}
