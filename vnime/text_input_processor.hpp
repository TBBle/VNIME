#include <msctf.h>
#include <winrt/base.h>

namespace vnime {

// UUID from https://www.uuidgenerator.net/
static constexpr GUID
    TextInputProcessorGUID // d99ae7e4-47ab-4da5-ad8c-b0f008c770c5
    {0xd99ae7e4,
     0x47ab,
     0x4da5,
     {0xad, 0x8c, 0xb0, 0xf0, 0x08, 0xc7, 0x70, 0xc5}};

// https://docs.microsoft.com/en-au/windows/desktop/com/-progid--key#remarks
static const std::wstring TextInputProcessorProgID{L"TBBle.vnime.0"};

struct TextInputProcessor
    : public winrt::implements<TextInputProcessor, ITfTextInputProcessor> {

  // ITfTextInputProcessor
  HRESULT __stdcall Activate(ITfThreadMgr *pThreadMgr,
                             TfClientId clientId) noexcept override;
  HRESULT __stdcall Deactivate() noexcept override;

  // Static registration API
  static void register_with_TSF();
  static void unregister_from_TSF();
};
}; // namespace vnime
