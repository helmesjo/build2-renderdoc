# librenderdoc-app - In-application API C header for RenderDoc

This is a `build2` package for the [RenderDoc](https://renderdoc.org)
in-application API. It ships the public `renderdoc_app.h` header so an
application can look up the capture module at runtime and call
`RENDERDOC_GetAPI`. It does not compile or link the capture library.

The documented in-application path is to probe for a module that is already
loaded in the process, typically injected when the program is launched from
the RenderDoc UI:

- Windows: `GetModuleHandleA("renderdoc.dll")`
- Linux: `dlopen("librenderdoc.so", RTLD_NOW | RTLD_NOLOAD)`
- macOS: `dlopen("librenderdoc.dylib", RTLD_NOW | RTLD_NOLOAD)`

Then resolve `RENDERDOC_GetAPI` with `GetProcAddress` or `dlsym`. The header
typedefs `pRENDERDOC_GetAPI` and does not declare the function. Do not link
`lib{renderdoc}`.


## Usage

Add the following `depends` value to your `manifest`, adjusting the version
constraint as appropriate:

```
depends: librenderdoc-app ^1.45.0-
```

Then import the library in your `buildfile`:

```
import libs = librenderdoc-app%lib{renderdoc-app}
```

Include the public header as `<renderdoc_app.h>`.


## Importable targets

```
lib{renderdoc-app}
```

Binless (header-only) library. The public header is included as
`<renderdoc_app.h>`, matching upstream CMake (`include/renderdoc_app.h`).


## Configuration variables

This package provides no configuration variables.
