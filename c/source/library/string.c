#include "string.h"

typedef uptr *va_args;
#define STRING_VA_GET(argument, type) *(type *)string_va_get_argument(argument)
STRING_API sint string_format_string(char *buffer, uptr buffer_size, char *format, ...);

INTERNAL va_args string_va_initialize(void *format)
{
    va_args result = (va_args)format + 1;
    return result;
}

INTERNAL va_args string_va_finalize()
{
    va_args result = 0;
    return result;
}

INTERNAL void *string_va_get_argument(va_args *argument)
{
    void *result = (*argument)++;
    return result;
}

STRING_API uptr string_length(char *string)
{
    uptr result = 0;

    while(*string++ != '\0')
    {
        if(result == MAX_U64)
        {
            log("return value overflow\n");
            break;
        }

        result++;
    }

    return result;
}

STRING_API sint string_write_character(char *buffer, uptr buffer_size, int character)
{
    sint result = 0;

    if(buffer_size < (2 * sizeof(char)))
    {
        log("buffer_size is %llu\n", buffer_size);
        return result;
    }

    buffer[0] = (char)character;
    buffer[1] = '\0';

    return 1;
}

STRING_API sint string_write_string(char *buffer, uptr buffer_size, char *string, uptr length)
{
    sint result = 0;
    uptr i = 0;
    uptr max_length = 0;
    
    max_length = string_length(string);

    if(length > max_length)
    {
        log("string %s has length is greater than max_length\n", string);
        return result;
    }

    for(i = 0; i < length; i++)
    {
        result += string_write_character(buffer + i, buffer_size - i, string[i]);
    }

    return result;
}

STRING_API sint string_write_signed32(char *buffer, uptr buffer_size, s32 value, int base, char *representation)
{
    sint result = 0;
    bool is_negative = value < 0;
    char work_buffer[32] = {0};
    int work_buffer_index = ARRAY_COUNT(work_buffer) - 2;

    if(!value)
    {
        result = string_write_character(buffer, buffer_size, '0');
        return result;
    }

    if(is_negative)
    {
        value = -value;
    }

    for(; value; value /= base)
    {
        work_buffer[work_buffer_index--] = representation[value % base];
    }

    if(is_negative)
    {
        work_buffer[work_buffer_index] = '-';
    }
    else
    {
        work_buffer_index++;
    }

    result = string_write_string(buffer, buffer_size, work_buffer + work_buffer_index, string_length(work_buffer + work_buffer_index));
    return result;
}

STRING_API sint string_write_unsigned32(char *buffer, uptr buffer_size, u32 value, int base, char *representation)
{
    sint result = 0;
    char work_buffer[32] = {0};
    int work_buffer_index = ARRAY_COUNT(work_buffer) - 2;

    if(!value)
    {
        result = string_write_character(buffer, buffer_size, '0');
        return result;
    }

    for(; value; value /= base)
    {
        work_buffer[work_buffer_index--] = representation[value % base];
    }
    
    work_buffer_index++;

    result = string_write_string(buffer, buffer_size, work_buffer + work_buffer_index, string_length(work_buffer + work_buffer_index));
    return result;
}

STRING_API sint string_write_signed64(char *buffer, uptr buffer_size, s64 value, int base, char *representation)
{
    sint result = 0;
    bool is_negative = value < 0;
    char work_buffer[64] = {0};
    int work_buffer_index = ARRAY_COUNT(work_buffer) - 2;

    if(!value)
    {
        result = string_write_character(buffer, buffer_size, '0');
        return result;
    }

    if(is_negative)
    {
        value = -value;
    }

    for(; value; value /= base)
    {
        work_buffer[work_buffer_index--] = representation[value % base];
    }

    if(is_negative)
    {
        work_buffer[work_buffer_index] = '-';
    }
    else
    {
        work_buffer_index++;
    }

    result = string_write_string(buffer, buffer_size, work_buffer + work_buffer_index, string_length(work_buffer + work_buffer_index));
    return result;
}

STRING_API sint string_write_unsigned64(char *buffer, uptr buffer_size, u64 value, int base, char *representation)
{
    sint result = 0;
    char work_buffer[64] = {0};
    int work_buffer_index = ARRAY_COUNT(work_buffer) - 2;

    if(!value)
    {
        result = string_write_character(buffer, buffer_size, '0');
        return result;
    }

    for(; value; value /= base)
    {
        work_buffer[work_buffer_index--] = representation[value % base];
    }
    
    work_buffer_index++;

    result = string_write_string(buffer, buffer_size, work_buffer + work_buffer_index, string_length(work_buffer + work_buffer_index));
    return result;
}

