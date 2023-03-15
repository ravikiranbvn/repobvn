#include <iostream>
#include <cassert>

#define MASK_BYTE_0 ((1 << 8) - 1)     // 00000000000000000000000011111111
#define MASK_BYTE_1 (MASK_BYTE_0 << 8) // 00000000000000001111111100000000
#define MASK_BYTE_2 (MASK_BYTE_1 << 8) // 00000000111111110000000000000000
#define MASK_BYTE_3 (MASK_BYTE_2 << 8) // 11111111000000000000000000000000

void bin(unsigned n)
{
    if (n > 1)
        bin(n >> 1);
 
    printf("%d", n & 1);
}

// unsigned int hash(unsigned int x, unsigned int m) {
//     assert(1 <= m && m <= 32);

//     if(m == 32) {
//         return 3026017933 * x;
//     }

//     unsigned int offset = 32 - (m >> 1);
//     unsigned int MASK   = ((1 << m) - 1) << offset;
//     unsigned int return_value =  ((3026017933*x) & MASK) >> offset;
// }

int main()
{
    unsigned int c = 3026017933;
    bin(c);
    printf( "\n%u\n", c & MASK_BYTE_0 ); // %u indicates it is an unsigned integer type
    bin(c & MASK_BYTE_0);
    printf( "\n%u\n", c & MASK_BYTE_1 );
    bin(c & MASK_BYTE_1);
    printf( "\n%u\n", c & MASK_BYTE_2 );
    bin(c & MASK_BYTE_2);
    printf( "\n%u\n", c & MASK_BYTE_3 );
    bin(c & MASK_BYTE_3);

    c = 3026017933;
    printf( "\n%u\n", c & MASK_BYTE_0 );
    bin(c & MASK_BYTE_0);
    printf( "\n%u\n", (c & MASK_BYTE_1) >> 8 );
    bin((c & MASK_BYTE_1) >> 8);
    printf( "\n%u\n", (c & MASK_BYTE_2) >> 16 );
    bin((c & MASK_BYTE_1) >> 16);
    printf( "\n%u\n", (c & MASK_BYTE_3) >> 24 );
    bin((c & MASK_BYTE_1) >> 24);

    return 0;
}

//https://graphics.stanford.edu/~seander/bithacks.html
//https://binary-system.base-conversion.ro/real-number-converted-from-decimal-system-to-32bit-single-precision-IEEE754-binary-floating-point.php?decimal_number_base_ten=0.625