#include <iostream>
#include <bits/stdc++.h>
#include <vector>

using namespace std;

void removeFromMap(std::map<vector<string>,vector<int>>& years, std::pair <vector<string>,vector<int>>& pair)
{
    cout << "******************removeFromMap*************" << endl;

    years.erase(pair.first);
}

void insertToMap(std::map<vector<string>,vector<int>>& years, std::pair <vector<string>,vector<int>>& pair)
{
    cout << "******************insertToMap*************" << endl;

    years.insert(pair);
}

void findInMap(std::map<vector<string>,vector<int>>& years, vector<string>& vec)
{
    cout << "***********findInMap*****************" << endl;

    std::map<vector<string>,vector<int>>::iterator it;
    it = years.find(vec);
    if(it != years.end())
    {
        vector<int> k;
        k = (it->second);
        for(auto &i: k)
            cout << "value" << std::distance(begin(years), it) << ":" << "      "<< i << endl;
    }
}

void displayMap(std::map<vector<string>,vector<int>>& years)
{
    cout << "******************DisplayMap************" << endl;

    std::map<vector<string>,vector<int>>::iterator it;
    for(it = years.begin(); it != years.end(); ++it)
    {
        vector<string> vec = it->first;
        it = years.find(vec);
        if(it != years.end())
        {
            for(auto &o: vec)
                cout << "key" << std::distance(begin(years), it) << ":" << "      "<< o << endl;

            vector<int> k;
            k = (it->second);
            for(auto &i: k)
                cout << "value" << std::distance(begin(years), it) << ":" << "      "<< i << endl;
        }
    }
}

int main()
{
    map<vector<string>,vector<int>> years = {
        { {"Maurice","Vincent", "Wilkes"},{1913, 1945, 1951, 1967, 2000} },
        { {"Martin", "Ritchards"}, {1982, 2003, 2007} },
        { {"David", "John", "Wheeler"}, {1927, 1947, 1951, 2004} }
    };

    // find
    vector<string> key = {"Martin", "Ritchards"};
    findInMap(years, key);

    // insert
    std::pair <vector<string>,vector<int>> insertPair ({"Bjarne","Stroustrup"},{1950, 1975, 1985});
    insertToMap(years, insertPair);

    // display
    displayMap(years);

    // remove
    std::pair <vector<string>,vector<int>> removePair ({"David", "John", "Wheeler"}, {1927, 1947, 1951, 2004});
    removeFromMap(years, removePair);

    // display
    displayMap(years);

    return 0;
}






