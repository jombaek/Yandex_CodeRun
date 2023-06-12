#include <iostream>

typedef long long int ll;

ll gcd(ll a, ll b)
{
    return b ? gcd(b, a % b) : a;
}

int main()
{
    ll x, y;
    std::cin >> x >> y;

    if (y % x != 0)
    {
        std::cout << 0 << "\n";
        return 0;
    }

    y /= x;

    ll count = 0;

    for (ll k = 1; k * k <= y; ++k)
        if (y % k == 0)
            if (gcd(k, y / k) == 1)
                count += 1 + (k * k != y);

    std::cout << count << "\n";

    return 0;
}