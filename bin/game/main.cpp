#include "create_window.h"
#include "editting_files.h"

int main()
{
    Simple_window *win = create_window("m");

    win->attach(*new Graph_lib::Image({100, 100}, source + "default.gif"));
    win->wait_for_button();

    std::cout << get_pic("apple", 150);

    clear();

    return 0;
}
