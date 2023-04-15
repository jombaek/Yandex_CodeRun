#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> arr(3);
    
    for (int i = 0; i < 3; i++)
    {
        std::cin >> arr[i];
    }

    std::sort(arr.begin(), arr.end());

    std::cout << arr[1] << "\n";
    
    return 0;
}