#include<string.h>
#include<algorithm>
#include<iostream>
#include<vector>
#include "chess.h"
using namespace std;

int pos[17][17];		//¿¿¿¿¿¿¿¿
int isover;			//¿¿¿¿¿¿¿¿¿¿¿
int myturn;			//¿¿¿¿¿ 
int backnum,whitenum;		//¿¿¿¿¿¿¿¿¿¿ 
int preWx,preWy;		//¿¿¿¿¿¿¿¿
int preBx,preBy; 

int main(int argc, char *argv[])
{
	memset(pos,0,sizeof(pos));
	isover=0; 
	myturn=1; 
	preBy=-1,preBx=-1,preWy=-1,preWx=-1;
	backnum=0,whitenum=0; 
	Draw d;
	d.draw_initpic();
	Chess cc;
	int choice;
	cin>>choice;
	switch(choice)
	{
		case 1: 
			d.draw_initpic2();
			int choice2;
			std::cin>>choice2;
			d.draw_chesspoint();
			while(!isover)
			{
				int x,y;
				if(myturn==1)	 
				{ 
					std::cin>>x;
					if(x==20&&preWx!=-1&&preWy!=-1)
					{
						pos[preWx][preWy]=0;
						pos[preBx][preBy]=0;
						preBy=-1,preBx=-1,preWy=-1,preWx=-1;
						d.draw_chesspoint();
						continue;	
					}
					else if(x==20)
					{
						d.draw_chesspoint();
						d.draw_backagain();
						std::cin>>x;
					}
					std::cin>>y;
					pos[x][y]=1;
					++backnum;
					preBx=x;
					preBy=y;
				} 
				else
				{
					switch(choice2)
					{
						case 1:
							cc.chess_ai_naive(x,y);
							break;
						case 2:
							cc.chess_ai_minmax_noalphabeta(x,y,2);//µÚÈýÎ»±ØÐëÊÇÅŒÊý¡£ÆæÊýÊÇai×ß£¬ÅŒÊýÊÇÍæŒÒ×ß£¬Èç¹ûai²»¿ŒÂÇÍæŒÒ×ß£¬ÄÇÃŽ²»·ÀÊØÒ»ÏÂ¿Ï¶š»áÓÐÎÊÌâµÄ 
							break;
						case 3:
							cc.chess_ai_minmax_alphabeta(x,y,6);
							break;
						case 4:
							cc.chess_ai_killcount(x,y,16);
							break;
					}
					pos[x][y]=2;
					++whitenum;
					preWx=x;
					preWy=y;
				}
				d.draw_chesspoint();				//»æÖÆœá¹û 
				cc.chess_isover(x,y,myturn);				//ÅÐ¶ÏÊÇ·ñÒÑÓÐÊ€žº 
				switch(isover)
				{
					case 0:
						break;
					default:
						d.draw_whowin(); 
						break;
				}
				myturn=(myturn==1)?2:1;
			}
			break;
		case 2:
			cout<<"ÈËÈË¶ÔÕœ"<<endl; 
			break;
		case 3:
			d.draw_info();
			break;
		case 4:
			d.draw_author();
			break;
	}
	return 0;
}
