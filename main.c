#include <windows.h>

#include "color_palettes.h"

LRESULT CALLBACK process_window
(
    HWND handle_window,
    UINT message_code,
    WPARAM parameter_w,
    LPARAM parameter_l
)
{
    switch (message_code)
    {
        case WM_NCHITTEST:
            POINT mouse_coordinates = {0};
            mouse_coordinates.x = LOWORD(parameter_l);
            mouse_coordinates.y = HIWORD(parameter_l);

            ScreenToClient(handle_window, &mouse_coordinates);

            if (mouse_coordinates.y < 40)
                return HTCAPTION;

            return HTCLIENT;

        case WM_PAINT:
            PAINTSTRUCT paint_struct;

            HDC handle_device_context = BeginPaint(handle_window, &paint_struct);

            // BG
            HBRUSH brush = CreateSolidBrush(COLOR_1);
            FillRect(handle_device_context, &paint_struct.rcPaint, brush);
            DeleteObject(brush);

            // Title Bar
            RECT title_bar = {0, 0, paint_struct.rcPaint.right, 40};
            HBRUSH title_brush = CreateSolidBrush(COLOR_2);
            FillRect(handle_device_context, &title_bar, title_brush);
            DeleteObject(title_brush);

            EndPaint(handle_window, &paint_struct);

            return 0;

        case WM_CLOSE:
            PostQuitMessage(0);
            return 0;

        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
    }

    return DefWindowProc(handle_window, message_code, parameter_w, parameter_l);
}

int create_window
(
    int window_init_position_x,
    int window_init_position_y,
    int window_init_width,
    int window_init_height
)
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

    ATOM register_class_return = RegisterClassEx(
        &window_class
    );

    if (register_class_return == 0) {
        return 0;
    }

    HWND window_handle = CreateWindowEx(
        0,
        class_name,
        window_title,
        WS_POPUP,
        window_init_position_x,
        window_init_position_y,
        window_init_width,
        window_init_height,
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

int main() {
    create_window(100, 100, 1280, 720);
}