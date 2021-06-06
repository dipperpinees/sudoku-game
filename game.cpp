#include <iostream>
#include <SDL.h>
#include "game.h"
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <queue>
#include "LTexture.h"
#include <cstdlib>
#include <ctime>
#include <SDL_mixer.h>
#include "board.h"

using namespace std;

Game::Game(){
    playGame = false;
    clickEmptyNum = false;
    wrong = false;
    row = -1;
    column = -1;
    wrongAnswer = -1;
    mistake = 3;
    hint = 3;
    level = "easy";
    pause = false;
    mute = false;
    chooseLevel = false;
    enterName = true;
    time = 0;
    score = 0;
    name = " ";
    showHighScore = false;

    sClick = NULL;
    sWrong = NULL;
    sCorrect = NULL;
    sWin = NULL;
    sLose = NULL;
}

Game::~Game(){
    freeMedia();
}

void Game::loadMediaGame(){
    gBoard.loadFromFile("data/image/boardd.png");
    gStart.loadFromFile("data/image/play.png");
    gPause.loadFromFile("data/image/pauseIcon.png");
    gClick.loadFromFile("data/image/click.png");
    gSuggest.loadFromFile("data/image/suggest.png");
    gNumber.loadFromFile("data/image/number.png");
    gHeart.loadFromFile("data/image/heart.png");
    gWin.loadFromFile("data/image/winIcon.png");
    gLose.loadFromFile("data/image/gameover.png");
    gPlayAgain.loadFromFile("data/image/playAgainIcon.png");
    gResume.loadFromFile("data/image/resume.png");
    gMainMenu.loadFromFile("data/image/mainmenu.png");
    gExit.loadFromFile("data/image/exit.png");
    gMute.loadFromFile("data/image/mute.png");
    gUnmute.loadFromFile("data/image/unmute.png");
    gClock.loadFromFile("data/image/alarm.png");
    gEasy.loadFromFile("data/image/easy.png");
    gMedium.loadFromFile("data/image/medium.png");
    gHard.loadFromFile("data/image/hard.png");
    gEnter.loadFromFile("data/image/name.png");
    gHighScore.loadFromFile("data/image/highscore.png");
    gTitle.loadFromFile("data/image/title.png");

    // text colors
    SDL_Color black = { 0, 0, 0 };
    SDL_Color red = { 223, 53, 57};
    SDL_Color gray = {192, 192, 192};

    blackNum[0].loadFromRenderedText(" ",black);
    for(int i=1;i<=9;i++){
        blackNum[i].loadFromRenderedText(to_String(i),black);
        redNum[i].loadFromRenderedText(to_String(i),red);
        grayNum[i].loadFromRenderedText(to_String(i),gray);
    }
    gFont = TTF_OpenFont( "data/font/consola.ttf", 30 );
    //high score text
    gTitleHS.loadFromRenderedText("HIGH SCORE", black);
    gBackHS.loadFromRenderedText("BACK", red);

    //load hint icon
    for(int i=0;i<=3;i++){
        gHint[i].loadFromFile("data/image/hint" + to_String(i) + ".png");
    }
    sClick = Mix_LoadWAV("data/sound/click.wav");
    sWrong = Mix_LoadWAV("data/sound/wrong.wav");
    sCorrect = Mix_LoadWAV("data/sound/correct.wav");
    sWin = Mix_LoadWAV("data/sound/win.wav");
    sLose = Mix_LoadWAV("data/sound/lose.wav");
}

