#include "field.h"
#include <algorithm>
#include <chrono>
#include <random>

Card *Field::get_card(int x, int y)
{
    return cards[(x - side_gap) / (size + shift)][(y - up_gap) / (size + shift)];
}

std::vector<int> rand_range(int max)
{
    srand(time(NULL));
    std::vector<int> res(max);
    for (auto i = 0; i < res.size(); ++i)
    {
        res[i] = i;
    }
    std::random_shuffle(res.begin(), res.end());

    return res;
}

Field::Field(int height, int width, int size, int shift, int side_gap, int up_gap)
    : Simple_window({0, 0}, 1920, 1080, ""),
      messages({x_max() / 2 - 120, y_max() / 2 - 50}, 240, 100, ""),
      opened{nullptr, nullptr},
      height{height},
      width{width},
      size{size},
      shift{shift},
      side_gap{side_gap},
      up_gap{up_gap}
{
    std::vector<std::string> pictures;
    get_names(pictures);
    std::random_shuffle(pictures.begin(), pictures.end());

    std::vector<int> pairs = rand_range(height * width);

    for (auto i = 0; i < height; ++i)
    {
        cards.emplace_back();
        for (auto j = 0; j < width; ++j)
            cards[i].push_back(nullptr);
    }

    for (auto i = 0; i < height * width; i += 2)
    {
        int i1 = pairs[i] / width, j1 = pairs[i] % width;
        cards[i1][j1] = new Card(i1, j1, get_point(i1, j1), size, get_pic(pictures[i / 2], size), cb_show);
        attach(*cards[i1][j1]);
        attach(*cards[i1][j1]->show);

        int i2 = pairs[i + 1] / width, j2 = pairs[i + 1] % width;
        cards[i2][j2] = new Card(i2, j2, get_point(i2, j2), size, get_pic(pictures[i / 2], size), cb_show);
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

                    Fl::redraw();

                    return;
                }
        }
    }
}

void Field::exit()
{
    wait(3);
    messages.put("Do you want to exit?");
    wait(2);

    hide();
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

    Fl::redraw();

    if (ready == height * width / 2 - 1)
    {
        treat_last(c);
    }
}
