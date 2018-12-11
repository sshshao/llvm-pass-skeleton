; ModuleID = 'loop.c'
source_filename = "loop.c"
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

@main.board = private unnamed_addr constant [9 x [9 x i8]] [[9 x i8] c"53..7....", [9 x i8] c"6..195...", [9 x i8] c".98....6.", [9 x i8] c"8...6...3", [9 x i8] c"4..8.3..1", [9 x i8] c"7...2...6", [9 x i8] c".6....28.", [9 x i8] c"...419..5", [9 x i8] c"....8..79"], align 16

; Function Attrs: noinline nounwind uwtable
define i32 @main() #0 {
  %1 = alloca i32, align 4
  %2 = alloca [9 x [9 x i8]], align 16
  store i32 0, i32* %1, align 4
  %3 = bitcast [9 x [9 x i8]]* %2 to i8*
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %3, i8* getelementptr inbounds ([9 x [9 x i8]], [9 x [9 x i8]]* @main.board, i32 0, i32 0, i32 0), i64 81, i32 16, i1 false)
  %4 = getelementptr inbounds [9 x [9 x i8]], [9 x [9 x i8]]* %2, i32 0, i32 0
  %5 = call i32 @isValidSudoku([9 x i8]* %4)
  ret i32 0
}

; Function Attrs: argmemonly nounwind
declare void @llvm.memcpy.p0i8.p0i8.i64(i8* nocapture writeonly, i8* nocapture readonly, i64, i32, i1) #1

; Function Attrs: noinline nounwind uwtable
define i32 @isValidSudoku([9 x i8]*) #0 {
  %2 = alloca i32, align 4
  %3 = alloca [9 x i8]*, align 8
  %4 = alloca i32, align 4
  %5 = alloca i32, align 4
  %6 = alloca i32, align 4
  store [9 x i8]* %0, [9 x i8]** %3, align 8
  store i32 0, i32* %4, align 4
  br label %7

; <label>:7:                                      ; preds = %25, %1
  %8 = load i32, i32* %4, align 4
  %9 = icmp slt i32 %8, 9
  br i1 %9, label %10, label %28

; <label>:10:                                     ; preds = %7
  %11 = load [9 x i8]*, [9 x i8]** %3, align 8
  %12 = load i32, i32* %4, align 4
  %13 = load i32, i32* %4, align 4
  %14 = call i32 @isPartialValid([9 x i8]* %11, i32 %12, i32 0, i32 %13, i32 8)
  %15 = icmp eq i32 %14, 0
  br i1 %15, label %16, label %17

; <label>:16:                                     ; preds = %10
  store i32 0, i32* %2, align 4
  br label %56

; <label>:17:                                     ; preds = %10
  %18 = load [9 x i8]*, [9 x i8]** %3, align 8
  %19 = load i32, i32* %4, align 4
  %20 = load i32, i32* %4, align 4
  %21 = call i32 @isPartialValid([9 x i8]* %18, i32 0, i32 %19, i32 8, i32 %20)
  %22 = icmp eq i32 %21, 0
  br i1 %22, label %23, label %24

; <label>:23:                                     ; preds = %17
  store i32 0, i32* %2, align 4
  br label %56

; <label>:24:                                     ; preds = %17
  br label %25

; <label>:25:                                     ; preds = %24
  %26 = load i32, i32* %4, align 4
  %27 = add nsw i32 %26, 1
  store i32 %27, i32* %4, align 4
  br label %7

; <label>:28:                                     ; preds = %7
  store i32 0, i32* %5, align 4
  br label %29

; <label>:29:                                     ; preds = %52, %28
  %30 = load i32, i32* %5, align 4
  %31 = icmp slt i32 %30, 9
  br i1 %31, label %32, label %55

; <label>:32:                                     ; preds = %29
  store i32 0, i32* %6, align 4
  br label %33

; <label>:33:                                     ; preds = %48, %32
  %34 = load i32, i32* %6, align 4
  %35 = icmp slt i32 %34, 9
  br i1 %35, label %36, label %51

; <label>:36:                                     ; preds = %33
  %37 = load [9 x i8]*, [9 x i8]** %3, align 8
  %38 = load i32, i32* %5, align 4
  %39 = load i32, i32* %6, align 4
  %40 = load i32, i32* %5, align 4
  %41 = add nsw i32 %40, 2
  %42 = load i32, i32* %6, align 4
  %43 = add nsw i32 %42, 2
  %44 = call i32 @isPartialValid([9 x i8]* %37, i32 %38, i32 %39, i32 %41, i32 %43)
  %45 = icmp eq i32 %44, 0
  br i1 %45, label %46, label %47

; <label>:46:                                     ; preds = %36
  store i32 0, i32* %2, align 4
  br label %56

; <label>:47:                                     ; preds = %36
  br label %48

; <label>:48:                                     ; preds = %47
  %49 = load i32, i32* %6, align 4
  %50 = add nsw i32 %49, 3
  store i32 %50, i32* %6, align 4
  br label %33

; <label>:51:                                     ; preds = %33
  br label %52

; <label>:52:                                     ; preds = %51
  %53 = load i32, i32* %5, align 4
  %54 = add nsw i32 %53, 3
  store i32 %54, i32* %5, align 4
  br label %29

