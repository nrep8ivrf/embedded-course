#include <stdio.h>
int main() {
    char name[50];
    printf("请输入你的名字：");
    scanf("%s", name);
    printf("你好，%s！欢迎学习嵌入式系统设计\n", name);
    return 0;
}