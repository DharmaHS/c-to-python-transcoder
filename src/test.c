#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool isPalindrome(char *str) {
    int i = 0;
    int j = strlen(str) - 1;
    while (i < j) {
        if (str[i] != str[j])
            return false;
        i++;
        j--;
    }
    return true;
}


int main() {
    printf("%s \n", isPalindrome("abcba") ? "true" : "false");
    return 0;
}