void Game::render(){
    if(enterName){
        //render game title
        gTitle.render(SCREEN_WIDTH/2 - gTitle.getWidth()/2, 100);
        renderName();
    }

    else if(!playGame){
        //render game title
        gTitle.render(SCREEN_WIDTH/2 - gTitle.getWidth()/2, 100);

        if(!chooseLevel){
            if(!showHighScore){
                gStart.render(SCREEN_WIDTH/2 - gStart.getWidth()/2, 260);
                gHighScore.render(SCREEN_WIDTH/2 - gHighScore.getWidth()/2, 400 );
                gExit.render(SCREEN_WIDTH/2 - gExit.getWidth()/2, 540);
            }
            else{
                drawHighScore();
            }
        }
        else{
            //render level button
            gEasy.render(1366/2 - gEasy.getWidth()/2, 260);
            gMedium.render(1366/2 - gMedium.getWidth()/2, 400);
            gHard.render(1366/2 - gHard.getWidth()/2, 540);
        }
        gName.render(0,0);
    }
    else{
        if(!pause){
            //render time texture
            drawTime();
            drawLevel();
            drawBoard();
            drawScore();
            if(clickEmptyNum){
                drawClick();
                gNumber.render(812,100);
            }
            drawMistake();
            drawHint();
            gPlayAgain.render(1100,5);
            gPause.render(1300,5);
            drawMuteIcon();
            if(emptyNum == 0){
                gWin.render(790,135);
                clickEmptyNum = false;
            }
            else if(mistake ==0){
                gLose.render(790,135);
                clickEmptyNum = false;
            }
        }
        else{
            gResume.render(SCREEN_WIDTH/2 - gResume.getWidth()/2, 120);
            gMainMenu.render(SCREEN_WIDTH/2 - gMainMenu.getWidth()/2, 270);
            gExit.render(SCREEN_WIDTH/2 - gExit.getWidth()/2, 420);
        }

    }

}

void Game::handleGame(SDL_Event &e, bool &quit ){
    //enter name
    if(enterName){
        handleName(e);
    }
    else{
        handleMouse(e, quit);
    }
}

void Game::handleMouse(SDL_Event &e, bool &quit){
    if(e.type == SDL_MOUSEBUTTONDOWN){
        if(e.button.button == SDL_BUTTON_LEFT){
            //mouse state
            int mouseX,mouseY;
            SDL_GetMouseState(&mouseX,&mouseY);
            //handle in main menu
            if(!playGame){
                if(!chooseLevel){
                    if(!showHighScore){

                        //go to the level selection step
                        if(clickButton(gStart, SCREEN_WIDTH/2 - gStart.getWidth()/2, 260, mouseX, mouseY)){
                            chooseLevel = true;
                            timer.start();
                        }

                        //
                        else if(clickButton(gHighScore, SCREEN_WIDTH/2 - gHighScore.getWidth()/2, 400, mouseX, mouseY )){
                            showHighScore = true;
                        }
                        else if(clickButton(gExit, SCREEN_WIDTH/2 - gExit.getWidth()/2, 540, mouseX, mouseY)){
                            quit = true;
                        }
                    }
                    else{

                        //click back button to main menu
                        if(clickButton(gBackHS, SCREEN_WIDTH/2 - gBackHS.getHeight()/2 - 50, 600, mouseX, mouseY )){
                            showHighScore = false;
                        }
                    }
                }
                else{
                    //choose level game
                    if(clickButton(gEasy, SCREEN_WIDTH/2 - gEasy.getWidth()/2, 260, mouseX, mouseY)){
                        level = "easy";
                        playGame = true;
                        initBoard();
                    }
                    else if(clickButton(gMedium, SCREEN_WIDTH/2 - gMedium.getWidth()/2, 400, mouseX, mouseY)){
                        level = "medium";
                        playGame = true;
                        initBoard();
                    }
                    else if(clickButton(gHard, SCREEN_WIDTH/2 - gHard.getWidth()/2, 540, mouseX, mouseY)){
                        level = "hard";
                        playGame = true;
                        initBoard();
                    }
                }
            }

            //handle when play game
            else if(!pause){
                if(mistake != 0 && emptyNum !=0) {
                    //return true when you click empty cell
                    if(clickEmptyNumber(mouseX, mouseY)){
                        clickEmptyNum = true;
                        wrong = false;
                        if(!mute){
                            Mix_PlayChannel( -1, sClick, 0 );
                        }
                    }

                    //when you have clicked empty cell and choose your answer
                    else if(clickEmptyNum && chooseAnswer(mouseX, mouseY) != -1 ){

                        //correct answer
                        if( answerArr[row][column] == chooseAnswer(mouseX, mouseY) ){
                            numArr[row][column]  = chooseAnswer(mouseX, mouseY);
                            clickEmptyNum = false;
                            wrong = false;
                            emptyNum--;
                            if(!mute){
                                Mix_PlayChannel( -1, sCorrect, 0 );
                            }
                            handleScore(0);
                        }

                        //wrong answer
                        else{
                            wrongAnswer = chooseAnswer(mouseX, mouseY);
                            wrong = true;
                            mistake--;
                            if(!mute){
                                Mix_PlayChannel( -1, sWrong, 0 );
                            }
                            handleScore(1);
                        }
                    }

                    //handle when click suggest button
                    else if( clickButton(gHint[0], 1004, 660, mouseX, mouseY) && hint > 0){
                        suggest();
                        emptyNum--;
                        hint--;
                        clickEmptyNum = false;
                        if(!mute){
                            Mix_PlayChannel( -1, sCorrect, 0 );
                        }
                    }

                    else{
                        clickEmptyNum = false;
                        wrong = false;
                    }

                    //play sound when you win and handle score
                    if(emptyNum == 0){
                        timer.pause();
                        time = int( timer.getTicks() );
                        handleScore(2);
                        handleHighScore();
                        if(!mute)
                            Mix_PlayChannel( -1, sWin, 0 );
                    }
                    //play sound when you lose
                    else if(mistake == 0){
                        timer.pause();
                        if(!mute){
                            Mix_PlayChannel( -1, sLose, 0 );
                        }
                    }
                }

                //click pause button
                if( clickButton(gPause, 1300, 5, mouseX, mouseY)){
                    timer.pause();
                    pause = true;
                }

                //click play again button
                if(clickButton(gPlayAgain, 1100, 5, mouseX, mouseY)){
                    playAgain();
                }

                //click mute button
                if(clickButton(gMute, 1300, 60, mouseX, mouseY)){
                    if(mute)
                        mute = false;
                    else{
                        mute = true;
                    }
                }
            }

            //handle when pause game
            else{
                if(clickButton(gResume, SCREEN_WIDTH/2 - gResume.getWidth()/2, 120, mouseX, mouseY )){
                    if(mistake!=0 && emptyNum!=0){
                        timer.unpause();
                    }
                    pause = false;
                }

                else if(clickButton(gMainMenu, SCREEN_WIDTH/2 - gMainMenu.getWidth()/2, 270, mouseX, mouseY)){
                    backGame();
                }

                else if(clickButton(gExit, SCREEN_WIDTH/2 - gExit.getWidth()/2, 420, mouseX, mouseY )){
                    quit = true;
                }
            }
        }
    }
}

