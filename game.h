#ifndef __GAME_
#define __GAME_

#include <SDL.h>
#include <iostream>
#include <vector>
#include "LTexture.h"
#include <SDL_mixer.h>
#include "LTimer.h"
#include <sstream>
#include <SDL_ttf.h>

using namespace std;

class Game{
    public:
        Game();
        ~Game();

        //load media
        void loadMediaGame();

        //load board data
        void initBoard();

        // handle game
        void handleGame(SDL_Event &e, bool &quit);

        //render texture to screen
        void render();

        //play again
        void playAgain();

        //back to main menu
        void backGame();

        // render mute icon
        void drawMuteIcon();

        // render board
        void drawBoard();

        // render click icon
        void drawClick();

        // render hint icon
        void drawHint();

        // render mistake number
        void drawMistake();

        //suggest
        void suggest();

        //handle when choose the answer
        int chooseAnswer(int mouseX, int mouseY);

        //return the position when an empty cell is clicked
        int getEmptyNumbers();

        //return true when an empty cell is clicked
        bool clickEmptyNumber(int mouseX, int mouseY);

        //handle when a button is clicked
        bool clickButton(LTexture &m, int x, int y, int mouseX, int mouseY);

        //handle mouse when play game
        void handleMouse(SDL_Event &e, bool &quit);

        //handle the event when entering a name
        void handleName(SDL_Event &e);

        //render player's name
        void renderName();

        //handle when type backspace when entering name
        string backSpace();

        //draw game level
        void drawLevel();

        //draw player's score
        void drawScore();

        //handle player's score
        void handleScore(int i);

        // handle high score
        void handleHighScore();

        // draw high score
        void drawHighScore();

        //render time texture
        void drawTime();

        // free media
        void freeMedia();

    private:
        bool playGame,wrong, playagain, backToMenu, pause, mute,
                chooseLevel, clickEmptyNum, enterName, showHighScore;
        int row, column, wrongAnswer, mistake, emptyNum, hint, time, score;
        vector< vector<int> > numArr, answerArr;
        string level, name;
        LTimer timer;
        stringstream timeText;
        LTexture gStart, gBoard, gClick, gPause, gLevel, gScore, gHighScore, gTitle, gTitleHS, gBackHS,
            gPlayAgain, gSuggest, gResume, gNumber, gHeart, gEasy, gMedium, gHard, gName, gEnter,
            gWin, gLose, gHome, timeTexture, timePlay, gMainMenu, gExit, gClock, gMute, gUnmute;
        LTexture blackNum[10], grayNum[10], redNum[10], gHint[4], nameArr[5], scoreArr[5];
        Mix_Chunk *sClick;
        Mix_Chunk *sWrong;
        Mix_Chunk *sCorrect;
        Mix_Chunk *sWin;
        Mix_Chunk *sLose;
};

struct Player{
    string name;
    int score;
    Player(string n, int s){
        name = n;
        score = s;
    }
};

int random(int minN, int maxN);
string to_String(int i);
int to_Int(string n);
extern TTF_Font *gFont;
extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;


#endif // __GAME_
