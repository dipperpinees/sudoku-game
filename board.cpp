#include <SDL.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include "board.h"
#include <queue>
#include "game.h"

using namespace std;

vector< vector<int> > readFile(string path){
	vector< vector<int> > arr;
	fstream fsFile;
	fsFile.open(path.c_str(), ios::in);
    int i ;
    queue <int> numData;
    while (!fsFile.eof())
    {
		fsFile>>i;
		numData.push(i);
    }
    for(int j = 0;j<9;j++){
    	vector<int> temp;
    	for(int k=0;k<9;k++){
    		temp.push_back(numData.front());
    		numData.pop();
		}
		arr.push_back(temp);
	}
	fsFile.close();
	return arr;
}

void rotateBoard(int k, vector< vector<int> > &numArr ){
    if(k==1){
        vector< vector<int> > temp;
        for(int i=0; i<9; i++){
            vector<int> temp2;
            for(int j=0; j<9; j++){
                temp2.push_back(numArr[j][i]);
            }
            temp.push_back(temp2);
        }
        numArr = temp;
    }
    else if(k==2){
        vector< vector<int> > temp;
        for(int i=8; i>=0; i--){
            vector<int> temp2;
            for(int j=0; j<9; j++){
                temp2.push_back(numArr[j][i]);
            }
            temp.push_back(temp2);
        }
        numArr = temp;
    }
    else if(k==3){
        vector< vector<int> > temp;
        for(int i=8; i>=0; i--){
            vector<int> temp2;
            for(int j=0; j<9; j++){
                temp2.push_back(numArr[i][j]);
            }
            temp.push_back(temp2);
        }
        numArr = temp;
    }
}

void swapRow(int a, int b, vector< vector<int> > &numArr){
    vector<int> temp;
    for(int i =0;i<9;i++){
        temp.push_back(numArr[a][i]);
    }
    for(int i=0;i<9;i++){
        numArr[a][i] = numArr[b][i];
    }
    for(int i=0;i<9;i++){
        numArr[b][i] = temp[i];
    }
}

void swapColumn(int a, int b, vector< vector<int> > &numArr){
    vector<int> temp;
    for(int i =0;i<9;i++){
        temp.push_back(numArr[i][a]);
    }
    for(int i=0;i<9;i++){
        numArr[i][a] = numArr[i][b];
    }
    for(int i=0;i<9;i++){
        numArr[i][b] = temp[i];
    }
}

void moveRow(int k, vector< vector<int> > &numArr){
    if(k==1){
        swapRow(0,3,numArr);
        swapRow(1,4,numArr);
        swapRow(2,5,numArr);
    }
    else if(k==2){
        swapRow(0,6,numArr);
        swapRow(1,7,numArr);
        swapRow(2,8,numArr);
    }
    else if(k==3){
        swapRow(3,6,numArr);
        swapRow(4,7,numArr);
        swapRow(5,8,numArr);
    }
}

void moveColumn(int k, vector< vector<int> > &numArr){
    if(k==1){
        swapColumn(0,3,numArr);
        swapColumn(1,4,numArr);
        swapColumn(2,5,numArr);
    }
    else if(k==2){
        swapColumn(0,6,numArr);
        swapColumn(1,7,numArr);
        swapColumn(2,8,numArr);
    }
    else if(k==3){
        swapColumn(3,6,numArr);
        swapColumn(4,7,numArr);
        swapColumn(5,8,numArr);
    }
}

void swapRandomRow(vector< vector<int> > &answerArr, vector< vector<int> > &numArr){
    for(int i=0;i<3;i++){
        int k = random(0,3);
        if(k==1){
           swapRow(i*3, i*3 + 1, answerArr);
           swapRow(i*3, i*3 + 1, numArr);
        }
        else if(k==2){
            swapRow(i*3, i*3 +2, answerArr);
            swapRow(i*3, i*3 +2, numArr);
        }
        else if(k==3){
            swapRow(i*3+1, i*3 +2, answerArr);
            swapRow(i*3+1, i*3 +2, numArr);
        }
    }
}

void swapRandomColumn(vector< vector<int> > &answerArr, vector< vector<int> > &numArr){
    int g = random(3,5);
    for(int i=0;i<g;i++){
        for(int i=0;i<3;i++){
            int k = random(0,3);
            if(k==1){
                swapColumn(i*3, i*3 + 1, answerArr);
                swapColumn(i*3, i*3 + 1, numArr);
            }
            else if(k==2){
                swapColumn(i*3, i*3 +2, answerArr);
                swapColumn(i*3, i*3 +2, numArr);
            }
            else if(k==3){
                swapColumn(i*3+1, i*3 +2, answerArr);
                swapColumn(i*3+1, i*3 +2, numArr);
            }
        }
    }
}

void changeBoard(vector< vector<int> > &numArr, vector< vector<int> > &answerArr){
    int rotate = random(0,3);
    int move1 = random(0,3);
    int move2 = random(0,3);
    rotateBoard(rotate, numArr);
    moveRow(move1, numArr);
    moveColumn(move2, numArr);
    rotateBoard(rotate, answerArr);
    moveRow(move1, answerArr);
    moveColumn(move2, answerArr);
    swapRandomRow(answerArr, numArr);
    swapRandomColumn(answerArr, numArr);
}
