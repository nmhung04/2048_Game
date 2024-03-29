//2048 GAME
#define _USE_MATH_DEFINES
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <string>
#include <SDl.h>
//=======================BoardGame size and position=====================//
int SCREEN_WIDTH = 1000;
int SCREEN_HEIGHT = 750;
unsigned int max_score = 0;
#define BOARD_SIZE 4

#define BOARD_WIDTH 400
#define BOARD_X 200
#define BOARD_Y 200

struct playerScore{
	int endScore;
	double endTime;
	int endSize;
};


//======================Draw a text txt on surface screen, starting from the point (x, y)=========================//
//======================Charset is a 128x128 bitmap containing character images==================================//
void DrawString(SDL_Surface *screen, int x, int y, const char *text, SDL_Surface *charset) {
	int px, py, c;
	SDL_Rect s, d;
	s.w = 8;
	s.h = 8;
	d.w = 8;
	d.h = 8;
	while(*text) {
		c = *text & 255;
		px = (c % 16) * 8;
		py = (c / 16) * 8;
		s.x = px;
		s.y = py;
		d.x = x;
		d.y = y;
		SDL_BlitSurface(charset, &s, screen, &d);
		x += 8;
		text++;
		};
	};




//================ Draw a single pixel======================================//
void DrawPixel(SDL_Surface *surface, int x, int y, Uint32 color) {
	int bpp = surface->format->BytesPerPixel;
	Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;
	*(Uint32 *)p = color;
};



//===================================Draw line===============================//
void DrawLine(SDL_Surface *screen, int x, int y, int l, int dx, int dy, Uint32 color) {
	for(int i = 0; i < l; i++) {
		DrawPixel(screen, x, y, color);
		x += dx;
		y += dy;
		};
	};

//===========================Draw a rectangle of size l by k=================//
void DrawRectangle(SDL_Surface *screen, int x, int y, int l, int k,
                   Uint32 outlineColor, Uint32 fillColor) {
	int i;
	DrawLine(screen, x, y, k, 0, 1, outlineColor);
	DrawLine(screen, x + l - 1, y, k, 0, 1, outlineColor);
	DrawLine(screen, x, y, l, 1, 0, outlineColor);
	DrawLine(screen, x, y + k - 1, l, 1, 0, outlineColor);
	for(i = y + 1; i < y + k - 1; i++)
		DrawLine(screen, x + 1, i, l - 2, 1, 0, fillColor);
	};

//====================Draw point of block====================================//
void DrawPoint(SDL_Surface *screen, int X, int Y, int width, const char *number, SDL_Surface *charset) {
	int length = strlen(number);
	DrawString(screen, (X + width / 2) - length*4, Y + width / 2, number, charset);
}


int get_power(int x) {
	int n = 0;
	while (x != 0) {
		x = x/2;
		n++;
	}

	return n;
}

//===================Draw Board, Score, Max Score=========================//
void DrawBoard(SDL_Surface *screen, int **value_arr, int size, Uint32 outlineColor, Uint32 fillColor, SDL_Surface *charset) {
	int width = (BOARD_WIDTH / size) - 2;
	int X, Y;
	char number[5];
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			X = BOARD_X + (BOARD_WIDTH / size)*i;
			Y = BOARD_Y + (BOARD_WIDTH / size)*j;
			int color_power = get_power(value_arr[i][j]);
			DrawRectangle(screen, Y, X, width, width, outlineColor, SDL_MapRGB(screen->format, 120, 120 + 20 * color_power, 196 + 10*color_power));
			if(value_arr[i][j] == 0) sprintf(number, "");
			else sprintf(number, "%d", value_arr[i][j]);
			DrawPoint(screen, Y, X, width, number, charset);
		}
	}
}

