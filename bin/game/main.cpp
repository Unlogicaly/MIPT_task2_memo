#include "create_window.h"
#include "split.h"
#include <iostream>

using namespace std;

static const string find_path()
{
    string result;

    for (string &t : split(__FILE__, '/'))
    {
        result += t + "\\";
        if (t == "memo")
            break;
    }

    return result + "source\\";
}

const string path = find_path();

int main()
{
    Simple_window *win = create_window("m");

    win->attach(*new Graph_lib::Image({100, 100}, path + "back.gif"));

    win->wait_for_button();

    return 0;
}
