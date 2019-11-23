#include "create_window.h"
#include "editting_files.h"
#include "field.h"
#include <algorithm>

template <class T>
void print(const std::vector<T> &src, const std::string &sep = " ", const std::string &end = "\n",
           std::ostream &os = std::cout)
{
    for (auto &t : src)
    {
        os << t << sep;
    }
    os << end;
}

int main()
{
    Field f{};

    f.wait_for_button();

    //    clear();

    return Graph_lib::gui_main();
}
