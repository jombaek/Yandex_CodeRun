#include <iostream>
#include <string>

void drawCalendar(int nDays, const std::string& weekday)
{
    std::string days[] = { "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday" };

    int startDayIndex = 0;
    for (int i = 0; i < 7; ++i)
    {
        if (days[i] == weekday)
        {
            startDayIndex = i;
            break;
        }
    }

    std::string calendar[6][7] = {
    {"..", "..", "..", "..", "..", "..", ".."}
    };

    int currentDay = 1;
    int col = startDayIndex;

    for (; col < 7; ++col)
        calendar[0][col] = (currentDay <= 10 ? "." : "") + std::to_string(currentDay++);

    for (int row = 1; row < 6; ++row)
    {
        for (col = 0; col < 7; ++col)
        {
            if (currentDay <= nDays)
                calendar[row][col] = (currentDay <= 10 ? "." : "") + std::to_string(currentDay++);
            else
                break;
        }
    }

    for (int row = 0; row < 6; ++row)
    {
        for (int col = 0; col < 7; ++col)
        {
            if (!calendar[row][col].empty())
                std::cout << calendar[row][col] << ' ';
        }

        std::cout << "\n";
    }
}

int main()
{
    int nDays;
    std::string weekday;
    std::cin >> nDays >> weekday;

    drawCalendar(nDays, weekday);

    return 0;
}