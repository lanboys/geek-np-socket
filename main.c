#include <stdio.h>
#include <unistd.h>
#include <sys/errno.h>


int main() {
    char b[] = "lemon";//创建于栈区
    char *q = b;//等同于 char *q=&b[0]
    char *qq = &b[1];

    printf("sizeof(b)=%d  strlen(b)=%d\n", sizeof(b), strlen(b));// 6  5

    printf("q1=%p\n", q);//输出16进制地址值
    printf("q2=%d\n", q);//输出10进制形式的地址值
    printf("q3=%s\n", q);//输出字符串
    printf("q4=%c\n", *q);//输出字符

    printf("b[0]=%c\n", b[0]);//输出字符l

    printf("qq1=%c\n", *qq);//输出字符
    printf("qq2=%s\n", qq);//输出字符串
    printf("qq4=%d\n", qq);//没有*，输出指针的地址值的10进制形式
    printf("qq3=%d\n", *qq);//有*，输出指针所指内容（e）,但%d要求输出整型，故输出e的ASCII码


    for (int i = 0; i < 5; i++) {
        char *t = q + i;
        printf("%c  %s\n", *t, t);
        *t = 'a';//更改b
    }
    printf("%s", b);//aaaaa
    return 0;
}
