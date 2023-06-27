#include <iostream>
#include <string>
#include <vector>

std::string split(std::string input)
{
    if (input.empty())
        return input;
    std::string output(std::move(input));

    for (int i = 0; i < output.size(); ++i)
    {
        char symb = (char)output[i];
        if (!(symb > 47 && symb < 58))
        {
            output.erase(i, 1);
            i--;
        }
    }
    return output;
}

class NumberFormat
{
protected:
    std::string country_code;
    std::string operator_code;
    std::string personal_number;
    std::string name;
public:
    explicit NumberFormat(const std::string& format)
    {
        read_format(format);
    }

    void read_format(const std::string& format)
    {
        country_code.clear();
        operator_code.clear();
        personal_number.clear();
        name.clear();

        if (format.empty())
            return;

        auto it = format.begin();

        ++it;
        for (; *it != ' '; ++it)
            country_code.push_back(*it);

        it += 2;
        for (; *it != ')'; ++it)
            operator_code.push_back(*it);

        it += 2;
        for (; *it != ' '; ++it)
            personal_number.push_back(*it);

        it += 3;
        for (; it != format.end(); ++it)
            name.push_back(*it);
    }

    bool match(const std::string& number) const
    {
        int count = country_code.size()
            + operator_code.size()
            + personal_number.size();

        if (count != number.size())
            return false;

        if (number.compare(0, country_code.size(), country_code) != 0)
            return false;

        if (number.compare(country_code.size(), operator_code.size(), operator_code) != 0)
            return false;

        for (size_t i = 0; i < personal_number.size(); ++i)
        {
            if (personal_number[i] == 'X')
                continue;
            else if (personal_number[i] != number[country_code.size() + operator_code.size() + i])
                return false;
        }
        return true;
    }

    std::string get_formatted_number(const std::string& number)
    {
        std::string formatted;
        formatted.append('+' + country_code + " (" + operator_code + ") "
            + number.substr(operator_code.size() + country_code.size()) + " - " + name);
        return formatted;
    }
};

int main()
{
    size_t n = 0, m = 0;
    std::vector<std::string> numbers;
    std::vector<std::string> formatted;
    std::vector<NumberFormat> formats;
    std::string tmp;

    std::cin >> n;
    std::cin.ignore();

    for (size_t i = 0; i < n; ++i)
    {
        std::getline(std::cin, tmp);
        numbers.push_back(split(tmp));
    }

    std::cin >> m;
    std::cin.ignore();

    for (size_t i = 0; i < m; ++i)
    {
        std::getline(std::cin, tmp);
        formats.emplace_back(NumberFormat(tmp));
    }

    for (const auto& num : numbers)
        for (auto& form : formats)
            if (form.match(num))
                formatted.emplace_back(form.get_formatted_number(num));

    for (const auto& p : formatted)
        std::cout << p << "\n";

    return 0;
}