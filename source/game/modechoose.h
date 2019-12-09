#ifndef MODECHOOSE_H
#define MODECHOOSE_H

#include "playagain.h"

const std::vector<std::pair<int, int>> modes = {{4, 4}, {6, 6}, {8, 8}, {6, 5}, {8, 7}, {10, 8}};

class modeChoose : public Graph_lib::Widget
{
  private:
    std::vector<Graph_lib::Button *> menu;

  public:
    modeChoose(myWin &win, Graph_lib::Callback cb_start);

    void hide() override
    {
        for (auto &button : menu)
        {
            button->hide();
        }
    }

    void attach(Graph_lib::Window &win) override
    {
        for (auto &button : menu)
        {
            win.attach(*button);
        }
    }

    ~modeChoose() override
    {
        for (auto &button : menu)
        {
            delete button;
        }
    }
};

#endif // MODECHOOSE_H
