#include "create_window.h"
#include "game_paths.h"

int main()
{
    Simple_window *win = create_window("m");

    win->attach(*new Graph_lib::Image({100, 100}, source + "back.gif"));
    win->wait_for_button();

    return 0;
}