void DrawScore(SDL_Surface *screen, unsigned int score, SDL_Surface *charset) {
	int X = BOARD_X;
	int Y = BOARD_Y + BOARD_WIDTH + 100;
	int width = 70;
	char number[18];
	int black = SDL_MapRGB(screen->format, 0, 0, 0);
	int lightblue = SDL_MapRGB(screen->format, 135, 132, 227);
	DrawRectangle(screen, SCREEN_WIDTH/2 + 155, SCREEN_HEIGHT/2 - 160, 200, 50, black, lightblue);
	sprintf(number, "SCORE: %u", score);
	DrawPoint(screen, Y, X, width, number, charset);
}
void DrawMaxScore(SDL_Surface *screen, unsigned int max_score, SDL_Surface *charset) {
	int X = BOARD_X + 50;
	int Y = BOARD_Y + BOARD_WIDTH + 100;
	int width = 70;
	char number[18];
	int black = SDL_MapRGB(screen->format, 0, 0, 0);
	int lightblue = SDL_MapRGB(screen->format, 135, 132, 227);
	DrawRectangle(screen, SCREEN_WIDTH/2 + 155, SCREEN_HEIGHT/2 - 110, 200, 50, black, lightblue);
	sprintf(number, "MAX_SCORE: %u", max_score);
	DrawPoint(screen, Y, X, width, number, charset);
}

//=============Create Array - value=====================//
int** createValue_arrleValue(int size) {
	int **value_arr;
	value_arr = new int *[size];
	for (int i = 0; i < size; ++i) value_arr[i] = new int[size];

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			value_arr[i][j] = 0;
		}
	}
	int X = rand() % size;
	int Y = rand() % size;
	value_arr[X][Y] = 2;
	X = rand() % size;
	Y = rand() % size;
	value_arr[X][Y] = 2;

	return value_arr;
}

//==================Check win=============================//
bool checkWin(int **&value_arr, int size) {
	bool win = 0;

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (value_arr[i][j] == 2048) win = 1;
		}
	}

	return win;
}

//===============Find 0 on board==========================//
bool checkPut(int **&value_arr, int size) {
	bool put = 0;

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (value_arr[i][j] == 0) put = 1;
		}
	}

	return put;
}

//=========Check lose===============//
bool checkLose(int **&value_arr, int size) {
	bool lose = 1;

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size - 1; j++) {
			if (value_arr[i][j] == value_arr[i][j + 1]) lose = 0;
		}
	}
	for (int i = 0; i < size - 1; i++) {
		for (int j = 0; j < size; j++) {
			if (value_arr[i][j] == value_arr[i + 1][j]) lose = 0;
		}
	}

	if (checkPut(value_arr, size)) lose = 0;

	return lose;
}

//========================Any move====================//
bool checkToRandom(int **&value_arr, int **&value_arr2, int size) {
	int can_put = 0;
	for (int i = 0; i < size; ++i) {
		for (int j = 0; j < size; ++j) {
			if (value_arr[i][j] != value_arr2[i][j]) can_put = 1;
		}
	}
	return can_put;
}

//=====================Set randomValue===================================//
void SetRandomValue(int **&value_arr, int size) {

	if (checkPut(value_arr, size)) {
		int value4_5[10] = {2, 4, 2, 2, 4, 2, 2, 4, 2, 4};
		int value6_8[10] = {2, 4, 2, 4, 4, 2, 4, 4, 2, 4};
		int value8_10[10] = {8, 4, 8, 2, 4, 2, 8, 4, 2, 4};
		int value;
		if (size <= 5) value = value4_5[rand() % 10];
		else if (size <= 8) value = value6_8[rand() % 10];
		else value = value8_10[rand() % 10];
		int X = rand() % size;
		int Y = rand() % size;
		if (value_arr[X][Y] == 0) value_arr[X][Y] = 2;
		else {
			while (value_arr[X][Y] != 0) {
				X = rand() % size;
				Y = rand() % size;
			}
			value_arr[X][Y] = value;
		}
	}
}

