#ifndef PLAYAGAIN_H
#define PLAYAGAIN_H

#include "editting_files.h"

class myWin;

class playAgain : public Graph_lib::Widget
{
  private:
    Graph_lib::Image *asc;

    Graph_lib::Button *yes_b;
    Graph_lib::Image *yes_im;

    Graph_lib::Button *no_b;
    Graph_lib::Image *no_im;

    Graph_lib::Rectangle *back;

    int _size;

    Graph_lib::Window &win;

  public:
    playAgain(myWin &win, Graph_lib::Callback cb_again, Graph_lib::Callback cb_end);

    void attach(Graph_lib::Window &win) override;

    void hide_q();

    void show_q();

    ~playAgain() override;
};

#endif // PLAYAGAIN_H
