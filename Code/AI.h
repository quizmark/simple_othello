#pragma once
#include"Board.h"

#define INF LONG_MAX
#define LINF 100000000

using namespace std;

class AI
{
private:
    pair<int,int> bestMove;
    int maxDepth,AItype,lvl;
public:
    Board game,brd;
    AI();
    friend istream &operator>>(istream&, AI&);
    friend ostream &operator<<(ostream&, AI&);
    bool put(int type,int x,int y);
    int get_AItype();
    int find_best_move(int type,int depth,long,long);
    void AImove(int type);
    void moveRandom(int,vector<pair<int,int> >);
    ~AI();
};