//===============MOVE & MERGE TILES - UP===========================//
void moveUp(int **&value_arr, int size) {
	for (int i = 1; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (value_arr[i][j] != 0) {
				for (int k = i; k > 0; --k) {
					if (value_arr[k - 1][j] == 0) {
						value_arr[k - 1][j] = value_arr[k][j];
						value_arr[k][j] = 0;
					}
				}
			}
		}
	}
}
void MERGE_UP(int **&value_arr, int size, unsigned int &score, unsigned int &max_score) {
	moveUp(value_arr, size);

	for (int i = 1; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (value_arr[i][j] != 0) {
				if (value_arr[i - 1][j] == value_arr[i][j]) {
					value_arr[i - 1][j]+= value_arr[i][j];
					score += value_arr[i][j];
					if (max_score < score) max_score = score;
					value_arr[i][j] = 0;

				}
			}
		}
	}

	moveUp(value_arr, size);
}
//===============MOVE & MERGE TILES - DOWN===========================//
void moveDown(int **&value_arr, int size) {
	for (int i = 0; i < size; i++) {
		for (int j = size - 2; j >= 0; j--) {
			if (value_arr[j][i] != 0) {
				for (int k = j; k < size - 1; ++k) {
					if (value_arr[k + 1][i] == 0) {
						value_arr[k + 1][i] = value_arr[k][i];
						value_arr[k][i] = 0;
					}
				}
			}
		}
	}
}
void MERGE_DOWN(int **&value_arr, int size, unsigned int &score, unsigned int &max_score) {
	moveDown(value_arr, size);

	for (int i = 0; i < size; i++) {
		for (int j = size - 2; j >= 0; j--) {
			if (value_arr[j][i] != 0) {
				if (value_arr[j][i] == value_arr[j + 1][i]) {
					value_arr[j + 1][i] += value_arr[j][i];
					score += value_arr[j][i];
					if (max_score < score) max_score = score;
					value_arr[j][i] = 0;
				}
			}
		}
	}

	moveDown(value_arr, size);
}
//===============MOVE & MERGE TILES - RIGHT===========================//
void moveRight(int **&value_arr, int size) {

	for (int i = 0; i < size; i++) {
		for (int j = size - 2; j >= 0; j--) {
			if (value_arr[i][j] != 0) {
				for (int k = j; k < size - 1; ++k) {
					if (value_arr[i][k + 1] == 0) {
						value_arr[i][k + 1] = value_arr[i][k];
						value_arr[i][k] = 0;
					}
				}
			}
		}
	}
}
void MERGE_RIGHT(int **&value_arr,int size, unsigned int &score, unsigned int &max_score) {
	moveRight(value_arr, size);

	for (int i = 0; i < size; i++) {
		for (int j = size - 2; j >= 0; j--) {
			if (value_arr[i][j] != 0) {
				if (value_arr[i][j] == value_arr[i][j + 1]) {
					value_arr[i][j + 1] += value_arr[i][j];
					score += value_arr[i][j];
					if (max_score < score) max_score = score;
					value_arr[i][j] = 0;
				}
			}
		}
	}

	moveRight(value_arr, size);
}
//===============MOVE & MERGE TILES - LEFT===========================//
void moveLeft(int **&value_arr, int size) {
	for (int i = 0; i < size; i++) {
		for (int j = 1; j < size; j++) {
			if (value_arr[i][j] != 0) {
				for (int k = j; k > 0; --k) {
					if (value_arr[i][k - 1] == 0) {
						value_arr[i][k - 1] = value_arr[i][k];
						value_arr[i][k] = 0;
					}
				}
			}
		}
	}
}
void MERGE_LEFT(int **&value_arr, int size, unsigned int &score, unsigned int &max_score) {

	moveLeft(value_arr, size);

	for(int i = 0; i < size; i++) {
		for (int j = 1; j < size; j++) {
			if (value_arr[i][j] != 0) {
				if (value_arr[i][j] == value_arr[i][j - 1]) {
					value_arr[i][j - 1] += value_arr[i][j];
					score += value_arr[i][j];
					if (max_score < score) max_score = score;
					value_arr[i][j] = 0;
				}
			}
		}
	}

	moveLeft(value_arr, size);
}

//==========Copy Value Array====================//
void copyValue_arr(int **&value_arr1,int **&value_arr2, int size) {
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) value_arr1[i][j] = value_arr2[i][j];
	}
}

//====================================MOVE===================================//
void MOVE(SDL_Event event, int **&value_arr, int size, int **&value_arr2, unsigned int &score,unsigned int &max_score, unsigned int &backScore) {
	int **checkValue_arr = createValue_arrleValue(size);
	int checkScore = backScore;
	copyValue_arr(checkValue_arr, value_arr2, size);

	copyValue_arr(value_arr2, value_arr, size);
	backScore = score;


	if (event.key.keysym.sym == SDLK_UP) MERGE_UP(value_arr, size, score, max_score);
	else if (event.key.keysym.sym == SDLK_DOWN) MERGE_DOWN(value_arr, size, score, max_score);
	else if (event.key.keysym.sym == SDLK_LEFT) MERGE_LEFT(value_arr, size, score, max_score);
	else if (event.key.keysym.sym == SDLK_RIGHT) MERGE_RIGHT(value_arr, size, score, max_score);

	if (checkToRandom(value_arr, value_arr2, size)) {
		SetRandomValue(value_arr, size);
	}
	else {
		copyValue_arr(value_arr2, checkValue_arr, size);
		backScore = checkScore;
	}

	for (int i = 0; i < size; ++i)
		delete[] checkValue_arr[i];
	delete[] checkValue_arr;
}

