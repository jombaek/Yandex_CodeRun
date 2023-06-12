#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace std
{
    template <class T1, class T2>
    struct hash<std::pair<T1, T2>>
    {
        size_t operator()(const std::pair<T1, T2>& p) const
        {
            size_t h1 = std::hash<T1>{}(p.first);
            size_t h2 = std::hash<T2>{}(p.second);
            return h1 ^ h2;
        }
    };
}

int main()
{
    int T;
    std::cin >> T;

    std::unordered_map<std::pair<std::string, std::string>, int> edges;
    std::unordered_set<std::string> vertices;

    for (int i = 0; i < T; ++i)
    {
        std::string word;
        std::cin >> word;

        for (auto j = 0; j < word.size() - 3; ++j)
        {
            std::string subword = word.substr(j, 3);
            std::string nextSubword = word.substr(j + 1, 3);

            vertices.insert(subword);
            vertices.insert(nextSubword);
            ++edges[{ subword, nextSubword }];
        }
    }

    int v = vertices.size();
    int e = edges.size();

    std::cout << v << "\n";
    std::cout << e << "\n";

    for (const auto& edge : edges)
        std::cout << edge.first.first << " " << edge.first.second << " " << edge.second << "\n";

    return 0;
}