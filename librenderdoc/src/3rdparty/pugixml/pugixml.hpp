// Compatibility shim: RenderDoc includes "pugixml/pugixml.hpp".
// The packaged pugixml also exports its header at <pugixml/pugixml.hpp>
// (same relative path as this file), so a plain #include would just
// re-open this shim under -I.../3rdparty. #include_next continues the
// search into the imported package.
//
#pragma once
#include_next <pugixml/pugixml.hpp>
