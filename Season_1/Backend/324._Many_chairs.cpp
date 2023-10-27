#include <iostream>
#include <vector>
#include <algorithm>

int main ()
{
    int n, m;
    std::cin >> n >> m;

    std::vector<int> a(n), b(m);

    for (int i = 0; i < n; i++)
        std::cin >> a[i];

    for (int i = 0; i < m; i++)
        std::cin >> b[i];
    
    std::sort(a.begin(), a.end());
    std::sort(b.begin(), b.end(), std::greater<>());

    int i = 0, j = 0;
    long long ans = 0;

    while (i < n && j < m)
    {
        if (a[i] <= b[j])
            ans += b[j] - a[i];
        i++;
        j++;
    }

    std::cout << ans << '\n';

    return 0;
}