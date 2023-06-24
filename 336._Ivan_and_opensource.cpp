#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
#include <unordered_map>

using namespace std;

struct MyFile
{
    string root;
    string name;
    string ext;
};

int main()
{
    int n;
    cin >> n;

    unordered_set<string> blackList;
    for (int i = 0; i < n; i++)
    {
        string word;
        cin >> word;
        blackList.insert(word);
    }

    int m;
    cin >> m;
    vector<MyFile> allFiles;

    for (int i = 0; i < m; i++)
    {
        string fullName;
        cin >> fullName;
        bool inBlackList = false;

        for (const string& bl : blackList)
        {
            if (fullName.find(bl) != string::npos)
            {
                inBlackList = true;
                break;
            }
        }

        if (!inBlackList)
            continue;

        string ext = fullName.substr(fullName.find_last_of('.'));
        MyFile my;
        my.ext = ext;
        my.name = fullName;
        allFiles.push_back(my);
    }

    int q;
    cin >> q;

    string result;
    for (int i = 0; i < q; i++)
    {
        string path;
        cin >> path;
        bool found = false;
        unordered_map<string, int> extMap;
        for (const MyFile& my : allFiles)
        {
            if (my.name.length() < path.length())
                continue;
            if (my.name.substr(0, path.length()) == path)
            {
                string ext = my.ext;
                extMap[ext]++;
                found = true;
            }
        }

        if (!found)
            result += "0\n";
        else
        {
            result += to_string(extMap.size()) + "\n";

            for (const auto& entry : extMap)
                result += entry.first + ": " + to_string(entry.second) + "\n";
        }
    }

    cout << result;

    return 0;
}