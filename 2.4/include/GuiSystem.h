#ifndef GUISYSTEM_H
#define GUISYSTEM_H
#include<Windows.h>
#include<bits/stdc++.h>
#include "ListOfPair.h"
#include "Event_type.h"
#define LIBRARY L"SDL2.dll"
#define BOARD_SIZE 8
#define TERMINATE_FLAG -2
#define SDL_WINDOWPOS_CENTERED 0x2FFF0000
#define SDL_RENDERER_ACCELERATED 0x00000002
#define SDL_MOUSEBUTTONDOWN 0x0401
#define SDL_QUIT 0x100
#define CELLWITDH 60
#define WINDOW_HEIGHT 600
#define WINDOW_WITDH 1000
#define BOARDCOLOR_1 0,128,0,255
#define BOARDCOLOR_2 0,96,0,255
#define BACKGROUND_COLOR 143,217,209,1
#define BLACK 0,0,0,1
#define WHITE 255,255,255,1
#define GREY 128,128,128,1
typedef struct SDL_Rect {
    int x, y;
    int w, h;
} SDL_Rect;
typedef enum Option{
    SETTING, START_GAME, QUIT, CONTINUE, NONE,ENDGAME
} Option;
typedef void* (*SDL_CreateWindow_ptr)(const char*, int, int, int, int, unsigned int);
typedef void* (*SDL_CreateRenderer_ptr)(void*, int, unsigned int);
typedef void (*SDL_RenderPresent_ptr)(void*);
typedef void (*SDL_SetRenderDrawColor_ptr)(void*, Uint8, Uint8, Uint8, Uint8);
typedef void (*SDL_RenderClear_ptr)(void*);
typedef void (*SDL_RenderFillRect_ptr)(void*, const SDL_Rect*);
typedef int (*SDL_RenderDrawLine_ptr)(void*, int, int, int, int);
typedef void (*SDL_RenderDrawPoint_ptr)(void*, int,int);
typedef int (*SDL_POLLEvent_ptr)(void*);
typedef Uint32 (*SDL_GetMouseState_ptr)(int *, int*);
typedef void (*SDL_Delay_ptr)(Uint32);
typedef void* (*SDL_LoadBMP_RW)(void*, int);
typedef void* (*SDL_RWFromFile)(const char*, const char*);
typedef void* (*SDL_CreateTextureFromSurface)(void*,void*);
typedef void (*SDL_FreeSurface)(void*);
typedef int (*SDL_QueryTexture)(void*, Uint32 *, int *,int *,int *);
typedef int (*SDL_RenderCopy)(void*,void*,const SDL_Rect*,const SDL_Rect*);
using namespace std;
class GuiSystem{
private:
    SDL_CreateWindow_ptr createGuiWindow;
    SDL_CreateRenderer_ptr createRenderer;
    SDL_RenderPresent_ptr renderPresent;
    SDL_SetRenderDrawColor_ptr setRenderColor;
    SDL_RenderClear_ptr renderClear;
    SDL_RenderFillRect_ptr renderFillRect;
    SDL_RenderDrawLine_ptr renderDrawLine;
    SDL_RenderDrawPoint_ptr renderDrawPoint;
    SDL_POLLEvent_ptr pollEvent;
    SDL_GetMouseState_ptr getMouseState;
    SDL_Delay_ptr delay;
    SDL_LoadBMP_RW loadBMP_RW;
    SDL_RWFromFile rwFromFile;
    SDL_CreateTextureFromSurface createTextureFromSurface;
    SDL_FreeSurface freeSurface;
    SDL_QueryTexture queryTexture;
    SDL_RenderCopy renderCopy;
    HINSTANCE lib;
    void * pwindow;
    void * prender;
public:
    GuiSystem();
    void init();
    void drawBoard();
    void drawCircle(int x, int y, int radius,int r, int g, int b, int a);
    void drawCurrState(int** board);
    void delayMiliSeconds(Uint32 n);
    int waitForChoosingMove(ListOfPair* valid_moves);
    enum Option menu();
    enum Option endGame(string winner);
    ~GuiSystem();
};
#endif
