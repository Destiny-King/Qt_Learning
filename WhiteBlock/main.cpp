#include <easyx.h>
#include <stdio.h>

#define INTERVAL 100 //����߶�
#define GRID_W 100
#define GRID_H 150

//�洢ÿһ�кڿ�ı��
int flag[4] = {3, 0, 1, 2};

//���ƽ���
void draw() {
  //����������ɫ
  settextcolor(BLACK);
  //����������ʽ
  settextstyle(36, 0, "΢���ź�");
  //�������
  char title[] = "��Ȱ׿�";
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

int main() {
  //��������
  initgraph(400, 700);
  //���ñ�����ɫΪ��ɫ
  setbkcolor(WHITE);
  //�����õ���ɫ�����������
  cleardevice();

  draw();

  while (true) {
    //��Ϣѭ��
  }

  getchar(); //��ֹ����
  return 0;
}