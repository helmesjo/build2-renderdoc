#include <renderdoc_app.h>

#undef NDEBUG
#include <assert.h>

int main (void)
{
  pRENDERDOC_GetAPI get_api = 0;
  RENDERDOC_API_1_6_0 *api = 0;
  RENDERDOC_AnnotationValue v = {0};

  assert (eRENDERDOC_API_Version_1_6_0 == 10600);
  assert (eRENDERDOC_API_Version_1_7_0 == 10700);
  assert (get_api == 0);
  assert (api == 0);

  v.boolean = true;
  assert (v.boolean);

  return 0;
}
