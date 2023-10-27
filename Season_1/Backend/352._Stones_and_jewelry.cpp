#include <iostream>
#include <string>
#include <unordered_set>

int main()
{
    std::string j, s;
    std::cin >> j >> s;

    std::unordered_set<char> jewerly;

    for (int i = 0; i < j.size(); i++)
        jewerly.insert(j[i]);

    int count = 0;

    for (int i = 0; i < s.size(); i++)
    {
        if (jewerly.count(s[i]))
            count++;
    }
    
    std::cout << count << "\n";
    
    return 0;
}