int Game::chooseAnswer(int mouseX, int mouseY){

    //return the number you pressed
    if(mouseX>=808 && mouseX <= 1262 && mouseY >= 139 && mouseY <=630){
        int x = (mouseX - 808)/167 + 1;
        int y = (mouseY - 139)/167 ;
        return y*3 + x;
    }
    return -1;
}

int Game::getEmptyNumbers(){
    int count = 0;
    for(int i = 0;i<9;i++){
        for(int j = 0;j<9;j++){
            if(numArr[i][j]==0){
                count++;
            }
        }
    }
    return count;
}

bool Game::clickEmptyNumber(int mouseX, int mouseY){

    //save the row and column position of the clicked cell
    if(mouseY >= 55 && mouseY <= 55 + 700 && mouseX >= 15 && mouseX <= 715 ){
        int b = (mouseX - 12)/76;
        int a = (mouseY - 55)/76;
        if(numArr[a][b] == 0){
            row = a;
            column = b;
            return true;
        }
    }
    return false;
}

void Game::initBoard(){

    //load random quiz array and random answer array
    int k = random(1, 4);
    numArr = readFile("data/boarddata/" + level + "/puzzle/" + to_String(k) + ".txt");
    answerArr = readFile("data/boarddata/" + level + "/solves/" + to_String(k) + ".txt");

    //Count how many numbers have to answer
    emptyNum = getEmptyNumbers();

    //random board
    changeBoard(numArr, answerArr);
}

void Game::drawBoard(){
    gBoard.render(15,55);
    for(int i=0;i<9;i++){
        for(int j=0;j<9;j++){
            blackNum[numArr[i][j]].render(38+77*j,65+77*i);
        }
    }

    //change the color of cells in the same row of the same column when clicking on an empty cell
    if(clickEmptyNum){
        for(int i = 0;i< 9 ;i++){
            grayNum[numArr[row][i]].render(38+77*i,65+77*row);
            grayNum[numArr[i][column]].render(38+77*column,65+77*i);
        }
        for(int i = (row/3) * 3;i<(row/3)*3+3;i++){
            for(int j = (column/3) * 3;j<(column/3)*3 + 3;j++){
                grayNum[numArr[i][j]].render(38+77*j,65+77*i);
            }
        }
    }
}

void Game::drawClick(){
    if(!wrong){
        gClick.render(30+77*column,60+77*row);
    }

    //if it is wrong, the number will be red
    else{
        redNum[wrongAnswer].render(35+77*column,65+77*row);
    }
}

