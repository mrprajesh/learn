# lean sycl

- check [my blog](https://mrprajesh.co.in/blog/how-to-install-sycl.html) for install, compile and run.



```
# do it
export PATH=$HOME/install/llvm/build/bin:$PATH
export LD_LIBRARY_PATH=$HOME/install/llvm/build/lib:$LD_LIBRARY_PATH

# verify
$ clang++ --version
clang version 16.0.0

```
## compile and run

```
#complie
clang++ -fsycl -fsycl-targets=nvptx64-nvidia-cuda simple-sycl-app.cpp -o simple-sycl-app-cuda

#run
./simple-sycl-app-cuda
The results are correct!

```
