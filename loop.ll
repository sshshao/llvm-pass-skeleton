; ModuleID = 'loop.c'
source_filename = "loop.c"
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

@main.board = private unnamed_addr constant [9 x [9 x i8]] [[9 x i8] c"53..7....", [9 x i8] c"6..195...", [9 x i8] c".98....6.", [9 x i8] c"8...6...3", [9 x i8] c"4..8.3..1", [9 x i8] c"7...2...6", [9 x i8] c".6....28.", [9 x i8] c"...419..5", [9 x i8] c"....8..79"], align 16

; Function Attrs: noinline nounwind
define i32 @main() #0 {
  %retval = alloca i32, align 4
  %board = alloca [9 x [9 x i8]], align 16
  store i32 0, i32* %retval, align 4
  %1 = bitcast [9 x [9 x i8]]* %board to i8*
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %1, i8* getelementptr inbounds ([9 x [9 x i8]], [9 x [9 x i8]]* @main.board, i32 0, i32 0, i32 0), i64 81, i32 16, i1 false)
  %arraydecay = getelementptr inbounds [9 x [9 x i8]], [9 x [9 x i8]]* %board, i32 0, i32 0
  %call = call i32 @isValidSudoku([9 x i8]* %arraydecay)
  ret i32 0
}

; Function Attrs: argmemonly nounwind
declare void @llvm.memcpy.p0i8.p0i8.i64(i8* nocapture writeonly, i8* nocapture readonly, i64, i32, i1) #1

; Function Attrs: noinline nounwind
define i32 @isValidSudoku([9 x i8]* %board) #0 {
  %retval = alloca i32, align 4
  %board.addr = alloca [9 x i8]*, align 8
  %i = alloca i32, align 4
  %i4 = alloca i32, align 4
  %j = alloca i32, align 4
  store [9 x i8]* %board, [9 x i8]** %board.addr, align 8
  store i32 0, i32* %i, align 4
  br label %1

; <label>:1:                                      ; preds = %14, %0
  %2 = load i32, i32* %i, align 4
  %cmp = icmp slt i32 %2, 9
  br i1 %cmp, label %3, label %16

; <label>:3:                                      ; preds = %1
  %4 = load [9 x i8]*, [9 x i8]** %board.addr, align 8
  %5 = load i32, i32* %i, align 4
  %6 = load i32, i32* %i, align 4
  %call = call i32 @isPartialValid([9 x i8]* %4, i32 %5, i32 0, i32 %6, i32 8)
  %cmp1 = icmp eq i32 %call, 0
  br i1 %cmp1, label %7, label %8

; <label>:7:                                      ; preds = %3
  store i32 0, i32* %retval, align 4
  br label %35

; <label>:8:                                      ; preds = %3
  %9 = load [9 x i8]*, [9 x i8]** %board.addr, align 8
  %10 = load i32, i32* %i, align 4
  %11 = load i32, i32* %i, align 4
  %call2 = call i32 @isPartialValid([9 x i8]* %9, i32 0, i32 %10, i32 8, i32 %11)
  %cmp3 = icmp eq i32 %call2, 0
  br i1 %cmp3, label %12, label %13

; <label>:12:                                     ; preds = %8
  store i32 0, i32* %retval, align 4
  br label %35

; <label>:13:                                     ; preds = %8
  br label %14

; <label>:14:                                     ; preds = %13
  %15 = load i32, i32* %i, align 4
  %inc = add nsw i32 %15, 1
  store i32 %inc, i32* %i, align 4
  br label %1

; <label>:16:                                     ; preds = %1
  store i32 0, i32* %i4, align 4
  br label %17

; <label>:17:                                     ; preds = %32, %16
  %18 = load i32, i32* %i4, align 4
  %cmp5 = icmp slt i32 %18, 9
  br i1 %cmp5, label %19, label %34

; <label>:19:                                     ; preds = %17
  store i32 0, i32* %j, align 4
  br label %20

; <label>:20:                                     ; preds = %29, %19
  %21 = load i32, i32* %j, align 4
  %cmp6 = icmp slt i32 %21, 9
  br i1 %cmp6, label %22, label %31

; <label>:22:                                     ; preds = %20
  %23 = load [9 x i8]*, [9 x i8]** %board.addr, align 8
  %24 = load i32, i32* %i4, align 4
  %25 = load i32, i32* %j, align 4
  %26 = load i32, i32* %i4, align 4
  %add = add nsw i32 %26, 2
  %27 = load i32, i32* %j, align 4
  %add7 = add nsw i32 %27, 2
  %call8 = call i32 @isPartialValid([9 x i8]* %23, i32 %24, i32 %25, i32 %add, i32 %add7)
  %cmp9 = icmp eq i32 %call8, 0
  br i1 %cmp9, label %28, label %29

; <label>:28:                                     ; preds = %22
  store i32 0, i32* %retval, align 4
  br label %35

; <label>:29:                                     ; preds = %22
  %30 = load i32, i32* %j, align 4
  %add10 = add nsw i32 %30, 3
  store i32 %add10, i32* %j, align 4
  br label %20

; <label>:31:                                     ; preds = %20
  br label %32

; <label>:32:                                     ; preds = %31
  %33 = load i32, i32* %i4, align 4
  %add11 = add nsw i32 %33, 3
  store i32 %add11, i32* %i4, align 4
  br label %17

; <label>:34:                                     ; preds = %17
  store i32 1, i32* %retval, align 4
  br label %35

