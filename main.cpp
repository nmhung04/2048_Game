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
