# renderdoc

This is a `build2` package repository for [RenderDoc](https://renderdoc.org),
a frame-capture graphics debugger.

This file contains setup instructions that are more appropriate for
development than consumption. If you want to use these packages in a
`build2`-based project, see [`librenderdoc/PACKAGE-README.md`](librenderdoc/PACKAGE-README.md)
and [`renderdoccmd/PACKAGE-README.md`](renderdoccmd/PACKAGE-README.md).

The development setup uses the standard `bdep`-based workflow. On macOS use
Apple Clang or Homebrew LLVM, not Homebrew GCC. GCC cannot compile the
Objective-C blocks in the macOS helpers.

```
git clone --recursive https://github.com/build2-packaging/renderdoc.git
cd renderdoc

bdep init -C @apple cc config.cxx=clang++
bdep update
bdep test
```

`bdep update @gcc` on macOS is expected to fail at configure with
`librenderdoc requires Clang on macOS: GCC has no Objective-C blocks support`.
Linux GCC remains a supported configuration in the package manifests.
