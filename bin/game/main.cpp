#include "card.h"
#include "create_window.h"
#include "game_paths.h"

int main()
{
    Simple_window *win = create_window("m");
    win->attach(*new Graph_lib::Image({100, 100}, source + "back.gif"));

    // Card my_card(2, 3);
    // my_card.attach(*win);

    win->wait_for_button();
    return 0;
}
