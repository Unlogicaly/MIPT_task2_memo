#include "split.h"
#include <sstream>

using namespace std;

vector<string> split(string s, char c)
{
    vector<string> result{s};

    if (!s.length())
        return result;

    int prev = -1;

    for (auto i = 0; i < s.length(); ++i)
    {
        if (s[i] == c)
        {
            result[result.size() - 1] = string(s.begin() + prev + 1, s.end() - (s.length() - i));
            result.emplace_back("");

            prev = i;

            continue;
        }
    }
    result[result.size() - 1] = string(s.begin() + prev + 1, s.end());

    return result;
}

bool in(const string &src, const char c)
{
    for (auto ch : src)
        if (ch == c)
            return true;
    return false;
}

bool in(const vector<string> &names, const string &s)
{
    for (const auto &name : names)
        if (name == s)
            return true;
    return false;
}

std::pair<std::string, int> separate(std::string s){
    if (isalpha(s.back())) return {s, 1};
    istringstream is{s};
    char c;
    string first;
    int second;
    is.get(c);
    while(isalpha(c))
    {
        first += c;
        is.get(c);
    }
    is.putback(c);
    is >> second;
    return {first, second};
}
