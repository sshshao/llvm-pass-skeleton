; ModuleID = 'test.c'
source_filename = "test.c"
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

; Function Attrs: noinline nounwind uwtable
define i32 @main(i32, i8**) #0 {
  %3 = alloca i32, align 4
  %4 = alloca i32, align 4
  %5 = alloca i8**, align 8
  %6 = alloca i32, align 4
  %7 = alloca i32, align 4
  %8 = alloca i32, align 4
  %9 = alloca i32, align 4
  %10 = alloca i32, align 4
  %11 = alloca i32, align 4
  %12 = alloca i32, align 4
  %13 = alloca i32, align 4
  store i32 0, i32* %3, align 4
  store i32 %0, i32* %4, align 4
  store i8** %1, i8*** %5, align 8
  store i32 0, i32* %6, align 4
  br label %14

; <label>:14:                                     ; preds = %48, %2
  %15 = load i32, i32* %6, align 4
  %16 = icmp slt i32 %15, 20
  br i1 %16, label %17, label %51

; <label>:17:                                     ; preds = %14
  store i32 0, i32* %7, align 4
  br label %18

; <label>:18:                                     ; preds = %34, %17
  %19 = load i32, i32* %7, align 4
  %20 = icmp slt i32 %19, 15
  br i1 %20, label %21, label %37

; <label>:21:                                     ; preds = %18
  %22 = load i32, i32* %6, align 4
  %23 = add nsw i32 %22, 1
  store i32 %23, i32* %6, align 4
  store i32 0, i32* %8, align 4
  br label %24

; <label>:24:                                     ; preds = %30, %21
  %25 = load i32, i32* %8, align 4
  %26 = icmp slt i32 %25, 15
  br i1 %26, label %27, label %33

; <label>:27:                                     ; preds = %24
  %28 = load i32, i32* %6, align 4
  %29 = add nsw i32 %28, 2
  store i32 %29, i32* %6, align 4
  br label %30

; <label>:30:                                     ; preds = %27
  %31 = load i32, i32* %8, align 4
  %32 = add nsw i32 %31, 1
  store i32 %32, i32* %8, align 4
  br label %24

; <label>:33:                                     ; preds = %24
  br label %34

; <label>:34:                                     ; preds = %33
  %35 = load i32, i32* %7, align 4
  %36 = add nsw i32 %35, 1
  store i32 %36, i32* %7, align 4
  br label %18

; <label>:37:                                     ; preds = %18
  store i32 0, i32* %9, align 4
  br label %38

; <label>:38:                                     ; preds = %44, %37
  %39 = load i32, i32* %9, align 4
  %40 = icmp slt i32 %39, 15
  br i1 %40, label %41, label %47

; <label>:41:                                     ; preds = %38
  %42 = load i32, i32* %6, align 4
  %43 = add nsw i32 %42, 2
  store i32 %43, i32* %6, align 4
  br label %44

; <label>:44:                                     ; preds = %41
  %45 = load i32, i32* %9, align 4
  %46 = add nsw i32 %45, 1
  store i32 %46, i32* %9, align 4
  br label %38

; <label>:47:                                     ; preds = %38
  br label %48

; <label>:48:                                     ; preds = %47
  %49 = load i32, i32* %6, align 4
  %50 = mul nsw i32 %49, 2
  store i32 %50, i32* %6, align 4
  br label %14

; <label>:51:                                     ; preds = %14
  store i32 0, i32* %11, align 4
  br label %52

; <label>:52:                                     ; preds = %57, %51
  %53 = load i32, i32* %11, align 4
  %54 = icmp slt i32 %53, 50
  br i1 %54, label %55, label %60

; <label>:55:                                     ; preds = %52
  %56 = load i32, i32* %11, align 4
  store i32 %56, i32* %10, align 4
  br label %57

; <label>:57:                                     ; preds = %55
  %58 = load i32, i32* %11, align 4
  %59 = add nsw i32 %58, 1
  store i32 %59, i32* %11, align 4
  br label %52

; <label>:60:                                     ; preds = %52
  store i32 0, i32* %12, align 4
  br label %61

; <label>:61:                                     ; preds = %78, %60
  %62 = load i32, i32* %12, align 4
  %63 = icmp slt i32 %62, 40
  br i1 %63, label %64, label %81

; <label>:64:                                     ; preds = %61
  %65 = load i32, i32* %12, align 4
  %66 = load i32, i32* %10, align 4
  %67 = sub nsw i32 %66, %65
  store i32 %67, i32* %10, align 4
  store i32 0, i32* %13, align 4
  br label %68

; <label>:68:                                     ; preds = %74, %64
  %69 = load i32, i32* %13, align 4
  %70 = icmp slt i32 %69, 5
  br i1 %70, label %71, label %77

; <label>:71:                                     ; preds = %68
  %72 = load i32, i32* %10, align 4
  %73 = add nsw i32 %72, 2
  store i32 %73, i32* %10, align 4
  br label %74

; <label>:74:                                     ; preds = %71
  %75 = load i32, i32* %13, align 4
  %76 = add nsw i32 %75, 1
  store i32 %76, i32* %13, align 4
  br label %68

; <label>:77:                                     ; preds = %68
  br label %78

; <label>:78:                                     ; preds = %77
  %79 = load i32, i32* %12, align 4
  %80 = add nsw i32 %79, 1
  store i32 %80, i32* %12, align 4
  br label %61

; <label>:81:                                     ; preds = %61
  %82 = load i32, i32* %3, align 4
  ret i32 %82
}

attributes #0 = { noinline nounwind uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.ident = !{!0}

!0 = !{!"clang version 4.0.1 (https://github.com/llvm-mirror/clang.git 3c8961bedc65c9a15cbe67a2ef385a0938f7cfef) (https://github.com/llvm-mirror/llvm.git c8fccc53ed66d505898f8850bcc690c977a7c9a7)"}
