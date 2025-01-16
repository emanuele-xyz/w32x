#include <win32x.h>

int main()
{
    WNDCLASSEX window_class_desc{};
    window_class_desc.cbSize = sizeof(window_class_desc);
    window_class_desc.style = CS_HREDRAW | CS_VREDRAW;
    window_class_desc.lpfnWndProc = DefWindowProc;
    //window_class_desc.cbClsExtra = ;
    //window_class_desc.cbWndExtra = ;
    window_class_desc.hInstance = GetModuleHandle(nullptr);
    window_class_desc.hIcon = LoadIcon(GetModuleHandle(nullptr), IDI_APPLICATION);
    window_class_desc.hCursor = LoadCursor(GetModuleHandle(nullptr), IDC_ARROW);
    //window_class_desc.hbrBackground = ;
    //window_class_desc.lpszMenuName = ;
    window_class_desc.lpszClassName = L"my_window_class";
    window_class_desc.hIconSm = LoadIcon(GetModuleHandle(nullptr), IDI_APPLICATION);
    win32x::WindowClass window_class{ &window_class_desc, GetModuleHandle(nullptr) };
    win32x::WindowHandle window_handle
    { 
        WS_EX_OVERLAPPEDWINDOW, L"my_window_class", L"My Window", WS_OVERLAPPED, 300, 300, 1280, 720, nullptr, nullptr, GetModuleHandle(nullptr), nullptr
    };

    return 0;
}
