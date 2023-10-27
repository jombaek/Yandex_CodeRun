#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

int main ()
{
    int T, n;
    std::cin >> T;

    while (T--)
    {
        int minXOR = INT_MAX;
        std::cin >> n;
        std::vector<int> arr(n);

        for (int i = 0; i < n; i++)
            std::cin >> arr[i];
        
        std::sort(arr.begin(), arr.end());

        for (int i = 0; i < n - 1; i++)
        {
            int XOR = arr[i] ^ arr[i + 1];
            if (XOR < minXOR)
                minXOR = XOR;
        }

        std::cout << minXOR << "\n";
    }

    return 0;
}