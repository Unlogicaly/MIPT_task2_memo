#ifndef MYWIN_H
#define MYWIN_H

#include "editting_files.h"
#include "tracer.h"

constexpr int mbs = 160;

const std::vector<std::pair<int, int>> modes = {{4, 4}, {6, 6}, {8, 8}, {6, 5}, {8, 7}, {10, 8}};

std::pair<int, int> convert(int n, int m, bool reverse);

class Field;

class modeChoose : public Graph_lib::Widget
{
  private:
    std::vector<Graph_lib::Button *> menu;

    //    void draw_lines() {

    //    }

  public:
    modeChoose(Graph_lib::Window &win, Graph_lib::Callback cb_start);

    void show() override
    {
        for (auto &button : menu)
        {
            button->show();
        }
    }

    void hide_menu()
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

    int size() { return menu.size(); }
};

class myWin : public Graph_lib::Window
{
  private:
    Graph_lib::Button exit_button;

    static void cb_exit(Graph_lib::Address, Graph_lib::Address addr) { static_cast<myWin *>(addr)->exit(); }

    static void cb_start(Graph_lib::Address pwin, Graph_lib::Address pwid) { static_cast<myWin *>(pwid)->start(pwin); }

    void start(Graph_lib::Address addr)
    {
        Fl_Widget &w = Graph_lib::reference_to<Fl_Widget>(addr);

        auto [j, i] = convert(w.x(), w.y(), true);

        int mode = i * 3 + j;

        height = modes[mode].first;
        width = modes[mode].second;

        std::cerr << i << " \t" << j << std::endl;
        std::cerr << height << " \t" << width << std::endl;

        started = true;
    }

    void exit() { hide(); }

    modeChoose *menu;

    Field *field;

    bool started{false};

  public:
    int height, width;

    myWin();
};

#endif // MYWIN_H
