# LLVM-Optimization-Pass
Implemented Data flow analysis pass available expressions on the intermediate LLVM code and Optimized the Code in compile-time after the analysis by eliminating the Common sub expression.
1.make acse
->will execute g++ -g -fPIC -shared available-cse.cc -o pass.so -std=c++11 `llvm-config --cppflags` 
->creates pass.so
2.make test1
->will execute the optimization pass on test1.ll file
3.make test2
->will execute the optimization pass on test2.ll file
4.make clean
->will remove the pass.so
->after make clean please start from 1 to do test the optimization pass on other test cases
