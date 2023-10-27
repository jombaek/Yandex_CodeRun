#include <iostream>
#include <vector>
#include <unordered_map>

int main() {
    int n, count = 0;
    std::cin >> n;

    std::vector<int> arr(n);
    std::unordered_map<int, int> mp;
    
    for (int i = 0; i < n; i++)
    {
        std::cin >> arr[i];
        mp[arr[i]]++;
    }

    for (auto it : mp)
    {
        if (it.second == 1)
            count++;
    }

    std::cout << count << "\n";
    
    return 0;
}
