#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
    int id;
    char model[100];
    char brand[20];
    char class[100];
    char body[100];
    char trasmissin[100];
    char fuel[100];
    char engine[100];
    float price, engineCapacity, enginePower;
} Car;

int main()
{
    printf("Hello World");

    return 0;
}
