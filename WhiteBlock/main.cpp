#include <easyx.h>
#include <stdio.h>

#define INTERVAL 100 //标题高度
#define GRID_W 100
#define GRID_H 150

//存储每一行黑块的编号
int flag[4] = {3, 0, 1, 2};

//绘制界面
void draw() {
  //设置文字颜色
  settextcolor(BLACK);
  //设置文字样式
  settextstyle(36, 0, "微软雅黑");
  //输出标题
  char title[] = "别踩白块";
  int space = (getwidth() - textwidth(title)) / 2;
  outtextxy(space, 20, title);

  //设置线条颜色
  setlinecolor(BLACK);
  //设置线条样式
  setlinestyle(PS_SOLID, 2);
  //绘制格子
  for (int i = 0; i < 5; ++i) {
    line(0, INTERVAL + i * GRID_H, 400, INTERVAL + i * GRID_H);
    line(i * GRID_W, 100, i * GRID_W, 700);
  }

  //绘制黑块
  setfillcolor(BLACK);
  for (int i = 0; i < 4; ++i) {
    int x = flag[i] * GRID_W;
    int y = i * GRID_H + INTERVAL;
    solidrectangle(x, y, x + GRID_W, y + GRID_H);
  }
}

int main() {
  //创建窗口
  initgraph(400, 700);
  //设置背景颜色为白色
  setbkcolor(WHITE);
  //用设置的颜色填充整个窗口
  cleardevice();

  draw();

  while (true) {
    //消息循环
  }

  getchar(); //防止闪退
  return 0;
}