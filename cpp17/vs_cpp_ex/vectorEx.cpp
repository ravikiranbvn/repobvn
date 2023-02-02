#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

std::ostream &operator<<(std::ostream &os, const std::vector<int> &input)
{
    for (auto const &i: input) {
        os << i << " ";
    }
    return os;
}

int main()
{
    vector<int> v1{1, 4, 9, 16};
    vector<int> v2{9, 7, 4, 9, 11};
    std::move(v2.begin(), v2.end(), std::back_inserter(v1));
    std::cout << v1;
    return 0;
}
