#ifndef FZ_CORE_H
#define FZ_CORE_H

////////////////////////////////
// Context Cracking

/* 
  Macro quick look-up:

  FZ_ENABLE_ASSERT

  COMPILER_CLANG
  COMPILER_MSVC
  COMPILER_GCC

  NOTE(fz): f_base only supports windows. It was not built to be abstracted.
  OS_WINDOWS
  OS_LINUX
  OS_MAC

  ARCH_X64
  ARCH_X86
  ARCH_ARM64
  ARCH_ARM32

  COMPILER_MSVC_YEAR

  ARCH_32BIT
  ARCH_64BIT

  ARCH_LITTLE_ENDIAN
*/

// Clang OS/Arch Cracking
#if defined(__clang__)

# define COMPILER_CLANG 1
# if defined(_WIN32)
#  define OS_WINDOWS 1
# elif defined(__gnu_linux__) || defined(__linux__)
#  define OS_LINUX 1
# elif defined(__APPLE__) && defined(__MACH__)
#  define OS_MAC 1
# else
#  error This compiler/OS combo is not supported.
# endif

# if defined(__amd64__) || defined(__amd64) || defined(__x86_64__) || defined(__x86_64)
#  define ARCH_X64 1
# elif defined(i386) || defined(__i386) || defined(__i386__)
#  define ARCH_X86 1
# elif defined(__aarch64__)
#  define ARCH_ARM64 1
# elif defined(__arm__)
#  define ARCH_ARM32 1
# else
#  error Architecture not supported.
# endif

// MSVC OS/Arch Cracking
#elif defined(_MSC_VER)

# define COMPILER_MSVC 1
# if _MSC_VER >= 1930
#  define COMPILER_MSVC_YEAR 2022
# elif _MSC_VER >= 1920
#  define COMPILER_MSVC_YEAR 2019
# elif _MSC_VER >= 1910
#  define COMPILER_MSVC_YEAR 2017
# elif _MSC_VER >= 1900
#  define COMPILER_MSVC_YEAR 2015
# elif _MSC_VER >= 1800
#  define COMPILER_MSVC_YEAR 2013
# elif _MSC_VER >= 1700
#  define COMPILER_MSVC_YEAR 2012
# elif _MSC_VER >= 1600
#  define COMPILER_MSVC_YEAR 2010
# elif _MSC_VER >= 1500
#  define COMPILER_MSVC_YEAR 2008
# elif _MSC_VER >= 1400
#  define COMPILER_MSVC_YEAR 2005
# else
#  define COMPILER_MSVC_YEAR 0
# endif

# if defined(_WIN32)
#  define OS_WINDOWS 1
# else
#  error This compiler/OS combo is not supported.
# endif

# if defined(_M_AMD64)
#  define ARCH_X64 1
# elif defined(_M_IX86)
#  define ARCH_X86 1
# elif defined(_M_ARM64)
#  define ARCH_ARM64 1
# elif defined(_M_ARM)
#  define ARCH_ARM32 1
# else
#  error Architecture not supported.
# endif

// GCC OS/Arch Cracking
#elif defined(__GNUC__) || defined(__GNUG__)

# define COMPILER_GCC 1
# if defined(__gnu_linux__) || defined(__linux__)
#  define OS_LINUX 1
# else
#  error This compiler/OS combo is not supported.
# endif

# if defined(__amd64__) || defined(__amd64) || defined(__x86_64__) || defined(__x86_64)
#  define ARCH_X64 1
# elif defined(i386) || defined(__i386) || defined(__i386__)
#  define ARCH_X86 1
# elif defined(__aarch64__)
#  define ARCH_ARM64 1
# elif defined(__arm__)
#  define ARCH_ARM32 1
# else
#  error Architecture not supported.
# endif

#else
# error Compiler not supported.
#endif

// Arch Cracking
#if defined(ARCH_X64)
# define ARCH_64BIT 1
#elif defined(ARCH_X86)
# define ARCH_32BIT 1
#endif

#if ARCH_ARM32 || ARCH_ARM64 || ARCH_X64 || ARCH_X86
# define ARCH_LITTLE_ENDIAN 1
#else
# error Endianness of this architecture not understood by context cracker.
#endif