//========================Burble sort==========================//
void sortByScore(playerScore *&value_arr, int size) {
	playerScore helper;
	for (int i = 0; i < size - 1; i++) {
		for (int j = 0; j < size - 1 - i; j++) {
			if (value_arr[j].endScore > value_arr[j + 1].endScore) {
				helper = value_arr[j];
				value_arr[j] = value_arr[j + 1];
				value_arr[j + 1] = helper;
			}
		}
	}

	for (int i = 0; i < size / 2; i++) {
		helper = value_arr[i];
		value_arr[i] = value_arr[size - i - 1];
		value_arr[size - i - 1] = helper;
	}
}

void sortByTime(playerScore *&value_arr, int size) {
	playerScore helper;
	for (int i = 0; i < size - 1; i++) {
		for (int j = 0; j < size - 1 - i; j++) {
			if (value_arr[j].endTime > value_arr[j + 1].endTime) {
				helper = value_arr[j];
				value_arr[j] = value_arr[j + 1];
				value_arr[j + 1] = helper;
			}
		}
	}
}

//==============create list of score for board size=================================
playerScore *createRanking(playerScore *value_arr, int amount, int size, int fileSize) {
	playerScore *ranking = new playerScore[amount];
	int j = 0;
	for (int i = 0; i < fileSize; i++) {
		if (value_arr[i].endSize == size) {
			ranking[j].endScore = value_arr[i].endScore;
			ranking[j].endTime = value_arr[i].endTime;
			ranking[j].endSize = value_arr[i].endSize;
			j++;
		}
	}
	return ranking;
}

void saveToFile(int score, double time, int size) {
	FILE *fileList = fopen("winnerList.txt", "a");
	fprintf(fileList, "%u %.1lf %d\n", score, time, size);

	fclose(fileList);
}
//===========List of score - File=================//
playerScore *openFile(int &lines){
	FILE *fileList = fopen("winnerList.txt", "r");
	int ch = 0;

	if (fileList == NULL)
	{
		return 0;
	}

	while (!feof(fileList))
	{
		ch = fgetc(fileList);
		if (ch == '\n')
		{
			lines++;
		}
	}

	playerScore *list = new playerScore [lines];
	fseek(fileList, 0, SEEK_SET);
	for (int i = 0; i < lines; i++) {
		fscanf(fileList, "%d %lf %d", &list[i].endScore, &list[i].endTime, &list[i].endSize);
	}
	fclose(fileList);

	return list;
}

