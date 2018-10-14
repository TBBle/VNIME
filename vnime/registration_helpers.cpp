#include "pch.hpp"

#include <winrt/base.h>

// Some helpers copied from or based on code on
// https://docs.microsoft.com/en-us/windows/uwp/cpp-and-winrt-apis/author-coclasses

namespace {
struct registry_traits {
  using type = HKEY;

  static void close(type value) noexcept {
    WINRT_VERIFY_(ERROR_SUCCESS, ::RegCloseKey(value));
  }

  static constexpr type invalid() noexcept { return nullptr; }
};

using registry_key = winrt::handle_type<registry_traits>;

// Modified to get the DLL we're in, not the exe that loaded it.
std::wstring get_module_path() {
  std::wstring path(100, L'?');
  uint32_t path_size{};
  DWORD actual_size{};
  HMODULE module{};
  if (!::GetModuleHandleEx(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS |
                               GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT,
                           reinterpret_cast<wchar_t *>(&get_module_path),
                           &module)) {
    winrt::throw_last_error();
  }

  do {
    path_size = static_cast<uint32_t>(path.size());
    actual_size = ::GetModuleFileName(module, path.data(), path_size);

    if (actual_size + 1 > path_size) {
      path.resize(path_size * 2, L'?');
    }
  } while (actual_size + 1 > path_size);

  path.resize(actual_size);
  return path;
}

// Helpers based on the above-mentioned page
void set_registry_key(HKEY root, const std::wstring &subKey,
                      const std::wstring &value) {
  registry_key key;
  winrt::check_win32(::RegCreateKeyEx(root, subKey.c_str(), 0, nullptr, 0,
                                      KEY_WRITE, nullptr, key.put(), nullptr));

  auto result = ::RegDeleteValue(key.get(), nullptr);
  if (result != ERROR_FILE_NOT_FOUND) {
    winrt::check_win32(result);
  }

  const auto pValue = reinterpret_cast<const BYTE *>(value.c_str());
  // pValueBytes includes the null pointer.
  const auto pValueBytes =
      static_cast<uint32_t>((value.size() + 1) * sizeof(wchar_t));

  winrt::check_win32(
      ::RegSetValueEx(key.get(), nullptr, 0, REG_SZ, pValue, pValueBytes));
}

void delete_registry_key(HKEY root, const std::wstring &subKey) {
  auto result = ::RegDeleteKey(root, subKey.c_str());
  if (result != ERROR_FILE_NOT_FOUND) {
    winrt::check_win32(result);
  }
}

std::wstring guid_to_string(const GUID guid) {
  // This is awful, but straight from the docs.
  auto clsidStr = std::wstring{L"{????????-????-????-????-????????????}"};
  const auto clsidLen = ::StringFromGUID2(
      guid, clsidStr.data(), static_cast<int>(clsidStr.length() + 1));
  if (clsidLen != clsidStr.length() + 1) {
    winrt::throw_hresult(E_FAIL);
  }
  return clsidStr;
}
} // namespace

void register_as_inproc_server(const GUID clsid,
                               const std::wstring &description,
                               const std::wstring & /*progID*/) {
  // Registration requirements, cadged from Registry.cpp on
  // https://www.codeguru.com/cpp/com-tech/activex/tutorials/article.php/c5567/Step-by-Step-COM-Tutorial.htm
  // HKEY_CLASSES_ROOT\\clsid\\{StringFromCLSID(guid)}: {description}
  // HKEY_CLASSES_ROOT\\clsid\\{StringFromCLSID(guid)}\\InprocServer32:
  // {get_module_path()}
  // HKEY_CLASSES_ROOT\\clsid\\{StringFromCLSID(guid)}\\ProgId: {progID}
  // HKEY_CLASSES_ROOT\\{progID}: {description}
  // HKEY_CLASSES_ROOT\\{progID}\\CLSID: {StringFromCLSID(guid)}
  // TODO: Do I actually need the progID?

  const auto clsidStr = guid_to_string(clsid);
  const auto clsidKeyPath = LR"(clsid\)" + clsidStr;
  set_registry_key(HKEY_CLASSES_ROOT, clsidKeyPath, description);
  set_registry_key(HKEY_CLASSES_ROOT, clsidKeyPath + LR"(\InprocServer32)",
                   get_module_path());
  //  set_registry_key(HKEY_CLASSES_ROOT, clsidKeyPath + LR"(\ProgId)", progID);
  //  set_registry_key(HKEY_CLASSES_ROOT, progID, description);
  //  set_registry_key(HKEY_CLASSES_ROOT, progID + LR"(\CLSID)", clsidStr);
}

void unregister_as_inproc_server(const GUID clsid,
                                 const std::wstring & /*progID*/) {
  const auto clsidStr = guid_to_string(clsid);
  const auto clsidKeyPath = LR"(clsid\)" + clsidStr;
  delete_registry_key(HKEY_CLASSES_ROOT, clsidKeyPath + LR"(\InprocServer32)");
  //  delete_registry_key(HKEY_CLASSES_ROOT, clsidKeyPath + LR"(\ProgId)");
  delete_registry_key(HKEY_CLASSES_ROOT, clsidKeyPath);
  //  delete_registry_key(HKEY_CLASSES_ROOT, progID + LR"(\CLSID)");
  //  delete_registry_key(HKEY_CLASSES_ROOT, progID);
}
