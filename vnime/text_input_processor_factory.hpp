#include <winrt/base.h>

namespace vnime {

// UUID from https://www.uuidgenerator.net/
struct __declspec(uuid("2219d3e5-1717-4026-aeb6-aea050f1379b"))
    TextInputProcessorFactory
    : public winrt::implements<TextInputProcessorFactory, IClassFactory> {
  HRESULT __stdcall CreateInstance(IUnknown *pOuter, IID const &iid,
                                   void **ppObject) noexcept override;

  HRESULT __stdcall LockServer(BOOL fLock) noexcept override;
};

}; // namespace vnime
