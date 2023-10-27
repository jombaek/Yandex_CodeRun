#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

const int MAX_N = 100 * 1000 + 227;
const int MAX_K = 105;

int n, k;
int arr[MAX_N];
long long int dp_l[MAX_N][MAX_K];
long long int dp_r[MAX_N][MAX_K];

void solve()
{
    cin >> n >> k;

    long long int ans = -LLONG_MAX;

    for (int i = 0; i < n; ++i)
    {
        cin >> arr[i];
        ans = max(ans, static_cast<long long int>(arr[i]));
    }

    if (ans <= 0)
    {
        cout << ans << "\n";
        return;
    }

    for (int i = 0; i <= k; ++i)
    {
        dp_l[n + 1][i] = 0;
        dp_r[n + 1][i] = 0;
    }

    for (int i = 1; i <= n; ++i)
    {
        for (int j = 0; j <= k; ++j)
        {
            dp_l[i][j] = max(0ll, dp_l[i - 1][j] + arr[i - 1]);

            if (j)
                dp_l[i][j] = max(dp_l[i][j], dp_l[i - 1][j - 1]);

            ans = max(ans, dp_l[i][j]);
        }
    }

    for (int i = 1; i <= n; ++i)
    {
        for (int j = 0; j <= k; ++j)
        {
            dp_l[i][j] = dp_l[i - 1][j] + arr[i - 1];

            if (j)
                dp_l[i][j] = max(dp_l[i][j], dp_l[i - 1][j - 1]);
        }
    }

    for (int i = n; i >= 1; --i)
    {
        for (int j = 0; j <= k; ++j)
        {
            dp_r[i][j] = dp_r[i + 1][j] + arr[i - 1];

            if (j)
                dp_r[i][j] = max(dp_r[i][j], dp_r[i + 1][j - 1]);
        }
    }

    for (int i = 1; i <= n; ++i)
    {
        for (int j = 0; j <= k; ++j)
        {
            if (i != 1)
                dp_l[i][j] = max(dp_l[i][j], dp_l[i - 1][j]);

            if (j)
                dp_l[i][j] = max(dp_l[i][j], dp_l[i][j - 1]);
        }
    }

    for (int i = n; i >= 1; --i)
    {
        for (int j = 0; j <= k; ++j)
        {
            if (i != n)
                dp_r[i][j] = max(dp_r[i][j], dp_r[i + 1][j]);

            if (j)
                dp_r[i][j] = max(dp_r[i][j], dp_r[i][j - 1]);
        }
    }

    for (int i = 1; i < n; ++i)
        for (int j = 0; j <= k; ++j)
            ans = max(ans, dp_l[i][j] + dp_r[i + 1][k - j]);

    cout << ans << "\n";
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--)
        solve();

    return 0;
}