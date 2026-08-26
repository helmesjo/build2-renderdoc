#include <renderdoc_app.h>

extern "C" int RENDERDOC_CC RENDERDOC_GetAPI (RENDERDOC_Version version,
                                              void **outAPIPointers);

#undef NDEBUG
#include <cassert>

int main ()
{
  void *api = nullptr;
  int r = RENDERDOC_GetAPI (eRENDERDOC_API_Version_1_6_0, &api);
  assert (r == 1);
  assert (api != nullptr);
}
