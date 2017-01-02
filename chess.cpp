#include "chess.h"
#include<algorithm>
#include<limits.h>
#include<vector>
#include<utility>
#include<string.h>
using namespace std;
void Chess::chess_isover(int x,int y,int turn) 
{
	int num=1;
	int i,j;
	for(i=y-1;i>=0;--i)
		if(pos[x][i]==turn)	++num;
		else	break;
	for(i=y+1;i<16;++i)
		if(pos[x][i]==turn)	++num;
		else	break;
	if(num>=5)
	{
		isover=turn;
		return;
	}
	num=1;
	for(i=x-1;i>=0;--i)
		if(pos[i][y]==turn)	++num;
		else	break;
	for(i=x+1;i<16;++i)
		if(pos[i][y]==turn)	++num;
		else	break;
	if(num>=5)
	{
		isover=turn;
		return;
	}
	num=1;
	for(i=x-1,j=y-1;i>=0&&j>=0;--i,--j)
		if(pos[i][j]==turn)	++num;
		else	break;
	for(i=x+1,j=y+1;i<16&&j<16;++i,++j)
		if(pos[i][j]==turn)	++num;
		else	break;
	if(num>=5)
	{
		isover=turn;
		return;
	}
	num=1;
	for(i=x-1,j=y+1;i>=0&&j<16;--i,++j)
		if(pos[i][j]==turn)	++num;
		else	break;
	for(i=x+1,j=y-1;i<16&&j>=0;++i,--j)
		if(pos[i][j]==turn)	++num;
		else	break;
	if(num>=5)
	{
		isover=turn;
		return;
	} 
	if(backnum+whitenum==16*16)
	{
		isover=3;
		return;
	}
}
static int score[17][17];
void evaluate_naive()
{		 
	memset(score,0,sizeof(score));
	int number1,number2,empty;
	for(int x=0;x<16;++x)
		for(int y=0;y<16;++y)
			if(pos[x][y]==0)
				for(int i=-1;i<=1;++i) 
					for(int j=-1;j<=1;++j)
						if(!(i==0&&j==0))
						{
							number1=0,number2=0,empty=0;
							for(int k=1;k<=5;++k)
								if(x+i*k>=0&&x+i*k<=15&&y+j*k>=0&&y+j*k<=15&&pos[x+i*k][y+j*k]==1)	++number1;
								else if(x+i*k>=0&&x+i*k<=15&&y+j*k>=0&&y+j*k<=15&&pos[x+i*k][y+j*k]==0)	{++empty;break;}
								else	break;
							for(int k=-1;k>=-5;--k)
								if(x+i*k>=0&&x+i*k<=15&&y+j*k>=0&&y+j*k<=15&&pos[x+i*k][y+j*k]==1)	++number1;
								else if(x+i*k>=0&&x+i*k<=15&&y+j*k>=0&&y+j*k<=15&&pos[x+i*k][y+j*k]==0)	{++empty;break;}
								else	break;
							if(number1==1)	score[x][y]+=1;
							else if(number1==2) 
							{
								if(empty==1)	score[x][y]+=5;
								else if(empty==2)	score[x][y]+=10;
							}
							else if(number1==3)
							{
								if(empty==1)	score[x][y]+=20;
								else if(empty==2)	score[x][y]+=100;
							}
							else if(number1==4) score[x][y]+=1000;
							empty=0;
							for(int k=1;k<=5;++k)
								if(x+i*k>=0&&x+i*k<=15&&y+j*k>=0&&y+j*k<=15&&pos[x+i*k][y+j*k]==2)	++number2;
								else if(x+i*k>=0&&x+i*k<=15&&y+j*k>=0&&y+j*k<=15&&pos[x+i*k][y+j*k]==0)	{++empty;break;}
								else	break;
							for(int k=-1;k>=-5;--k)
								if(x+i*k>=0&&x+i*k<=15&&y+j*k>=0&&y+j*k<=15&&pos[x+i*k][y+j*k]==2)	++number2;
								else if(x+i*k>=0&&x+i*k<=15&&y+j*k>=0&&y+j*k<=15&&pos[x+i*k][y+j*k]==0)	{++empty;break;}
								else	break;
							if(number2==0)	score[x][y]+=1;
							else if(number2==1)	score[x][y]+=2;
							else if(number2==2) 
							{
								if(empty==1)	score[x][y]+=8;
								else if(empty==2)	score[x][y]+=30;
							}	 
							else if(number2==3)
							{
								if(empty==1)	score[x][y]+=50;
								else if(empty==2)	score[x][y]+=200;
							}
							else if(number2==4) score[x][y]+=10000;
						}
}
void Chess::chess_ai_naive(int &x,int &y)
{
	evaluate_naive();
	int maxpos=0;
	for(int i=0;i<16;++i)
		for(int j=0;j<16;++j)	
			if(score[i][j]>maxpos)
			{
				maxpos=score[i][j];
				x=i;
				y=j;
			}
}
int max_noalphabeta(int depth,int i1,int i2);
int min_noalphabeta(int depth,int i1,int i2);
void generatepoint(vector< pair<int,int> > &v);
int scoretable(int number,int empty1);
int countscore(vector<int> n,int turn);
bool hasne(int x,int y);
bool hasne(int x,int y)
{
	int i,j;
	for(i=(x-1>0?x-1:0);i<=x+1&&i<16;++i) 
		for(j=(y-1>0?y-1:0);j<=y+1&&j<16;++j)
			if(i!=0||j!=0)
				if(pos[i][j]!=0)
					return true;
	return false;
} 
int evaluate_point(int x,int y,int turn)
{
	int scoree=0;
	int number=0;
	int empty1=0;
	int i,j;
	for(i=y-1;i>=0&&i>y-6;--i)
		if(pos[x][i]==turn)	++number;
		else if(pos[x][i]==0)	{++empty1;break;}
		else break;		
	for(i=y+1;i<16&&i<y+6;++i)
		if(pos[x][i]==turn)	++number;
		else if(pos[x][i]==0)	{++empty1;break;}
		else break;
	scoree+=scoretable(number+1,empty1);
	number=0;
	empty1=0;
	for(i=x-1;i>=0&&i>x-6;--i)
		if(pos[i][y]==turn)	++number;
		else if(pos[i][y]==0)	{++empty1;break;}
		else break;	
	for(i=x+1;i<16&&i<x+6;++i)
		if(pos[i][y]==turn)	++number;
		else if(pos[i][y]==0)	{++empty1;break;}
		else break;
	scoree+=scoretable(number+1,empty1);
	number=0;
	empty1=0;
	for(i=x-1,j=y-1;i>=0&&j>=0&&i>x-6&&j>y-6;--i,--j)
		if(pos[i][j]==turn)	++number;
		else if(pos[i][j]==0)	{++empty1;break;}
		else	break;
	for(i=x+1,j=y+1;i<16&&j<16&&i<x+6&&j<y+6;++i,++j)
		if(pos[i][j]==turn)	++number;
		else if(pos[i][j]==0)	{++empty1;break;}
		else	break;
	scoree+=scoretable(number+1,empty1);
	number=0;
	empty1=0;
	for(i=x-1,j=y+1;i>=0&&i>x-6&&j<16&&j<y+6;--i,++j)
		if(pos[i][j]==turn)	++number;
		else if(pos[i][j]==0)	{++empty1;break;}
		else	break;
	for(i=x+1,j=y-1;i<16&&i<x+6&&j>=0&&j>y-6;++i,--j)
		if(pos[i][j]==turn)	++number;
		else if(pos[i][j]==0)	{++empty1;break;}
		else	break;
	scoree+=scoretable(number+1,empty1);
	return scoree;
} 
void generatepoint(vector< pair<int,int> > &v)	
{
	vector<	pair<int,int> > humfive;
	vector< pair<int,int> > comfour;
	vector< pair<int,int> > humfour;
	vector< pair<int,int> >	comdoublethree;
	vector< pair<int,int> >	humdoublethree;
	vector< pair<int,int> > comthree;
	vector< pair<int,int> > humthree;
	vector<	pair<int,int> > comtwo;
	vector< pair<int,int> > humtwo;
	vector< pair<int,int> > others;
	for(int i=0;i<16;++i)
		for(int j=0;j<16;++j)
			if(pos[i][j]==0&&hasne(i,j))
			{
				int scorecom=evaluate_point(i,j,2);
				int scorehum=evaluate_point(i,j,1);
				pair<int,int> p;
				p.first=i;
				p.second=j;
				if(scorecom>=100000)	{v.push_back(p);return;}
				else if(scorehum>=100000)	{humfive.push_back(p);}
				else if(scorecom>=10000)	comfour.push_back(p);
				else if(scorehum>=10000)	humfour.push_back(p);
				else if(scorecom>=2*1000) 	comdoublethree.push_back(p);
				else if(scorehum>=2*1000)	humdoublethree.push_back(p);
				else if(scorecom>=1000)	comthree.push_back(p);
				else if(scorehum>=1000)	humthree.push_back(p);
				else if(scorecom>=100)	comtwo.push_back(p);
				else if(scorehum>=100)	humtwo.push_back(p);
				else 	 others.push_back(p);
			} 
	if(humfive.size()>0)	{v=humfive;return;}
	if(comfour.size()>0||humfour.size()>0)	{v=comfour;v.insert(v.end(),humfour.begin(),humfour.end());return;}
	if(comdoublethree.size()>0||humdoublethree.size()>0)	{v=comdoublethree;v.insert(v.end(),humdoublethree.begin(),humdoublethree.end());return;} 
	v=comthree;
	v.insert(v.end(),humthree.begin(),humthree.end());
	v.insert(v.end(),comtwo.begin(),comtwo.end());
	v.insert(v.end(),humtwo.begin(),humtwo.end());
	v.insert(v.end(),others.begin(),others.end());
	return; 
}
int scoretable(int number,int empty1)
{
	if(number>=5)	return 100000;
	else if(number==4)
	{
		if(empty1==2)	return 10000;
		else if(empty1==1)	return 1000;
	}
	else if(number==3)	
	{
		if(empty1==2)	return 1000;
		else if(empty1==1)	return 100;
	}
	else if(number==2)
	{
		if(empty1==2)	return 100;
		else if(empty1==1)	return 10;
	}
	else if(number==1&&empty1==2)	return 10;
	return 0;
}
int countscore(vector<int> n,int turn)
{
	int scoretmp=0;
	int len=n.size();
	int empty1=0;
	int number=0;
	if(n[0]==0)	++empty1;
	else if(n[0]==turn)	++number;
	int i=1;
	while(i<len)
	{
		if(n[i]==turn)	++number;
		else if(n[i]==0)
		{
			if(number==0)	empty1=1;
			else
			{
				scoretmp+=scoretable(number,empty1+1);
				empty1=1;
				number=0;
			}
		}
		else
		{
			scoretmp+=scoretable(number,empty1);
			empty1=0;
			number=0;
		}
		++i;
	}
	scoretmp+=scoretable(number,empty1);
	return scoretmp;
}
int evaluate_minmax_noalphabeta()
{
	int scorecomputer=0;
	int scorehumber=0;
	for(int i=0;i<16;++i)
	{
		vector<int> n;
		for(int j=0;j<16;++j)
			n.push_back(pos[i][j]);
		scorecomputer+=countscore(n,2);
		scorehumber+=countscore(n,1);
		n.clear();
	}
	for(int j=0;j<16;++j)
	{
		vector<int> n;
		for(int i=0;i<16;++i)
			n.push_back(pos[i][j]);
		scorecomputer+=countscore(n,2);
		scorehumber+=countscore(n,1);
		n.clear();
	} 
	for(int i=0;i<16;++i)
	{
		int x,y;
		vector<int> n;
		for(x=i,y=0;x<16&&y<16;++x,++y)
			n.push_back(pos[y][x]);
		scorecomputer+=countscore(n,2);
		scorehumber+=countscore(n,1);
		n.clear();
	}
	for(int j=1;j<16;++j)
	{
		int x,y;
		vector<int> n;
		for(x=0,y=j;y<16&&x<16;++x,++y)
			n.push_back(pos[y][x]);
	 	scorecomputer+=countscore(n,2);
		scorehumber+=countscore(n,1);
		n.clear();
	}
	for(int i=0;i<16;++i)
	{
		vector<int> n;
		int x,y;
		for(y=i,x=0;y>=0&&x<16;--y,++x)
			n.push_back(pos[y][x]);
		scorecomputer+=countscore(n,2);
		scorehumber+=countscore(n,1);
		n.clear();
	}
	for(int j=1;j<16;++j)
	{
		vector<int> n;
		int x,y;
		for(y=j,x=15;y<16&&x>=0;++y,--x)
			n.push_back(pos[x][y]);
		scorecomputer+=countscore(n,2);
		scorehumber+=countscore(n,1);
		n.clear();
	} 
	return scorecomputer-scorehumber;
} 
int min_noalphabeta(int depth,int i1,int i2)
{
	int res=evaluate_minmax_noalphabeta();
	Chess cc;
	cc.chess_isover(i1,i2,2);
	if(isover!=0||depth<=0)
	{
		isover=0;
		return res;
	}
	vector< pair<int,int> > v;
	generatepoint(v);
	int len=v.size();
	int best=INT_MAX;
	for(int i=0;i<len;++i)
	{
		pos[v[i].first][v[i].second]=1;
		int tmp=max_noalphabeta(depth-1,v[i].first,v[i].second); 
		if(tmp<best)	best=tmp;	
		pos[v[i].first][v[i].second]=0;
	} 
	return best;
}
int max_noalphabeta(int depth,int i1,int i2) 
{
	int res=evaluate_minmax_noalphabeta();
	Chess cc;
	cc.chess_isover(i1,i2,1);
	if(isover!=0||depth<=0)
	{
		isover=0;
		return res;
	}
	vector< pair<int,int> > v;
	generatepoint(v);
	int len=v.size();
	int best=INT_MIN;
	for(int i=0;i<len;++i)
	{
		pos[v[i].first][v[i].second]=2;
		int tmp=min_noalphabeta(depth-1,v[i].first,v[i].second);
		if(tmp>best)	best=tmp;	
		pos[v[i].first][v[i].second]=0;
	} 
	return best;
}
void Chess::chess_ai_minmax_noalphabeta(int &x,int &y,int depth)
{
	vector< pair<int,int> > v;
	generatepoint(v);
	int best=INT_MIN;
	int len=v.size();
	vector< pair<int,int> > v2; 
	for(int i=0;i<len;++i)
	{
		pos[v[i].first][v[i].second]=2;
		int tmp=min_noalphabeta(depth-1,v[i].first,v[i].second);
		if(tmp==best)
			v2.push_back(v[i]);
		if(tmp>best)
		{
			best=tmp;
			v2.clear();
			v2.push_back(v[i]);
		}
		pos[v[i].first][v[i].second]=0;
	}
	len=v2.size();
	int i=(int)(rand()%len);
	x=v2[i].first;
	y=v2[i].second; 
}

