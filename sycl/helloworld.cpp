//~ icpx -fsycl  -o helloworld helloworld.cpp
//~ OneAPI 2023.
#include <CL/sycl.hpp>
#include <iostream>

using namespace cl::sycl;
constexpr int num = 32;

int main() {

    auto R = range<1> {num};
    buffer<int> A{R}, B{R};
    
    // Define a kernel that prints "Hello, World!" to the console
    queue{}.submit([&](handler& h) {
        auto out = A.get_access<access::mode::write>(h);
        h.parallel_for(R, [=](id<1> idx) {
          out[idx] = idx[0];
        });
    });
    
    auto result = A.get_access<access::mode::read>();
    
    for(int i=0; i < num; ++i){
        std::cout<< result [i]<< '\n';
    }
    
      

    // Wait for the kernel to complete before exiting the program
    //~ q.wait();

    return 0;
}