// Zero All Undefined Options
#if !defined(ARCH_32BIT)
# define ARCH_32BIT 0
#endif
#if !defined(ARCH_64BIT)
# define ARCH_64BIT 0
#endif
#if !defined(ARCH_X64)
# define ARCH_X64 0
#endif
#if !defined(ARCH_X86)
# define ARCH_X86 0
#endif
#if !defined(ARCH_ARM64)
# define ARCH_ARM64 0
#endif
#if !defined(ARCH_ARM32)
# define ARCH_ARM32 0
#endif
#if !defined(COMPILER_MSVC)
# define COMPILER_MSVC 0
#endif
#if !defined(COMPILER_GCC)
# define COMPILER_GCC 0
#endif
#if !defined(COMPILER_CLANG)
# define COMPILER_CLANG 0
#endif
#if !defined(OS_WINDOWS)
# define OS_WINDOWS 0
#endif
#if !defined(OS_LINUX)
# define OS_LINUX 0
#endif
#if !defined(OS_MAC)
# define OS_MAC 0
#endif

#if ARCH_X64 || ARCH_ARM64
# define ARCH_ADDRSIZE 64
#else
# define ARCH_ADDRSIZE 32
#endif

#if COMPILER_MSVC
# define thread_static __declspec(thread)
#elif COMPILER_CLANG || COMPILER_GCC
# define thread_static __thread
#endif

#if OS_WINDOWS
# define shared_internal C_LINKAGE __declspec(dllexport)
#else
# define shared_internal C_LINKAGE
#endif

#if LANG_CPP
# define C_LINKAGE_BEGIN extern "C"{
# define C_LINKAGE_END }
# define C_LINKAGE extern "C"
#else
# define C_LINKAGE_BEGIN
# define C_LINKAGE_END
# define C_LINKAGE
#endif

////////////////////////////////
// Core

#define true  1
#define false 0

#define Stringify_(S) #S
#define Stringify(S) Stringify_(S)
#define Glue_(A,B) A##B
#define Glue(A,B) Glue_(A,B)

#if COMPILER_MSVC
# define Trap() __debugbreak()
#elif COMPILER_CLANG || COMPILER_GCC
# define Trap() __builtin_trap()
#else
# error Unknown trap intrinsic for this compiler.
#endif

#define Statement(S) do{ S }while(0)


#if !defined(AssertBreak)
# if defined(OS_WINDOWS)
#  define AssertBreak(condition) Statement(if (!(condition)) { ERROR_MESSAGE_AND_EXIT("Assert Failed\nExpression: %s", Stringify(condition)); })
# else
#  define AssertBreak(condition) (*(volatile int*)0 = 0)
# endif
#endif

#if FZ_ENABLE_ASSERT
# define Assert(condition) Statement( if (!(condition)){ AssertBreak(condition); } )
# define AssertNoReentry() Statement(local_persist b32 triggered = 0;Assert(triggered == 0); triggered = 1;) 
#else
# define Assert(condition)
# define AssertNoReentry()
#endif

#define StaticAssert(condition,label) typedef u8 Glue(label,__LINE__) [(condition)?1:-1]

#define RunOnce(expr, lbl) Statement(local_persist flag##lbl = 0; if (flag##lbl == 0) {expr; flag##lbl = 1;})

#define ArrayCount(a) (sizeof(a)/sizeof((a)[0]))

#define Min(A,B) (((A)<(B))?(A):(B))
#define Max(A,B) (((A)>(B))?(A):(B))
#define ClampTop(A,X) Min(A,X)
#define ClampBot(X,B) Max(X,B)
#define Clamp(val,min,max) (((val)<(min))?(min):((val)>(max))?(max):(val))

#define IntFromPtr(p) (u64)((u8*)p - (u8*)0)
#define PtrFromInt(i) (void*)((u8*)0 + (i))
#define Member(T,m) (((T*)0)->m)
#define OffsetOfMember(T,m) IntFromPtr(&Member(T,m))

#define Kilobytes(n) ((u64)(n * 1024))
#define Megabytes(n) ((u64)(n * 1024 * 1024))
#define Gigabytes(n) ((u64)(n * 1024 * 1024 * 1024))
#define Terabytes(n) ((u64)(n * 1024 * 1024 * 1024 * 1024))

