// Compatibility shim: RenderDoc includes "official/metal-cpp.h".
// Packaged libmetal-cpp exports Apple's split headers. Implementation lives
// in lib{metal-cpp}. Do not define *_PRIVATE_IMPLEMENTATION here.
//
// Packaged _NS_OPTIONS aliases NS::UInteger, so TypeName<> collapses and the
// serialiser rejects unsigned long enums. After Foundation, remap Metal enums
// to distinct uint64_t types (values include NS::UIntegerMax). NS::UInteger
// itself stays uintptr_t, so metal_types.h serialises it as uint64_t. Two
// Foundation helpers missing in 381 are objc_msgSend wrappers below.
//
#pragma once

#include <cstdint>
#include <objc/message.h>
#include <objc/runtime.h>

#include <Foundation/Foundation.hpp>

#undef _NS_ENUM
#undef _NS_OPTIONS
#define _NS_ENUM(type, name) enum name : std::uint64_t
#define _NS_OPTIONS(type, name) enum name : std::uint64_t

#include <Metal/Metal.hpp>
#include <QuartzCore/QuartzCore.hpp>
#include <MetalFX/MetalFX.hpp>

inline NS::String *rdoc_pathForResource(NS::Bundle *bundle, NS::String *name, NS::String *ext)
{
  using MsgSend = id (*)(id, SEL, id, id);
  return reinterpret_cast<NS::String *>(
      reinterpret_cast<MsgSend>(objc_msgSend)(reinterpret_cast<id>(bundle),
                                              sel_registerName("pathForResource:ofType:"),
                                              reinterpret_cast<id>(name),
                                              reinterpret_cast<id>(ext)));
}

inline NS::Data *rdoc_dataWithContentsOfFile(NS::String *path)
{
  using MsgSend = id (*)(id, SEL, id);
  return reinterpret_cast<NS::Data *>(
      reinterpret_cast<MsgSend>(objc_msgSend)(reinterpret_cast<id>(objc_lookUpClass("NSData")),
                                              sel_registerName("dataWithContentsOfFile:"),
                                              reinterpret_cast<id>(path)));
}
