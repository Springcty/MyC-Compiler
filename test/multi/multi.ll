; ModuleID = 'main'
source_filename = "main"

@A = private global [200000 x i32] zeroinitializer
@B = private global [200000 x i32] zeroinitializer
@C = private global [200000 x i32] zeroinitializer
@input = private global [100000 x i8] zeroinitializer
@_Const_String_ = private constant [7 x i8] c"%d %d\0A\00"
@_Const_String_.1 = private constant [3 x i8] c"%d\00"
@_Const_String_.2 = private constant [6 x i8] c"%d %d\00"
@_Const_String_.3 = private constant [3 x i8] c"%d\00"
@_Const_String_.4 = private constant [25 x i8] c"Incompatible Dimensions\0A\00"
@_Const_String_.5 = private constant [5 x i8] c"%10d\00"
@_Const_String_.6 = private constant [2 x i8] c"\0A\00"

declare i32 @printf(i8*, ...)

declare i32 @scanf(...)

declare i32 @gets(...)

define i32 @main() {
entry:
  %0 = alloca i32
  %A_M = alloca i32
  %A_N = alloca i32
  %B_M = alloca i32
  %B_N = alloca i32
  %scanf = call i32 (...) @scanf(i8* getelementptr inbounds ([7 x i8], [7 x i8]* @_Const_String_, i32 0, i32 0), i32* %A_M, i32* %A_N)
  %i = alloca i32
  store i32 0, i32* %i
  %j = alloca i32
  store i32 0, i32* %j
  br label %cond

return:                                           ; preds = %afterLoop88, %if
  %1 = load i32, i32* %0
  ret i32 %1

cond:                                             ; preds = %afterLoop4, %entry
  %LoadInst = load i32, i32* %i
  %LoadInst1 = load i32, i32* %A_M
  %icmptmp = icmp slt i32 %LoadInst, %LoadInst1
  %whileCond = icmp ne i1 %icmptmp, false
  br i1 %whileCond, label %loop, label %afterLoop

loop:                                             ; preds = %cond
  store i32 0, i32* %j
  br label %cond2

afterLoop:                                        ; preds = %cond
  %scanf15 = call i32 (...) @scanf(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @_Const_String_.2, i32 0, i32 0), i32* %B_M, i32* %B_N)
  store i32 0, i32* %i
  store i32 0, i32* %j
  br label %cond16

cond2:                                            ; preds = %loop3, %loop
  %LoadInst5 = load i32, i32* %j
  %LoadInst6 = load i32, i32* %A_N
  %icmptmp7 = icmp slt i32 %LoadInst5, %LoadInst6
  %whileCond8 = icmp ne i1 %icmptmp7, false
  br i1 %whileCond8, label %loop3, label %afterLoop4

loop3:                                            ; preds = %cond2
  %LoadInst9 = load i32, i32* %i
  %LoadInst10 = load i32, i32* %A_N
  %2 = mul i32 %LoadInst9, %LoadInst10
  %LoadInst11 = load i32, i32* %j
  %3 = add i32 %2, %LoadInst11
  %elePtr = getelementptr inbounds [200000 x i32], [200000 x i32]* @A, i32 0, i32 %3
  %scanf12 = call i32 (...) @scanf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @_Const_String_.1, i32 0, i32 0), i32* %elePtr)
  %LoadInst13 = load i32, i32* %j
  %4 = add i32 %LoadInst13, 1
  store i32 %4, i32* %j
  br label %cond2

afterLoop4:                                       ; preds = %cond2
  %LoadInst14 = load i32, i32* %i
  %5 = add i32 %LoadInst14, 1
  store i32 %5, i32* %i
  br label %cond

cond16:                                           ; preds = %afterLoop25, %afterLoop
  %LoadInst19 = load i32, i32* %i
  %LoadInst20 = load i32, i32* %B_M
  %icmptmp21 = icmp slt i32 %LoadInst19, %LoadInst20
  %whileCond22 = icmp ne i1 %icmptmp21, false
  br i1 %whileCond22, label %loop17, label %afterLoop18

loop17:                                           ; preds = %cond16
  store i32 0, i32* %j
  br label %cond23

