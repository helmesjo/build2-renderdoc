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
depends: librenderdoc ^1.45.0-
```

Then import the library in your `buildfile`:

```
import libs = librenderdoc%lib{renderdoc}
```

Include the public header as `<renderdoc_app.h>`. The header typedefs
`pRENDERDOC_GetAPI` and does not declare `RENDERDOC_GetAPI`. Linking
consumers that want the exported symbol must declare it themselves.


## Importable targets

```
lib{renderdoc}
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


## Configuration variables

```
[bool] config.librenderdoc.vulkan ?= true
[bool] config.librenderdoc.gl     ?= ($cxx.target.class != 'windows')
[bool] config.librenderdoc.metal  ?= ($cxx.target.class == 'macos')
[bool] config.librenderdoc.d3d11  ?= ($cxx.target.class == 'windows')
[bool] config.librenderdoc.d3d12  ?= ($cxx.target.class == 'windows')
```

Each flag compiles the corresponding graphics API driver. Metal requires
macOS. D3D11/D3D12 require Windows.

On macOS this package depends on `libmetal-cpp` with
`config.libmetal_cpp.implementation=true`. A local `official/metal-cpp.h`
shim remaps Metal option enums to distinct `uint64_t` types so `TypeName<>`
and the serialiser work, and supplies `pathForResource` /
`dataWithContentsOfFile` helpers that 381 does not declare.

A Vulkan implicit layer manifest is installed to
`etc/vulkan/implicit_layer.d/renderdoc_capture.json` when the shared library
is built on non-Windows targets.
