#include <iostream>
#include <vector>
#include <map>

int main() {
    int n;
    std::cin >> n;

    std::vector<int> arr(n);
    std::map<int, int> mp;

    for (int i = 0; i < n; i++)
    {
        std::cin >> arr[i];
        mp[arr[i]]++;
    }

    int maxKey = mp.begin()->first;
    int maxValue = mp.begin()->second;

    for (const auto& [key, value] : mp)
    {
        if (value >= maxValue)
        {
            maxValue = value;
            maxKey = key;
        }
    }

    std::cout << maxKey << "\n";
    
    return 0;
}