#include <windows.h>

LRESULT CALLBACK window_processing
(
    HWND handle_window,                         // HWND             hwnd
    UINT message_code,                          // UINT             uMsg
    WPARAM parameter_w,                         // WPARAM           wParam
    LPARAM parameter_l                          // LPARAM           lParam
)
{
    switch (message_code)
    {
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
    }

    return DefWindowProc
    (
        handle_window,                          // HWND             hwnd
        message_code,                           // UINT             Msg
        parameter_w,                            // WPARAM           wParam
        parameter_l                             // LPARAM           lParam
    );
}

int WINAPI WinMain
(
    HINSTANCE handle_instance,                  // HINSTANCE        hInstance
    HINSTANCE handle_previous_instance,         // HINSTANCE        hPrevInstance
    PSTR command_line_arguments,                // LPSTR            lpCmdLine
    int flag_window_display_mode                // int              nShowCmd
)
{
    const char class_name[] = "WindowClass";
    const char window_title[] = "My Window in C";

    WNDCLASSEX window_class = {
        sizeof(WNDCLASSEX),                     // UINT             cbSize
        0,                                      // UINT             style
        window_processing,                      // WNDPROC          lpfnWndProc
        0,                                      // int              cbClsExtra
        0,                                      // int              cbWndExtra
        handle_instance,                        // HINSTANCE        hInstance
        0,                                      // HICON            hIcon
        0,                                      // HCURSOR          hCursor
        0,                                      // HBRUSH           hbrBackground
        0,                                      // LPCSTR           lpszMenuName
        class_name,                             // LPCSTR           lpszClassName
        0                                       // HICON            hIconSm
    };

    ATOM register_class_return = RegisterClassEx
    (
        &window_class                           // const WNDCLASSEXA        *unnamedParam1
    );

    if (register_class_return == 0)
    {
        return 0;
    }

    HWND window_handle = CreateWindowEx
    (
        0,                                      // DWORD            dwExStyle
        class_name,                             // LPCSTR           lpClassName
        window_title,                           // LPCSTR           lpWindowName
        WS_OVERLAPPEDWINDOW,                    // DWORD            dwStyle
        CW_USEDEFAULT,                          // int              X
        CW_USEDEFAULT,                          // int              Y
        CW_USEDEFAULT,                          // int              nWidth
        CW_USEDEFAULT,                          // int              nHeight
        NULL,                                   // HWND             hWndParent
        NULL,                                   // HMENU            hMenu
        handle_instance,                        // HINSTANCE        hInstance
        NULL                                    // LPVOID           lpParam
    );

    if (window_handle == NULL)
    {
        return 0;
    }

    ShowWindow
    (
        window_handle,                          // HWND             hWnd
        SW_SHOW                                 // int              nCmdShow
    );

    UpdateWindow
    (
        window_handle                           // HWND             hWnd
    );

    MSG message = {0};

    while (
        GetMessage(
            &message,                           // LPMSG            lpMsg
            NULL,                               // HWND             hWnd
            0,                                  // UINT             wMsgFilterMin
            0                                   // UINT             wMsgFilterMax
        )
    )
    {
        TranslateMessage(&message);
        DispatchMessage(&message);
    }

    return 0;
}
