#include "field.h"
#include <algorithm>
#include <chrono>
#include <random>

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

Card *Field::get_card(int x, int y)
{
    return cards[(x - get_side_gap()) / (get_size() + get_shift())][(y - get_up_gap()) / (get_size() + get_shift())];
}

std::vector<int> rand_range(int max, int seed)
{
    if (seed == -1)
        long long seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::vector<int> res(max);
    for (auto i = 0; i < res.size(); ++i)
    {
        res[i] = i;
    }

    std::shuffle(res.begin(), res.end(), std::default_random_engine{seed});

    return res;
}

Field::Field(bool &_end, int x_resol, int y_resol)
    : myWin(_end, x_resol, y_resol),
      opened{nullptr, nullptr},
      messages({x_max() / 2 - 120, y_max() / 2 - 50}, 240, 100, "")
{
    long long seed = std::chrono::system_clock::now().time_since_epoch().count();

    myWin::color(Graph_lib::Color::white);

    std::vector<std::string> pictures;
    get_names(pictures);
    std::shuffle(pictures.begin(), pictures.end(), std::default_random_engine{seed});

    std::vector<int> pairs = rand_range(get_height() * get_width(), seed);

    for (auto i = 0; i < get_height(); ++i)
    {
        cards.emplace_back();
        for (auto j = 0; j < get_width(); ++j)
            cards[i].push_back(nullptr);
    }

    for (auto i = 0; i < get_height() * get_width(); i += 2)
    {
        int i1 = pairs[i] / get_width(), j1 = pairs[i] % get_width();
        cards[i1][j1] =
            new Card(i1, j1, get_point(i1, j1), get_size(), get_pic(pictures[i / 2], get_size(), get_size()), cb_show);
        attach(*cards[i1][j1]);
        attach(*cards[i1][j1]->show);

        int i2 = pairs[i + 1] / get_width(), j2 = pairs[i + 1] % get_width();
        cards[i2][j2] =
            new Card(i2, j2, get_point(i2, j2), get_size(), get_pic(pictures[i / 2], get_size(), get_size()), cb_show);
        attach(*cards[i2][j2]);
        attach(*cards[i2][j2]->show);
    }

    attach(messages);
    messages.hide();
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

void Field::treat_last(Card *last)
{
    for (auto &lines : cards)
    {
        for (auto *card : lines)
        {
            if (!card->is_found)
                if (card != last)
                {
                    card->is_found = true;
                    last->is_found = true;
                    card->click();

                    messages.put("Congratulations!");
                    messages.show();

                    started = false;

                    return;
                }
        }
    }
}

void Field::flip(Graph_lib::Address pwin)
{
    Fl_Widget &w = Graph_lib::reference_to<Fl_Widget>(pwin);
    auto c = get_card(w.x(), w.y());
    if (!opened.first)
        opened.first = c;
    else if (!opened.second)
    {
        if (opened.first == c)
            return;
        opened.second = c;
    }
    else
    {
        if (opened.first->get_name() == opened.second->get_name())
        {
            opened.first->show->hide();
            opened.second->show->hide();

            opened.first->is_found = true;
            opened.second->is_found = true;

            ready++;
        }
        else
        {
            opened.first->click();
            opened.second->click();
        }

        opened.first = c;
        opened.second = nullptr;
    }

    c->click();

    if (ready == get_height() * get_width() / 2 - 1)
    {
        treat_last(c);
        asc();
    }

    Fl::redraw();
}

Field::~Field()
{
    for (auto &line : cards)
        for (auto *card : line)
            delete card;
}
