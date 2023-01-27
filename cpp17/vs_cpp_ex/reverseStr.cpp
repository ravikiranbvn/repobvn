#include<iostream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <algorithm>

using namespace std;

string revStr(string s)
{
    string rev;

    /* int n = s.length(); 
    while(n--) {
        rev.push_back(s[n]);
    }*/
    
    // c++17
    // std::reverse(s.begin(), s.end());

    for (int i = s.length() - 1; i >= 0; i--)
        rev.push_back(s[i]);

    return rev;
}

void strrev(char *head)
{
  if (!head) return;
  char *tail = head;
  while(*tail) ++tail;       // find the 0 terminator, like head+strlen
  --tail;                   // tail points to the last real char
                            // head still points to the first
  for( ; head < tail; ++head, --tail) {
      // walk pointers inwards until they meet or cross in the middle
      char h = *head, t = *tail;
      *head = t;           // swapping as we go
      *tail = h;
  }
}

int main()
{
    string s = "I will clear the interview!";
    string r = revStr(s);
    strrev(r.data());
    cout << r << endl;
}
