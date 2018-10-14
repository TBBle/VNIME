#include "pch.hpp"

#include "text_input_processor.hpp"
#include "text_input_processor_factory.hpp"

using namespace vnime;

// Straight from the C++/WinRT docs

HRESULT TextInputProcessorFactory::CreateInstance(IUnknown *pOuter, IID const &,
                                                  void **ppObject) noexcept {
  if (pOuter != nullptr) {
    return CLASS_E_NOAGGREGATION;
  }
  try {
    *ppObject = winrt::make<TextInputProcessor>().get();
    return S_OK;
  } catch (...) {
    return winrt::to_hresult();
  }
}

HRESULT TextInputProcessorFactory::LockServer(BOOL) noexcept { return S_OK; }
