#include <thread>
#include <string>
#include <iostream>
#include <numeric>
#include <algorithm>
#include <string_view>
#include <assert.h>

bool check_isbn13(std::string isbn) {    
    auto valid = false;
    std::string isbn_{isbn};
    isbn_.erase(std::remove(isbn_.begin(), isbn_.end(), '-'), isbn_.end());
    
   if (isbn_.size() == 13 &&
       std::count_if(std::begin(isbn_), std::end(isbn_), isdigit) == 13)
   {
      auto w = 0;
      auto sum = std::accumulate(
         std::begin(isbn_), std::end(isbn_), 0,
         [&w](int total, char const ch) {
            if (w++ & 1)
              total += (3 *(ch - '0'));
            else
              total += (ch - '0'); 
            return total;});
            
      valid = !(sum % 10);
   }

   return valid;
}

int main() {
    auto isbns = { "978-1734314502", "978-1734314509", "978-1788399081", "978-1788399083" };
    for (auto isbn : isbns) {
        std::cout << isbn << ": " << (check_isbn13(isbn) ? "good" : "bad") << '\n';
    }

    return 0;
}
