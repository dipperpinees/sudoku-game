#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include "LTexture.h"
#include "game.h"
#include "LTimer.h"
#include <sstream>
#include <string>
#include "header.h"
#include <ctime>
#include <cstdlib>
#include "board.h"

using namespace std;

TTF_Font *gFont = NULL;

//screen ratio
const int SCREEN_WIDTH = 1366;
const int SCREEN_HEIGHT = 768;

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;

void init(){
    //Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO ) < 0 )
    {
        cout<< "SDL could not initialize! SDL Error: %s\n"<< SDL_GetError() ;
    }

	//Create window
	gWindow = SDL_CreateWindow("SUDOKU", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (gWindow == NULL) {
		cout<<"Window could not be created! SDL Error: " << SDL_GetError();
	}

	//Create renderer
	gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (gRenderer == NULL) {
		// Create software renderer if we couldn't create hardware accelerated one.
		// TODO: Works too fast, need a frame cap
		gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_SOFTWARE);

		if (gRenderer == NULL)
		{
			cout<<"Renderer could not be created! SDL Error: "<<SDL_GetError();
		}
	}

	//Set texture filtering to linear
	if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
		cout<<"Warning: Linear texture filtering not enabled!";
	}

	//Initialize SDL_ttf module
	if (TTF_Init() == -1) {
		cout<<"SDL_ttf could not initialized! TTF Error: " << TTF_GetError();
	}
	if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 ){
        cout<< "SDL_mixer could not initialize! SDL_mixer Error: %s\n"<< Mix_GetError();
    }
}

Game boardGame;

void loadMedia(){
    //load font
    gFont = TTF_OpenFont( "data/font/consola.ttf", 68 );
}

void close(){
    boardGame.freeMedia();
    TTF_CloseFont( gFont );
    gFont = NULL;

    SDL_DestroyRenderer( gRenderer );
    SDL_DestroyWindow( gWindow );
    gWindow = NULL;
    gRenderer = NULL;

    IMG_Quit();
    SDL_Quit();
    TTF_Quit();
}

void playGame(){
    boardGame.loadMediaGame();
    bool quit = false;
    SDL_Event e;
    while(!quit){
        while(SDL_PollEvent(&e)!=0){
            if(e.type == SDL_QUIT){
                quit = true;
            }
            else{

                //handle game
                boardGame.handleGame(e, quit);
            }
        }
        SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
        SDL_RenderClear( gRenderer );

        //render game
        boardGame.render();

        SDL_RenderPresent(gRenderer);
    }
}

int main(int argc, char *argv[]){
    srand((int) time(0));
    init();
    loadMedia();
    playGame();
    close();
    return 0;
}
