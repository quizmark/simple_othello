#include"Board.h"

Board::Board()
{
    board_size=8;
}

Board::Board(const Board &a)
{
    board_size=a.board_size;
    for(int i=0;i<board_size;i++)
    for(int j=0;j<board_size;j++) chess[i][j]=a.chess[i][j];
}

istream &operator>>(istream &inp, Board &a)
{
	cout << "Choose board size: ";
	return inp >> a.board_size;
}

ostream &operator<<(ostream &out, Board &a)
{
	out<<"   ";
    for(char i='A';i<a.board_size+'A';i++)
    {
        out<<i<<"   ";
    }
    out<<endl;
    for(int i=0;i<a.board_size;i++)
    {
        if(i<9) out<<'0';
        out<<i+1;
        for(int j=0;j<a.board_size;j++)
        if(a.chess[i][j]==WHITE) out<<" W  ";
        else if(a.chess[i][j]==BLACK) out<<" B  ";
        else out<<" [] ";
        out<<endl;
    }
    return out;
}

int Board::get_board_size()
{
    return board_size;
}

void Board::new_Game()
{
    for(int i=0;i<board_size;i++)
    for(int j=0;j<board_size;j++)
        chess[i][j]=NONE;
    chess[board_size/2-1][board_size/2-1]=WHITE;
    chess[board_size/2-1][board_size/2]=BLACK;
    chess[board_size/2][board_size/2-1]=BLACK;
    chess[board_size/2][board_size/2]=WHITE;
}

void Board::new_Valmat()
{
    for(int i=0;i<board_size;i++)
    for(int j=0;j<board_size;j++)
    {
        if((i==0&&j==0)||(i==0&&j==board_size-1)||
           (i==board_size-1&&j==0)||(i==board_size-1&&j==board_size-1))
                        valmat[i][j]=200.0;
        else if((i==0&&j==1)||(i==1&&j==0)||
                (i==board_size-2&&j==0)||(i==board_size-1&&j==1)||
                (i==board_size-1&&j==board_size-2)||(i==board_size-2&&j==board_size-1)||
                (i==1&&j==board_size-1)||(i==0&&j==board_size-2))
                        valmat[i][j]=-25.0;
        else if((i==1&&j==1)||(i==board_size-2&&j==1)||
                (i==board_size-2&&j==board_size-2)||(i==1&&j==board_size-2))
                        valmat[i][j]=-50.0;
        else if((i==0&&j>1&&j<board_size-2)||
                (i>1&&i<board_size-2&&j==0)||
                (i==board_size-1&&j>1&&j<board_size-2)||
                (i>1&&i<board_size-2&&j==board_size-1))
                        valmat[i][j]=20.0;
        else if((i==1&&j>1&&j<board_size-2)||
                (i>1&&i<board_size-2&&j==1)||
                (i==board_size-2&&j>1&&j<board_size-2)||
                (i>1&&i<board_size-2&&j==board_size-2))
                        valmat[i][j]=5.0;
        else valmat[i][j]=1.0;
    }
}

bool Board::canPut(int type,int x,int y,int dx,int dy)
{
    x+=dx;y+=dy;
    if(x<0||x>=board_size||y<0||y>=board_size)return false;
    if(chess[x][y]!=-type)return false;
    while(x>=0&&x<board_size&&y>=0&&y<board_size)
    {
        if(chess[x][y]==type)return true;
        else if(chess[x][y]==NONE)return false;
        x+=dx;y+=dy;
    }
    return false;
}

bool Board::canPut(int type,int x,int y)
{
    if(chess[x][y]!=NONE)return false;
    const int dx[8]={-1,1,0,0,-1,1,-1,1};
    const int dy[8]={0,0,1,-1,-1,-1,1,1};
    for(int i=0;i<8;i++)
    if(canPut(type,x,y,dx[i],dy[i]))return true;
    return false;
}

void Board::reverse(int type,int x,int y,int dx,int dy)
{
    x+=dx;y+=dy;
    while(x>=0&&x<board_size&&y>=0&&y<board_size)
    {
        if(chess[x][y]==-type) chess[x][y]=type;
        else return;
        x+=dx;y+=dy;
    }
}

bool Board::put(int type,int x,int y)
{
    const int dx[8]={-1,1,0,0,-1,1,-1,1};
    const int dy[8]={0,0,1,-1,-1,-1,1,1};
    if(!canPut(type,x,y))return false;
    for(int i=0;i<8;i++)
    if(canPut(type,x,y,dx[i],dy[i])) reverse(type,x,y,dx[i],dy[i]);
    chess[x][y]=type;
    return true;
}

vector<pair<int,int> > Board::check_move(int type)
{
    vector<pair<int,int> >suggest_move;
    for(int x=0;x<board_size;x++)
    for(int y=0;y<board_size;y++)
    if(canPut(type,x,y))suggest_move.push_back(make_pair(x,y));
    return suggest_move;
}

bool Board::check(int type)
{
    for(int x=0;x<board_size;x++)
    for(int y=0;y<board_size;y++)
    if(canPut(type,x,y))return true;
    return false;
}

int Board::getWinLose()
{
    int res=0;
    for(int i=0;i<board_size;i++)
    for(int j=0;j<board_size;j++) res+=chess[i][j];
    return res;
}

double Board::eval()
{
    double res=0;
    for(int i=0;i<board_size;i++)
    for(int j=0;j<board_size;j++)
    res+=valmat[i][j]*chess[i][j];
    return res;
}

bool Board::over()
{
    return !check(BLACK)&&!check(WHITE);
}

int Board::emptyCount()
{
    int res=0;
    for(int i=0;i<board_size;i++)
    for(int j=0;j<board_size;j++)
    if(chess[i][j]==NONE) res++;
    return res;
}

pair<int,int> Board::currentScore()
{
    int resA=0,resB=0;
    for(int i=0;i<board_size;i++)
    for(int j=0;j<board_size;j++)
    if(chess[i][j]==BLACK) resA++;
    else if(chess[i][j]==WHITE) resB++;
    return make_pair(resA,resB);
}

Board::~Board()
{
}
