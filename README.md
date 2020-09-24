Obsolete Project
================

Windows 10 1903 [introduced TELEX support to the built-in Vietnamese IME](https://answers.microsoft.com/en-us/windows/forum/all/telex-mode-for-vietnamese-keyboard-on-windows-10/744d4c2d-6d17-421e-ace0-d75e7ea7092d), so this project is now archived.

It might be useful as a partial reference for anyone trying to work with one of the technologies (WinRT/C++ with CMake, or Text Services Framework).

VNIME - Vietnamese IME for Windows
==================================

Since early in my Vietnamese studies, the following things have bugged me:
* The most-common Vietnamese IME, [UniKey](https://unikey.vn/vietnam/)
** runs as a separate application instead of a Windows IME
** needs [special effort](https://www.unikey.org/en/autostart-admin.html) to work in Admin-level applications
** is closed source, although [older versions](https://www.unikey.org/en/source.html) area available under the GPL
* The MS Windows built-in IME only supports [a Windows-specific variant of VNI](http://winvnkey.sourceforge.net/download-winvnkey-and-type-vietnamese.htm#Typing_method_Microsoft) instead of the default-on-all-other-platforms [TELEX](http://winvnkey.sourceforge.net/download-winvnkey-and-type-vietnamese.htm#Typing_method_Telex)

This project is my attempt to create a simple, UI-less TELEX IME for Windows, using the Windows [Text Services Framework](https://docs.microsoft.com/en-us/windows/desktop/tsf/text-services-framework).

It's also my chance to play with the modern projection of the Windows API, [C++/WinRT](https://docs.microsoft.com/en-us/windows/uwp/cpp-and-winrt-apis/intro-to-using-cpp-with-winrt).

References
==========

Text Services Framework
-----------------------
* [Text Services Framework](https://docs.microsoft.com/en-us/windows/desktop/tsf/text-services-framework) -- The modern framework for accessing and implementing text input in Windows.
** [TSF Aware](https://blogs.msdn.microsoft.com/tsfaware/) -- Blog post series about TSF from 2007 to 2013
* [libIME](https://github.com/EasyIME/libIME) -- A wrapper library for TSF APIs for easier access
* [PIME](https://github.com/EasyIME/PIME) and [windows-chewing-tsf](https://github.com/chewing/windows-chewing-tsf) -- Uses of libIME

C++/WinRT
---------
* [Introduction to C++/WinRT](https://docs.microsoft.com/en-us/windows/uwp/cpp-and-winrt-apis/intro-to-using-cpp-with-winrt)
* [Author COM components with C++/WinRT](https://docs.microsoft.com/en-au/windows/uwp/cpp-and-winrt-apis/author-coclasses)
