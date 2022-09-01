#include <easyx.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define INTERVAL 100 //标题高度
#define GRID_W 100
#define GRID_H 150

//存储每一行黑块的编号
int flag[4] = {3, 0, 1, 2};
//游戏结束标志
bool isOver = false;
//计数
int score = 0;
//计时
int startTime = 0;
//初始化数据
void init() {
  //设置随机数种子
  srand(time(NULL));
  //初始化flag
  for (int i = 0; i < 4; ++i) {
    flag[i] = rand() % 4;
  }
}

//绘制界面
void draw() {
  //设置文字颜色
  settextcolor(BLACK);
  //设置文字样式
  settextstyle(36, 0, "微软雅黑");
  //输出标题
  char title[50] = "别踩白块";
  //拼接分数
  sprintf_s(title, "别踩白块 %d %d", score, (clock() - startTime) / 1000);
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

//鼠标点击最后一个格子处理
void mouseMsg(ExMessage *msg) {
  if (msg->message == WM_LBUTTONDOWN) {
    //先获取最后一个黑块的坐标
    int x = flag[3] * GRID_W;
    int y = 3 * GRID_H + INTERVAL;
    //先判断是不是点击的最后一个黑块
    if (msg->x >= x && msg->x <= x + GRID_W && msg->y >= y &&
        msg->y <= y + GRID_H) {
      //遍历数组
      for (int i = 3; i > 0; i--) {
        flag[i] = flag[i - 1];
      }

      //下标为0的黑块重置一下
      flag[0] = rand() % 4;
      score++;
    } else {
      isOver = true;
    }
  }
}

//判断是否失败
void gameOver() {
  if (isOver) {
    int ret = MessageBox(GetHWnd(), "你输了", "游戏结束", MB_OKCANCEL);
    if (ret == IDOK) {
      //继续游戏
      isOver = false;
      init();
    } else {
      //退出游戏
      exit(0);
    }
  }
}

int main() {
  //创建窗口
  initgraph(400, 700, EW_SHOWCONSOLE);
  //设置背景颜色为白色
  setbkcolor(WHITE);
  //用设置的颜色填充整个窗口
  cleardevice();

  init();
  startTime = clock();

  while (true) {
    //双缓冲
    BeginBatchDraw();
    //清屏
    cleardevice();
    draw();
    //刷新窗口
    FlushBatchDraw();
    if (isOver) {
      gameOver();
    }
    //消息循环
    ExMessage msg;
    //如果获取到消息，返回true
    if (peekmessage(&msg, EM_MOUSE)) {
      if (msg.message == WM_LBUTTONDOWN) { //鼠标左键点击
        mouseMsg(&msg);
      }
    }
  }

  getchar(); //防止闪退
  return 0;
}