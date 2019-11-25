#include "field.h"
#include <algorithm>
#include <chrono>

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
    Field f(2, 2, 150, 5, 150, 150);

    f.wait_for_button();

    //    clear();

    return Graph_lib::gui_main();
}
