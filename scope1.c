#include <stdio.h>

static void printHello() {
    printf("hello\n");
}

void printHello2();

int main() {
    printHello();
    printHello2();
}
