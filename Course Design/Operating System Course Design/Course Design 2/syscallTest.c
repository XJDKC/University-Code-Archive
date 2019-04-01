#include <stdio.h>
#include <linux/kernel.h>
#include <sys/syscall.h>
#include <unistd.h>

int main()
{
    long a = syscall(1023,"in.txt","out.txt");
    printf("%ld", a);
    return 0;
}