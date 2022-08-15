#include "graphics.h"
#include "time.h"
#include <iostream>

#define WIN_SIZE 500            //窗口大小
#define WIN_HALF (WIN_SIZE / 2) //窗口一半

IMAGE spaceMan[59]; //太空人图片
void loadImg() {
  //加载图片
  char fileName[50] = {0};
  for (int i = 0; i < 59; ++i) {
    sprintf_s(fileName, "../images/human (%d).jpg", i + 2);
    //加载图片
    loadimage(spaceMan + i, fileName, 140, 130);
  }
}

void setTextStyle(int h, int w, const char *faceName) {
  LOGFONT f = {0};
  f.lfHeight = h;
  f.lfWidth = w;
  strcpy(f.lfFaceName, faceName);
  settextstyle(&f);
}

//太空人动画效果
void animation() {
  static DWORD t1 = clock(); //只初始化一次
  DWORD t2 = clock(); //获取程序运行到调用该函数所经过的毫秒数
  //把图片输出到窗口上面
  static int i = 0;
  if (t2 - t1 > 20) {
    //贴图
    putimage(150, 150, spaceMan + i);
    t1 = t2;
  }
  i = (i + 1) % 59;
}

//其他界面绘制
void gameDraw() {
  setbkcolor(RGB(223, 230, 240)); //设置背景颜色
  cleardevice();                  //清空绘图设备
  //绘制表盘

  //显示动态时间
  //获取当前系统时间
  time_t curTime = time(NULL);
  printf("%lld\n", curTime);
  struct tm *humanTime = localtime(&curTime);

  char buf[40] = {0};
  sprintf_s(buf, "%d:%d", humanTime->tm_hour, humanTime->tm_min);
  outtextxy(105, 120, buf);

  sprintf_s(buf, "%d", humanTime->tm_sec);
  outtextxy(335, 160, buf);
}

int main() {
  //创建图形窗口
  initgraph(500, 500, EW_SHOWCONSOLE);

  setbkcolor(RGB(223, 230, 240)); //设置背景颜色
  cleardevice();                  //清空绘图设备
  //设置文字样式
  settextcolor(BLACK);
  setTextStyle(55, 23, "Arial");
  outtextxy(50, 50, "90%");
  loadImg();
  while (true) {
    animation();
    gameDraw();
  }

  getchar();
  return 0;
}
