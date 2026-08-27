// Compatibility shim: RenderDoc includes "compressonator/CMP_Core.h".
// The packaged header is <cmp_core/cmp_core.h> (build2 consumers do not
// get the unqualified pkg-config include path).
#pragma once
#include <cmp_core/cmp_core.h>
