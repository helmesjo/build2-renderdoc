// Compatibility shim: RenderDoc includes "driver/dx/official/d3d11_4.h".
// The libdirectx-headers copies of the headers shared with D3D12 come
// first, so the include guards keep the Windows SDK copies out.
//
#pragma once
#include <directx/d3dcommon.h>
#include <directx/dxgiformat.h>
#include <directx/dxgicommon.h>
#include <d3d11_4.h>
