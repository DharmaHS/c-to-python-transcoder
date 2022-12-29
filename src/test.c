#include <stdio.h>
#include <stdbool.h>
#include <string.h>

int main()
{
    char str[100];
    scanf("%s", str);

    int i = 0;
    int j = strlen(str) - 1;
    int flag = 0;
    while (i < j)
    {
        if (str[i] != str[j])
        {
            flag = 0;
            break;
        }
        else
        {
            flag = 1;
        }
        i += 1;
        j -= 1;
    }

    if (flag)
    {
        printf("True\n");
    }
    else
    {
        printf("False\n");
    }
}