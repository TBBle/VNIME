#include "pch.hpp"

#include "registration_helpers.hpp"
#include "text_input_processor.hpp"

extern "C" {

/*
 * Entry points for a self-registering COM DLL
 */

HRESULT __stdcall DllRegisterServer() {
  // Per
  // https://blogs.msdn.microsoft.com/tsfaware/2007/05/07/text-service-basics/
  try {
    // 1. Register as an in-proc COM server
    register_as_inproc_server(vnime::TextInputProcessorGUID,
                              L"TBBle's Vietnamese IME",
                              vnime::TextInputProcessorProgID);
    // 2. Register with TSF
    // 3. Register categories
    vnime::TextInputProcessor::register_with_TSF();
  } catch (...) {
    return winrt::to_hresult();
  }

  return S_OK;
}

HRESULT __stdcall DllUnregisterServer() {
  try {
    vnime::TextInputProcessor::unregister_from_TSF();
    unregister_as_inproc_server(vnime::TextInputProcessorGUID,
                                vnime::TextInputProcessorProgID);
  } catch (...) {
    return winrt::to_hresult();
  }
  return S_OK;
}
}
