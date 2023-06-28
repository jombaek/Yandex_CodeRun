#include <iostream>
#include <map>
#include <string>

typedef long long ll;

struct ff
{
	ll len_before;
	ll el_here;
	ll len_here;
};

ll symbolsToRLE(ll x)
{
	if (x > 1) {
		ll res = 0;
		while (x > 0)
		{
			++res;
			x /= 10;
		}

		return res + 1;
	}

	return x;
}

inline bool isSymbol(char c)
{
	return c < '0' || c > '9';
}

void InitializeMap(std::map<ll, ff>& m, const std::string& s) {
	bool flag = false;
	std::string num;
	ll cnt = 0;
	ll len = 0;

	for (char c : s)
	{
		if (isSymbol(c))
		{
			ll len_prev = len;
			ll cnt_prev = cnt;
			if (flag)
			{
				flag = false;
				cnt += std::stoi(num);
			}
			else
				cnt += 1;

			auto re = symbolsToRLE(cnt - cnt_prev);
			len = len_prev + re;
			m[cnt_prev] = { len_prev,cnt - cnt_prev, re };
			num.clear();
		}
		else
		{
			flag = true;
			num += c;
		}
	}
}

int main()
{
	std::cin.tie(nullptr);
	std::ios::sync_with_stdio(false);
	std::string s;
	std::cin >> s;
	ll q, l, r;
	std::map<ll, ff> m;

	InitializeMap(m, s);

	std::cin >> q;
	while (q--)
	{
		std::cin >> l >> r;
		auto lit = prev(m.lower_bound(l));
		auto rit = prev(m.upper_bound(r));

		ll res;

		if (lit == rit)
			res = symbolsToRLE(r - l + 1);
		else
		{
			res = rit->second.len_before - (lit->second.len_before + lit->second.len_here)
				+ symbolsToRLE(r - rit->first)
				+ symbolsToRLE(lit->first + lit->second.el_here - l + 1);
		}

		std::cout << res << "\n";
	}

	return 0;
}