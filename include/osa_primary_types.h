#ifndef __OSA_PRIMARY_TYPES__
#define __OSA_PRIMARY_TYPES__


/*
 * Created by Liu Papillon, on Sep 6, 2017.
 */


#if defined(__i386) || defined(_WIN32) || defined(__arm__)
#define OSA_POINTER_SIZE        4
#elif defined(__WIN64) || defined(__x86_64__) || defined(__aarch64__)
#define OSA_POINTER_SIZE        8
#else
#error "Cannot determine pointer size"
#endif


typedef void*                   OSA_Handle;
typedef char                    Char;
typedef unsigned char           Uchar;


#if (4 == OSA_POINTER_SIZE)

typedef unsigned char           Byte;
typedef unsigned char           Uint8;
typedef char                    Int8;
typedef unsigned short          Uint16;
typedef short                   Int16;
typedef unsigned int            Uint32;
typedef int                     Int32;
typedef unsigned long long      Uint64;
typedef long long               Int64;
typedef float                   Float32;
typedef double                  Float64;


#elif  (8 == OSA_POINTER_SIZE)

typedef unsigned char           Byte;
typedef unsigned char           Uint8;
typedef char                    Int8;
typedef unsigned short          Uint16;
typedef short                   Int16;
typedef unsigned int            Uint32;
typedef int                     Int32;
typedef unsigned long           Uint64;
typedef long                    Int64;
typedef float                   Float32;
typedef double                  Float64;


#endif

#endif  /* __OSA_PRIMARY_TYPES__ */

