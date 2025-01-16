#include <win32x.h>

struct Ctx
{
    bool is_running{ true };
};

static LRESULT WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
    auto ctx{ reinterpret_cast<Ctx*>(GetWindowLongPtr(hwnd, GWLP_USERDATA)) };

    LRESULT result{};
    switch (msg)
    {
    case WM_CREATE:
    {
        auto create{ reinterpret_cast<CREATESTRUCT*>(lparam) };
        auto p{ static_cast<Ctx*>(create->lpCreateParams) };
        SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(p));
        result = DefWindowProc(hwnd, msg, wparam, lparam);
    } break;
    case WM_CLOSE:
    {
        ctx->is_running = false;
        DefWindowProc(hwnd, msg, wparam, lparam);
    } break;
    default: { result = DefWindowProc(hwnd, msg, wparam, lparam); } break;
    }
    return result;
}

int main()
{
    Ctx ctx{};

    WNDCLASSEX window_class_desc{};
    window_class_desc.cbSize = sizeof(window_class_desc);
    window_class_desc.style = CS_HREDRAW | CS_VREDRAW;
    window_class_desc.lpfnWndProc = WindowProc;
    window_class_desc.cbClsExtra = 0;
    window_class_desc.cbWndExtra = 0;
    window_class_desc.hInstance = GetModuleHandle(nullptr);
    window_class_desc.hIcon = LoadIcon(GetModuleHandle(nullptr), IDI_APPLICATION);
    window_class_desc.hCursor = LoadCursor(GetModuleHandle(nullptr), IDC_ARROW);
    //window_class_desc.hbrBackground = ;
    window_class_desc.lpszMenuName = nullptr;
    window_class_desc.lpszClassName = L"my_window_class";
    window_class_desc.hIconSm = LoadIcon(GetModuleHandle(nullptr), IDI_APPLICATION);
    win32x::WindowClass window_class{ &window_class_desc, GetModuleHandle(nullptr) };
    win32x::Rect window_rect{ CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT + 1280, CW_USEDEFAULT + 720 };
    win32x::WindowHandle window_handle
    {
        0, L"my_window_class", L"My Window", WS_OVERLAPPEDWINDOW | WS_VISIBLE, window_rect, nullptr, nullptr, GetModuleHandle(nullptr),& ctx
    };
    window_handle.Show(SW_SHOW);

    while (ctx.is_running)
    {
        win32x::ExecuteMessagePump();
    }

    return 0;
}
