#include "field.h"
#include <algorithm>
#include <chrono>
#include <random>

// Generate shuffled range from 0 to max
std::vector<int> rand_range(int max, long long seed = 0)
{
    if (seed == 0)
        seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::vector<int> res(max);
    for (decltype(res.size()) i = 0; i < res.size(); ++i)
    {
        res[i] = static_cast<int>(i);
    }

    std::shuffle(res.begin(), res.end(), std::default_random_engine{seed});

    return res;
}

Card *Field::get_card(int x, int y)
{
    return cards[(x - get_side_gap()) / (get_size() + get_shift())][(y - get_up_gap()) / (get_size() + get_shift())];
}

Field::Field(bool &_end, int x_resol, int y_resol) : myWin(_end, x_resol, y_resol), opened{nullptr, nullptr}
{
    long long seed = std::chrono::system_clock::now().time_since_epoch().count();

    myWin::color(Graph_lib::Color::white);

    std::vector<std::string> pictures;
    get_names(pictures);
    std::shuffle(pictures.begin(), pictures.end(), std::default_random_engine{seed});

    std::vector<int> pairs = rand_range(get_height() * get_width(), seed);

    for (auto i = 0; i < get_width(); ++i)
    {
        cards.emplace_back();
        for (auto j = 0; j < get_height(); ++j)
            cards[i].push_back(nullptr);
    }

    for (auto i = 0; i < get_height() * get_width(); i += 2)
    {
        int i1 = pairs[i] / get_width(), j1 = pairs[i] % get_width();
        cards[j1][i1] =
            new Card(get_point(j1, i1), get_size(), get_pic(pictures[i / 2], get_size(), get_size()), cb_show);
        attach(*cards[j1][i1]);
        attach(*cards[j1][i1]->show);

        int i2 = pairs[i + 1] / get_width(), j2 = pairs[i + 1] % get_width();
        cards[j2][i2] =
            new Card(get_point(j2, i2), get_size(), get_pic(pictures[i / 2], get_size(), get_size()), cb_show);
        attach(*cards[j2][i2]);
        attach(*cards[j2][i2]->show);
    }
}

void Field::treat_last(Card *last)
{
    for (auto &lines : cards)
    {
        for (auto *card : lines)
        {
            if (!card->is_found and card != last)
            {
                card->is_found = true;
                last->is_found = true;

                card->show->hide();
                last->show->hide();

                card->click();

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

            if (c == opened.first or c == opened.second)
            {
                opened.first = nullptr;
                opened.second = nullptr;
                return;
            }
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
