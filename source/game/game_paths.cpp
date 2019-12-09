#include "game_paths.h"

const std::string find_path()
{
    std::string result;
    for (std::string &t : split(__FILE__, '/'))
    {
        result += t + "\\";
        if (t == "memo")
            break;
    }
    return result;
}
