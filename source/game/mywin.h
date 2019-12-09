#ifndef MYWIN_H
#define MYWIN_H

#include "modechoose.h"
#include "tracer.h"

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

    void start(Graph_lib::Address addr);

    void exit() { hide(); }

    Graph_lib::Button *exit_button;
    Graph_lib::Button *new_button;

    modeChoose *mode_ch;

    playAgain *play_ag;

    int height, width; // Размеры поля

    int size, shift, side_gap,
        up_gap; // размер карточки, длина промежутка между карточками, отступ с боков, отступ сверху и снизу

    int choose_mode_bs, yes_no_bs; // Размер кнопок выбора режима и ответа да/нет

  public:
    bool &end;
    bool started{false};

    myWin(bool &end, int x_resol, int y_resol);

    void asc() { attach(*play_ag); }

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
        delete new_button;
    }
};

#endif // MYWIN_H