STRING_API sint string_write_float64(char *buffer, uptr buffer_size, f64 value, int precision)
{
    sint result = 0;
    int i = 0;
    char *decimal = "0123456789";
    s32 integer_part = (int)value;
    result += string_write_signed32(buffer, buffer_size, integer_part, 10, decimal);
    result += string_write_character(buffer + result, buffer_size - result, '.');

    if(value < 0)
    {
        value = -value;
        integer_part = -integer_part;
    }

    value -= integer_part;

    for(i = 0; i < precision; i++)
    {
        value *= 10;
        integer_part = (int)value;
        result += string_write_signed32(buffer + result, buffer_size - result, integer_part, 10, decimal);
        value -= integer_part;
    }

    return result;
}

STRING_API sint string_format_string(char *buffer, uptr buffer_size, char *format, ...)
{
    sint result = 0;
    va_args argument = 0;
    char *c = format;
    char *octal = "01234567";
    char *decimal = "0123456789";
    char *hexadecimal_lowercase = "0123456789abcdef";
    char *hexadecimal_uppercase = "0123456789ABCDEF";

    argument = string_va_initialize(&format);

    while(*c != '\0')
    {
        if(*c != '%')
        {
            result += string_write_character(buffer + result, buffer_size - result, *c);
            c++;
            continue;
        }

        if(*++c == '%')
        {
            result += string_write_character(buffer + result, buffer_size - result, *c);
            c++;
        }
        else if(*c == 'c')
        {
            int value = STRING_VA_GET(&argument, int);
            result += string_write_character(buffer + result, buffer_size - result, value);
            c++;
        }
        else if((*c == 'd') || (*c == 'i'))
        {
            s32 value = STRING_VA_GET(&argument, s32);
            result += string_write_signed32(buffer + result, buffer_size - result, value, 10, decimal);
            c++;
        }
        else if(*c == 'f')
        {
            f64 value = STRING_VA_GET(&argument, f64);
            result += string_write_float64(buffer + result, buffer_size - result, value, 6);
            c++;
        }
        else if((c[0] == 'l') && (c[1] == 'l') && ((c[2] == 'd') || (c[2] == 'i')))
        {
            s64 value = STRING_VA_GET(&argument, s64);
            result += string_write_signed64(buffer + result, buffer_size - result, value, 10, decimal);
            c += 3;
        }
        else if((c[0] == 'l') && (c[1] == 'l') && (c[2] == 'u'))
        {
            u64 value = STRING_VA_GET(&argument, u64);
            result += string_write_unsigned64(buffer + result, buffer_size - result, value, 10, decimal);
            c += 3;
        }
        else if(*c == 'o')
        {
            u32 value = STRING_VA_GET(&argument, u32);
            result += string_write_unsigned32(buffer + result, buffer_size - result, value, 8, octal);
            c++;
        }
        else if(*c == 'p')
        {
            void *value = STRING_VA_GET(&argument, void *);
            result += string_write_unsigned64(buffer + result, buffer_size - result, (u64)value, 16, hexadecimal_lowercase);
            c++;
        }
        else if(*c == 's')
        {
            char *value = STRING_VA_GET(&argument, char *);
            result += string_write_string(buffer + result, buffer_size - result, value, string_length(value));
            c++;
        }
        else if(*c == 'u')
        {
            u32 value = STRING_VA_GET(&argument, u32);
            result += string_write_unsigned32(buffer + result, buffer_size - result, value, 10, decimal);
            c++;
        }
        else if((*c == 'x') || (*c == 'X'))
        {
            u32 value = STRING_VA_GET(&argument, u32);
            
            if(*c == 'x')
            {
                result += string_write_unsigned32(buffer + result, buffer_size - result, value, 16, hexadecimal_lowercase);
            }
            else
            {
                result += string_write_unsigned32(buffer + result, buffer_size - result, value, 16, hexadecimal_uppercase);
            }

            c++;
        }
        else
        {
            log("Invalid format specifier: %c\n", *c);
            break;
        }
    }

    argument = string_va_finalize();

    return result;
}