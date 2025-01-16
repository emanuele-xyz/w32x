#pragma once

#pragma warning(push)
#pragma warning(disable : 5039)
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#pragma warning(pop)

#if defined(_DEBUG)
#define win32x_Check(p) do { if (!(p)) { __debugbreak(); } } while (false) 
#else
#define win32x_Check(p) do { if (!(p)) { throw ::win32x::CheckFail{__FILE__, __LINE__, #p}; } } while (false)
#endif

#if defined(_DEBUG)
#define win32x_CheckHR(result) do { if (auto __hres{ result }; !(SUCCEEDED(__hres))) { __debugbreak(); } } while (false) 
#else
#define win32x_CheckHR(result) do { if (auto __hres{ result }; !(SUCCEEDED(__hres))) throw ::win32x::CheckHRFail(__FILE__, __LINE__, __hres); } while (false)
#endif

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
    #pragma warning(disable : 4514)
    struct CheckFail
    {
        const char* file;
        int line;
        const char* p;
    };
    struct CheckHRFail
    {
        CheckHRFail(const char* file, int line, HRESULT result) : file{ file }, line{ line }, result{ result }, code{ GetLastError() } {}

        const char* file;
        int line;
        HRESULT result;
        DWORD code;
    };
    #pragma warning(pop)

    struct Rect : public RECT
    {
        inline Rect(LONG left, LONG top, LONG right, LONG bottom) : RECT{ left, top, right, bottom } {}
        inline Rect(LONG right, LONG bottom) : Rect{ 0, 0, right, bottom } {}
        inline Rect() : Rect{ 0, 0, 0, 0 } {}
    };

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
        WindowHandle(DWORD stylex, cstr clss, cstr title, DWORD style, Rect rect, HWND parent, HMENU menu, HINSTANCE inst, void* p);
        ~WindowHandle();
        WindowHandle(const WindowHandle&) = delete;
        WindowHandle(WindowHandle&&) noexcept = delete;
        WindowHandle& operator=(const WindowHandle&) = delete;
        WindowHandle& operator=(WindowHandle&&) noexcept = delete;
    public:
        inline HWND GetHWND() const noexcept { return m_hwnd; }
        void Show(int command) const { win32x_CheckHR(ShowWindow(m_hwnd, command)); }
        Rect GetClientRect() const;
    private:
        HWND m_hwnd;
    };

    void ExecuteMessagePump() noexcept;
}
