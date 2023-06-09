#include "include/GuiSystem.h"

GuiSystem::GuiSystem(){
    this->pwindow = NULL;
    this->prender = NULL;
    this->lib = LoadLibraryW(LIBRARY);
    this->createGuiWindow = (SDL_CreateWindow_ptr)GetProcAddress(this->lib, "SDL_CreateWindow");
    this->createRenderer = (SDL_CreateRenderer_ptr)GetProcAddress(this->lib, "SDL_CreateRenderer");
    this->renderPresent = (SDL_RenderPresent_ptr)GetProcAddress(this->lib, "SDL_RenderPresent");
    this->setRenderColor = (SDL_SetRenderDrawColor_ptr)GetProcAddress(this->lib, "SDL_SetRenderDrawColor");
    this->renderClear = (SDL_RenderClear_ptr)GetProcAddress(this->lib, "SDL_RenderClear");
    this->renderFillRect = (SDL_RenderFillRect_ptr)GetProcAddress(this->lib, "SDL_RenderFillRect");
    this->renderDrawLine = (SDL_RenderDrawLine_ptr)GetProcAddress(this->lib, "SDL_RenderDrawLine");
    this->renderDrawPoint = (SDL_RenderDrawPoint_ptr)GetProcAddress(this->lib,"SDL_RenderDrawPoint");
    this->pollEvent = (SDL_POLLEvent_ptr)GetProcAddress(this->lib,"SDL_PollEvent");
    this->getMouseState = (SDL_GetMouseState_ptr)GetProcAddress(this->lib,"SDL_GetMouseState");
    this->delay = (SDL_Delay_ptr)GetProcAddress(this->lib,"SDL_Delay");
    this->loadBMP_RW = (SDL_LoadBMP_RW)GetProcAddress(this->lib,"SDL_LoadBMP_RW");
    this->createTextureFromSurface = (SDL_CreateTextureFromSurface)GetProcAddress(this->lib,"SDL_CreateTextureFromSurface");
    this->queryTexture = (SDL_QueryTexture)GetProcAddress(this->lib,"SDL_QueryTexture");
    this->freeSurface = (SDL_FreeSurface)GetProcAddress(this->lib,"SDL_FreeSurface");
    this->renderCopy = (SDL_RenderCopy)GetProcAddress(this->lib,"SDL_RenderCopy");
    this->rwFromFile = (SDL_RWFromFile)GetProcAddress(this->lib,"SDL_RWFromFile");
}

GuiSystem::~GuiSystem(){
    FreeLibrary(this->lib);
}

void GuiSystem::init(){
    this->pwindow = this->createGuiWindow("My game",SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WITDH, WINDOW_HEIGHT, 0);
    this->prender = this->createRenderer(this->pwindow,-1,SDL_RENDERER_ACCELERATED);
}

void GuiSystem::drawBoard(){
    SDL_Rect rect;
    rect.w = WINDOW_WITDH;
    rect.h = WINDOW_HEIGHT;
    rect.x =0;
    rect.y =0;
    this->setRenderColor(this->prender,BACKGROUND_COLOR);
    this->renderFillRect(this->prender,&rect);
    rect.w = rect.h = CELLWITDH;
    int x_offset = (WINDOW_WITDH - 8*CELLWITDH)/2;
    int y_offset = (WINDOW_HEIGHT - 8*CELLWITDH)/2;
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            rect.x = x_offset + col * CELLWITDH;
            rect.y = y_offset + row * CELLWITDH;
            if ((row+col)%2==0) this->setRenderColor(this->prender,BOARDCOLOR_1);
                else this->setRenderColor(this->prender,BOARDCOLOR_2);
            this->renderFillRect(this->prender,&rect);
        }
    }
    this->renderPresent(this->prender);
}

void GuiSystem::drawCircle(int x,int y, int radius, int r, int g, int b, int a){
    this->setRenderColor(this->prender,r,g,b,a);
    for (int i = x-radius;i<=x+radius;i++){
        for (int j=y-radius;j<=y+radius;j++){
            if ((i-x)*(i-x)+(j-y)*(j-y)<=radius*radius) this->renderDrawPoint(this->prender,i,j);
        }
    }
    this->renderPresent(this->prender);
}

void GuiSystem::delayMiliSeconds(Uint32 n){
    this->delay(n);
}