; <label>:55:                                     ; preds = %29
  store i32 1, i32* %2, align 4
  br label %56

; <label>:56:                                     ; preds = %55, %46, %23, %16
  %57 = load i32, i32* %2, align 4
  ret i32 %57
}

; Function Attrs: noinline nounwind uwtable
define i32 @isPartialValid([9 x i8]*, i32, i32, i32, i32) #0 {
  %6 = alloca i32, align 4
  %7 = alloca [9 x i8]*, align 8
  %8 = alloca i32, align 4
  %9 = alloca i32, align 4
  %10 = alloca i32, align 4
  %11 = alloca i32, align 4
  %12 = alloca [9 x i32], align 16
  %13 = alloca i32, align 4
  %14 = alloca i32, align 4
  %15 = alloca i32, align 4
  store [9 x i8]* %0, [9 x i8]** %7, align 8
  store i32 %1, i32* %8, align 4
  store i32 %2, i32* %9, align 4
  store i32 %3, i32* %10, align 4
  store i32 %4, i32* %11, align 4
  %16 = load i32, i32* %8, align 4
  store i32 %16, i32* %13, align 4
  br label %17

; <label>:17:                                     ; preds = %65, %5
  %18 = load i32, i32* %13, align 4
  %19 = load i32, i32* %10, align 4
  %20 = icmp sle i32 %18, %19
  br i1 %20, label %21, label %68

; <label>:21:                                     ; preds = %17
  %22 = load i32, i32* %9, align 4
  store i32 %22, i32* %14, align 4
  br label %23

; <label>:23:                                     ; preds = %61, %21
  %24 = load i32, i32* %14, align 4
  %25 = load i32, i32* %11, align 4
  %26 = icmp sle i32 %24, %25
  br i1 %26, label %27, label %64

; <label>:27:                                     ; preds = %23
  %28 = load [9 x i8]*, [9 x i8]** %7, align 8
  %29 = load i32, i32* %13, align 4
  %30 = sext i32 %29 to i64
  %31 = getelementptr inbounds [9 x i8], [9 x i8]* %28, i64 %30
  %32 = load i32, i32* %14, align 4
  %33 = sext i32 %32 to i64
  %34 = getelementptr inbounds [9 x i8], [9 x i8]* %31, i64 0, i64 %33
  %35 = load i8, i8* %34, align 1
  %36 = sext i8 %35 to i32
  %37 = icmp ne i32 %36, 46
  br i1 %37, label %38, label %60

; <label>:38:                                     ; preds = %27
  %39 = load [9 x i8]*, [9 x i8]** %7, align 8
  %40 = load i32, i32* %13, align 4
  %41 = sext i32 %40 to i64
  %42 = getelementptr inbounds [9 x i8], [9 x i8]* %39, i64 %41
  %43 = load i32, i32* %14, align 4
  %44 = sext i32 %43 to i64
  %45 = getelementptr inbounds [9 x i8], [9 x i8]* %42, i64 0, i64 %44
  %46 = load i8, i8* %45, align 1
  %47 = sext i8 %46 to i32
  %48 = sub nsw i32 %47, 48
  store i32 %48, i32* %15, align 4
  %49 = load i32, i32* %15, align 4
  %50 = sext i32 %49 to i64
  %51 = getelementptr inbounds [9 x i32], [9 x i32]* %12, i64 0, i64 %50
  %52 = load i32, i32* %51, align 4
  %53 = icmp ne i32 %52, 0
  br i1 %53, label %54, label %55

; <label>:54:                                     ; preds = %38
  store i32 0, i32* %6, align 4
  br label %69

; <label>:55:                                     ; preds = %38
  %56 = load i32, i32* %15, align 4
  %57 = sext i32 %56 to i64
  %58 = getelementptr inbounds [9 x i32], [9 x i32]* %12, i64 0, i64 %57
  store i32 1, i32* %58, align 4
  br label %59

; <label>:59:                                     ; preds = %55
  br label %60

; <label>:60:                                     ; preds = %59, %27
  br label %61

; <label>:61:                                     ; preds = %60
  %62 = load i32, i32* %14, align 4
  %63 = add nsw i32 %62, 1
  store i32 %63, i32* %14, align 4
  br label %23

; <label>:64:                                     ; preds = %23
  br label %65

; <label>:65:                                     ; preds = %64
  %66 = load i32, i32* %13, align 4
  %67 = add nsw i32 %66, 1
  store i32 %67, i32* %13, align 4
  br label %17

; <label>:68:                                     ; preds = %17
  store i32 1, i32* %6, align 4
  br label %69

; <label>:69:                                     ; preds = %68, %54
  %70 = load i32, i32* %6, align 4
  ret i32 %70
}

attributes #0 = { noinline nounwind uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { argmemonly nounwind }

!llvm.ident = !{!0}

!0 = !{!"clang version 4.0.1 (https://github.com/llvm-mirror/clang.git 3c8961bedc65c9a15cbe67a2ef385a0938f7cfef) (https://github.com/llvm-mirror/llvm.git c8fccc53ed66d505898f8850bcc690c977a7c9a7)"}
