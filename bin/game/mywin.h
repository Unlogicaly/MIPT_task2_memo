#ifndef MYWIN_H
#define MYWIN_H

#include "editting_files.h"
#include "tracer.h"

class myWin;
class Field;

const std::vector<std::pair<int, int>> modes = {{4, 4}, {6, 6}, {8, 8}, {6, 5}, {8, 7}, {10, 8}};

std::pair<int, int> convert(myWin &win, int n, int m, bool reverse);

class modeChoose : public Graph_lib::Widget
{
  private:
    std::vector<Graph_lib::Button *> menu;

    Graph_lib::Window &win;

  public:
    modeChoose(myWin &win, Graph_lib::Callback cb_start);

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
};

class playAgain : public Graph_lib::Widget
{
  private:
    Graph_lib::Text *asc;

    Graph_lib::Button *yes;
    Graph_lib::Button *no;

    Graph_lib::Window &win;

  public:
    playAgain(Graph_lib::Window &win, Graph_lib::Callback cb_again, Graph_lib::Callback cb_end);

    void attach(Graph_lib::Window &win) override
    {
        win.attach(*asc);

        win.attach(*yes);

        win.attach(*no);
    }

    void hide_q()
    {
        asc->set_label("");
        no->hide();
        yes->hide();
    }

    void show_q()
    {
        asc->set_label("Play again?");
        yes->show();
        no->show();
    }
};

class myWin : public Graph_lib::Window
{
  private:
    static void cb_exit(Graph_lib::Address, Graph_lib::Address addr) { static_cast<myWin *>(addr)->exit(); }

    static void cb_start(Graph_lib::Address pwin, Graph_lib::Address pwid) { static_cast<myWin *>(pwid)->start(pwin); }

    static void cb_end(Graph_lib::Address, Graph_lib::Address pwid)
    {
        static_cast<myWin *>(pwid)->end = true;
        static_cast<myWin *>(pwid)->exit();
    }

    void start(Graph_lib::Address addr)
    {
        Fl_Widget &w = Graph_lib::reference_to<Fl_Widget>(addr);

        auto [j, i] = convert(*this, w.x(), w.y(), true);

        int mode = i * 3 + j;

        height = modes[mode].first;
        width = modes[mode].second;

        started = true;
    }

    void exit() { hide(); }

    Graph_lib::Button *exit_button;

    modeChoose *mode_ch;
    playAgain *play_ag;

    Field *field;

    int height, width;

    int size, shift, side_gap, up_gap;

    int choose_mode_bs, yes_no_bs; // Размер кнопок выбора режима и ответа да/нет

  public:
    bool &end;

    void asc();

    bool started{false};

    myWin(bool &end, int x_resol, int y_resol);

    int get_size() const { return size; }
    int get_shift() const { return shift; }
    int get_side_gap() const { return side_gap; }
    int get_up_gap() const { return up_gap; }

    int get_width() const { return width; }
    int get_height() const { return height; }

    int get_choose_mode_bs() const { return choose_mode_bs; }
    int get_yes_no_bs() const { return choose_mode_bs; }

    void set_size(int value) { size = value; }
    void set_shift(int value) { shift = value; }
    void set_side_gap(int value) { side_gap = value; }
    void set_up_gap(int value) { up_gap = value; }
};

#endif // MYWIN_H
