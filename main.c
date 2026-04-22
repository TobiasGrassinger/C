#include <windows.h>
#include <windowsx.h>

#include "color_palettes.h"

const int TITLEBAR_HEIGHT = 40;

const int CLOSE_BUTTON_WIDTH = 50;
const int CLOSE_BUTTON_HEIGHT = 20;
const int CLOSE_BUTTON_PADDING = 10;

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
        case WM_ERASEBKGND:
        {
            return 1;
        }

        case WM_NCHITTEST:
        {
            POINT mouse_coordinates;
            mouse_coordinates.x = GET_X_LPARAM(parameter_l);
            mouse_coordinates.y = GET_Y_LPARAM(parameter_l);
            ScreenToClient(handle_window, &mouse_coordinates);

            RECT window_rect;
            GetClientRect(handle_window, &window_rect);

            RECT close_button;
            close_button.left = window_rect.right - CLOSE_BUTTON_WIDTH - CLOSE_BUTTON_PADDING;
            close_button.top = CLOSE_BUTTON_PADDING;
            close_button.right = window_rect.right - CLOSE_BUTTON_PADDING;
            close_button.bottom = TITLEBAR_HEIGHT - CLOSE_BUTTON_PADDING;

            if (PtInRect(&close_button, mouse_coordinates))
                return HTCLIENT;

            if (mouse_coordinates.y < TITLEBAR_HEIGHT)
                return HTCAPTION;

            return HTCLIENT;
        }

        case WM_LBUTTONDOWN:
        {
            POINT mouse_coordinates;
            mouse_coordinates.x = GET_X_LPARAM(parameter_l);
            mouse_coordinates.y = GET_Y_LPARAM(parameter_l);

            RECT window_rect;
            GetClientRect(handle_window, &window_rect);

            RECT close_button;
            close_button.left = window_rect.right - CLOSE_BUTTON_WIDTH - CLOSE_BUTTON_PADDING;
            close_button.top = CLOSE_BUTTON_PADDING;
            close_button.right = window_rect.right - CLOSE_BUTTON_PADDING;
            close_button.bottom = TITLEBAR_HEIGHT - CLOSE_BUTTON_PADDING;

            if (PtInRect(&close_button, mouse_coordinates)) {
                PostQuitMessage(0);
            }

            return 0;
        }

        case WM_PAINT:
        {
            PAINTSTRUCT paint_struct;

            HDC handle_device_context = BeginPaint(handle_window, &paint_struct);

            // BG
            HBRUSH brush = CreateSolidBrush(COLOR_1);
            FillRect(handle_device_context, &paint_struct.rcPaint, brush);
            DeleteObject(brush);

            // Title Bar
            RECT title_bar;
            title_bar.left = 0;
            title_bar.top = 0;
            title_bar.right = paint_struct.rcPaint.right;
            title_bar.bottom = TITLEBAR_HEIGHT;

            HBRUSH title_brush = CreateSolidBrush(COLOR_2);
            FillRect(handle_device_context, &title_bar, title_brush);
            DeleteObject(title_brush);

            // Border
            RECT border = paint_struct.rcPaint;

            HBRUSH border_brush = CreateSolidBrush(COLOR_3);
            FrameRect(handle_device_context, &border, border_brush);
            DeleteObject(border_brush);

            //Close Button
            RECT close_button;
            close_button.left = paint_struct.rcPaint.right - CLOSE_BUTTON_WIDTH - CLOSE_BUTTON_PADDING;
            close_button.top = CLOSE_BUTTON_PADDING;
            close_button.right = paint_struct.rcPaint.right - CLOSE_BUTTON_PADDING;
            close_button.bottom = TITLEBAR_HEIGHT - CLOSE_BUTTON_PADDING;

            HBRUSH close_brush = CreateSolidBrush(COLOR_5);
            FillRect(handle_device_context, &close_button, close_brush);
            DeleteObject(close_brush);

            EndPaint(handle_window, &paint_struct);

            return 0;
        }

        case WM_CLOSE:
        {
            PostQuitMessage(0);
            return 0;
        }

        case WM_DESTROY:
        {
            PostQuitMessage(0);
            return 0;
        }
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