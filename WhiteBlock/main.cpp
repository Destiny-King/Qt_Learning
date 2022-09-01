#include <easyx.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define INTERVAL 100 //����߶�
#define GRID_W 100
#define GRID_H 150

//�洢ÿһ�кڿ�ı��
int flag[4] = {3, 0, 1, 2};
//��Ϸ������־
bool isOver = false;
//����
int score = 0;
//��ʱ
int startTime = 0;
//��ʼ������
void init() {
  //�������������
  srand(time(NULL));
  //��ʼ��flag
  for (int i = 0; i < 4; ++i) {
    flag[i] = rand() % 4;
  }
}

//���ƽ���
void draw() {
  //����������ɫ
  settextcolor(BLACK);
  //����������ʽ
  settextstyle(36, 0, "΢���ź�");
  //�������
  char title[50] = "��Ȱ׿�";
  //ƴ�ӷ���
  sprintf_s(title, "��Ȱ׿� %d %d", score, (clock() - startTime) / 1000);
  int space = (getwidth() - textwidth(title)) / 2;
  outtextxy(space, 20, title);

  //����������ɫ
  setlinecolor(BLACK);
  //����������ʽ
  setlinestyle(PS_SOLID, 2);
  //���Ƹ���
  for (int i = 0; i < 5; ++i) {
    line(0, INTERVAL + i * GRID_H, 400, INTERVAL + i * GRID_H);
    line(i * GRID_W, 100, i * GRID_W, 700);
  }

  //���ƺڿ�
  setfillcolor(BLACK);
  for (int i = 0; i < 4; ++i) {
    int x = flag[i] * GRID_W;
    int y = i * GRID_H + INTERVAL;
    solidrectangle(x, y, x + GRID_W, y + GRID_H);
  }
}

//��������һ�����Ӵ���
void mouseMsg(ExMessage *msg) {
  if (msg->message == WM_LBUTTONDOWN) {
    //�Ȼ�ȡ���һ���ڿ������
    int x = flag[3] * GRID_W;
    int y = 3 * GRID_H + INTERVAL;
    //���ж��ǲ��ǵ�������һ���ڿ�
    if (msg->x >= x && msg->x <= x + GRID_W && msg->y >= y &&
        msg->y <= y + GRID_H) {
      //��������
      for (int i = 3; i > 0; i--) {
        flag[i] = flag[i - 1];
      }

      //�±�Ϊ0�ĺڿ�����һ��
      flag[0] = rand() % 4;
      score++;
    } else {
      isOver = true;
    }
  }
}

//�ж��Ƿ�ʧ��
void gameOver() {
  if (isOver) {
    int ret = MessageBox(GetHWnd(), "������", "��Ϸ����", MB_OKCANCEL);
    if (ret == IDOK) {
      //������Ϸ
      isOver = false;
      init();
    } else {
      //�˳���Ϸ
      exit(0);
    }
  }
}

int main() {
  //��������
  initgraph(400, 700, EW_SHOWCONSOLE);
  //���ñ�����ɫΪ��ɫ
  setbkcolor(WHITE);
  //�����õ���ɫ�����������
  cleardevice();

  init();
  startTime = clock();

  while (true) {
    //˫����
    BeginBatchDraw();
    //����
    cleardevice();
    draw();
    //ˢ�´���
    FlushBatchDraw();
    if (isOver) {
      gameOver();
    }
    //��Ϣѭ��
    ExMessage msg;
    //�����ȡ����Ϣ������true
    if (peekmessage(&msg, EM_MOUSE)) {
      if (msg.message == WM_LBUTTONDOWN) { //���������
        mouseMsg(&msg);
      }
    }
  }

  getchar(); //��ֹ����
  return 0;
}