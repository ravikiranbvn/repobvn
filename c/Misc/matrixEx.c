#include <stdio.h>

int main()
{
  int matrix[3][5] =
  {
    {0,1,2,3,4},
    {5,6,7,8,9},
    {10,11,12,13,14}
  };
  
   printf("        matrix[0]: %zu\n", matrix[0]);
   printf("        matrix[1]: %zu\n", matrix[1]);
   printf("        matrix[2]: %zu\n", matrix[2]);
   
   printf("        matrix[0][0]: %zu\n", *(matrix[0] + 0));
   printf("        matrix[1][0]: %zu\n", *(matrix[1]+ 0));
   printf("        matrix[2][0]: %zu\n", *(matrix[2]+ 0));

   printf("        matrix[0][1]: %zu\n", *(matrix[0] + 1));
   printf("        matrix[1][1]: %zu\n", *(matrix[1]+ 1));
   printf("        matrix[2][1]: %zu\n", *(matrix[2]+ 1));
   
   printf("       &matrix[0]: %zu\n", &matrix[0]);
   printf("   &matrix[1] + 1: %zu\n", &matrix[1] + 1);
   printf("   &matrix[2] + 1: %zu\n", &matrix[2] + 1);
   printf("*(&matrix[1] +1 ): %zu\n\n", *(&matrix[0] + 1));
   printf("*(*(&matrix[1] + 1)): %zu\n", *(*(&matrix[0] + 0)));
   
   for(int i=0; i < 3; i++)
   {
       for(int j=0; j < 5; j++)
       {
           printf("i = %d j =%d matrix[i][j] = %d\n", i, j, matrix[i][j]);
           printf("i = %d j =%d *(*(matrix+i) + j) = %d\n", i, j, *(*(matrix+i) + j));
       }
   }
}
