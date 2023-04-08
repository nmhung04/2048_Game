//GAME 2048
#include <SDL.h>
#include <stdio.h>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iostream>
using namespace std;

int boardGame[4][4] = {{0, 2, 0, 0},{0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};
int Score = 0;
//Board game is full?
bool isFull(int a[4][4])
{
    int cnt = 0;
    for(int i = 0; i <= 3; ++i)
    {
        for (int j = 0; j <= 3; ++j)
        {
            if(a[i][j] == 0) ++cnt;
        }
    }
    if (cnt != 0) return false;
    return true;
}

// Get random value: 2 or 4
int getRandomValue()
{
    srand(time(nullptr));
    int r = rand() % 2 ? 2 : 4;
    return r;
}

//Set random value for blank tile
void setRandValue(int a[4][4])
{
    vector <int> r;
    for (int i = 0; i <= 3; ++i)
    {
        for (int j = 0; j <= 3; ++j)
            if (a[i][j] == 0)
                r.push_back(i*10 + j);
    }
    int n = r.size();
    srand(time(nullptr));
    int pos = rand() % (n);
    a[r[pos] /10][r[pos] % 10] = getRandomValue();
}

//=======================Move LEFT and Merge Tiles======================================//
void moveLeft(int a[4][4])
{
    for (int row = 0; row <= 3; ++row)
    {
        for (int j = 0; j <= 3; ++j)
        {
            if (a[row][j] == 0)
            {
                int x = j;
                while (a[row][x] == 0 && x <= 3)
                    ++x;
                if (x > 3)
                    ;
                else
                {
                    a[row][j] = a[row][x];
                    a[row][x] = 0;
                }
            }
        }
    }
}

void MERGE_LEFT(int a[4][4])
{
    moveLeft(a);
    for (int row = 0; row <= 3; ++row)
    {
        for (int j = 0; j <= 2; ++j)
        {
            if (a[row][j] == a[row][j + 1])
            {
                Score += a[row][j];
                a[row][j] *= 2;
                a[row][j + 1] = 0;
            }
        }
    }
    moveLeft(a);
}
//==========================Move RIGHT and Merge Tiles==================================//
void moveRight(int a[4][4])
{
    for (int row = 0; row <= 3; ++row)
    {
        for (int j = 3; j >= 0; --j)
        {
            if (a[row][j] == 0)
            {
                int x = j;
                while (a[row][x] == 0 && x >= 0)
                    --x;
                if (x < 0);
                else
                {
                    a[row][j] = a[row][x];
                    a[row][x] = 0;
                }
            }
        }
    }
}
void MERGE_RIGHT(int a[4][4])
{
    moveRight(a);
    for (int row = 0; row <= 3; ++row)
    {
        for (int j = 3; j >= 1; --j)
        {
            if (a[row][j] == a[row][j - 1])
            {
                Score += a[row][j];
                a[row][j] *= 2;
                a[row][j - 1] = 0;
            }
        }
    }
    moveRight(a);
}
//===============================Move UP and Merge Tiles====================================//
void moveUp(int a[4][4])
{
    for (int col = 0; col <= 3; ++col)
    {
        for (int j = 0; j <= 3; ++j)
        {
            if (a[j][col] == 0)
            {
                int x = j;
                while (a[x][col] == 0 && x <= 3)
                    ++x;
                if (x > 3);
                else
                {
                    a[j][col] = a[x][col];
                    a[x][col] = 0;
                }
            }
        }
    }
}
void MERGE_UP(int a[4][4]){
    moveUp(a);
    for (int col = 0; col <= 3; ++col)
    {
        for (int j = 0; j <= 2; ++j)
        {
            if (a[j][col] == a[j+1][col])
            {   
                Score += a[j][col];
                a[j][col] *= 2;
                a[j+1][col] = 0;
            }
        }
    }
    moveUp(a);
}
//===================Move DOWN and Merge Tiles==========================//
void moveDown(int a[4][4])
{
    for (int col = 0; col <= 3; ++col)
    {
        for (int j = 3; j >= 0; --j)
        {
            if (a[j][col] == 0)
            {
                int x = j;
                while (a[x][col] == 0 && x >= 0)
                    --x;
                if (x < 0);
                else
                {
                    a[j][col] = a[x][col];
                    a[x][col] = 0;
                }
            }
        }
    }
    
}

void MERGE_DOWN(int a[4][4]){
    moveDown(a);
    for (int col = 0; col <= 3; ++col)
    {
        for (int j = 3; j >= 1; --j)
        {
            if (a[j][col] == a[j-1][col])
            {
                Score += a[j][col];
                a[j][col] *= 2;
                a[j-1][col] = 0;
            }
        }
    }
    moveDown(a);
}
//==========================================================//

const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 750;
const string WINDOW_TITLE = "2048 Game";

void logSDLError(std::ostream& os,
                 const std::string &msg, bool fatal = false);
void initSDL(SDL_Window* &window, SDL_Renderer* &renderer)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        logSDLError(std::cout, "SDL_Init", true);
    window = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
//window = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_CENTERED,
    //SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_FULLSCREEN_DESKTOP);
    if (window == nullptr) logSDLError(std::cout, "CreateWindow", true);
//Khi thông thường chạy với môi trường bình thường ở nhà
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED |
                                  SDL_RENDERER_PRESENTVSYNC);
