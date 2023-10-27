#include <iostream> 
#include <vector> 
#include <deque> 
#include <string> 
#include <algorithm> 
#include <unordered_map> 

using namespace std;

class Point
{
public:
    int index{ 0 };
    int value{ 0 };

    Point(int index, int value)
    {
        this->index = index;
        this->value = value;
    }

    bool operator==(const Point& other) const
    {
        return index == other.index && value == other.value;
    }

    bool operator<(const Point& other) const
    {
        return value < other.value;
    }

    bool operator>(const Point& other) const
    {
        return value > other.value;
    }
};

string solve(const vector<Point>& array, vector<Point>& arrayCorrect, int k, int m)
{
    sort(arrayCorrect.begin(), arrayCorrect.end(), greater<Point>());

    string result = "";
    //result.reserve(k); 

    if (m == 0)
    {
        for (int i = 0; i < array.size(); ++i)
        {
            if (array[i].value == 0)
            {
                result += to_string(i + 1) + ' ';
                --k;
                for (int j = 0; j < array.size(); ++j)
                {
                    if (i == j)
                        continue;
                    if (k == 0)
                        break;
                    result += to_string(j + 1) + ' ';
                    --k;
                }
                return result;
            }
        }
    }

    if (m == 1)
    {
        for (int i = 0; i < array.size(); ++i)
        {
            if (array[i].value == 1)
            {
                result += to_string(i + 1) + ' ';
                --k;
                if (k <= 0)
                    break;
            }
        }
        return result;
    }

    deque<int> indexStack;
    deque<Point> st;
    int lastBad = 0;
    int end = arrayCorrect.size() - 1;
    int rest = m;
    unordered_map<int, int> indexOfNextValue(end);
    int indexOfOne = -1;
    int amountOfOne = 0;
    int prev = -1;

    for (int i = 0; i <= end; ++i)
    {
        Point p = arrayCorrect[i];
        int cur = p.value;

        if (cur != prev && prev != -1)
            indexOfNextValue[prev] = i;
        if (cur == 1 && indexOfOne == -1)
        {
            indexOfOne = i;
            amountOfOne = end - i + 1;
        }
        prev = cur;
    }

    for (int i = 0; i <= end; ++i)
    {
        Point p = arrayCorrect[i];
        int cur = p.value;
        if (rest == 1)
        {
            if (indexOfOne == -1)
            {
                rest = rest * st.back().value;
                lastBad = st.back().value;
                st.pop_back();
                i = indexStack.back();
                indexStack.pop_back();
                continue;
            }
            else
            {
                if (i < (indexOfOne - 1))
                {
                    int need = k - st.size();
                    if (need <= amountOfOne)
                    {
                        for (int j = indexOfOne; j < indexOfOne + need; ++j)
                        {
                            Point pp = arrayCorrect[j];
                            st.push_back(pp);
                        }
                        break;
                    }
                    else
                    {
                        rest = rest * st.back().value;
                        lastBad = st.back().value;
                        st.pop_back();
                        i = indexStack.back();
                        indexStack.pop_back();
                    }
                    continue;
                }
            }
        }

        if (lastBad == cur)
        {
            auto it = indexOfNextValue.find(cur);
            if (it == indexOfNextValue.end())
            {
                rest = rest * st.back().value;
                lastBad = st.back().value;
                st.pop_back();
                i = indexStack.back();
                indexStack.pop_back();
            }
            else  i = it->second - 1;
            continue;
        }
        if (cur > rest || (rest % cur != 0))
        {
            lastBad = cur;
            if (i == end)
            {
                while (i >= (end - 1))
                {
                    lastBad = st.back().value;
                    st.pop_back();
                    rest *= lastBad;

                    i = indexStack.back();
                    indexStack.pop_back();
                }
            }
            continue;
        }

        rest = rest / cur;
        st.push_back(p);
        indexStack.push_back(i);

        if (st.size() == k && rest == 1)
            break;
        if (i == end)
        {
            while (i >= (end - 1))
            {
                lastBad = st.back().value;
                st.pop_back();
                rest *= lastBad;
                i = indexStack.back();
                indexStack.pop_back();
            }
        }
    }

    for (const Point& point : st)
        result += to_string(point.index + 1) + ' ';

    return result;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, k;
    cin >> n >> m >> k;

    vector<Point> array;
    vector<Point> arrayCorrect;
    array.reserve(n);
    arrayCorrect.reserve(n);

    for (int i = 0; i < n; ++i)
    {
        int cur;
        cin >> cur;
        Point p(i, cur);
        array.push_back(p);

        if (cur == 0 && m != 0)
            continue;
        if (cur == 0)
        {
            if (m == 0)
                arrayCorrect.push_back(p);
        }
        else if (m % cur == 0)
            arrayCorrect.push_back(p);
    }

    string res = solve(array, arrayCorrect, k, m);
    cout << res << "\n";

    return 0;
}