#include "pch.hpp"

#include "text_input_processor.hpp"

using namespace vnime;

namespace {
namespace VI_VN_TELEX {
// UUID from https://www.uuidgenerator.net/
static constexpr GUID profileId // c0eeee73-9753-4202-92a6-8f6cc6e98783
    {0xc0eeee73,
     0x9753,
     0x4202,
     {0x92, 0xa6, 0x8f, 0x6c, 0xc6, 0xe9, 0x87, 0x83}};

static constexpr auto description{L"TELEX Keyboard"};
static const auto description_len{static_cast<ULONG>(wcslen(description))};
} // namespace VI_VN_TELEX
} // namespace

HRESULT TextInputProcessor::Activate(ITfThreadMgr *pThreadMgr,
                                     TfClientId clientId) noexcept {
  return S_OK;
}

HRESULT TextInputProcessor::Deactivate() noexcept { return S_OK; }

void TextInputProcessor::register_with_TSF() {
	winrt::com_ptr<ITfCategoryMgr> pCategoryMgr{};
	winrt::check_hresult(
		CoCreateInstance(CLSID_TF_CategoryMgr, nullptr, CLSCTX_INPROC_SERVER,
			IID_ITfCategoryMgr, pCategoryMgr.put_void()));

	// Keyboard
	winrt::check_hresult(pCategoryMgr->RegisterCategory(TextInputProcessorGUID, GUID_TFCAT_TIP_KEYBOARD, TextInputProcessorGUID));

	//TODO: UILess winrt::check_hresult(pCategoryMgr->RegisterCategory(TextInputProcessorGUID, GUID_TFCAT_TIPCAP_UIELEMENTENABLED, TextInputProcessorGUID));
	// No plans to use COM in the code itself, ensures game-compatibility
	winrt::check_hresult(pCategoryMgr->RegisterCategory(TextInputProcessorGUID, GUID_TFCAT_TIPCAP_COMLESS, TextInputProcessorGUID));
	
	winrt::com_ptr<ITfInputProcessorProfileMgr> pInputProcessProfileMgr{};
  // TODO: I don't know if there's a C++/WinRT version of this?
  winrt::check_hresult(CoCreateInstance(
      CLSID_TF_InputProcessorProfiles, nullptr, CLSCTX_INPROC_SERVER,
      IID_ITfInputProcessorProfileMgr, pInputProcessProfileMgr.put_void()));

  winrt::check_hresult(pInputProcessProfileMgr->RegisterProfile(
      TextInputProcessorGUID,
      MAKELANGID(LANG_VIETNAMESE, SUBLANG_VIETNAMESE_VIETNAM),
      VI_VN_TELEX::profileId, VI_VN_TELEX::description,
      VI_VN_TELEX::description_len, L"", 0, 0, nullptr, 0, TRUE, 0));

}

void TextInputProcessor::unregister_from_TSF() {
  winrt::com_ptr<ITfInputProcessorProfileMgr> pInputProcessProfileMgr{};
  // TODO: I don't know if there's a C++/WinRT version of this?
  winrt::check_hresult(CoCreateInstance(
      CLSID_TF_InputProcessorProfiles, nullptr, CLSCTX_INPROC_SERVER,
      IID_ITfInputProcessorProfileMgr, pInputProcessProfileMgr.put_void()));

  winrt::check_hresult(pInputProcessProfileMgr->UnregisterProfile(
      TextInputProcessorGUID,
      MAKELANGID(LANG_VIETNAMESE, SUBLANG_VIETNAMESE_VIETNAM),
      VI_VN_TELEX::profileId, 0));

  winrt::com_ptr<ITfCategoryMgr> pCategoryMgr{};
  winrt::check_hresult(
	  CoCreateInstance(CLSID_TF_CategoryMgr, nullptr, CLSCTX_INPROC_SERVER,
		  IID_ITfCategoryMgr, pCategoryMgr.put_void()));

  // Keyboard
  winrt::check_hresult(pCategoryMgr->UnregisterCategory(TextInputProcessorGUID, GUID_TFCAT_TIP_KEYBOARD, TextInputProcessorGUID));

  //TODO: UILess winrt::check_hresult(pCategoryMgr->UnregisterCategory(TextInputProcessorGUID, GUID_TFCAT_TIPCAP_UIELEMENTENABLED, TextInputProcessorGUID));
  // No plans to use COM in the code itself, ensures game-compatibility
  winrt::check_hresult(pCategoryMgr->UnregisterCategory(TextInputProcessorGUID, GUID_TFCAT_TIPCAP_COMLESS, TextInputProcessorGUID));

}
