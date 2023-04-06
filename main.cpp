//GAME 2048
#include <SDL.h>
#include <stdio.h>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

//Screen dimension constants
const int SCREEN_WIDTH = 320*3;
const int SCREEN_HEIGHT = 240*3;

int boardGame[4][4] = {{0, 2, 0, 0},{0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};

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

int main( int argc, char* args[] )
{
    //The window we'll be rendering to
    SDL_Window* window = NULL;

    //The surface contained by the window
    SDL_Surface* screenSurface = NULL;

    //Initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
    }
    else
    {
        //Create window
        window = SDL_CreateWindow( "2048", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
        if( window == NULL )
        {
            printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
        }
        else
        {
            //Get window surface
            screenSurface = SDL_GetWindowSurface( window );

            //Fill the surface white
            SDL_FillRect( screenSurface, NULL, SDL_MapRGB( screenSurface->format, 0xFF, 0xFF, 0xFF ) );

            //Update the surface
            SDL_UpdateWindowSurface( window );

            //Hack to get window to stay up
            SDL_Event e;
            bool quit = false;
            while( quit == false )
            {
                while( SDL_PollEvent( &e ) )
                {
                    if( e.type == SDL_QUIT ) quit = true;
                }
            }
        }
    }    //Destroy window
    SDL_DestroyWindow( window );

    //Quit SDL subsystems
    SDL_Quit();

    return 0;
}
