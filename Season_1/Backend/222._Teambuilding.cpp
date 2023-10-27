#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <stack>
#include <set>

using namespace std;

bool contains(const unordered_set<int>& where, const unordered_set<int>& what)
{
    for (int num : what)
    {
        if (where.find(num) == where.end())
            return false;
    }

    return true;
}

bool solve(unordered_map<int, unordered_set<int>>& graph, unordered_set<int>& allNodes)
{
    stack<int> nodeStack;
    vector<unordered_set<int>> teams;

    while (!allNodes.empty())
    {
        unordered_set<int> tempTeam;
        unordered_set<int> team;
        auto it = allNodes.begin();
        int startNode = *it;
        unordered_set<int> brak;
        unordered_set<int> commonVertex;

        nodeStack.push(startNode);
        allNodes.erase(startNode);
        bool first = true;
        unordered_set<int>& currentEdgeList = graph[nodeStack.top()];

        while (!nodeStack.empty())
        {
            bool end = false;
            bool badVertex = false;

            if (first) {
                commonVertex = currentEdgeList;

                for (int num : allNodes)
                {
                    if (commonVertex.find(num) == commonVertex.end())
                        commonVertex.erase(num);
                }

                first = false;
            }

            tempTeam.insert(nodeStack.top());

            if (!currentEdgeList.empty())
            {
                end = true;
                bool hasItem = false;
                auto iterator = currentEdgeList.begin();
                int goodVertex = -1;

                while (iterator != currentEdgeList.end())
                {
                    int next = *iterator;

                    if (allNodes.find(next) != allNodes.end() && contains(graph[next], tempTeam) &&
                        brak.find(next) == brak.end() && commonVertex.find(next) != commonVertex.end())
                    {
                        nodeStack.push(next);
                        allNodes.erase(next);
                        goodVertex = next;
                        hasItem = true;
                        break;
                    }

                    ++iterator;
                }

                if (hasItem)
                {
                    end = false;
                    currentEdgeList = graph[goodVertex];
                    commonVertex.erase(goodVertex);

                    if (!commonVertex.empty())
                    {
                        unordered_set<int> copy = commonVertex;

                        for (int num : currentEdgeList)
                        {
                            if (copy.find(num) == copy.end())
                                copy.erase(num);
                        }

                        if (copy.empty())
                        {
                            badVertex = true;
                            end = true;
                        }
                        else
                            commonVertex = copy;
                    }
                }
            }
            else
                end = true;

            if (end)
            {
                if (badVertex)
                {
                    brak.insert(nodeStack.top());
                    allNodes.insert(nodeStack.top());
                    tempTeam.erase(nodeStack.top());
                    currentEdgeList = graph[nodeStack.top()];
                }
                else
                    team.insert(nodeStack.top());

                nodeStack.pop();
            }
        }

        teams.push_back(team);
    }

    if (teams.size() != 2)
        return false;

    cout << teams[0].size() << "\n";

    for (const unordered_set<int>& t : teams)
    {
        for (int num : t)
            cout << num << " ";

        cout << "\n";
    }

    return true;
}

int main()
{
    int n, m;
    cin >> n >> m;

    if (n * (n - 1) / 2 == m)
    {
        cout << 1 << "\n";
        cout << 1 << "\n";

        for (int i = 2; i <= n; ++i)
            cout << i << " ";

        cout << "\n";

        return 0;
    }

    unordered_map<int, unordered_set<int>> graph;
    unordered_set<int> allNodes;

    for (int i = 1; i <= n; ++i)
    {
        allNodes.insert(i);
        graph[i] = unordered_set<int>();
    }

    for (int i = 0; i < m; ++i)
    {
        int node1, node2;
        cin >> node1 >> node2;
        graph[node1].insert(node2);
        graph[node2].insert(node1);
    }

    if ((m == 0 && n != 2) || !solve(graph, allNodes))
        cout << -1 << "\n";

    return 0;
}