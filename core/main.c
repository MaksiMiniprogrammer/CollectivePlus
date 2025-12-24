#include <stdio.h>
#include <core/cli.h>

int main(int argc, char *argv[]) 
{
    printf("result: %d\n", check_args(argc, argv));
    return 0;
}