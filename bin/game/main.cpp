#include "create_window.h"
#include "editting_files.h"
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

int get_local_time()
{
    time_t calendar = time(nullptr);
    tm *local = std::localtime(&calendar);

    if (local)
        return local->tm_hour * 3600 + local->tm_min * 60 + local->tm_sec;

    return 0;
}

void wait(int time)
{
    int start = get_local_time();
    while (get_local_time() - start < time)
        ;
}

int main()
{
    Field f{};

    f.wait_for_button();

    clear();

    return Graph_lib::gui_main();
}
