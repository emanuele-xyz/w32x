#pragma once

#pragma warning(push)
#pragma warning(disable : 5039)
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#pragma warning(pop)

#if defined(_DEBUG)
#define win32x_Crash(result) do { if (!(SUCCEEDED(result))) { __debugbreak(); } } while (false) 
#else
#define win32x_Crash(result) do { if (!(SUCCEEDED(result))) { throw ::win32x::Error(__FILE__, __LINE__, result, ::GetLastError()) } } while (true)
#endif

#define win32x_Check(p) win32x_Crash(p)

namespace win32x
{
    #if defined(UNICODE)
    using str = WCHAR*;
    using cstr = const WCHAR*;
    #else
    using str = char*;
    using cstr = const char*;
    #endif

    #pragma warning(push)
    #pragma warning(disable : 4820)
    struct Error
    {
        char* file;
        int line;
        HRESULT result;
        DWORD code;
    };
    #pragma warning(pop)

    class WindowClass
    {
    public:
        WindowClass(const WNDCLASSEX* desc, HINSTANCE inst);
        ~WindowClass() noexcept;
        WindowClass(const WindowClass&) = delete;
        WindowClass(WindowClass&&) noexcept = delete;
        WindowClass& operator=(const WindowClass&) = delete;
        WindowClass& operator=(WindowClass&&) noexcept = delete;
    private:
        cstr m_name;
        HINSTANCE m_inst;
    };

    class WindowHandle
    {
    public:
        WindowHandle(DWORD stylex, cstr clss, cstr title, DWORD style, int x, int y, int w, int h, HWND parent, HMENU menu, HINSTANCE inst, void* p);
        ~WindowHandle();
        WindowHandle(const WindowHandle&) = delete;
        WindowHandle(WindowHandle&&) noexcept = delete;
        WindowHandle& operator=(const WindowHandle&) = delete;
        WindowHandle& operator=(WindowHandle&&) noexcept = delete;
    public:
        #pragma warning(push)
        #pragma warning(disable : 4514)
        inline HWND GetHWND() const noexcept { return m_hwnd; }
        #pragma warning(pop)

        RECT GetClientRect() const;
    private:
        HWND m_hwnd;
    };
}
