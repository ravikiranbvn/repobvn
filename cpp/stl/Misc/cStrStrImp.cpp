#include <cstring>
#include <cassert>
#include <cstdio>

char* mystrstrwithArray(const char* s1, const char* s2) {
    for(size_t i=0; s1[i]!= 0; i++ )
    {
        size_t j = 0;
        while(s2[j]!= 0 && s2[j] == s1[i+j])
            ++j;
        
        if (!s2[j]) {
            return (char*) &s1[i];
        }
    }
    
    if (!s2[0]) {
        return (char*) s1;
    }
    
    return nullptr;
}

char* mystrstrwithPtr(const char* s1, const char* s2) {
    while(*s1)
    {
        const char* s1try = s1;
        const char* s2try = s2;
        while(*s2try && *s2try == *s1try){
            ++s2try;
            ++s1try;
        }
        
        if (*s2try == '\0') {
            return (char*)s1;
        }    
        
        ++s1;
    }
    
    if (*s2 == '\0' ) {
        return (char*) s1;
    }
    
    return nullptr;
}

int main(int argc, char* argv[]) {
    assert(argc == 3);
    printf("strstr(\"%s\", \"%s\") = %p\n",
           argv[1], argv[2], strstr(argv[1], argv[2]));
    printf("mystrstrwithArray(\"%s\", \"%s\") = %p\n",
           argv[1], argv[2], mystrstrwithArray(argv[1], argv[2]));
    printf("mystrstrwithPtr(\"%s\", \"%s\") = %p\n",
           argv[1], argv[2], mystrstrwithPtr(argv[1], argv[2]));
    assert(strstr(argv[1], argv[2]) == mystrstrwithArray(argv[1], argv[2]));
    assert(strstr(argv[1], argv[2]) == mystrstrwithPtr(argv[1], argv[2]));
}
