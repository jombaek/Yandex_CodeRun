#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;

class Pallet
{
public:
    int w;
    int h;

    Pallet(int w, int h) : w(w), h(h) {}

    Pallet() : w(0), h(0) {}

    bool operator<(const Pallet& other) const
    {
        if (w == other.w)
            return h > other.h;

        return w > other.w;
    }
};

int solve(vector<Pallet>& pallets, int n)
{
    sort(pallets.begin(), pallets.end());
    unordered_map<int, int> highWidthMap;
    int maxWidth = pallets[0].w;
    int maxHigh = pallets[0].h;
    highWidthMap[maxHigh] = maxWidth;
    vector<int> heightsList;
    heightsList.push_back(maxHigh);
    int result = 1;

    for (int i = 1; i < n; i++)
    {
        Pallet p = pallets[i];
        int w = p.w;
        int h = p.h;
        if (w == maxWidth || h >= maxHigh)
        {
            result++;

            if (h > maxHigh)
            {
                maxHigh = h;
                heightsList.push_back(maxHigh);
            }
        }
        else
        {
            bool found = false;

            for (int j = heightsList.size() - 1; j >= 0; j--)
            {
                int curH = heightsList[j];

                if (curH <= h)
                    break;

                int tempW = highWidthMap[curH];

                if (w < tempW)
                {
                    found = true;
                    break;
                }
            }

            if (!found)
                result++;
        }

        int maxWForH = highWidthMap[h];

        if (maxWForH == 0 || w > maxWForH)
            highWidthMap[h] = w;
    }

    return result;
}

int main()
{
    int n;
    cin >> n;

    vector<Pallet> pallets(n);

    for (int i = 0; i < n; i++)
    {
        int w, h;
        cin >> w >> h;
        pallets[i] = Pallet(max(w, h), min(w, h));
    }

    int result = solve(pallets, n);

    cout << result << endl;

    return 0;
}