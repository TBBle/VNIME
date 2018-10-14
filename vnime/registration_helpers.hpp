#include <string>

#include <winrt/base.h>

void register_as_inproc_server(const GUID guid, const std::wstring &description,
                               const std::wstring &progID);

void unregister_as_inproc_server(const GUID guid, const std::wstring &progID);