void GuiSystem::drawCurrState(int** board){
    this->renderClear(this->prender);
    this->drawBoard();
    int x_offset = (WINDOW_WITDH - 8*CELLWITDH)/2;
    int y_offset = (WINDOW_HEIGHT - 8*CELLWITDH)/2;
    int x,y;
    int radius = CELLWITDH/2;
    for (int row=0;row<BOARD_SIZE;row++){
        for (int col=0;col<BOARD_SIZE;col++) {
            x = x_offset + col*CELLWITDH;
            y = y_offset + row*CELLWITDH;
            if (board[row][col]==1) this->drawCircle(x+radius,y+radius,radius,WHITE);
            else if (board[row][col]==-1) this->drawCircle(x+radius,y+radius,radius,BLACK);
        }
    }

}

int GuiSystem::waitForChoosingMove(ListOfPair* valid_moves){
    if (valid_moves == NULL) return -1;
    int ** move_ptr = new int*[valid_moves->getSize()];
    for (int i=0;i<valid_moves->getSize();i++) {
        move_ptr[i] = new int[2];
        move_ptr[i][0] = valid_moves[0][i][0];
        move_ptr[i][1] = valid_moves[0][i][1]; 
    }
    SDL_Event event;
    int ans = 0;
    int x_offset = (WINDOW_WITDH-8*CELLWITDH)/2;
    int y_offset = (WINDOW_HEIGHT-8*CELLWITDH)/2;
    bool looping = true;
    while (looping){
        if (this->pollEvent(&event) !=0){
            if (event.type==SDL_QUIT){
                looping = false;
                throw Terminate_program();
                break;
            }
            if (event.type==SDL_MOUSEBUTTONDOWN){
                int x,y;
                this->getMouseState(&x,&y);
                for (int i=0;i<valid_moves->getSize();i++){
                    if ((x > (x_offset+move_ptr[i][1]*CELLWITDH))
                    && (x < (x_offset+(move_ptr[i][1]+1)*CELLWITDH))
                    && (y > (y_offset+move_ptr[i][0]*CELLWITDH))
                    && (y <  (y_offset+(move_ptr[i][0]+1)*CELLWITDH))){ 
                        ans = i;
                        looping = false;
                        break;
                    }
                }
            }
        }
    }
    for (int i=0;i<valid_moves->getSize();i++) delete[] move_ptr[i];
    delete[] move_ptr;
    return ans;
}

enum Option GuiSystem::menu(){
    SDL_Rect rect;
    rect.x = 0;
    rect.y = 0;
    void * textSurface = this->loadBMP_RW(this->rwFromFile("bitmap/menu.bmp","rb"),1);
    void * texture = this->createTextureFromSurface(this->prender,textSurface);
    this->freeSurface(textSurface);
    this->queryTexture(texture,NULL,NULL,&rect.w,&rect.h);
    this->renderCopy(this->prender,texture,NULL,&rect);
    this->renderPresent(this->prender);
    SDL_Event event;
    enum Option option;
    bool looping = true;
    while (looping){
        if (this->pollEvent(&event) !=0){
            if (event.type==SDL_QUIT){
                looping = false;
                throw Terminate_program();
                break;
            }
            if (event.type==SDL_MOUSEBUTTONDOWN){
                int x,y;
                this->getMouseState(&x,&y);
                if (x>=62 && x<= 165 && y>=68 && y<=119) {
                    option = START_GAME;
                    looping = false;
                    break;
                } else if (x>=192 && x<=279 && y<= 320 && y>= 270){
                    throw Terminate_program();
                }
            }
        }
    }
    return option;
}

enum Option GuiSystem::endGame(string winner){
    int x_offset = (WINDOW_WITDH - 500)/2;
    int y_offset = (WINDOW_HEIGHT - 300)/2;
    SDL_Rect rect;
    rect.x = x_offset;
    rect.y = y_offset;
    cout<<winner.c_str()<<endl;
    void * textSurface = this->loadBMP_RW(this->rwFromFile(winner.c_str(),"rb"),1);
    void * texture = this->createTextureFromSurface(this->prender,textSurface);
    this->freeSurface(textSurface);
    this->queryTexture(texture,NULL,NULL,&rect.w,&rect.h);
    this->renderCopy(this->prender,texture,NULL,&rect);
    this->renderPresent(this->prender);
    SDL_Event event;
    enum Option option;
    bool looping = true;
    while (looping){
        if (this->pollEvent(&event) !=0){
            if (event.type==SDL_QUIT){
                looping = false;
                throw Terminate_program();
                break;
            }
            if (event.type==SDL_MOUSEBUTTONDOWN){
                int x,y;
                this->getMouseState(&x,&y);
                if (x>=16+x_offset && x<=213+x_offset && y<= 289+x_offset && y>= 241+y_offset) {
                    option = START_GAME;
                    looping = false;
                    break;
                }
                else if (x>=366+x_offset && x<=455+x_offset && y<= 289+x_offset && y>= 241+y_offset){
                    throw Terminate_program();
                }
            }
        }
    }
    return option;
}