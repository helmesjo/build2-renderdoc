# renderdoccmd - Frame-capture graphics debugger command-line tool

This is a `build2` package for the [RenderDoc](https://renderdoc.org)
command-line tool. It injects the capture library, starts target programs, and
prints version and compile-time API support.


## Usage

Add the following build-time `depends` value to your `manifest`, adjusting the
version constraint as appropriate:

```
depends: * renderdoccmd ^1.45.0-
```

Then import the executable in your `buildfile`:

```
import! renderdoccmd = renderdoccmd%exe{renderdoccmd}
```


## Importable targets

```
exe{renderdoccmd}
```

The command-line driver. On macOS it links Cocoa and QuartzCore and must be
built with Clang (Objective-C blocks in `cocoa_window.mm`). It depends on
`librenderdoc` from this repository (`depends: librenderdoc == $`).


## Configuration variables

This package has no configuration variables. Graphics API support follows
`librenderdoc`.
