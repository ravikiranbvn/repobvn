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

 size_t strlen(const char* s)
  {
    size_t k;
    for(k = 0; s[k] != '\0'; k++) {}
    return k;
  }

  int strcmp(const char* s, const char* t)
  {
    int k = 0;
    while(s[k] != '\0' && s[k] == t[k])
    {
      k++;
    }

    // We want to return s[k] - t[k], but be
    // sure to treat the characters as numbers
    // from 0 to 255, not as numbers from
    // -128 to 127.

    int sk = (unsigned char) s[k];
    int tk = (unsigned char) t[k];
    return sk - tk;
  }

  char* strncat(char *dest, const char *src, size_t n)
  {
    size_t dest_len = strlen(dest);
    size_t i;

    for (i = 0 ; i < n && src[i] != '\0' ; i++)
    {
      dest[dest_len + i] = src[i];
    }
    dest[dest_len + i] = '\0';
    return dest;
  }

int main(int argc, char *argv[]) {
    int i;
    for(i=1; i < argc; i++) {
        printf("%d\n", mystrlen(argv[i]));
        char* arg = argv[i];
        printf("%s (compared to %s = %d)\n", arg, argv[1], mystrcmp(arg, argv[1]));
    }
}
