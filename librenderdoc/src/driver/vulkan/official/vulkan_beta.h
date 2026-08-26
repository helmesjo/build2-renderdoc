// Compatibility shim: packaged vulkan.h includes "vulkan_beta.h" when
// VK_ENABLE_BETA_EXTENSIONS is set. Keep a sibling thunk next to the other
// official/ headers so quoted includes resolve in this overlay.
//
#pragma once
#include <vulkan/vulkan_beta.h>
