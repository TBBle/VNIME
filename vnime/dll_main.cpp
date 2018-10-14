#include "pch.hpp"

extern "C" {

BOOL __stdcall DllMain(HINSTANCE hinst, DWORD reason, void *) {
  switch (reason) {
  case DLL_PROCESS_ATTACH:
    // Disable thread notifications. This is an optimisation, so
    // if it fails, we don't care, we'll just ignore the calls.
    ::DisableThreadLibraryCalls(hinst);
    break;
  }
  return TRUE;
}
}
