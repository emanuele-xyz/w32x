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

    WindowHandle::WindowHandle(DWORD stylex, cstr clss, cstr title, DWORD style, Rect rect, HWND parent, HMENU menu, HINSTANCE inst, void* p)
        : m_hwnd{}
    {
        LONG x{ rect.left };
        LONG y{ rect.top };
        LONG w{ rect.right - rect.left };
        LONG h{ rect.bottom - rect.top };
        win32x_Check(m_hwnd = CreateWindowEx(stylex, clss, title, style, x, y, w, h, parent, menu, inst, p));
    }
    WindowHandle::~WindowHandle()
    {
        DestroyWindow(m_hwnd);
    }
    Rect WindowHandle::GetClientRect() const
    {
        Rect rect{};
        win32x_CheckHR(::GetClientRect(m_hwnd, &rect));
        return rect;
    }

    void ExecuteMessagePump() noexcept
    {
        MSG msg{};
        while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }
}
