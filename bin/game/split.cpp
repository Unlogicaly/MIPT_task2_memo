#include "split.h"
#include <sstream>

using namespace std;

vector<string> split(string s, char c)
{
    vector<string> result{s};

    if (!s.length())
        return result;

    int prev = -1;

    for (int i = 0; i < int(s.length()); ++i)
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
