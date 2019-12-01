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
        TRACE_FUNC;
        for (auto &button : menu)
        {
            std::cerr << button->label << std::endl;
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

class playAgain : public Graph_lib::Widget
{
  private:
    Graph_lib::Image *asc;

    Graph_lib::Button *yes_b;
    Graph_lib::Image *yes_im;

    Graph_lib::Button *no_b;
    Graph_lib::Image *no_im;

    Graph_lib::Rectangle *back;

    Graph_lib::Window &win;

    int _size;

  public:
    playAgain(myWin &win, Graph_lib::Callback cb_again, Graph_lib::Callback cb_end);

    void attach(Graph_lib::Window &win) override
    {
        win.attach(*back);

        win.attach(*asc);

        win.attach(*yes_b);
        win.attach(*yes_im);

        win.attach(*no_b);
        win.attach(*no_im);
    }

    void hide_q()
    {
        win.detach(*asc);

        win.detach(*back);

        no_b->hide();
        win.detach(*no_im);

        yes_b->hide();
        win.detach(*yes_im);
    }

    void show_q()
    {
        win.attach(*asc);

        win.attach(*back);

        yes_b->show();
        win.attach(*yes_im);

        no_b->show();
        win.attach(*no_im);
    }

    ~playAgain() override
    {
        delete asc;
        delete no_im;
        delete no_b;
        delete yes_im;
        delete yes_b;
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

        int j = (w.x() + choose_mode_bs * 3 / 2 - x_max() / 2) / choose_mode_bs;
        int i = (w.y() + choose_mode_bs - y_max() / 2) / choose_mode_bs;

        int mode = i * 3 + j;

        height = modes[mode].second;
        width = modes[mode].first;

        started = true;
    }

    void exit() { hide(); }

    Graph_lib::Button *exit_button;

    modeChoose *mode_ch;
    playAgain *play_ag;

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

    ~myWin()
    {
        delete mode_ch;
        delete play_ag;
        delete exit_button;
    }
};

#endif // MYWIN_H
