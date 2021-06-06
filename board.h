#ifndef __BOARD_
#define __BOARD_

#include <SDL.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

//read quiz array and answer array
vector< vector<int> > readFile(string path);

//random board
void changeBoard(vector< vector<int> > &numArr, vector< vector<int> > &answerArr);
void rotateBoard(int k, vector< vector<int> > &numArr );
void swapRow(int a, int b, vector< vector<int> > &numArr);
void swapColumn(int a, int b, vector< vector<int> > &numArr);
void moveRow(int k, vector< vector<int> > &numArr);
void moveColumn(int k, vector< vector<int> > &numArr);
void swapRandomRow(vector< vector<int> > &answerArr, vector< vector<int> > &numArr);
void swapRandomColumn(vector< vector<int> > &answerArr, vector< vector<int> > &numArr);

#endif // __BOARD_
