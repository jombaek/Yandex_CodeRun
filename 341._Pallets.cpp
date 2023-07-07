#include <iostream>
#include <vector>
#include <set>
#include <unordered_set>

using namespace std;

void solve(const unordered_set<int>& mySet, const vector<int>& delivery, const vector<int>& parent, int n, set<int>& pallets)
{
    unordered_set<int> badPallets;

    for (int i = 0; i < n; ++i)
    {
        int num = i + 1;
        if (mySet.count(delivery[i]) > 0)
        {
            if (badPallets.count(num) > 0)
                continue;

            int p = parent[i];
            if (p == 0)
                pallets.erase(num);
            else
            {
                bool needRemove = true;
                while (true)
                {
                    if (p - 1 >= n)
                        break;
                    if (parent[p - 1] == 0)
                        break;
                    else
                    {
                        p = parent[p - 1];
                        if (badPallets.count(p) > 0)
                        {
                            needRemove = false;
                            break;
                        }
                        else
                            badPallets.insert(p);
                    }
                }

                if (needRemove)
                    pallets.erase(p);
            }
        }
    }

    cout << pallets.size() << "\n";

    for (const auto& pallet : pallets)
        cout << pallet << " ";
}

int main()
{
    int n;
    cin >> n;
    vector<int> delivery(n);

    for (int i = 0; i < n; ++i)
        cin >> delivery[i];

    vector<int> parent(n);
    set<int> pallets;

    for (int i = 0; i < n; ++i)
    {
        cin >> parent[i];

        if (parent[i] == 0)
            pallets.insert(i + 1);
    }

    int k;
    cin >> k;
    unordered_set<int> mySet;

    if (k != 0)
    {
        for (int i = 0; i < k; ++i)
        {
            int num;
            cin >> num;
            mySet.insert(num);
        }
    }

    if (n == k)
        cout << 0 << "\n";
    else
        solve(mySet, delivery, parent, n, pallets);

    return 0;
}