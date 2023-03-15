#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>

using namespace std;

int main()
{
    vector<string> strCollect;

    strCollect.push_back("hello");
    strCollect.push_back("world");
    strCollect.push_back("work");
    strCollect.push_back("sasasa");
    
    std::replace(strCollect.begin(), strCollect.end(), string{"world"}, string{"nil"}) ;
    std::replace_if(strCollect.begin(), strCollect.end(),
                       []( const std::string& s ) { return !s.empty() && s[0] == 'h' ; },
                       "ttttt" ) ;

    for(string str: strCollect)
        cout << str << "\n";
}
