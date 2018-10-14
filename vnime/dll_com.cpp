#include "pch.hpp"

#include <winrt/base.h>

#include "text_input_processor.hpp"
#include "text_input_processor_factory.hpp"

extern "C" {

/*
 * Required entry points for a COM DLL, mostly pulled from the docs.
 */
HRESULT __stdcall DllGetClassObject(GUID const &clsid, GUID const &iid,
                                    void **result) {
  try {
    *result = nullptr;

    if (clsid == vnime::TextInputProcessorGUID) {
      return winrt::make<vnime::TextInputProcessorFactory>()->QueryInterface(
          iid, result);
    }

    return winrt::hresult_class_not_available().to_abi();
  } catch (...) {
    return winrt::to_hresult();
  }
}

HRESULT __stdcall DllCanUnloadNow() {
  if (winrt::get_module_lock()) {
    return S_FALSE;
  }

  winrt::clear_factory_cache();
  return S_OK;
}
}