int min_alphabeta(int depth,int i1,int i2,int alpha,int beta);
int max_alphabeta(int depth,int i1,int i2,int alpha,int beta); 
int min_alphabeta(int depth,int i1,int i2,int alpha,int beta)
{
	int res=evaluate_minmax_noalphabeta();
	Chess cc;
	cc.chess_isover(i1,i2,2);
	if(isover!=0||depth<=0)
	{
		isover=0;
		return res;
	}
	vector< pair<int,int> > v;
	generatepoint(v);
	int len=v.size();
	int best=INT_MAX;
	for(int i=0;i<len;++i)
	{
		pos[v[i].first][v[i].second]=1;
		int tmp=max_alphabeta(depth-1,v[i].first,v[i].second,best<alpha?best:alpha,beta);
		pos[v[i].first][v[i].second]=0;
		if(tmp<best)	best=tmp;
		if(tmp<beta)	break;
		
	} 
	return best;
}
int max_alphabeta(int depth,int i1,int i2,int alpha,int beta)
{
	int res=evaluate_minmax_noalphabeta();
	Chess cc;
	cc.chess_isover(i1,i2,1);
	if(isover!=0||depth<=0)
	{
		isover=0;
		return res;
	}
	vector< pair<int,int> > v;
	generatepoint(v);
	int len=v.size();
	int best=INT_MIN;
	for(int i=0;i<len;++i)
	{
		pos[v[i].first][v[i].second]=2;
		int tmp=min_alphabeta(depth-1,v[i].first,v[i].second,alpha,best>beta?best:beta);
		pos[v[i].first][v[i].second]=0; 
		if(tmp>best)	best=tmp;
		if(tmp>alpha)	break;	
	} 
	return best;
}
void Chess::chess_ai_minmax_alphabeta(int &x,int &y,int depth)
{
	vector< pair<int,int> > v;
	generatepoint(v);
	int best=INT_MIN;
	int len=v.size();
	vector< pair<int,int> > v2; 
	for(int i=0;i<len;++i)
	{
		pos[v[i].first][v[i].second]=2;	
		int tmp=min_alphabeta(depth-1,v[i].first,v[i].second,INT_MAX,INT_MIN);
		if(tmp==best)
			v2.push_back(v[i]);
		if(tmp>best)
		{
			best=tmp;
			v2.clear();
			v2.push_back(v[i]);
		}
		pos[v[i].first][v[i].second]=0;		
	}
	len=v2.size();
	int i=(int)(rand()%len);
	x=v2[i].first;
	y=v2[i].second; 
}

