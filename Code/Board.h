#pragma once
#include<iostream>
#include<vector>

using namespace std;

#define NONE 0
#define BLACK 1
#define WHITE -1

class Board
{
private:
    int board_size;
    vector<vector<int> >chess;
    vector<vector<int> >valmat;
public:
    Board();
    Board(const Board&);
    friend istream &operator>>(istream&, Board&);
    friend ostream &operator<<(ostream&, Board&);
    int get_board_size();
    vector<vector<int> > get_chess();
    void new_Game();
    void new_Valmat();
    bool canPut(int type,int x,int y,int dx,int dy);
    bool canPut(int type,int x,int y);
    void reverse(int type,int x,int y,int dx,int dy);
    bool put(int type,int x,int y);
    vector<pair<int,int> > check_move(int type);
    bool check(int type);
    int getWinLose();
    int eval();
    bool over();
    int emptyCount();
    pair<int,int> currentScore();
    ~Board();
};