//Khi chạy ở máy thực hành WinXP ở trường (máy ảo)
//renderer = SDL_CreateSoftwareRenderer(SDL_GetWindowSurface(window));
    if (renderer == nullptr) logSDLError(std::cout, "CreateRenderer", true);
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
}

//Exit
void quitSDL(SDL_Window* window, SDL_Renderer* renderer);
void quitSDL(SDL_Window* window, SDL_Renderer* renderer)
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

//Wait until key pressed
void waitUntilKeyPressed()
{
    SDL_Event e;
    while (true)
    {
        if ( SDL_WaitEvent(&e) != 0 &&
                (e.type == SDL_KEYDOWN || e.type == SDL_QUIT) )
            return;
        SDL_Delay(100);
    }
}



//Error message
void logSDLError(std::ostream& os,
                 const std::string &msg, bool fatal)
{
    os << msg << " Error: " << SDL_GetError() << std::endl;
    if (fatal)
    {
        SDL_Quit();
        exit(1);
    }
}


int main(int argc, char* argv[])
{
    SDL_Window* window;
    SDL_Renderer* renderer;
    initSDL(window, renderer);
// Your drawing code here
    SDL_SetRenderDrawColor(renderer, 240, 248, 255, 1);
    SDL_Rect W = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
    SDL_RenderFillRect(renderer, &W);
    SDL_SetRenderDrawColor(renderer, 70, 70, 70, 70);
    for (int i = 15; i<= 1000; i+= 15){
        SDL_RenderDrawLine(renderer,i, 0 , i, 750);
        SDL_RenderPresent(renderer);
    }
    for (int i = 15; i<= 750; i+= 15){
        SDL_RenderDrawLine(renderer,0, i , 1000, i);
        SDL_RenderPresent(renderer);
    }
    SDL_Rect board;
    board.x = 100;
    board.y = 200;
    board.w = 400;
    board.h = 400;
    SDL_SetRenderDrawColor(renderer, 100, 200, 100, 255);
    SDL_RenderFillRect(renderer, &board);
    int x1 = 100, x2 = 200, x3 = 300, x4 = 400, x5 = 500;
    int y1 = 200, y2 = 300, y3 = 400, y4 = 500, y5 = 600;
    SDL_SetRenderDrawColor(renderer, 100, 100, 100, 100);
    SDL_RenderDrawLine(renderer, x1, y1, x5, y1);
    SDL_RenderDrawLine(renderer, x1, y2, x5, y2);
    SDL_RenderDrawLine(renderer, x1, y3, x5, y3);
    SDL_RenderDrawLine(renderer, x1, y4, x5, y4);
    SDL_RenderDrawLine(renderer, x1, y5, x5, y5);

    SDL_RenderDrawLine(renderer, x1, y1, x1, y5);
    SDL_RenderDrawLine(renderer, x2, y1, x2, y5);
    SDL_RenderDrawLine(renderer, x3, y1, x3, y5);
    SDL_RenderDrawLine(renderer, x4, y1, x4, y5);
    SDL_RenderDrawLine(renderer, x5, y1, x5, y5);
    //  PLAY
    SDL_RenderDrawLine(renderer, x5 + x2, y2, x5 + x2 + 200, y2);
    SDL_RenderDrawLine(renderer, x5 + x2, y2 + 75, x5 + x2 + 200, y2 + 75);
    SDL_RenderDrawLine(renderer, x5 + x2, y2, x5 + x2, y2 + 75);
    SDL_RenderDrawLine(renderer, x5 + x2 + 200, y2, x5 + x2 + 200, y2 + 75);

    SDL_Rect Play;
    Play.x = x5 + x2;
    Play.y = y2;
    Play.w = 200;
    Play.h = 75;
    SDL_SetRenderDrawColor(renderer, 184, 134, 11, 1); // green
    SDL_RenderFillRect(renderer, &Play);
    //Play Again
    SDL_Rect PlAgain;
    PlAgain.x = x5 + x2;
    PlAgain.y = y4;
    PlAgain.w = 200;
    PlAgain.h = 75;
    SDL_SetRenderDrawColor(renderer, 184, 134, 11, 1);
    SDL_RenderFillRect(renderer, &PlAgain);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderDrawLine(renderer, x5 + x2, y4, x5 + x2 + 200, y4);
    SDL_RenderDrawLine(renderer, x5 + x2, y4 + 75, x5 + x2 + 200, y4 + 75);
    SDL_RenderDrawLine(renderer, x5 + x2, y4, x5 + x2, y4 + 75);
    SDL_RenderDrawLine(renderer, x5 + x2 + 200, y4, x5 + x2 + 200, y4 + 75);

    //Score
    SDL_Rect Score;
    Score.x = 50;
    Score.y = 75;
    Score.w = 200;
    Score.h = 60;
    SDL_SetRenderDrawColor(renderer, 184, 134, 11, 1);
    SDL_RenderFillRect(renderer, &Score);

    //MaxScore
    SDL_Rect maxScore;
    maxScore.x = 350;
    maxScore.y = 75;
    maxScore.w = 200;
    maxScore.h = 60;
    SDL_SetRenderDrawColor(renderer, 184, 134, 11, 1);
    SDL_RenderFillRect(renderer, &maxScore);
// use SDL_RenderPresent(renderer) to show it
    SDL_RenderPresent(renderer);
    waitUntilKeyPressed();
    quitSDL(window, renderer);
    return 0;
}
