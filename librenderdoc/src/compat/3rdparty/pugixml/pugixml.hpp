// Compatibility shim: RenderDoc includes "3rdparty/pugixml/pugixml.hpp".
// It lives under the compat/ include root rather than 3rdparty/, where it
// would also be found for "pugixml/pugixml.hpp" and shadow the packaged
// header.
//
#pragma once
#include <pugixml/pugixml.hpp>
