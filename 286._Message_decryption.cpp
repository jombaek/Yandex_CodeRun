#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

std::unordered_map<char, int> mapChar;
std::unordered_map<int, char> mapInteger;

void fillMap()
{
    int i = 1;
	
    for (char c = 'a'; c <= 'z'; ++c)
    {
        mapChar[c] = i;
        mapInteger[i] = c;
        ++i;
    }
}

std::string convertWord(const std::string& word)
{
    std::string convertedWord = "";
    int k = 1 - mapChar[word[0]];

    if (k == 0)
        return word;

    for (char ch : word)
    {
        int n = mapChar[ch] + k;
        if (n <= 0)
            n += 26;
        convertedWord += mapInteger[n];
    }

    return convertedWord;
}

std::string decode(const std::vector<std::string>& textArray, const std::vector<std::string>& message)
{
    std::unordered_map<std::string, std::string> match;

    for (const std::string& word : textArray)
        match[convertWord(word)] = word;

    std::string decodedMessage = "";
    for (const std::string& word : message)
    {
        std::string tmp = convertWord(word);
        decodedMessage += match[tmp] + "\n";
    }

    return decodedMessage;
}

int main()
{
    fillMap();

    std::string line;
    std::getline(std::cin, line);
    std::vector<std::string> textArray;
    std::string word;
	
    for (char c : line)
    {
        if (c == ' ')
        {
            textArray.push_back(word);
            word = "";
        }
        else
            word += c;
    }

    textArray.push_back(word);

    int n;
    std::cin >> n;
    std::cin.ignore();

    std::vector<std::string> message(n);
    for (int i = 0; i < n; ++i)
        std::getline(std::cin, message[i]);

    std::string decodedMessage = decode(textArray, message);
    std::cout << decodedMessage << "\n";

    return 0;
}