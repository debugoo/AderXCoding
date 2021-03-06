#include <stdio.h>
#include <stdlib.h>
//#include <avr/io.h>



char* my_memory(char *dest, const char *src, unsigned int n)
{

    void* _ret = dest;

    __asm__("cld;rep;movsb"
            ::"D"((void *)(_ret)),
              "S"((void *)(src)),
              "c"((n)));
    return _ret;
}


void* MyMemcpy(void* dest, const void* src, unsigned int n)
{
    char* d = (char*)dest;
    const char* s = (const char*)src;
    char* ret = d;

    while(n--)
    {
        *d++ = *s++;
    }
    return ret;
}



// 位于 /arch/x86/boot/compressed/misc.c
void *memcpy(void *dest, const void *src, size_t n)
{
    int d0, d1, d2;

    asm volatile(
        "rep ; movsl\n\t"
        "movl %4,%%ecx\n\t"
        "rep ; movsb\n\t"
        : "=&c" (d0), "=&D" (d1), "=&S" (d2)
        : "0" (n >> 2), "g" (n & 3), "1" (dest), "2" (src)
        : "memory");

    return dest;
}


int main(void)
{
    char test1[] = "yuzhihui";
    char test2[1024] = {};
    char test3[1024] = {};

    my_memory(test2, test1, sizeof(test1));
    MyMemcpy(test3, test1, sizeof(test1));

    printf("test1:%s\n", test1);
    printf("test2:%s\n", test2);
    printf("test3:%s\n", test3);

    int t1 = 100;
    int t2 = 0;
    int t3 = 0;

    my_memory(&t2, &t1, sizeof(t1));
    MyMemcpy(&t3, &t1, sizeof(t1));

    printf("t1:%d\n", t1);
    printf("t2:%d\n", t2);
    printf("t3:%d\n", t3);

    return 0;
}
