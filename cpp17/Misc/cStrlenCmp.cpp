#include <stdio.h>

int mystrlen(const char* str) {
    int len = 0;
    while(*str++) {
        len++;
    }
    
    return len;
}

int mystrcmp(const char* str1, const char* str2) {
    const unsigned char* p1 = (const char*) str1;
    const unsigned char* p2 = (const char*) str2;
    while(*p1 && *p2 == *p1) {
        ++p1;
        ++p2;
    }
    
    return (*p1 > *p2) - (*p2 > *p1);
}

int main(int argc, char *argv[]) {
    int i;
    for(i=1; i < argc; i++) {
        printf("%d\n", mystrlen(argv[i]));
        char* arg = argv[i];
        printf("%s (compared to %s = %d)\n", arg, argv[1], mystrcmp(arg, argv[1]));
    }
}
