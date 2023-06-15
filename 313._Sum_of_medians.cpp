#include <iostream>
#include <queue>
#include <vector>

int main()
{
    int n, median;
    std::cin >> n;

    std::vector<int> sequence(n);
    for (int i = 0; i < n; i++)
        std::cin >> sequence[i];

    std::priority_queue<int> maxHeap;
    std::priority_queue<int, std::vector<int>, std::greater<int>> minHeap;

    long long sumOfMedians = 0;

    for (int i = 0; i < n; i++)
    {
        if (maxHeap.empty() || sequence[i] < maxHeap.top())
            maxHeap.push(sequence[i]);
        else
            minHeap.push(sequence[i]);

        if (maxHeap.size() > minHeap.size() + 1)
        {
            minHeap.push(maxHeap.top());
            maxHeap.pop();
        }
        else if (minHeap.size() > maxHeap.size())
        {
            maxHeap.push(minHeap.top());
            minHeap.pop();
        }

        median = maxHeap.top();

        sumOfMedians += median;
    }

    std::cout << sumOfMedians << "\n";

    return 0;
}