//=========================MAIN==================================//
#ifdef __cplusplus
extern "C"
#endif
int main(int argc, char **argv) {
	int size = 4;
	bool getStart = 0;
	unsigned int score = 0;
	unsigned int backScore = score;
	srand(time(NULL));
	int** value_arr;
	int** value_arr2;
	int fileSize = 0;
	playerScore *winnerList;

	int t1, t2, quit, frames, rc;
	double delta, worldTime, fpsTimer, fps;
	SDL_Event event;
	SDL_Surface *screen, *charset;
	//SDL_Surface *eti;
	SDL_Texture *scrtex;
	SDL_Window *window;
	SDL_Renderer *renderer;
	if(SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		printf("SDL_Init error: %s\n", SDL_GetError());
		return 1;
	}


	rc = SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, 0,
	                                 &window, &renderer);
	if(rc != 0) {
		SDL_Quit();
		printf("SDL_CreateWindowAndRenderer error: %s\n", SDL_GetError());
		return 1;
		};

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
	SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

	SDL_SetWindowTitle(window, "2048 GAME");


	screen = SDL_CreateRGBSurface(0, SCREEN_WIDTH, SCREEN_HEIGHT, 32,
	                              0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);
	scrtex = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888,
	                           SDL_TEXTUREACCESS_STREAMING,
	                           SCREEN_WIDTH, SCREEN_HEIGHT);

	charset = SDL_LoadBMP("./cs8x8.bmp");
	if(charset == NULL) {
		printf("SDL_LoadBMP(cs8x8.bmp) error: %s\n", SDL_GetError());
		SDL_FreeSurface(screen);
		SDL_DestroyTexture(scrtex);
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		SDL_Quit();
		return 1;
	};
	SDL_SetColorKey(charset, true, 0x000000);

	char text[128];

	int black = SDL_MapRGB(screen->format, 10, 10, 10);
	int lightblue = SDL_MapRGB(screen->format, 135, 132, 200);

	value_arr = createValue_arrleValue(size);
	value_arr2 = createValue_arrleValue(size);
	copyValue_arr(value_arr, value_arr2, size);
	winnerList = openFile(fileSize);

	frames = 0;
	fpsTimer = 0;
	fps = 0;
	quit = 0;
	worldTime = 0;
	while(!quit) {

		//SHOW START WINDOW TO CHOOSE SIZE FROM 3 TO 10
		if (!getStart) {

			if (size >= 10) size = 10;
			if (size <= 4) size = 4;

			SDL_FillRect(screen, NULL, black);
			DrawRectangle(screen, 4, 120, SCREEN_WIDTH - 8, 36, black, lightblue);
			sprintf(text, "CHOOSE SIZE OF GAME: \030 - BIGGER, \031 - SMALLER, ENTER - START PLAYING, ESC - EXIT");
			DrawString(screen, screen->w / 2 - strlen(text) * 8 / 2, 135, text, charset);

			DrawRectangle(screen, SCREEN_WIDTH/2 - 100, SCREEN_HEIGHT/2 - 36, 200, 36, black, lightblue);
			sprintf(text, "SIZE: %d", size);
			DrawString(screen, SCREEN_WIDTH/2  -  strlen(text) * 4, SCREEN_HEIGHT / 2 - 20, text, charset);


			while (SDL_PollEvent(&event)) {
				switch (event.type) {
				case SDL_KEYDOWN:
					if (event.key.keysym.sym == SDLK_ESCAPE) quit = 1;
					else if (event.key.keysym.sym == SDLK_UP) size++;
					else if (event.key.keysym.sym == SDLK_DOWN) size--;
					else if (event.key.keysym.sym == SDLK_RETURN) {
						getStart = 1;
						value_arr = createValue_arrleValue(size);
						value_arr2 = createValue_arrleValue(size);
						copyValue_arr(value_arr, value_arr2, size);
						t1 = SDL_GetTicks();
						backScore = 0;
						score = 0;
						worldTime = 0;
					}
					break;
				case SDL_QUIT:
					quit = 1;
					break;
				};
			};

			SDL_UpdateTexture(scrtex, NULL, screen->pixels, screen->pitch);
			SDL_RenderCopy(renderer, scrtex, NULL, NULL);
			SDL_RenderPresent(renderer);
		}
		//SHOW GAME WINDOW
		else if(getStart && !checkLose(value_arr, size) && !checkWin(value_arr, size)){

			//TIME COUNING
			t2 = SDL_GetTicks();
			delta = (t2 - t1) * 0.001;
			t1 = t2;
			worldTime += delta;
			fpsTimer += delta;
			if (fpsTimer > 0.5) {
				fps = frames * 2;
				frames = 0;
				fpsTimer -= 0.5;
			};

			SDL_FillRect(screen, NULL, black);


			DrawBoard(screen, value_arr, size, black, lightblue, charset);
			DrawScore(screen, score, charset);
            DrawMaxScore(screen, max_score, charset);
			//info text
			DrawRectangle(screen, 4, 20, SCREEN_WIDTH - 8, 62, black, lightblue);
			sprintf(text, "        Your Time = %.1lf s  %.0lf frames / s", worldTime, fps);
			DrawString(screen, screen->w / 2 - strlen(text) * 8 / 2, 36, text, charset);
			sprintf(text, "ESC - Exit, ARROW - Move, U - Back move, N - New game, R - Ranking (Winner list)");
			DrawString(screen, screen->w / 2 - strlen(text) * 8 / 2, 52, text, charset);

			SDL_UpdateTexture(scrtex, NULL, screen->pixels, screen->pitch);
			//SDL_RenderClear(renderer);
			SDL_RenderCopy(renderer, scrtex, NULL, NULL);
			SDL_RenderPresent(renderer);

			while(SDL_PollEvent(&event)) {
				switch(event.type) {
					case SDL_KEYDOWN:
						if (event.key.keysym.sym == SDLK_ESCAPE) quit = 1;
						else if (event.key.keysym.sym == SDLK_UP || event.key.keysym.sym == SDLK_DOWN ||
							event.key.keysym.sym == SDLK_LEFT || event.key.keysym.sym == SDLK_RIGHT) MOVE(event, value_arr, size, value_arr2, score, max_score, backScore);
						else if (event.key.keysym.sym == SDLK_u) {
							copyValue_arr(value_arr, value_arr2, size);
							score = backScore;
						}
						else if (event.key.keysym.sym == SDLK_n) {
							for (int i = 0; i < size; ++i)
								delete[] value_arr[i];
							delete[] value_arr;

							for (int i = 0; i < size; ++i)
								delete[] value_arr2[i];
							delete[] value_arr2;
							getStart = 0;
						}
						else if (event.key.keysym.sym == SDLK_r) {	//SHOW RANKING WINDOW

							bool show_ranking = 0;
							int amountBoard = 0;
							int startShow = 0;
							int limit = 10;
							for (int i = 0; i < fileSize; i++) if (size == winnerList[i].endSize) amountBoard++;
							playerScore *sizeRanking = createRanking(winnerList, amountBoard, size, fileSize);
							while (!show_ranking) {

								SDL_FillRect(screen, NULL, black);
								DrawRectangle(screen, 4, 4, SCREEN_WIDTH - 8, 36, black, lightblue);
								sprintf(text, "Winner list for %dx%d", size, size);
								DrawString(screen, screen->w / 2 - strlen(text) * 8 / 2, 10, text, charset);
								sprintf(text, "ESC -  Go Back, T - Sort by time, P - Sort by points");
								DrawString(screen, screen->w / 2 - strlen(text) * 8 / 2, 26, text, charset);


								//set start of ranking
								if (startShow <= 0) startShow = 0;
								if (startShow >= amountBoard - 10) startShow = amountBoard - 10;
								if (amountBoard <= 10) {
									startShow = 0;
									limit = amountBoard;
								}

								//check there is winner list
								if (fileSize == 0 || limit == 0) {
									sprintf(text, "Winner list in empty");
									DrawString(screen, SCREEN_WIDTH / 2 - strlen(text) * 4, SCREEN_HEIGHT / 2 + 16, text, charset);
								}

								int placeShow = 0;
								for (int i = startShow; placeShow < limit; i++) {
									DrawRectangle(screen, SCREEN_WIDTH / 2 - 200, SCREEN_HEIGHT / 2 - 190 + placeShow * 40, 400, 40, black, lightblue);
									sprintf(text, "%d. Your time: %.1lfs Your score: %d",startShow + placeShow + 1, sizeRanking[i].endTime, sizeRanking[i].endScore);
									DrawString(screen, SCREEN_WIDTH / 2 - strlen(text) * 4, SCREEN_HEIGHT / 2 - 200 + 26 + placeShow * 40, text, charset);
									placeShow++;
								}

								while (SDL_PollEvent(&event)) {
									switch (event.type) {
									case SDL_KEYDOWN:
										if (event.key.keysym.sym == SDLK_ESCAPE) show_ranking = 1;
										if (event.key.keysym.sym == SDLK_t) sortByTime(sizeRanking, amountBoard);
										if (event.key.keysym.sym == SDLK_p) sortByScore(sizeRanking, amountBoard);
										else if (event.key.keysym.sym == SDLK_UP) startShow++;
										else if (event.key.keysym.sym == SDLK_DOWN) startShow--;

										break;
									case SDL_QUIT:
										quit = 1;
										show_ranking = 1;
										break;
									};
								};

								SDL_UpdateTexture(scrtex, NULL, screen->pixels, screen->pitch);
								SDL_RenderCopy(renderer, scrtex, NULL, NULL);
								SDL_RenderPresent(renderer);
							}
							delete[] sizeRanking;
						}
						break;
					case SDL_KEYUP:
						break;
					case SDL_QUIT:
						quit = 1;
						break;
				};
			};
			frames++;
		}
		//CHECK IF PLAYER LOSE AND SHOW ENDCSREEN
		else if (checkLose(value_arr, size)) {
			double endTime = worldTime;
			bool check = true;
			while (check) {
				SDL_FillRect(screen, NULL, black);
				DrawRectangle(screen, 4, 4, SCREEN_WIDTH - 8, 36, black, lightblue);
				sprintf(text, "You Lose: ESC - Quit, N - New Game");
				DrawString(screen, screen->w / 2 - strlen(text) * 8 / 2, 26, text, charset);

				DrawRectangle(screen, SCREEN_WIDTH / 2 - 200, SCREEN_HEIGHT / 2 - 36, 400, 36, black, lightblue);
				sprintf(text, "Your time: %.1lfs  Your score: %u", endTime, score);
				DrawString(screen, SCREEN_WIDTH / 2 - strlen(text) * 4, SCREEN_HEIGHT / 2 - 20, text, charset);


				while (SDL_PollEvent(&event)) {
					switch (event.type) {
					case SDL_KEYDOWN:
						if (event.key.keysym.sym == SDLK_ESCAPE) {
                                quit = 1;
                                check = false;
						}
						else if (event.key.keysym.sym == SDLK_n) {
							for (int i = 0; i < size; ++i)
								delete[] value_arr[i];
							delete[] value_arr;

							for (int i = 0; i < size; ++i)
								delete[] value_arr2[i];
							delete[] value_arr2;
							getStart = 0;
							check = false;
						}
						break;
					case SDL_QUIT:
						quit = 1;
						check = false;
						break;
					};
				};

				SDL_UpdateTexture(scrtex, NULL, screen->pixels, screen->pitch);
				SDL_RenderCopy(renderer, scrtex, NULL, NULL);
				SDL_RenderPresent(renderer);
			}
		}
		else if (checkWin(value_arr, size)) {
			double endTime = worldTime;
			bool check = true;
			while (check) {
				SDL_FillRect(screen, NULL, black);
				DrawRectangle(screen, 4, 4, SCREEN_WIDTH - 8, 36, black, lightblue);
				sprintf(text, "You Win");
				DrawString(screen, screen->w / 2 - strlen(text) * 8 / 2, 26, text, charset);

				DrawRectangle(screen, SCREEN_WIDTH / 2 - 200, SCREEN_HEIGHT / 2 - 36, 400, 36, black, lightblue);
				sprintf(text, "Your Score: %u", score);
				DrawString(screen, SCREEN_WIDTH / 2 - strlen(text) * 4, SCREEN_HEIGHT / 2 - 20, text, charset);


				while (SDL_PollEvent(&event)) {
					switch (event.type) {
					case SDL_KEYDOWN:
						if (event.key.keysym.sym == SDLK_ESCAPE) quit = 1;
						if (event.key.keysym.sym == SDLK_s) {
							saveToFile(score, endTime, size);



							while (!quit) {

								SDL_FillRect(screen, NULL, black);
								DrawRectangle(screen, 4, 4, SCREEN_WIDTH - 8, 36, black, lightblue);
								sprintf(text, "Score saved!");
								DrawString(screen, screen->w / 2 - strlen(text) * 8 / 2, 10, text, charset);
								sprintf(text, "ESC -  Close game");
								DrawString(screen, screen->w / 2 - strlen(text) * 8 / 2, 26, text, charset);

								while (SDL_PollEvent(&event)) {
									switch (event.type) {
									case SDL_KEYDOWN:
										if (event.key.keysym.sym == SDLK_ESCAPE) quit = 1;

										break;
									case SDL_QUIT:
										quit = 1;
										break;
									};
								};

								SDL_UpdateTexture(scrtex, NULL, screen->pixels, screen->pitch);
								SDL_RenderCopy(renderer, scrtex, NULL, NULL);
								SDL_RenderPresent(renderer);
							}
						}
						break;
					case SDL_QUIT:
						quit = 1;
						break;
					};
				};

				SDL_UpdateTexture(scrtex, NULL, screen->pixels, screen->pitch);
				SDL_RenderCopy(renderer, scrtex, NULL, NULL);
				SDL_RenderPresent(renderer);
			}
		}
	};

	//freeing all surfaces and memory
	for (int i = 0; i < size; ++i)
		delete[] value_arr[i];
	delete[] value_arr;

	for (int i = 0; i < size; ++i)
		delete[] value_arr2[i];
	delete[] value_arr2;

	delete[] winnerList;

	SDL_FreeSurface(charset);
	SDL_FreeSurface(screen);
	SDL_DestroyTexture(scrtex);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	SDL_Quit();
	return 0;
	};
