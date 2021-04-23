#include "Board.h"
#include "AI.h"
#include "time.h"
#include <cstdio>

using namespace std;

int main()
{
    clock_t t,c;
    int type=BLACK,current=0;
    AI hard;
    cin>>hard;
    vector<Board> movedList;
    t=clock();
    c=clock();
    hard.game.new_Game();
    hard.game.new_Valmat();
    movedList.push_back(hard.game);
    int q=-1;
    while(!hard.game.over()&&q<5000)
	{
	    q++;
	    cout<<hard;
		if(!hard.game.check(type))
		{
			type=-type;
			continue;
		}
		if(!hard.get_AItype()||hard.get_AItype()==type)
		{
			cout<<(type>0?"Black":"White")<<" Move:"<<'\n';
			hard.AImove(type);
			movedList.push_back(hard.game);
			current++;
			type=-type;
		}
		else if(hard.get_AItype()!=type&&hard.get_AItype()!=2)
        {
            cout<<(type>0?"Black":"White")<<" Move:"<<'\n';
            hard.moveRandom(type,hard.game.check_move(type));
            type=-type;
        }
		else
		{
			cout<<(type>0?"Black":"White")<<" Move:"<<'\n';
			vector<pair<int,int> > canMove=hard.game.check_move(type);
			for(int i=0;i<canMove.size();i++)
                cout<<'('<<canMove[i].second+1<<(char)(canMove[i].first+'A')<<") ";
			cout<<'\n';
			string s;
			cin>>s;
			if(s=="undo"&&current>0)
            {
                hard.game=movedList[current-1];
                current--;
                type=-type;
            }
            else if(s=="redo"&&current<movedList.size()-1)
            {
                hard.game=movedList[current+1];
                current++;
                type=-type;
            }
			else
            if(hard.put(type,tolower(s[1])-'a',s[0]-'1'))
            {
                while(current<movedList.size()-1) movedList.pop_back();
                movedList.push_back(hard.game);
                current++;
                type=-type;
            }
		}
		c=clock()-c;
        cout<<(float)c/CLOCKS_PER_SEC<<'\n';
        c=clock();
	}
	cout<<hard;
	current=hard.game.get_board_size();
	vector<vector<int> > a=hard.game.get_chess();
	freopen("test3.txt","w",stdout);
	cout<<current<<" -1"<<'\n';
	cout<<type<<'\n';
	for(int i=0;i<current;i++)
    {
        for(int j=0;j<current;j++) cout<<a[i][j]<<' ';
        cout<<'\n';
    }
	/*type=hard.game.getWinLose();
	pair<int,int> currentScore=hard.game.currentScore();
	cout<<currentScore.first<<":"<<currentScore.second<<'\n';
	if(type<0)cout<<"white win!"<<'\n';
	else if(type>0)cout<<"black win!"<<'\n';
	else cout<<"tie!"<<'\n';*/
	t=clock()-t;
	cout<<(float)t/CLOCKS_PER_SEC<<'\n';
    return 0;
}
