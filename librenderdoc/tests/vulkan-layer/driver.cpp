#include <vulkan/vulkan.h>

#undef NDEBUG
#include <cassert>
#include <cstring>
#include <vector>

// The loader discovers this build's Vulkan capture layer via
// VK_ADD_IMPLICIT_LAYER_PATH (set by Testscript env, see ./testscript)
// naming the directory containing the json built by
// librenderdoc%json{renderdoc_capture}.
// Enumeration alone needs no VkInstance or physical device: the loader
// reads layer name, versions, and description straight out of the json,
// without loading the layer's library, so this proves manifest discovery
// and parsing, not capture itself.
//
int main ()
{
  uint32_t count = 0;
  VkResult r = vkEnumerateInstanceLayerProperties (&count, nullptr);
  assert (r == VK_SUCCESS);

  std::vector<VkLayerProperties> layers (count);
  r = vkEnumerateInstanceLayerProperties (&count, layers.data ());
  assert (r == VK_SUCCESS);

  bool found = false;
  for (const auto& l : layers)
  {
    if (std::strcmp (l.layerName, "VK_LAYER_RENDERDOC_Capture") == 0)
      found = true;
  }

  assert (found);
}
