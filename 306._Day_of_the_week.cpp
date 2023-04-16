#include <iostream>
#include <string>
#include <unordered_map>

int main()
{
    int d, m, y, dayOfTheWeek;
    std::string M;
    
    std::unordered_map<std::string, int> monthMap = {
        {"January", 1},
        {"February", 2},
        {"March", 3},
        {"April", 4},
        {"May", 5},
        {"June", 6},
        {"July", 7},
        {"August", 8},
        {"September", 9},
        {"October", 10},
        {"November", 11},
        {"December", 12}
    };

    std::unordered_map<int, std::string> dayOfTheWeekMap = {
        {0, "Sunday"},
        {1, "Monday"},
        {2, "Tuesday"},
        {3, "Wednesday"},
        {4, "Thursday"},
        {5, "Friday"},
        {6, "Saturday"}
    };

    while (std::cin >> d >> M >> y)
    {
        m = monthMap[M];
        int a = (14 - m) / 12;
        y = y - a;
        m = m + 12 * a - 2;
        dayOfTheWeek = (7000 + (d + y + y / 4 - y / 100 + y / 400 + (31 * m) / 12)) % 7;

        std::cout << dayOfTheWeekMap[dayOfTheWeek] << "\n";
    }

    return 0;
}