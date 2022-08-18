#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

using namespace std;

#undef main
int main() {
  if (SDL_Init(SDL_INIT_VIDEO) == -1) { // SDL_��ʼ��
    printf("Could not initialize SDL!\n");
    return 0;
  }
  printf("SDL initialized.\n");

  //��������
  SDL_Window *win =
      SDL_CreateWindow("picture", SDL_WINDOWPOS_CENTERED,
                       SDL_WINDOWPOS_CENTERED, 600, 480, SDL_WINDOW_SHOWN);
  //������Ⱦ��
  SDL_Renderer *ren = SDL_CreateRenderer(
      win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

  //��������
  SDL_Surface *temp_Surface = IMG_Load("1.png");

  if (win == NULL || ren == NULL || temp_Surface == NULL)
    printf("%s\n", SDL_GetError());

  //��������
  SDL_Texture *tex = NULL;
  tex = SDL_CreateTextureFromSurface(ren, temp_Surface);
  //�����Ⱦ��
  SDL_RenderClear(ren);
  //�����ʸ��Ƶ���Ⱦ��
  SDL_RenderCopy(ren, tex, NULL, NULL);
  //������Ⱦ��
  SDL_RenderPresent(ren);

  int quit = 0;    //�˳�
  SDL_Event event; //�����˳��

  while (!quit) { //����Ϣѭ��
    SDL_WaitEvent(&event);
    switch (event.type) {
      //�û��Ӳ˵�Ҫ���˳�����
    case SDL_QUIT:
      quit = 1;
      break;
    }
  }

  //������Դ
  SDL_DestroyTexture(tex);
  SDL_FreeSurface(temp_Surface);
  SDL_DestroyRenderer(ren);
  if (SDL_GetError())
    printf("%s\n", SDL_GetError());
  SDL_Quit(); //�˳�SDL����

  return 0;
}