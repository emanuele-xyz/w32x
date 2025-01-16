#include <win32x.h>

namespace win32x
{
    WindowClass::WindowClass(const WNDCLASSEX* desc, HINSTANCE inst)
        : m_name{ desc->lpszClassName }
        , m_inst{ inst }
    {
        win32x_Check(RegisterClassEx(desc));
    }
    WindowClass::~WindowClass() noexcept
    {
        UnregisterClass(m_name, m_inst);
    }

    WindowHandle::WindowHandle(DWORD stylex, cstr clss, cstr title, DWORD style, int x, int y, int w, int h, HWND parent, HMENU menu, HINSTANCE inst, void* p)
        : m_hwnd{}
    {
        #pragma warning(push)
        #pragma warning(disable : 4311)
        #pragma warning(disable : 4302)
        win32x_Check(m_hwnd = CreateWindowEx(stylex, clss, title, style, x, y, w, h, parent, menu, inst, p));
        #pragma warning(pop)
    }
    WindowHandle::~WindowHandle()
    {
        DestroyWindow(m_hwnd);
    }
    RECT WindowHandle::GetClientRect() const
    {
        RECT rect{};
        win32x_Check(::GetClientRect(m_hwnd, &rect));
        return rect;
    }
}
