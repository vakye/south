
#pragma once

#define local static
#define persist static

#define CTAssert(Expression) _Static_assert(Expression, "Compile-time assertion failed")

#define ArrayCount(Array) (sizeof(Array) / sizeof((Array)[0]))

#define AlignAs(Value) _Alignas(Value)

#define Minimum(A, B) ((A) < (B) ? (A) : (B))
#define Maximum(A, B) ((A) > (B) ? (A) : (B))

#define KB(Amount) ((ssize)(Amount) << 10)
#define MB(Amount) ((ssize)(Amount) << 20)
#define GB(Amount) ((ssize)(Amount) << 30)
#define TB(Amount) ((ssize)(Amount) << 40)

#define IsPowerOf2(Value) (((Value) & ((Value) - 1)) == 0)

typedef signed char         s8;
typedef signed short        s16;
typedef signed int          s32;
typedef signed long long    s64;

typedef unsigned char       u8;
typedef unsigned short      u16;
typedef unsigned int        u32;
typedef unsigned long long  u64;

typedef s64 ssize;
typedef u64 usize;

typedef float   f32;
typedef double  f64;

typedef u8  b8;
typedef u16 b16;
typedef u32 b32;
typedef u64 b64;

#define true  (1)
#define false (0)

#define ZeroStruct(Pointer) ZeroMemory(Pointer, sizeof(*(Pointer)))
#define ZeroArray(Pointer, Count) ZeroMemory(Pointer, sizeof(*(Pointer)) * (Count))

local void ZeroMemory(void* DestInit, usize Size);
