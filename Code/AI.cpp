#include"AI.h"
#include <cstdlib>
#include <ctime>

AI::AI()
{
    maxDepth=0;
}

istream &operator>>(istream &inp, AI &a)
{
    inp>>a.game;
    cout<<"Choose color: ";
    return inp>>a.AItype;
}

ostream &operator<<(ostream &out, AI &a)
{
    return out<<a.game;
}

int AI::get_AItype()
{
    return AItype;
}

bool AI::put(int type,int x,int y)
{
    return game.put(type,x,y);
}

long MX(long a,long b)
{
    if(a>b)return a;
    return b;
}

int AI::find_best_move(int type,int depth,long alpha,long beta)
{
    int size=brd.get_board_size();
	if(brd.over())return type*brd.getWinLose()*LINF;
	if(depth==0)return type*brd.eval();
	Board sav=brd;
	if(!brd.check(type))return MX(alpha,-find_best_move(-type,depth-1,-beta,-alpha));
	for(int i=0;i<size;++i)
	{
		for(int j=0;j<size;++j)
		{
			if(brd.canPut(type,i,j))
			{
				brd.put(type,i,j);
				long score=-find_best_move(-type,depth-1,-beta,-alpha);
				cout<<j+1<<(char)(i+'A')<<" score="<<score<<'\n';
				brd=sav;
				if(score>=beta)return score;
				if(score>alpha)
				{
					if(depth==maxDepth) bestMove=make_pair(i,j);
					alpha=score;
				}
			}
		}
	}
	return alpha;
}

void AI::AImove(int type)
{
	bestMove=make_pair(-1,-1);
	brd=game;
	maxDepth=2;
	int emptyCount=brd.emptyCount();
	if(emptyCount<=13) maxDepth=2000;
	double score=find_best_move(type,maxDepth,-INF,INF);
	cout<<" "<<score<<" "<<bestMove.first<<' '<<bestMove.second<<endl;
	game.put(type,bestMove.first,bestMove.second);
}

void AI::moveRandom(int type,vector<pair<int,int> >a)
{
    srand(time(NULL));
    int i=a.size();
    i=rand()%i;
    bestMove=a[i];
    cout<<" 0 "<<bestMove.first<<' '<<bestMove.second<<endl;
	game.put(type,bestMove.first,bestMove.second);
}

AI::~AI()
{
}