void Game::drawHint(){
    gHint[hint].render(1015, 645);
}

void Game::drawMistake(){
    for(int i=0;i<mistake;i++){
        gHeart.render(900+(gHeart.getWidth() + 10)*i,7);
    }
}

void Game::drawLevel(){
    SDL_Color textColor = { 0, 0, 0, 255 };
    gLevel.loadFromRenderedText(level, textColor);
    gLevel.render(18,20);
}

void Game::drawScore(){
    SDL_Color textColor = { 0, 0, 0, 255 };
    gScore.loadFromRenderedText("Score: " +to_String(score), textColor);
    gScore.render(558,20);
}

void Game::drawMuteIcon(){
    if(!mute){
        gMute.render(1300,60);
    }
    else{
        gUnmute.render(1300,60);
    }
}

void Game::drawTime(){
        timeText.str( "" );
        if(int( timer.getTicks() / 1000.f)/60 < 10){
            timeText << "0" << (int( timer.getTicks() / 1000.f)/60 ) ;
        }
        else{
            timeText << (int( timer.getTicks() / 1000.f)/60 ) ;
        }
        timeText << ":";
        if(int( timer.getTicks() / 1000.f)%60 < 10){
            timeText << "0" << (int( timer.getTicks() / 1000.f)%60 ) ;
        }
        else{
            timeText << (int( timer.getTicks() / 1000.f)%60 ) ;
        }
        SDL_Color textColor = { 0, 0, 0, 255 };
        timePlay.loadFromRenderedText( timeText.str().c_str(), textColor );
        timePlay.render(310,20);
        gClock.render(410,21);
}

void Game::renderName(){
    SDL_Color textColor = { 0, 0, 0, 255 };
    gEnter.render(SCREEN_WIDTH/2 - gEnter.getWidth()/2, 200);
    gName.loadFromRenderedText(name, textColor);
    gName.render(350,390);
}

void Game::handleName(SDL_Event &e){
    if(e.type == SDL_KEYDOWN ){

        //press backspace
        if(e.key.keysym.sym == SDLK_BACKSPACE ){
            name = name.substr(0, name.size()-1);
        }

        // press enter
        else if(e.key.keysym.sym == 13){
            enterName = false;
        }
        else if(name.size()<40){
            name += e.key.keysym.sym;
        }
    }
}

void Game::handleScore(int i){

    //increase score
    if(i==0){
        if(level == "easy"){
            score += 100;
        }
        else if(level == "medium"){
            score += 150;
        }
        else{
            score += 200;
        }
    }

    //decrease score
    else if(i==1){
        if(level == "easy"){
            score -= 50;
        }
        else if(level == "medium"){
            score -= 100;
        }
        else{
            score -= 150;
        }
    }

    //summary score
    else{
        score = score + 100000/time + 200;
    }
}

bool Game::clickButton(LTexture &m,int x, int y, int mouseX, int mouseY){
    return (mouseX>=x && mouseX<=x+m.getWidth() && mouseY>=y && mouseY<=y+m.getHeight());
}

void Game::suggest(){

    //use vector temp to save the remaining empty cells
    vector< vector<int> > temp;
    for(int i = 0;i<9;i++){
        for(int j = 0;j<9;j++){
            if(numArr[i][j]==0){
                vector<int> temp2;
                temp2.push_back(i);
                temp2.push_back(j);
                temp.push_back(temp2);
            }
        }
    }

    //random cell hint
    int randomInt = random(0, temp.size() - 1);
    numArr[ temp[randomInt][0] ][ temp[randomInt][1] ] = answerArr[ temp[randomInt][0] ][ temp[randomInt][1] ];
}

void Game::handleHighScore(){
    string n;
    fstream fsFile;
    fsFile.open("data/highscore.txt", ios::in);
    vector< Player > playerGame;
    while (!fsFile.eof())
    {
        char c;
        fsFile>>c;
        n+=c;
    }
    bool next = true;
    string temp = "";
    Player temp2(temp,0);
    for(unsigned int i=0;i<n.size();i++){
        if(n[i]=='.'){
            if(next){
                temp2.name = temp;
                next = false;
            }

            else{
                temp2.score = to_Int(temp);
                playerGame.push_back(temp2);
                next = true;
            }
            temp = "";
        }
        else{
            temp+=n[i];
        }
    }
    Player currentPlayer(name, score);
    playerGame.push_back(currentPlayer);
    for(int i=0;i<6;i++){
        for(int j=i+1;j<6;j++){
            if(playerGame[i].score<playerGame[j].score){
                Player temp3 = playerGame[i];
                playerGame[i] = playerGame[j];
                playerGame[j] = temp3;
            }
        }
    }
    playerGame.erase(playerGame.end());
    string save = "";
    for(int i=0;i<5;i++){
        save = save + playerGame[i].name + "." + to_String(playerGame[i].score) + ".";
    }
    ofstream ofs ("data/highscore.txt");
    ofs<<save;
    ofs.close();
    fsFile.close();
}

