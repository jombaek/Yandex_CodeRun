#include <iostream>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <climits>

int main()
{
    std::string s, c;
    std::cin >> s >> c;

    std::unordered_map<char, int> mp;

    for (int i = 0; i < c.size(); ++i)
        mp[c[i]] = 1;

    int l = 0, r = 0;
    int n = s.size(), count = mp.size(), ans = INT_MAX;

    while (r < n)
    {
        if (mp.count(s[r]))
        {
            if (mp[s[r++]]-- > 0)
                --count;

            while (count == 0)
            {
                ans = std::min(ans, r - l);

                if (mp[s[l++]]++ == 0)
                    count++;
            }
        }
        else
        {
            ++r;
            l = r;
            count = mp.size();

            for (auto& pair : mp)
                pair.second = 1;
        }
    }

    std::cout << (ans == INT_MAX ? 0 : ans) << '\n';

    return 0;
}