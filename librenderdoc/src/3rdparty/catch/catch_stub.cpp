// Local RELEASE stub. This package builds with -DRELEASE, so Catch is off.
// renderdoccmd test unit stays a no-op.

#include "api/replay/apidefs.h"
#include "api/replay/rdcarray.h"
#include "api/replay/rdcstr.h"

extern "C" RENDERDOC_API int RENDERDOC_CC RENDERDOC_RunUnitTests(const rdcstr &command,
                                                                 const rdcarray<rdcstr> &args)
{
  return 0;
}
