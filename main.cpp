//GAME 2048
#include <SDL.h>
#include <stdio.h>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <iomanip>
using namespace std;
//=============================================GAME LOGIC==================================//
int boardGame[4][4] = { {0, 0, 0, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0}
};
int Score = 0;
bool checkUpdate;
//Board game is full?
bool isFull(int a[4][4])
{
    int cnt = 0;
    for(int i = 0; i <= 3; ++i)
    {
        for (int j = 0; j <= 3; ++j)
        {
            if(a[i][j] == 0)
            {
                ++cnt;
                break;
            }
        }
    }
    for(int i = 0; i <= 3; ++i)
    {
        for (int j = 0; j <= 2; ++j)
        {
            if(a[i][j] == a[i][j+1])
            {
                ++cnt;
                break;
            }
        }
    }
    for(int i = 0; i <= 3; ++i)
    {
        for (int j = 0; j <= 2; ++j)
        {
            if(a[j][i] == a[j+1][i])
            {
                ++cnt;
                break;
            }
        }
    }
    if (cnt == 0) return true;
    return false;
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
                if (x > 3);
                else
                {
                    checkUpdate = true;
                    a[row][j] = a[row][x];
                    a[row][x] = 0;
                }
            }
        }
    }
}

void MERGE_LEFT(int a[4][4])
{
    checkUpdate = false;
    moveLeft(a);
    for (int row = 0; row <= 3; ++row)
    {
        for (int j = 0; j <= 2; ++j)
        {
            if (a[row][j] == a[row][j + 1] && a[row][j] != 0)
            {
                checkUpdate = true;
                Score += a[row][j];
                a[row][j] *= 2;
                a[row][j + 1] = 0;
            }
        }
    }
    moveLeft(a);
    if (checkUpdate) setRandValue(boardGame);
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
                    checkUpdate = true;
                    a[row][j] = a[row][x];
                    a[row][x] = 0;
                }
            }
        }
    }
}
void MERGE_RIGHT(int a[4][4])
{
    checkUpdate = false;
    moveRight(a);
    for (int row = 0; row <= 3; ++row)
    {
        for (int j = 3; j >= 1; --j)
        {
            if (a[row][j] == a[row][j - 1] && a[row][j] != 0)
            {
                checkUpdate = true;
                Score += a[row][j];
                a[row][j] *= 2;
                a[row][j - 1] = 0;
            }
        }
    }
    moveRight(a);
    if (checkUpdate) setRandValue(boardGame);
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
                    checkUpdate = true;
                    a[j][col] = a[x][col];
                    a[x][col] = 0;
                }
            }
        }
    }
}
void MERGE_UP(int a[4][4])
{
    checkUpdate = false;
    moveUp(a);
    for (int col = 0; col <= 3; ++col)
    {
        for (int j = 0; j <= 2; ++j)
        {
            if (a[j][col] == a[j+1][col] && a[j][col] != 0)
            {
                checkUpdate = true;
                Score += a[j][col];
                a[j][col] *= 2;
                a[j+1][col] = 0;
            }
        }
    }
    moveUp(a);
    if (checkUpdate) setRandValue(boardGame);
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
                    checkUpdate = true;
                    a[j][col] = a[x][col];
                    a[x][col] = 0;
                }
            }
        }
    }

}

void MERGE_DOWN(int a[4][4])
{
    checkUpdate = false;
    moveDown(a);
    for (int col = 0; col <= 3; ++col)
    {
        for (int j = 3; j >= 1; --j)
        {
            if (a[j][col] == a[j-1][col] && a[j][col] != 0)
            {
                checkUpdate = true;
                Score += a[j][col];
                a[j][col] *= 2;
                a[j-1][col] = 0;
            }
        }
    }
    moveDown(a);
    if (checkUpdate) setRandValue(boardGame);
}

