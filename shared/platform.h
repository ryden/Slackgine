/////////////////////////////////////////////////////////////
//
// Slackgine - Copyright (C) 2010-2011
// The Slackgine development team
//
// See the LICENSE file in the top-level directory.
//
// FILE:        platform.h
// PURPOSE:     Platform-dependent stuff.
// AUTHORS:     Alberto Alonso <rydencillo@gmail.com>
//

#pragma once

#if defined(__arm__)
typedef char b8;
typedef unsigned char byte;
typedef char i8;
typedef unsigned char u8;
typedef short i16;
typedef unsigned short u16;
typedef int i32;
typedef unsigned int u32;
typedef long long i64;
typedef unsigned long long u64;
typedef float f32;
typedef double f64;
#elif defined(__x86_64)
typedef char b8;
typedef unsigned char byte;
typedef char i8;
typedef unsigned char u8;
typedef short i16;
typedef unsigned short u16;
typedef int i32;
typedef unsigned int u32;
typedef long i64;
typedef unsigned long u64;
typedef float f32;
typedef double f64;
#elif defined(__i586__) || defined(__i686__) || defined(_X86) || defined(_WIN32) || defined(__i386__) || defined(__i486__)
typedef char b8;
typedef unsigned char byte;
typedef char i8;
typedef unsigned char u8;
typedef short i16;
typedef unsigned short u16;
typedef int i32;
typedef unsigned int u32;
typedef long long i64;
typedef unsigned long long u64;
typedef float f32;
typedef double f64;
#endif

static inline bool detectBigEndian ()
{
    static union { const u16 w; const u8 v[2]; } const u = { 1 };
    return ( u.v[0] == 0 );
}

#ifdef __cplusplus
#  define OFFSETOF(T, MEMBER) (reinterpret_cast<size_t>(&(reinterpret_cast<T *>(0))->MEMBER))
#else
#  define OFFSETOF(T, MEMBER) ((size_t)(&((T)(0))->MEMBER))
#endif

#include "memory.h"