afterLoop18:                                      ; preds = %cond16
  %LoadInst37 = load i32, i32* %A_N
  %LoadInst38 = load i32, i32* %B_M
  %icmptmp39 = icmp ne i32 %LoadInst37, %LoadInst38
  %ifCond = icmp ne i1 %icmptmp39, false
  br i1 %ifCond, label %if, label %afterifonly

cond23:                                           ; preds = %loop24, %loop17
  %LoadInst26 = load i32, i32* %j
  %LoadInst27 = load i32, i32* %B_N
  %icmptmp28 = icmp slt i32 %LoadInst26, %LoadInst27
  %whileCond29 = icmp ne i1 %icmptmp28, false
  br i1 %whileCond29, label %loop24, label %afterLoop25

loop24:                                           ; preds = %cond23
  %LoadInst30 = load i32, i32* %i
  %LoadInst31 = load i32, i32* %B_N
  %6 = mul i32 %LoadInst30, %LoadInst31
  %LoadInst32 = load i32, i32* %j
  %7 = add i32 %6, %LoadInst32
  %elePtr33 = getelementptr inbounds [200000 x i32], [200000 x i32]* @B, i32 0, i32 %7
  %scanf34 = call i32 (...) @scanf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @_Const_String_.3, i32 0, i32 0), i32* %elePtr33)
  %LoadInst35 = load i32, i32* %j
  %8 = add i32 %LoadInst35, 1
  store i32 %8, i32* %j
  br label %cond23

afterLoop25:                                      ; preds = %cond23
  %LoadInst36 = load i32, i32* %i
  %9 = add i32 %LoadInst36, 1
  store i32 %9, i32* %i
  br label %cond16

if:                                               ; preds = %afterLoop18
  %printf = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([25 x i8], [25 x i8]* @_Const_String_.4, i32 0, i32 0))
  store i32 0, i32* %0
  br label %return

afterifonly:                                      ; preds = %afterLoop18
  store i32 0, i32* %i
  store i32 0, i32* %j
  br label %cond40

cond40:                                           ; preds = %afterLoop49, %afterifonly
  %LoadInst43 = load i32, i32* %i
  %LoadInst44 = load i32, i32* %A_M
  %icmptmp45 = icmp slt i32 %LoadInst43, %LoadInst44
  %whileCond46 = icmp ne i1 %icmptmp45, false
  br i1 %whileCond46, label %loop41, label %afterLoop42

loop41:                                           ; preds = %cond40
  store i32 0, i32* %j
  br label %cond47

afterLoop42:                                      ; preds = %cond40
  store i32 0, i32* %i
  br label %cond86

cond47:                                           ; preds = %afterLoop60, %loop41
  %LoadInst50 = load i32, i32* %j
  %LoadInst51 = load i32, i32* %B_N
  %icmptmp52 = icmp slt i32 %LoadInst50, %LoadInst51
  %whileCond53 = icmp ne i1 %icmptmp52, false
  br i1 %whileCond53, label %loop48, label %afterLoop49

loop48:                                           ; preds = %cond47
  %LoadInst54 = load i32, i32* %i
  %LoadInst55 = load i32, i32* %B_N
  %10 = mul i32 %LoadInst54, %LoadInst55
  %LoadInst56 = load i32, i32* %j
  %11 = add i32 %10, %LoadInst56
  %elePtr57 = getelementptr inbounds [200000 x i32], [200000 x i32]* @C, i32 0, i32 %11
  store i32 0, i32* %elePtr57
  %k = alloca i32
  store i32 0, i32* %k
  br label %cond58

afterLoop49:                                      ; preds = %cond47
  %LoadInst85 = load i32, i32* %i
  %12 = add i32 %LoadInst85, 1
  store i32 %12, i32* %i
  br label %cond40

cond58:                                           ; preds = %loop59, %loop48
  %LoadInst61 = load i32, i32* %k
  %LoadInst62 = load i32, i32* %A_N
  %icmptmp63 = icmp slt i32 %LoadInst61, %LoadInst62
  %whileCond64 = icmp ne i1 %icmptmp63, false
  br i1 %whileCond64, label %loop59, label %afterLoop60

