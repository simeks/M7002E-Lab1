#ifndef __COMMON_H__
#define __COMMON_H__

#ifdef PLATFORM_WIN32

#define WIN32_LEAN_AND_MEAN // Exclude rarely-used stuff from Windows headers
#include <windows.h>

#endif

#include <stdint.h>

#include "debug.h"

#endif // __COMMON_H__
