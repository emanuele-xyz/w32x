#pragma once

#pragma warning(push, 0)
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
    #pragma warning(push, 0)
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
        WindowClass(const WNDCLASSEX* desc, HINSTANCE inst = GetModuleHandle(nullptr));
        ~WindowClass() noexcept;
        WindowClass(const WindowClass&) = delete;
        WindowClass(WindowClass&&) noexcept = delete;
        WindowClass& operator=(const WindowClass&) = delete;
        WindowClass& operator=(WindowClass&&) noexcept = delete;
    private:
        #if defined(UNICODE)
        const WCHAR* m_name;
        #else
        const char* m_name;
        #endif
        HINSTANCE m_inst;
    };
}
