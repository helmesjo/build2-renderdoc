// Compatibility shim: RenderDoc includes "dbghelp/dbghelp.h", its copy of the
// Windows SDK header edited only to compile without warning C4091. Use the
// SDK header instead, with that warning disabled.
//
#pragma once
#pragma warning(push)
#pragma warning(disable : 4091)
#include <DbgHelp.h>
#pragma warning(pop)
