#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * helper function to generate a random string
 */
static char *rand_string(char *str, size_t size) {
    const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJK...";
    if (size) {
        --size;
        for (size_t n = 0; n < size; n++) {
            int key = rand() % (int) (sizeof charset - 1);
            str[n] = charset[key];
        }
        str[size] = '\0';
    }
    return str;
}
int main() {
    char buffer[8];
    rand_string(buffer, 8);
    printf("%s %d\n", buffer, strlen(buffer));
}
