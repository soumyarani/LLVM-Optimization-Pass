; ModuleID = '<stdin>'

define void @f() {
L0:
  %t2=alloca i32
  %t3=alloca i32
  %t1=add i32 8,9
  %t10=add i32 10,11
  %t7=icmp sgt i32 %t1,%t10
  br i1 %t7,label %L3,label %L2

L1:                                               ; preds = %L0
  %t4 = add i32 12,13
  br label %L3

L2:                                               ; preds = %L0
  %t5 = add i32 8, 9
  %t9=add i32 8,9
  %t11=add i32 10,11
  %t12=add i32 8,9
  br label %L3

L3:
                                                ; preds = %L2, %L1
  ret void
}
