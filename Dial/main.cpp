#include "Draw.hpp"

int main() {
  initgraph(WIN_SIZE, WIN_SIZE /*,EW_SHOWCONSOLE*/);
  SetWindowNewStyle(WIN_SIZE, WIN_SIZE);

  loadImg();

  BeginBatchDraw(); //Ë«»º³å
  while (true) {
    gameDraw();
    animation();

    mouseEvent();

    FlushBatchDraw();
  }
  EndBatchDraw();

  getchar();
  return 0;
}