#include "game_paths.h"

const string find_path()
{
    string result;
    for (string &t : split(__FILE__, '/'))
    {
        result += t + "\\";
        if (t == "memo")
            break;
    }
    return result;
}