#define Thousand(n) ((n)*1000)
#define Million(n)  ((n)*1000000llu)
#define Billion(n)  ((n)*1000000000llu)
#define Trillion(n) ((n)*1000000000000llu)

#define DEFAULT_ALIGNMENT sizeof(void*)
#define AlignPow2(x,b)     (((x) + (b) - 1)&(~((b) - 1)))
#define AlignDownPow2(x,b) ((x)&(~((b) - 1)))
#define IsPow2(x)          ((x)!=0 && ((x)&((x)-1))==0)
#define IsPow2OrZero(x)    ((((x) - 1)&(x)) == 0)

#define MemoryCopy(dst, src, size) memcpy((dst), (src), (size))
#define MemoryMove(dst, src, size) memmove((dst), (src), (size))
#define MemorySet(dst, val, size)  memset((dst), (val), (size))
#define MemoryMatch(a,b,size)     (memcmp((a),(b),(size)) == 0)

#define MemoryCopyStruct(dst, src) do { Assert(sizeof(*(dst)) == sizeof(*(src))); MemoryCopy((dst), (src), sizeof(*(dst))); } while(0)
#define MemoryCopyArray(dst, src)  do { Assert(sizeof(dst) == sizeof(src)); MemoryCopy((dst), (src), sizeof(src)); }while(0)

#define MemoryZero(ptr, size) MemorySet((ptr), 0, (size))
#define MemoryZeroStruct(ptr) MemoryZero((ptr), sizeof(*(ptr)))
#define MemoryZeroArray(arr)  MemoryZero((arr), sizeof(arr))

#define SetFlag(flags, flag)    ((flags) |= (flag))
#define HasFlags(flags, check_flags) (((flags) & (check_flags)) == (check_flags))
#define ToggleFlag(flags, flag) ((flags) ^= (flag))

#define local_persist static
#define global        static
#define internal      static

////////////////////////////////
// Types 

#if defined(__STDC_UTF_8__)
typedef char8_t char8;
#else
typedef unsigned char char8;
#endif
#define CHAR8_MIN 0x00
#define CHAR8_MAX 0xFF

#if defined(__STDC_UTF_16__)
typedef char16_t char16;
#else
typedef unsigned short char16;
#endif
#define CHAR16_MIN 0x0000
#define CHAR16_MAX 0xFFFF

#if defined(__STDC_UTF_32__)
typedef char32_t char32;
#else
typedef unsigned int char32;
#endif
#define CHAR32_MIN 0x00000000
#define CHAR32_MAX 0xFFFFFFFF

typedef unsigned char      u8;
typedef unsigned short     u16;
typedef unsigned int       u32;
typedef unsigned long long u64;
#define U8_MIN  0x00
#define U8_MAX  0xFF
#define U16_MIN 0x0000
#define U16_MAX 0xFFFF
#define U32_MIN 0x00000000
#define U32_MAX 0xFFFFFFFF
#define U64_MIN 0x0000000000000000
#define U64_MAX 0xFFFFFFFFFFFFFFFF

typedef signed char      s8;
typedef signed short     s16;
typedef signed int       s32;
typedef signed long long s64;
#define S8_MIN  (-0x7F - 1)
#define S8_MAX  0x7F
#define S16_MIN (-0x7FFF - 1)
#define S16_MAX 0x7FFF
#define S32_MIN (-0x7FFFFFFF - 1)
#define S32_MAX 0x7FFFFFFF
#define S64_MIN (-0x7FFFFFFFFFFFFFFF - 1)
#define S64_MAX 0x7FFFFFFFFFFFFFFF

typedef float  f32;
typedef double f64;

#define F32_MIN (-3.402823466e+38f)
#define F32_MAX 3.402823466e+38f
#define F32_EPSILON 1.192092896e-07f
#define F64_MIN (-1.7976931348623158e+308)
#define F64_MAX 1.7976931348623158e+308
#define F64_EPSILON 2.2204460492503131e-16

typedef unsigned char b8;
typedef unsigned int  b32;

#endif // FZ_CORE_H