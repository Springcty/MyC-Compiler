; ModuleID = 'main'
source_filename = "main"

@_Const_String_ = private constant [3 x i8] c"%d\00"

declare i32 @printf(i8*, ...)

declare i32 @scanf(...)

declare i32 @gets(...)

define i32 @fib(i32 %a1) {
entry:
  %0 = alloca i32
  %a = alloca i32
  store i32 %a1, i32* %a
  %LoadInst = load i32, i32* %a
  %icmptmp = icmp eq i32 %LoadInst, 1
  %LoadInst2 = load i32, i32* %a
  %icmptmp3 = icmp eq i32 %LoadInst2, 0
  %tmpOR = or i1 %icmptmp, %icmptmp3
  %ifCond = icmp ne i1 %tmpOR, false
  br i1 %ifCond, label %if, label %afterifonly

return:                                           ; preds = %afterifonly, %if
  %1 = load i32, i32* %0
  ret i32 %1

if:                                               ; preds = %entry
  store i32 1, i32* %0
  br label %return

afterifonly:                                      ; preds = %entry
  %LoadInst4 = load i32, i32* %a
  %2 = sub i32 %LoadInst4, 1
  %3 = call i32 @fib(i32 %2)
  %LoadInst5 = load i32, i32* %a
  %4 = sub i32 %LoadInst5, 2
  %5 = call i32 @fib(i32 %4)
  %6 = add i32 %3, %5
  store i32 %6, i32* %0
  br label %return
}

define i32 @main() {
entry:
  %0 = alloca i32
  %1 = call i32 @fib(i32 5)
  %printf = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @_Const_String_, i32 0, i32 0), i32 %1)
  store i32 0, i32* %0
  br label %return

return:                                           ; preds = %entry
  %2 = load i32, i32* %0
  ret i32 %2
}