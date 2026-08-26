#include <renderdoc_app.h>
#include <cstring>

extern "C" int RENDERDOC_CC RENDERDOC_GetAPI (RENDERDOC_Version version,
                                              void **outAPIPointers);
extern "C" void RENDERDOC_CC RENDERDOC_ShutdownReplay ();

#undef NDEBUG
#include <cassert>

int main ()
{
  // The in-application API must load, return a table, and accept calls with
  // no device and no GPU. Capture entry points without a frame capturer are
  // no-ops and must not create a capture.
  //
  void *p = nullptr;
  int r = RENDERDOC_GetAPI (eRENDERDOC_API_Version_1_6_0, &p);
  assert (r == 1);
  assert (p != nullptr);

  RENDERDOC_API_1_6_0 *api = static_cast<RENDERDOC_API_1_6_0 *> (p);

  int major = 0;
  int minor = 0;
  int patch = 0;
  api->GetAPIVersion (&major, &minor, &patch);
  assert (major == RENDERDOC_API_VERSION_MAJOR);
  assert (minor == RENDERDOC_API_VERSION_MINOR);
  assert (patch == RENDERDOC_API_VERSION_PATCH);

  r = RENDERDOC_GetAPI (static_cast<RENDERDOC_Version> (
                          RENDERDOC_API_VERSION_MAJOR * 10000 +
                          RENDERDOC_API_VERSION_MINOR * 100 +
                          RENDERDOC_API_VERSION_PATCH),
                        &p);
  assert (r == 1);
  assert (p == api);

  r = RENDERDOC_GetAPI (static_cast<RENDERDOC_Version> (0), &p);
  assert (r == 0);

  assert (api->GetCaptureOptionU32 (eRENDERDOC_Option_AllowVSync) == 1);
  assert (api->SetCaptureOptionU32 (eRENDERDOC_Option_AllowVSync, 0) == 1);
  assert (api->GetCaptureOptionU32 (eRENDERDOC_Option_AllowVSync) == 0);
  assert (api->SetCaptureOptionU32 (eRENDERDOC_Option_AllowVSync, 1) == 1);
  assert (api->GetCaptureOptionU32 (eRENDERDOC_Option_AllowVSync) == 1);

  assert (api->SetCaptureOptionF32 (eRENDERDOC_Option_SoftMemoryLimit, 256.0f) == 1);
  assert (api->GetCaptureOptionF32 (eRENDERDOC_Option_SoftMemoryLimit) == 256.0f);
  assert (api->GetCaptureOptionU32 (eRENDERDOC_Option_SoftMemoryLimit) == 256);
  assert (api->SetCaptureOptionU32 (eRENDERDOC_Option_SoftMemoryLimit, 0) == 1);
  assert (api->GetCaptureOptionU32 (eRENDERDOC_Option_SoftMemoryLimit) == 0);

  RENDERDOC_CaptureOption unknown = static_cast<RENDERDOC_CaptureOption> (999);
  assert (api->SetCaptureOptionU32 (unknown, 1) == 0);
  assert (api->GetCaptureOptionU32 (unknown) == 0xffffffffu);

  api->SetCaptureFilePathTemplate ("rdc-smoke-cap");
  const char *tmpl = api->GetCaptureFilePathTemplate ();
  assert (tmpl != nullptr);
  assert (std::strcmp (tmpl, "rdc-smoke-cap") == 0);

  assert (api->GetNumCaptures () == 0);
  assert (api->IsFrameCapturing () == 0);
  assert (api->IsTargetControlConnected () == 0);

  assert (api->GetOverlayBits () == eRENDERDOC_Overlay_Default);
  api->MaskOverlayBits (eRENDERDOC_Overlay_None, eRENDERDOC_Overlay_None);
  assert (api->GetOverlayBits () == eRENDERDOC_Overlay_None);
  api->MaskOverlayBits (eRENDERDOC_Overlay_None, eRENDERDOC_Overlay_Default);
  assert (api->GetOverlayBits () == eRENDERDOC_Overlay_Default);

  RENDERDOC_InputButton keys[] = {eRENDERDOC_Key_F12};
  api->SetCaptureKeys (keys, 1);
  api->SetCaptureKeys (nullptr, 0);

  api->TriggerCapture ();
  assert (api->IsFrameCapturing () == 0);
  assert (api->GetNumCaptures () == 0);

  api->StartFrameCapture (nullptr, nullptr);
  assert (api->IsFrameCapturing () == 0);
  assert (api->EndFrameCapture (nullptr, nullptr) == 0);
  assert (api->DiscardFrameCapture (nullptr, nullptr) == 0);
  assert (api->GetNumCaptures () == 0);
  // Run the shutdown functions registered during static initialization here,
  // while the global lock of the glslang library is still alive. Otherwise
  // they run from the RenderDoc destructor, after that lock was destroyed.
  //
  RENDERDOC_ShutdownReplay ();
}
