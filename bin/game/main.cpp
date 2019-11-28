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
    Graph_lib::Font font(Graph_lib::Font::courier);

    std::cout << font.as_int();

    Field f(120, 5, 20, 20);

    clear();

    return Graph_lib::gui_main();
}