void Game::drawHighScore(){

    //open file, read and write to string n
    string n;
    fstream fsFile;
    fsFile.open("data/highscore.txt", ios::in);
    vector< Player > playerGame;
    while (!fsFile.eof())
    {
        char c;
        fsFile>>c;
        n+=c;
    }

    //if next is true then save the player name and next is false then save player score
    bool next = true;
    string temp = "";
    Player temp2(temp,0);
    for(unsigned int i=0;i<n.size();i++){
        if(n[i]=='.'){
            if(next){
                temp2.name = temp;
                next = false;
            }

            else{
                temp2.score = to_Int(temp);
                playerGame.push_back(temp2);
                next = true;
            }
            temp = "";
        }
        else{
            temp+=n[i];
        }
    }
    SDL_Color textColor = { 0, 0, 0, 255 };

    //save player names and points in 2 arrays and then render in turn
    for(int i=0;i<5;i++){
        nameArr[i].loadFromRenderedText(playerGame[i].name, textColor);
        scoreArr[i].loadFromRenderedText(to_String(playerGame[i].score), textColor);
    }

    //high score text
    gTitleHS.render(SCREEN_WIDTH/2 - gTitleHS.getWidth()/2,250);

    //back button
    gBackHS.render(SCREEN_WIDTH/2 - gBackHS.getHeight()/2 - 50,600);
    for(int i=0;i<5;i++){
        nameArr[i].render(500, 350+50*i);
        scoreArr[i].render(768, 350+50*i);
    }
    fsFile.close();
}

void Game::playAgain(){

    //reset time
    timer.stop();
    timer.start();

    //reset Board
    initBoard();
    playGame = true;
    clickEmptyNum = false;
    wrong = false;
    row = -1;
    column = -1;
    wrongAnswer = -1;
    mistake = 3;
    hint = 3;
    score = 0;
}

void Game::backGame(){
    timer.stop();
    playGame = false;
    pause = false;
    clickEmptyNum = false;
    wrong = false;
    row = -1;
    column = -1;
    wrongAnswer = -1;
    mistake = 3;
    hint = 3;
    level = "easy";
    chooseLevel = false;
    score = 0;
}

void Game::freeMedia(){

    //free textures
    gBoard.free();
    gStart.free();
    gClick.free();
    gPlayAgain.free();
    gSuggest.free();
    gPause.free();
    gNumber.free();
    gHeart.free();
    gWin.free();
    gLose.free();
    gResume.free();
    gMainMenu.free();
    gExit.free();
    gClock.free();
    gMute.free();
    gUnmute.free();
    gClock.free();
    gEasy.free();
    gMedium.free();
    gHard.free();
    gName.free();
    timeTexture.free();
    gEnter.free();
    gHighScore.free();
    gTitle.free();
    gTitleHS.free();
    gBackHS.free();

    for(int i=0;i<=3;i++){
        gHint[i].free();
    }
    for(int i=0;i<=9;i++){
        blackNum[i].free();
        grayNum[i].free();
        redNum[i].free();
    }
    for(int i=0; i<5;i++){
        nameArr[i].free();
        scoreArr[i].free();
    }

    //free sounds
    Mix_FreeChunk( sClick );
    Mix_FreeChunk( sWin );
    Mix_FreeChunk( sCorrect );
    Mix_FreeChunk( sLose );
    Mix_FreeChunk( sWrong );
    sClick = NULL;
    sWrong = NULL;
    sCorrect = NULL;
    sWin = NULL;
    sLose = NULL;
}

string to_String(int i){
	string k;
	ostringstream convert;
	convert<<i;
	k = convert.str();
	return k;
}

int to_Int(string n){
    return atoi(n.c_str());
}

int random(int minN, int maxN){
    return minN + rand() % (maxN + 1 - minN);
}
