#include "chip8.h"

int main(int argument_count, char **argument)
{
    print("%% Hello, world! %%\n");
    print("%% Hello, world! %%\n");
    print("%% Hello, world! %%\n");

    print("%c %c %c\n", 'A', 'B', 'C');
    print("%c %c %c\n", 'A', 'B', 'C');
    print("%c %c %c\n", 'A', 'B', 'C');

    print("%d %i %d\n", 0, -1, 1234);
    print("%d %i %d\n", 0, -1, 1234);
    print("%d %i %d\n", 0, -1, 1234);

    print("%f %f %f\n", 0.0, -1.0, 1.234);
    print("%f %f %f\n", 0.0, -1.0, 1.234);
    print("%f %f %f\n", 0.0, -1.0, 1.234);
    
    print("%lld %lli\n", MAX_S64, MAX_S64);
    print("%lld %lli\n", MAX_S64, MAX_S64);
    print("%lld %lli\n", MAX_S64, MAX_S64);

    print("%llu\n", MAX_U64);
    print("%llu\n", MAX_U64);
    print("%llu\n", MAX_U64);

    print("%o %o %o\n", 0, 8, 16);
    print("%o %o %o\n", 0, 8, 16);
    print("%o %o %o\n", 0, 8, 16);

    print("%p %p %p\n", 0, main, argument);
    print("%p %p %p\n", 0, main, argument);
    print("%p %p %p\n", 0, main, argument);

    print("%s %s %s\n", "ABC", "DEF", "GHI");
    print("%s %s %s\n", "ABC", "DEF", "GHI");
    print("%s %s %s\n", "ABC", "DEF", "GHI");

    print("%u %u %u\n", 0, -1, 1234);
    print("%u %u %u\n", 0, -1, 1234);
    print("%u %u %u\n", 0, -1, 1234);

    print("%x %X %x\n", 0, -1, 255);
    print("%x %X %x\n", 0, -1, 255);
    print("%x %X %x\n", 0, -1, 255);

    return 0;
}