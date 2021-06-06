#ifndef __LTEXTURE_
#define __LTEXTURE_

#include<iostream>
#include<SDL.h>
#include<string>

using namespace std;


class LTexture{
    public:
        LTexture();
        ~LTexture();
        void loadFromFile(string path);
        void loadFromRenderedText(string textureText, SDL_Color textColor );
        void free();
        void render(int x,int y);
        int getWidth();
        int getHeight();
    private:
        SDL_Texture* mTexture;
        int mWidth;
        int mHeight;
};


#endif // __LTEXTURE_
