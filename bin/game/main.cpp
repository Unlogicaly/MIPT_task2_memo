#include "card.h"
#include "create_window.h"
#include "editting_files.h"

int main()
{
    Simple_window *win = create_window("m");

    // Card my_card(2, 3);
    // my_card.attach(*win);

    win->attach(*new Graph_lib::Image({100, 100}, source + "default.gif"));
    win->wait_for_button();

    std::cout << get_pic("apple", 150);

    clear();

    return 0;
}
