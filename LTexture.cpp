#include <iostream>
#include <SDL.h>
#include "LTexture.h"
#include <SDL_image.h>
#include <string>
#include "LTexture.h"
#include <SDL_ttf.h>

using namespace std;

extern SDL_Renderer* gRenderer ;
extern TTF_Font *gFont;

LTexture::LTexture(){
    mTexture = NULL;
    mWidth = 0;
    mHeight = 0;
}

LTexture::~LTexture(){
    free();
}

void LTexture::loadFromFile(string path){
    SDL_Texture* newTexture;
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    SDL_SetColorKey(loadedSurface,SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 0xFF, 0xFF ) );
    newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
    mWidth = loadedSurface->w;
    mHeight = loadedSurface->h;

    SDL_FreeSurface(loadedSurface);
    mTexture = newTexture;
}

void LTexture::free(){
    if(mTexture!=NULL){
        SDL_DestroyTexture(mTexture);
        mTexture = NULL;
        mWidth = 0;
        mHeight = 0;
    }
}

void LTexture::render(int x, int y){
    SDL_Rect renderQuad = {x , y , mWidth, mHeight};
    SDL_RenderCopy(gRenderer, mTexture, NULL, &renderQuad);
}

int LTexture::getWidth(){
    return mWidth;
}

int LTexture::getHeight(){
    return mHeight;
}

void LTexture::loadFromRenderedText(string textureText, SDL_Color textColor )
{
    free();
    SDL_Surface* textSurface = TTF_RenderText_Solid( gFont, textureText.c_str(), textColor );
    mTexture = SDL_CreateTextureFromSurface( gRenderer, textSurface );
    mWidth = textSurface->w;
    mHeight = textSurface->h;
    SDL_FreeSurface( textSurface );
}