void displayBoard(int a[4][4])
{
    cout << "========================" << endl;
    cout << "Score: " << Score << endl;
    for (int i = 0; i <= 3; ++i)
    {
        for (int j = 0; j <= 3; ++j)
            cout << setw(3) << left << a[i][j] << " ";
        cout << endl;
    }
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
    if (window == nullptr) logSDLError(std::cout, "CreateWindow", true);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED |
                                  SDL_RENDERER_PRESENTVSYNC);
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

int main(int argc, char* argv[])
{
    SDL_Window* window;
    SDL_Renderer* renderer;
    initSDL(window, renderer);
    SDL_SetRenderDrawColor(renderer, 240, 248, 255, 1);
    SDL_Rect W = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
    SDL_RenderFillRect(renderer, &W);
    SDL_SetRenderDrawColor(renderer, 70, 70, 70, 70);
    for (int i = 25; i<= 1000; i+= 25)
    {
        SDL_RenderDrawLine(renderer,i, 0, i, 750);
        SDL_RenderPresent(renderer);
    }
    for (int i = 25; i<= 750; i+= 25)
    {
        SDL_RenderDrawLine(renderer,0, i, 1000, i);
        SDL_RenderPresent(renderer);
    }

    int home[25][25] = {{0, 0, 1, 0, 0 },
                        {0,1 , 1, 1, 0 },
                        {1, 1, 1, 1, 1 },
                        {0, 1, 1, 1, 0 },
                        {0, 1, 1, 1, 0 }};
    SDL_SetRenderDrawColor(renderer, 0, 0, 230, 1);
    for (int i = 0; i <= 4; ++i){
        for (int j = 0; j <= 4; ++j){
            if (home[j][i] == 1){
                SDL_Rect cell = {(i + 1)*25, (j+1) * 25, 25, 25};
                SDL_RenderFillRect(renderer, &cell);
            }
        }
    }
    int Text[24][5] ={{1, 1, 1, 1, 1, },
                        {1, 1, 1, 1, 1, },
                        {1, 0, 1, 0, 0, },
                        {1, 1, 1, 0, 0, },
                        {0, 0, 0, 0, 0, },
                        {1, 1, 1, 1, 1, },
                        {1, 1, 1, 1, 1, },
                        {0, 0, 0, 1, 1, },
                        {0, 0, 0, 1, 1, },
                        {0, 0, 0, 0, 0, },
                        {0, 0, 0, 1, 1, },
                        {0, 0, 1, 1, 0, },
                        {0, 1, 1, 1, 0, },
                        {1, 1, 0, 1, 0, },
                        {0, 1, 1, 1, 0, },
                        {0, 0, 1, 1, 0, },
                        {1, 0, 0, 1, 1, },
                        {1, 1, 0, 0, 0, },
                        {0, 1, 1, 0, 0, },
                        {0, 0, 1, 1, 1, },
                        {0, 0, 1, 1, 1, },
                        {0, 1, 1, 0, 0, },
                        {1, 1, 0, 0, 0, },
                        {1, 0, 0, 0, 0, }};
    SDL_SetRenderDrawColor(renderer, 0, 0, 230, 1);
    for (int i = 0; i <= 23; ++i){
        for (int j = 0; j <= 4; ++j){
            if (Text[i][j] == 1){
                SDL_Rect cell = {(i + 8)*25, (j+1) * 25, 25, 25};
                SDL_RenderFillRect(renderer, &cell);
            }
        }
    }
    //Board game
    int x1 = 100, x2 = 200, x3 = 300, x4 = 400, x5 = 500;
    int y1 = 225, y2 = y1 + 100, y3 = y1 + 200, y4 = y1 + 300, y5 = y1 + 400;
    SDL_Rect board;
    board.x = x1;
    board.y = y1;
    board.w = 400;
    board.h = 400;
    SDL_SetRenderDrawColor(renderer, 100, 200, 100, 255);
    SDL_RenderFillRect(renderer, &board);
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


    //  PLAY Button
    SDL_Rect Play;
    Play.x = x5 + x2;
    Play.y = y3 + 25 ;
    Play.w = 200;
    Play.h = 75;
    SDL_SetRenderDrawColor(renderer, 184, 134, 11, 1);
    SDL_RenderFillRect(renderer, &Play);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 1);
    SDL_RenderDrawLine(renderer, x5 + x2, y3 + 25 , x5 + x2 + 200, y3 + 25 );
    SDL_RenderDrawLine(renderer, x5 + x2, y3 + 25  + 75, x5 + x2 + 200, y3 + 25  + 75);
    SDL_RenderDrawLine(renderer, x5 + x2, y3 + 25 , x5 + x2, y3 + 25  + 75);
    SDL_RenderDrawLine(renderer, x5 + x2 + 200, y3 + 25 , x5 + x2 + 200, y3 + 75);

    //Play Again Button
    SDL_Rect PlAgain;
    PlAgain.x = x5 + x2;
    PlAgain.y = y4 + 25;
    PlAgain.w = 200;
    PlAgain.h = 75;
    SDL_SetRenderDrawColor(renderer, 184, 134, 11, 1);
    SDL_RenderFillRect(renderer, &PlAgain);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 1);
    SDL_RenderDrawLine(renderer, x5 + x2, y4 + 25, x5 + x2 + 200, y4 + 25);
    SDL_RenderDrawLine(renderer, x5 + x2, y4 + 25 + 75, x5 + x2 + 200, y4 + 25 + 75);
    SDL_RenderDrawLine(renderer, x5 + x2, y4 + 25, x5 + x2, y4 + 25 + 75);
    SDL_RenderDrawLine(renderer, x5 + x2 + 200, y4 + 25, x5 + x2 + 200, y4 + 25 + 75);
    //Score
    SDL_Rect Score;
    Score.x = x5 + x2;
    Score.y = y2;
    Score.w = 200;
    Score.h = 60;
    SDL_SetRenderDrawColor(renderer, 184, 134, 11, 1);
    SDL_RenderFillRect(renderer, &Score);

    //MaxScore
    SDL_Rect maxScore;
    maxScore.x = x5 + x2;
    maxScore.y = y1;
    maxScore.w = 200;
    maxScore.h = 60;
    SDL_SetRenderDrawColor(renderer, 184, 134, 11, 1);
    SDL_RenderFillRect(renderer, &maxScore);
    SDL_RenderPresent(renderer);


