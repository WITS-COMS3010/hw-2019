#include <stdio.h>
#include <string.h>

int main(void) {
    int len;
    
    char hello[6] = "Hello"; // C strings are null terminated, so the last element is used for the null character \0
    char world[] = ", World"; // You don't have to specify array length for string literals
    char str[128];
    
    // copy hello into str (str = hello does NOT work in C)
    strcpy(str, hello);
    // concatenate str with ", World"
    strcat(str, world);
    // print "Hello, World"
    printf("%s\n",str);

    // TODO: use strlen to get the length of str
    len = 0;
    printf("Length is %d\n", len);

    return 0;
}