; <label>:35:                                     ; preds = %34, %28, %12, %7
  %36 = load i32, i32* %retval, align 4
  ret i32 %36
}

; Function Attrs: noinline nounwind
define i32 @isPartialValid([9 x i8]* %board, i32 %r1, i32 %c1, i32 %r2, i32 %c2) #0 {
  %retval = alloca i32, align 4
  %board.addr = alloca [9 x i8]*, align 8
  %r1.addr = alloca i32, align 4
  %c1.addr = alloca i32, align 4
  %r2.addr = alloca i32, align 4
  %c2.addr = alloca i32, align 4
  %hashset = alloca [9 x i32], align 16
  %i = alloca i32, align 4
  %j = alloca i32, align 4
  %number = alloca i32, align 4
  store [9 x i8]* %board, [9 x i8]** %board.addr, align 8
  store i32 %r1, i32* %r1.addr, align 4
  store i32 %c1, i32* %c1.addr, align 4
  store i32 %r2, i32* %r2.addr, align 4
  store i32 %c2, i32* %c2.addr, align 4
  %1 = load i32, i32* %r1.addr, align 4
  store i32 %1, i32* %i, align 4
  br label %2

; <label>:2:                                      ; preds = %30, %0
  %3 = load i32, i32* %i, align 4
  %4 = load i32, i32* %r2.addr, align 4
  %cmp = icmp sle i32 %3, %4
  br i1 %cmp, label %5, label %32

; <label>:5:                                      ; preds = %2
  %6 = load i32, i32* %c1.addr, align 4
  store i32 %6, i32* %j, align 4
  br label %7

; <label>:7:                                      ; preds = %27, %5
  %8 = load i32, i32* %j, align 4
  %9 = load i32, i32* %c2.addr, align 4
  %cmp1 = icmp sle i32 %8, %9
  br i1 %cmp1, label %10, label %29

; <label>:10:                                     ; preds = %7
  %11 = load [9 x i8]*, [9 x i8]** %board.addr, align 8
  %12 = load i32, i32* %i, align 4
  %idxprom = sext i32 %12 to i64
  %arrayidx = getelementptr inbounds [9 x i8], [9 x i8]* %11, i64 %idxprom
  %13 = load i32, i32* %j, align 4
  %idxprom2 = sext i32 %13 to i64
  %arrayidx3 = getelementptr inbounds [9 x i8], [9 x i8]* %arrayidx, i64 0, i64 %idxprom2
  %14 = load i8, i8* %arrayidx3, align 1
  %conv = sext i8 %14 to i32
  %cmp4 = icmp ne i32 %conv, 46
  br i1 %cmp4, label %15, label %26

; <label>:15:                                     ; preds = %10
  %16 = load [9 x i8]*, [9 x i8]** %board.addr, align 8
  %17 = load i32, i32* %i, align 4
  %idxprom6 = sext i32 %17 to i64
  %arrayidx7 = getelementptr inbounds [9 x i8], [9 x i8]* %16, i64 %idxprom6
  %18 = load i32, i32* %j, align 4
  %idxprom8 = sext i32 %18 to i64
  %arrayidx9 = getelementptr inbounds [9 x i8], [9 x i8]* %arrayidx7, i64 0, i64 %idxprom8
  %19 = load i8, i8* %arrayidx9, align 1
  %conv10 = sext i8 %19 to i32
  %sub = sub nsw i32 %conv10, 48
  store i32 %sub, i32* %number, align 4
  %20 = load i32, i32* %number, align 4
  %idxprom11 = sext i32 %20 to i64
  %arrayidx12 = getelementptr inbounds [9 x i32], [9 x i32]* %hashset, i64 0, i64 %idxprom11
  %21 = load i32, i32* %arrayidx12, align 4
  %cmp13 = icmp ne i32 %21, 0
  br i1 %cmp13, label %22, label %23

; <label>:22:                                     ; preds = %15
  store i32 0, i32* %retval, align 4
  br label %33

; <label>:23:                                     ; preds = %15
  %24 = load i32, i32* %number, align 4
  %idxprom15 = sext i32 %24 to i64
  %arrayidx16 = getelementptr inbounds [9 x i32], [9 x i32]* %hashset, i64 0, i64 %idxprom15
  store i32 1, i32* %arrayidx16, align 4
  br label %25

; <label>:25:                                     ; preds = %23
  br label %26

; <label>:26:                                     ; preds = %25, %10
  br label %27

; <label>:27:                                     ; preds = %26
  %28 = load i32, i32* %j, align 4
  %inc = add nsw i32 %28, 1
  store i32 %inc, i32* %j, align 4
  br label %7

; <label>:29:                                     ; preds = %7
  br label %30

; <label>:30:                                     ; preds = %29
  %31 = load i32, i32* %i, align 4
  %inc17 = add nsw i32 %31, 1
  store i32 %inc17, i32* %i, align 4
  br label %2

; <label>:32:                                     ; preds = %2
  store i32 1, i32* %retval, align 4
  br label %33

; <label>:33:                                     ; preds = %32, %22
  %34 = load i32, i32* %retval, align 4
  ret i32 %34
}

attributes #0 = { noinline nounwind "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="false" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-features"="+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { argmemonly nounwind }

!llvm.ident = !{!0}

!0 = !{!"clang version 4.0.1 (https://github.com/llvm-mirror/clang.git 3c8961bedc65c9a15cbe67a2ef385a0938f7cfef) (https://github.com/llvm-mirror/llvm.git c8fccc53ed66d505898f8850bcc690c977a7c9a7)"}
