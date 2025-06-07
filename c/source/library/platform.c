#include "platform.h"

#ifdef _WIN32
    #define WINDOWS
    #include <windows.h>
#else
    #error
#endif

#define print(format, ...) do { char _buffer[1024]; string_format_string(_buffer, sizeof(_buffer), format, __VA_ARGS__); platform_write_console(_buffer, (u32)string_length(_buffer)); } while(0)
#define log(format, ...) print(format, __VA_ARGS__)
PLATFORM_API bool platform_write_console(void *buffer, u32 buffer_size);
#include "string.c"

PLATFORM_API bool platform_write_console(void *buffer, u32 buffer_size)
{
    bool error = 0;
    HANDLE output_console_handle = 0;

    output_console_handle = GetStdHandle(STD_OUTPUT_HANDLE);

    if(!output_console_handle)
    {
        log("GetStdHandle function failed: %X\n", GetLastError());
        return error;
    }
    else if(output_console_handle == INVALID_HANDLE_VALUE)
    {
        log("GetStdHandle function failed: %X\n", GetLastError());
        return error;
    }

    if(!WriteConsoleA(output_console_handle, buffer, buffer_size, 0, 0))
    {
        log("WriteConsoleA function failed: %X\n", GetLastError());
        return error;
    }

    return 1;
}