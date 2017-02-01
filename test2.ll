define void @f() 
{
L0:
  %t0 = alloca [5 x i32]
  %t1 = getelementptr [5 x i32]* %t0, i32 0, i32 1
  %t2 = load i32* %t1
  %t3 = add i32 %t2, 1
  %t4 = getelementptr [5 x i32]* %t0, i32 0, i32 1
  %t5 = getelementptr [5 x i32]* %t0, i32 0, i32 1
  %t6 = getelementptr [5 x i32]* %t0, i32 0, i32 1
  store i32 %t3, i32* %t4
  ret void
}
