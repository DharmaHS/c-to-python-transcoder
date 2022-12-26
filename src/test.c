#include <stdio.h>
#include <stdbool.h>
#include <string.h>

int main() {
    char str[100];
    scanf("%s", str);

    int i = 0;
    int j = strlen(str) - 1;
    while (i < j) {
        if (str[i] != str[j]) {
            printf("False\n");
            break;
        }
        else {
            printf("True\n");
        }
        i+=1;
        j-=1;
    }
}