loop59:                                           ; preds = %cond58
  %LoadInst65 = load i32, i32* %i
  %LoadInst66 = load i32, i32* %B_N
  %13 = mul i32 %LoadInst65, %LoadInst66
  %LoadInst67 = load i32, i32* %j
  %14 = add i32 %13, %LoadInst67
  %elePtr68 = getelementptr inbounds [200000 x i32], [200000 x i32]* @C, i32 0, i32 %14
  %LoadInst69 = load i32, i32* %i
  %LoadInst70 = load i32, i32* %B_N
  %15 = mul i32 %LoadInst69, %LoadInst70
  %LoadInst71 = load i32, i32* %j
  %16 = add i32 %15, %LoadInst71
  %elePtr72 = getelementptr inbounds [200000 x i32], [200000 x i32]* @C, i32 0, i32 %16
  %tmpvar = load i32, i32* %elePtr72
  %LoadInst73 = load i32, i32* %i
  %LoadInst74 = load i32, i32* %A_N
  %17 = mul i32 %LoadInst73, %LoadInst74
  %LoadInst75 = load i32, i32* %k
  %18 = add i32 %17, %LoadInst75
  %elePtr76 = getelementptr inbounds [200000 x i32], [200000 x i32]* @A, i32 0, i32 %18
  %tmpvar77 = load i32, i32* %elePtr76
  %19 = add i32 %tmpvar, %tmpvar77
  %LoadInst78 = load i32, i32* %k
  %LoadInst79 = load i32, i32* %B_N
  %20 = mul i32 %LoadInst78, %LoadInst79
  %LoadInst80 = load i32, i32* %j
  %21 = add i32 %20, %LoadInst80
  %elePtr81 = getelementptr inbounds [200000 x i32], [200000 x i32]* @B, i32 0, i32 %21
  %tmpvar82 = load i32, i32* %elePtr81
  %22 = mul i32 %19, %tmpvar82
  store i32 %22, i32* %elePtr68
  %LoadInst83 = load i32, i32* %k
  %23 = add i32 %LoadInst83, 1
  store i32 %23, i32* %k
  br label %cond58

afterLoop60:                                      ; preds = %cond58
  %LoadInst84 = load i32, i32* %j
  %24 = add i32 %LoadInst84, 1
  store i32 %24, i32* %j
  br label %cond47

cond86:                                           ; preds = %afterLoop95, %afterLoop42
  %LoadInst89 = load i32, i32* %i
  %LoadInst90 = load i32, i32* %A_M
  %icmptmp91 = icmp slt i32 %LoadInst89, %LoadInst90
  %whileCond92 = icmp ne i1 %icmptmp91, false
  br i1 %whileCond92, label %loop87, label %afterLoop88

loop87:                                           ; preds = %cond86
  store i32 0, i32* %j
  br label %cond93

afterLoop88:                                      ; preds = %cond86
  store i32 0, i32* %0
  br label %return

cond93:                                           ; preds = %loop94, %loop87
  %LoadInst96 = load i32, i32* %j
  %LoadInst97 = load i32, i32* %B_N
  %icmptmp98 = icmp slt i32 %LoadInst96, %LoadInst97
  %whileCond99 = icmp ne i1 %icmptmp98, false
  br i1 %whileCond99, label %loop94, label %afterLoop95

loop94:                                           ; preds = %cond93
  %LoadInst100 = load i32, i32* %i
  %LoadInst101 = load i32, i32* %B_N
  %25 = mul i32 %LoadInst100, %LoadInst101
  %LoadInst102 = load i32, i32* %j
  %26 = add i32 %25, %LoadInst102
  %elePtr103 = getelementptr inbounds [200000 x i32], [200000 x i32]* @C, i32 0, i32 %26
  %tmpvar104 = load i32, i32* %elePtr103
  %printf105 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([5 x i8], [5 x i8]* @_Const_String_.5, i32 0, i32 0), i32 %tmpvar104)
  %LoadInst106 = load i32, i32* %j
  %27 = add i32 %LoadInst106, 1
  store i32 %27, i32* %j
  br label %cond93

afterLoop95:                                      ; preds = %cond93
  %printf107 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([2 x i8], [2 x i8]* @_Const_String_.6, i32 0, i32 0))
  %LoadInst108 = load i32, i32* %i
  %28 = add i32 %LoadInst108, 1
  store i32 %28, i32* %i
  br label %cond86
}