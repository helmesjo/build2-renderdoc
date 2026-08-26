// Compatibility shim: RenderDoc includes "official/vulkan.h".
// libvulkan-headers exports <vulkan/vulkan.h>.
//
// Upstream stubs Win32 types so Linux can compile with VK_USE_PLATFORM_WIN32_KHR
// (needed to serialise Windows captures). It also stubs RROutput so the build
// does not depend on libXrandr. Keep those two deviations. Everything else
// comes from the packaged Khronos headers.
//
#pragma once

#if defined(VK_USE_PLATFORM_WIN32_KHR) && !defined(_WIN32)
#define RDOC_VK_STUB_WIN32 1
#undef VK_USE_PLATFORM_WIN32_KHR
#endif

#if defined(VK_USE_PLATFORM_XLIB_XRANDR_EXT)
#define RDOC_VK_STUB_XRANDR 1
#undef VK_USE_PLATFORM_XLIB_XRANDR_EXT
#endif

#include <vulkan/vulkan.h>

#if defined(RDOC_VK_STUB_WIN32)
#define VK_USE_PLATFORM_WIN32_KHR
typedef unsigned long DWORD;
typedef wchar_t WCHAR;
typedef WCHAR *LPWSTR;
typedef const WCHAR *LPCWSTR;
typedef void *HANDLE;
struct HINSTANCE__;
typedef struct HINSTANCE__ *HINSTANCE;
struct HMONITOR__;
typedef struct HMONITOR__ *HMONITOR;
struct HWND__;
typedef struct HWND__ *HWND;
struct _SECURITY_ATTRIBUTES;
typedef struct _SECURITY_ATTRIBUTES SECURITY_ATTRIBUTES;
#include <vulkan/vulkan_win32.h>
#endif

#if defined(RDOC_VK_STUB_XRANDR)
#define VK_USE_PLATFORM_XLIB_XRANDR_EXT
typedef unsigned int RROutput;
#include <vulkan/vulkan_xlib_xrandr.h>
#endif
