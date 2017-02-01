acse:
	 g++ -g -fPIC -shared available-cse.cc -o pass.so -std=c++11 `llvm-config --cppflags`
m2r:
	cat test.ll 2>&1|opt -mem2reg |llvm-dis>test1.ll
test1:
	cat test1.ll | opt -mem2reg -load ./pass.so -avexp -cse 
test2:
	cat test2.ll | opt -mem2reg -load ./pass.so -avexp -cse
cfg:
	cat test1.ll 2>&1 | opt -dot-cfg > /dev/null
clean:
	rm pass.so

 
