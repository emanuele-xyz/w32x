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
}
