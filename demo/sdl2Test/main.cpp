#include <stdio.h>

extern "C"{
#include "SDL.h"
//SDL中的SDL_main.h已经定义了main
#undef main
}

int main()
{
    //初始化视频
    if(SDL_Init(SDL_INIT_VIDEO)){
        //如果初始化失败，打印错误信息
        printf("Can't initialize SDL - %s\n",SDL_GetError());
    }else {
        printf("Success init SDL");
    }

    return 0;
}
