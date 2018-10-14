cmake_minimum_required(VERSION 3.11.1)

# TODO: Is a COM DLL 'SHARED' or 'MODULE'?
add_library(vnime SHARED)
target_compile_definitions(vnime PRIVATE UNICODE _UNICODE)

# PCH support: https://stackoverflow.com/a/3211026
target_sources(vnime PRIVATE pch.hpp pch.cpp)
target_compile_options(vnime PRIVATE "/Yupch.hpp")
set_source_files_properties(pch.cpp PROPERTIES COMPILE_OPTIONS "/Ycpch.hpp")

# Enable C++/WinRT
# https://docs.microsoft.com/en-us/windows/uwp/cpp-and-winrt-apis/intro-to-using-cpp-with-winrt
set_target_properties(vnime PROPERTIES VS_GLOBAL_CppWinRTEnabled "true" CXX_STANDARD 17)
target_link_libraries(vnime PRIVATE runtimeobject)

# DLL entry points
target_sources(vnime PRIVATE dll_main.cpp dll_registration.cpp dll_com.cpp)
target_sources(vnime PRIVATE registration_helpers.hpp registration_helpers.cpp)
target_sources(vnime PRIVATE vnime.def)

# Classes
target_sources(vnime PRIVATE text_input_processor.hpp text_input_processor.cpp)
target_sources(vnime PRIVATE text_input_processor_factory.hpp text_input_processor_factory.cpp)