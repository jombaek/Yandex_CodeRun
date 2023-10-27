#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <climits>

int main()
{
    int n;
    std::cin >> n;

    std::map<long long, long long> allProduct;
    for (int i = 0; i < n; ++i)
    {
        long long product, category;
        std::cin >> product >> category;
        allProduct[product] = category;
    }

    std::map<long long, std::vector<int>> map;
    for (int i = 0; i < n; ++i)
    {
        long long product;
        std::cin >> product;
        long long category = allProduct[product];
        std::vector<int>& arr = map[category];
        arr.push_back(i + 1);
    }

    long long result = LLONG_MAX;
    long long count = 0;

    for (const auto& entry : map)
    {
        const std::vector<int>& arr = entry.second;
        std::vector<int> sortedArr(arr);
        std::sort(sortedArr.begin(), sortedArr.end());

        if (arr.size() == 1)
            ++count;
        else
        {
            long long min = sortedArr[1] - sortedArr[0];
            for (size_t i = 2; i < sortedArr.size(); i++)
            {
                long long div = sortedArr[i] - sortedArr[i - 1];
                if (div < min)
                    min = div;
            }

            result = std::min(result, min);
        }
    }

    if (count == map.size())
        result = count;

    std::cout << result << "\n";

    return 0;
}