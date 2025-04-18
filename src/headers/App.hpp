#pragma once

#include "Board.hpp"
#include "Info.hpp"

class App {
public:
  App(unsigned int board_size);

  Board *get_board();

  void init();
  void update();
  void render_app();
  void render_info();
  void run();

  void loadCustomFont();

private:
  Board board;
  Color turn;
  Info info;
  bool end_game;
};