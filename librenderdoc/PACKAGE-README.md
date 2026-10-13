# librenderdoc - Frame-capture graphics debugger C++ library

This is a `build2` package for the [RenderDoc](https://renderdoc.org) C++
library. It captures frames from Vulkan, OpenGL, Metal, D3D11, and D3D12
applications. Linking against `lib{renderdoc}` also transitively imports
`lib{renderdoc-app}` so consumers get `<renderdoc_app.h>` without a separate
`depends:` entry.


## Usage

Add the following `depends` value to your `manifest`, adjusting the version
constraint as appropriate:

```
depends: librenderdoc ^1.45.0
```

Then import the library in your `buildfile`:

```
import libs = librenderdoc%lib{renderdoc}
```

Include the public header as `<renderdoc_app.h>`. The header typedefs
`pRENDERDOC_GetAPI` and does not declare `RENDERDOC_GetAPI`. Linking
consumers that want the exported symbol must declare it themselves.


### Vulkan capture layer registration

When the shared library is built, the Vulkan capture-layer manifest is
installed to `etc/vulkan/implicit_layer.d/renderdoc_capture.json` under
`config.install.root`. On Linux and macOS the Vulkan loader only finds it
there if it scans that directory (for example `/etc/vulkan/implicit_layer.d`
for the `/` prefix). On Windows the loader does not scan directories for
implicit layers at all, it reads them from the registry. Otherwise, point
`VK_ADD_IMPLICIT_LAYER_PATH` at that directory, or register the layer at
runtime as described in `renderdoccmd/PACKAGE-README.md`.


## Importable targets

```
lib{renderdoc}
json{renderdoc_capture}
```

The capture/replay library. Replay headers stay private, matching upstream
CMake. The public in-application API header is installed by `librenderdoc-app`.
A final release uses unversioned names matching upstream CMake (`librenderdoc.so`,
`librenderdoc.dylib`, `renderdoc.dll`) so the in-application API can find this
module by those names.

On macOS the compiler must be Clang. GCC cannot parse the Objective-C blocks
used in `apple_helpers.mm` and the Metal/GL helpers (the same limitation as
`libmetal-cpp`). Homebrew `g++` on macOS is rejected at configure. Linux GCC
is supported.

`json{renderdoc_capture}` is the build-tree Vulkan capture-layer manifest
that exists for this project's own testing (see `librenderdoc-tests`), not
a general consumer API. The installed manifest is described above.


## Windows

Upstream builds Windows only with Visual Studio, so this package requires
the MSVC toolset and the shared library. Clang (including clang-cl) and
MinGW are rejected at configure. Differences from upstream's build:

- `renderdocshim64.dll`, the global capture hook, is built and installed
  next to `renderdoc.dll`, where `renderdoc.dll` looks for it. It is not an
  importable target.
- The embedded shaders and font are Win32 resources of `renderdoc.dll`,
  compiled with the toolchain's `rc.exe` and `cvtres.exe`. The DXIL helper
  shaders are not baked with DXC at build time. D3D12 compiles them at
  runtime with `dxcompiler.dll`, as in upstream builds without DXC, but has
  no baked fallback.
- Callstack resolution uses the system `dbghelp.dll` from `System32`
  instead of a copy next to `renderdoc.dll`. Downloading symbols from a
  symbol server also needs `symsrv.dll` (Debugging Tools for Windows).
- D3D12On7 (D3D12 on Windows 7) is patched out. It needs
  `D3D12Downlevel.h` and `D3D11On12On7.h`, which neither the Windows SDK
  nor `libdirectx-headers` provides.
- The NVIDIA PerfKit D3D11 counters are patched out, since the PerfKit
  headers may not be redistributed. The Nsight Perf SDK counters
  (`libnvperf`) remain.
- NVIDIA Aftermath is the stub that upstream's source ships.
- The AMD AGS headers are `libags` 6.3.1, so the
  `plugins/amd/ags/amd_ags_x64.dll` that replay loads must be the 6.3.1
  one. AMD ships it as a prebuilt binary, which this package does not
  provide.


## Vendored files

A few small files stay in-tree rather than as separate dependencies:

- `3rdparty/md5/` - Solar Designer's public-domain MD5, used for DXBC
  shader-bytecode hashing. No versioned upstream, just a wiki page.
- `3rdparty/superluminal/` - Superluminal's C API header for optional
  profiler marker regions. Ships only inside their installer, not a repo.
- `3rdparty/include-bin/` - a small build-time tool that embeds shader and
  manifest data as C arrays. No known upstream repo.
- `driver/ihv/amd/official/RGA/elf/` - the ELF structure definitions from
  FreeBSD's `sys/sys` (BSD-2-Clause), which the AMD ISA disassembly uses on
  Windows, where there is no `<elf.h>`. Three headers do not warrant a
  package.
- `driver/ihv/intel/official/DriverStorePath.h` - Intel's helper (MIT) for
  locating the driver's DLLs, added in upstream commit `4a4fdb40e`. It has
  no public upstream.


## Configuration variables

```
[bool] config.librenderdoc.vulkan ?= true
[bool] config.librenderdoc.gl     ?= ($cxx.target.class != 'windows')
[bool] config.librenderdoc.metal  ?= ($cxx.target.class == 'macos')
[bool] config.librenderdoc.d3d11  ?= ($cxx.target.class == 'windows')
[bool] config.librenderdoc.d3d12  ?= ($cxx.target.class == 'windows')
```

Each flag compiles the corresponding graphics API driver. Metal requires
macOS. D3D11/D3D12 require Windows. With `config.librenderdoc.gl` this
package depends on `libopengl-registry` and `libegl-registry` for the
Khronos OpenGL, OpenGL ES, and EGL headers. With `config.librenderdoc.d3d11`
or `config.librenderdoc.d3d12` it depends on `libmicrosoft-pdb` for the
Microsoft CodeView debug information headers.

On macOS this package depends on `libmetal-cpp` with
`config.libmetal_cpp.implementation=true`. A local `official/metal-cpp.h`
shim remaps Metal option enums to distinct `uint64_t` types so `TypeName<>`
and the serialiser work, and supplies `pathForResource` /
`dataWithContentsOfFile` helpers that 381 does not declare.
