#ifndef DEFINITIONS_H
#define DEFINITIONS_H

typedef char s8;
typedef unsigned char u8;
typedef short s16;
typedef unsigned short u16;
typedef int s32;
typedef unsigned int u32;
typedef s32 sint;
typedef u32 uint;
typedef u32 bool;
typedef long long s64;
typedef unsigned long long u64;
typedef s64 sptr;
typedef u64 uptr;
typedef float f32;
typedef double f64;

#define INTERNAL static
#define GLOBAL static
#define LOCAL static
#define ASSERT(expression) do { if(!(expression)) { *(int *)0 = 0; } } while(0)
#define ARRAY_COUNT(array) (sizeof(array) / sizeof((array)[0]))
#define KILOBYTES(value) ((value) * (u64)1024)
#define MEGABYTES(value) (KILOBYTES(value) * (u64)1024)
#define GIGABYTES(value) (MEGABYTES(value) * (u64)1024)
#define TERABYTES(value) (GIGABYTES(value) * (u64)1024)
#define MAX_S32 0x7FFFFFFF
#define MAX_U32 0xFFFFFFFF
#define MAX_S64 0x7FFFFFFFFFFFFFFF
#define MAX_U64 0xFFFFFFFFFFFFFFFF
#endif