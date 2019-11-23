#include "create_window.h"
#include "editting_files.h"
#include "field.h"

int main()
{

    Field f{};

    f.wait_for_button();

    clear();

    return Graph_lib::gui_main();
}
