#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <iomanip>

using namespace std;

typedef long long int ll;
typedef long double ld;

const int MAX_N = 10 * 1000 + 227;
const int MAX_LEN = 35;

struct ig_info
{
    ll cost = 0;
    ll cnt = 0;
    ll buy_cnt = 0;
    ll eg_cnt = 0;
    ld arr[4] = { 0.0, 0.0, 0.0, 0.0 };
};

struct rs
{
    string name;
    ll mult = 0;
    vector<pair<string, ll>> igs;
    ld arr[4] = { 0.0, 0.0, 0.0, 0.0 };
};

ll getСnt()
{
    ll cnt;
    cin >> cnt;

    string buf_cnt;
    cin >> buf_cnt;

    if (buf_cnt == "kg" || buf_cnt == "l")
        return 1000 * cnt;

    if (buf_cnt == "tens")
        return 10 * cnt;

    return cnt;
}

int main()
{
    int n, k, m;
    char buf[MAX_LEN];
    char buf_cnt[MAX_LEN];
    unordered_map<string, ig_info> info;

    cin >> n;
    vector<rs> arr(n);

    for (int i = 0; i < n; ++i)
    {
        int sz;
        cin >> buf >> arr[i].mult >> sz;
        arr[i].name = buf;
        arr[i].igs.resize(sz);
        for (int j = 0; j < sz; ++j)
        {
            cin >> buf;
            arr[i].igs[j].first = buf;
            arr[i].igs[j].second = getСnt();
        }
    }

    cin >> k;

    for (int i = 0; i < k; ++i)
    {
        ll cost;
        cin >> buf >> cost;
        ig_info& cur_info = info[buf];
        cur_info.cost = cost;
        cur_info.cnt = getСnt();
    }

    cin >> m;

    for (int i = 0; i < m; ++i)
    {
        cin >> buf;
        ig_info& cur_info = info[buf];
        cur_info.eg_cnt = getСnt();

        for (int j = 0; j < 4; ++j)
        {
            double x;
            cin >> x;
            cur_info.arr[j] = x;
        }

        if (cur_info.cnt == 0)
            info.erase(buf);
    }

    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < static_cast<int>(arr[i].igs.size()); ++j)
        {
            ig_info& cur_info = info[arr[i].igs[j].first];
            cur_info.buy_cnt += arr[i].mult * arr[i].igs[j].second;

            for (int k = 0; k < 4; ++k)
                arr[i].arr[k] += (static_cast<double>(arr[i].igs[j].second) / static_cast<double>(cur_info.eg_cnt)) * cur_info.arr[k];
        }
    }

    ll ans = 0;
    for (auto& cur_info : info)
    {
        cur_info.second.buy_cnt = (cur_info.second.buy_cnt + cur_info.second.cnt - 1) / cur_info.second.cnt;
        ans += cur_info.second.buy_cnt * cur_info.second.cost;
    }

    cout << ans << "\n";

    for (const auto& cur_info : info)
        cout << cur_info.first << " " << cur_info.second.buy_cnt << "\n";

    for (int i = 0; i < n; ++i)
    {
        cout << arr[i].name << " ";
        for (int j = 0; j < 4; ++j)
            cout << fixed << setprecision(3) << arr[i].arr[j] << (j == 3 ? "\n" : " ");
    }

    return 0;
}