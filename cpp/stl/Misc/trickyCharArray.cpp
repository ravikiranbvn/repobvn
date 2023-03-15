// To see the output: https://pythontutor.com/visualize.html#mode=edit

#include <bits/stdc++.h>
using namespace std;

int main()
{
  char b2[5] = { 'A', 'h', 'o', 'j', '\0' };
 
  char** arr2 = new char*[3];
  for (int i = 0; i < 3; ++i)
  {
      arr2[i] = b2;
      cout << arr2[i] << "\n";
      //printf("arr2\n");
  }
      
  arr2[0][0] = 'c';
  arr2[0][1] = 'c';
  arr2[0][2] = 'c';
  arr2[0][3] = 'c';
  
  std::cout << arr2[0] << std::endl;
  std::cout << arr2[1] << std::endl;
  std::cout << arr2[2] << std::endl;
  
  arr2[1][0] = 'd';
  arr2[1][1] = 'd';
  arr2[1][2] = 'd';
  arr2[1][3] = 'd';
  
  std::cout << arr2[0] << std::endl;
  std::cout << arr2[1] << std::endl;
  std::cout << arr2[2] << std::endl;
  
  arr2[2][0] = 'e';
  arr2[2][1] = 'e';
  arr2[2][2] = 'e';
  arr2[2][3] = 'e';
  
  std::cout << arr2[0] << std::endl;
  std::cout << arr2[1] << std::endl;
  std::cout << arr2[2] << std::endl;
  
  delete[] arr2;
  
  // ------------
  
  std::string b1 = "Ahoj";
  std::string* arr1 = new std::string[3];
  
  for (int i = 0; i < 3; ++i)
    arr1[i] = b1;
    // arr1[i] = std::move(b1);
  
  arr1[0][1] = 'c';
  std::cout << arr1[0] << arr1[1] << arr1[2] << std::endl;
  
  delete[] arr1;
}

