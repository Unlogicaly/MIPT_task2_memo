#include "create_window.h"
#include <iostream>

using namespace std;

int main()
{
    auto win = create_window("m", true);
    win->wait_for_button();
    return 0;
}