//Game
    cout <<"GAME (using SDL)HAVEN'T BEEN COMPLETED \nDISPLAY ON CONSOLE SCREEN \n";
    cout << "Click to game's window and press UP, DOWN, LEFT, or RIGHT to play \nView result on console screen" <<endl;
    SDL_Event e;
    bool quit = false;
    setRandValue(boardGame);
    displayBoard(boardGame);
    while (!quit)
    {
        while( SDL_PollEvent( &e ) != 0 )
        {
            //User requests quit
            if( e.type == SDL_QUIT)
            {
                quit = true;
            }
            else if(isFull(boardGame))
                cout<< "Game Over"<<endl;
            //User presses a key
            else if( e.type == SDL_KEYDOWN )
            {

                //Select surfaces based on key press
                switch( e.key.keysym.sym )
                {
                case SDLK_UP:
                    MERGE_UP(boardGame);
                    displayBoard(boardGame);
                    break;

                case SDLK_DOWN:
                    MERGE_DOWN(boardGame);
                    displayBoard(boardGame);
                    break;

                case SDLK_LEFT:
                    MERGE_LEFT(boardGame);
                    displayBoard(boardGame);
                    break;

                case SDLK_RIGHT:
                    MERGE_RIGHT(boardGame);
                    displayBoard(boardGame);
                    break;
                default:
                    break;
                }
            }

        }
    }

    waitUntilKeyPressed();
    void quitSDL(window, renderer);
    return 0;
}