struct Node
{
	int x;
	int y;
	int s;
	Node(int i,int j,int k):x(i),y(j),s(k){}
};
vector<Node> min_kill(int turn,int depth,int x,int y,bool &tmp);
vector<Node> max_kill(int turn,int depth,int x,int y,bool &tmp);
void generatepoint_2(int turn,int scoree,vector<Node> &v);
bool cmp(Node a,Node b)
{
	return a.s>b.s;
}
void generatepoint_2(int turn,int scoree,vector<Node> &v)
{
	for(int i=0;i<16;++i)
		for(int j=0;j<16;++j)
			if(pos[i][j]==0&&hasne(i,j))
				if(turn==0)
				{
					int comscore=evaluate_point(i,j,2);
					int humscore=evaluate_point(i,j,1);
					if(comscore+humscore>scoree)
					{
						Node p(i,j,comscore+humscore);
						v.push_back(p);
					}
				}
				else
				{
					int s=evaluate_point(i,j,turn);
					if(s>scoree)
					{
						Node p(i,j,s);
						v.push_back(p);
					}
				}
	sort(v.begin(),v.end(),cmp);
}
vector<Node> min_kill(int turn,int depth,int x,int y,bool &tmp)
{
	vector<Node> v;
	Chess cc;
	cc.chess_isover(x,y,2);
	if(isover==2)
	{
		isover=0;
		tmp=true;
//---------------------------------------------------------------»úÆ÷¡Ÿ4¡¿-----------------------------------------------------------
		return v; 
	}
	if(depth<0)
	{
		tmp=false;
		return v;
	}
	vector<Node> p;
	generatepoint_2(0,1000,p);
	int len=p.size();
	if(len==0)
	{
		tmp=false;
		return v;
	}
	vector< vector<Node> > cands;
	for(int i=0;i<len;++i)
	{
		bool tmp=false;
		pos[p[i].x][p[i].y]=(turn==1)?2:1;
		v.clear();
		v=max_kill(turn,depth-1,p[i].x,p[i].y,tmp);
		pos[p[i].x][p[i].y]=0;
		if(tmp)
		{
			vector<Node> kk;
			kk.push_back(p[i]);
			v.insert(v.begin(),kk.begin(),kk.end());
			cands.push_back(v); 
			continue;
		}
		else
		{
			tmp=false;
			return v;
		} 
	}
	int i=rand()%cands.size();
	return cands[i];
}
vector<Node> max_kill(int turn,int depth,int x,int y,bool &tmp)
{
	vector<Node> v;
	Chess cc;
	cc.chess_isover(x,y,1);
	if(isover==1)
	{
		isover=0;
		tmp=false;
		return v; 
	} 
	if(depth<0)
	{
		tmp=false;
		return v;
	} 
	vector<Node> p;
	generatepoint_2(turn,2000,p);
	if(p.size()==0)
	{
		tmp=false;
		return v;
	}
	int len=p.size();
	for(int i=0;i<len;++i)
	{
		bool tmp=false;
		pos[p[i].x][p[i].y]=turn; 
		v.clear();
		v=min_kill(turn,depth-1,p[i].x,p[i].y,tmp);
		pos[p[i].x][p[i].y]=0;
		if(tmp) 
		{
			vector<Node> kk;
			kk.push_back(p[i]);
			v.insert(v.begin(),kk.begin(),kk.end());
			return v;
		}
	}
	tmp=false;
	return v;	
}
void Chess::chess_ai_killcount(int &x,int &y,int depth)
{
	vector< pair<int,int> > v;
	generatepoint(v); 
	int len=v.size();
	vector< pair<int,int> > v2; 
	for(int i=0;i<len;++i)
	{
		pos[v[i].first][v[i].second]=2;	
		bool tmp=false;
		min_kill(2,depth,v[i].first,v[i].second,tmp);
		if(tmp)
			v2.push_back(v[i]);
		pos[v[i].first][v[i].second]=0;		
	}
	len=v2.size();
	if(len==0)
	{
		x=v[0].first;
		y=v[0].second;
		return;
	}
	int i=(int)(rand()%len);
	x=v2[i].first;
	y=v2[i].second; 
}
