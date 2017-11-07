#ifndef __OSA_PLATFORMS_H__
#define __OSA_PLATFORMS_H__


/*
 * Created by Liu Papillon, on Sep 20, 2017.
 */


/****************************** Operating Systems Below: *********************************/

#if defined(__WINDOWS__) || defined(_WIN32) || defined(_WIN64) || defined(__WIN32__)
    #define OSA_OS_WINDOWS
#elif defined(__ANDROID__)
    #define OSA_OS_ANDROID
#elif defined(__gnu_linux__)
    #define OSA_OS_GNU_LINUX
#elif defined(__linux__) || defined(linux) || defined(__linux)
    #define OSA_OS_LINUX_KERNEL
#elif defined(macintosh) || defined(Macintosh)
    #define OSA_OS_MACOS
#else
    #error "Cannot determine Operating System"
#endif


/****************************** Architectures Below: *********************************/

#if defined(__amd64__) || defined(__amd64) || defined(__x86_64__) || defined(__x86_64)
    #define OSA_ARCH_AMD64
#elif defined(i386) || defined(__i386) || defined(__i386__) || defined(_M_I86) || defined(_M_IX86)
    #define OSA_ARCH_X86
#elif defined(__arm__) || defined(__thumb__) || defined(_M_ARM) || defined(_M_ARMT)
    #define OSA_ARCH_ARM
#elif defined(__aarch64__)
    #define OSA_ARCH_ARM64
#else
    #error "Cannot determine architecture"
#endif



#endif  /* __OSA_PLATFORMS_H__ */

