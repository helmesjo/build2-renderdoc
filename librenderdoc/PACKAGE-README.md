# librenderdoc - Frame-capture graphics debugger C++ library

This is a `build2` package for the [RenderDoc](https://renderdoc.org) C++
library. It captures frames from Vulkan, OpenGL, Metal, D3D11, and D3D12
applications and exposes the in-application API through `<renderdoc_app.h>`.


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

Include the public header as `<renderdoc_app.h>` and call `RENDERDOC_GetAPI`.


## Importable targets

```
lib{renderdoc}
```

The capture/replay library. Only `renderdoc_app.h` is installed. Replay
headers stay private, matching upstream CMake.

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

This package compiles upstream's amalgamated `metal-cpp` (RenderDoc's
`NS::Integer` as `int64_t`, `_MTL_OPTIONS` as distinct enums, and extra
Foundation helpers). Packaged `libmetal-cpp` 381 does not yet carry those
patches.

A Vulkan implicit layer manifest is installed to
`etc/vulkan/implicit_layer.d/renderdoc_capture.json` when the shared library
is built on non-Windows targets.
