// Compatibility shim: RenderDoc includes "official/metal-cpp.h".
// libmetal-cpp exports the Apple headers under Foundation/, Metal/,
// QuartzCore/, and MetalFX/.
//
#pragma once
#include <Foundation/Foundation.hpp>
#include <Metal/Metal.hpp>
#include <QuartzCore/QuartzCore.hpp>
#include <MetalFX/MetalFX.hpp>
