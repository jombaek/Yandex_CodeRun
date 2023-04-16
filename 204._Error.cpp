#include <iostream>
#include <vector>
#include <iomanip>

int main ()
{
    int n, a, b, sum = 0;
    std::cin >> n;
    std::vector<int> arr(n);

    for (int i = 0; i < n; i++)
    {
        std::cin >> a >> b;
        arr[i] = a * b;
        sum += arr[i];
    }

    for (int i = 0; i < n; i++)
    {
        std::cout << std::fixed << std::setprecision(12) << (double) arr[i] / sum << '\n';
    }

    return 0;
}