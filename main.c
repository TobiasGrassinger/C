#include <windows.h>

LRESULT CALLBACK process_window
(
    HWND handle_window,
    UINT message_code,
    WPARAM parameter_w,
    LPARAM parameter_l
)
{
    LRESULT result = 0;

    switch (message_code)
    {
        default:
            result = DefWindowProc(handle_window, message_code, parameter_w, parameter_l);
        break;
    }

    return result;
}

int create_window()
{
    HINSTANCE handle_instance = GetModuleHandle(
        NULL
    );

    const char class_name[] = "WindowClass";
    const char window_title[] = "My Window in C";

    WNDCLASSEX window_class = {0};
    window_class.cbSize = sizeof(WNDCLASSEX);
    window_class.lpfnWndProc = process_window;
    window_class.hInstance = handle_instance;
    window_class.lpszClassName = class_name;

    ATOM register_class_return = RegisterClassEx(&window_class);

    if (register_class_return == 0) {
        return 0;
    }

    HWND window_handle = CreateWindowEx(
        0,
        class_name,
        window_title,
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        NULL,
        NULL,
        handle_instance,
        NULL
    );

    if (window_handle == NULL) {
        return 0;
    }

    ShowWindow(window_handle, SW_SHOW);
    UpdateWindow(window_handle);

    MSG message = {0};

    while (GetMessage(&message, NULL, 0, 0)) {
        TranslateMessage(&message);
        DispatchMessage(&message);
    }

    return 0;
}


int main(){
    create_window();
}