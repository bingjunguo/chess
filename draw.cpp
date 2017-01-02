#include "chess.h"
#include<stdlib.h>
#include<iostream>
#include<string>
#include<string.h>
using namespace std;

static const char  ch[11][8]={"┌─","┬─","┐","├─","┼─","┤","└─","┴─","┘","○─","●─"};
const int chessshift=20;

void whichpic(char drawch[11],int i,int x,int y) 
{
	switch(pos[x][y])
	{
		case 0://0是空子 
			memcpy(drawch,ch[i],sizeof(ch[i]));
			return;
		case 1://1是黑子 
			memcpy(drawch,ch[9],sizeof(ch[9]));
			return;
		case 2://2是白子
			memcpy(drawch,ch[10],sizeof(ch[10]));
			return; 
	}	
}
void Draw::draw_chesspoint()
{
	char drawch[11];
	system("clear");
	for(int i=0;i<chessshift;++i)
		cout<<" ";
	for(int i=0;i<16;++i)
		cout<<i%10<<" ";
	cout<<endl;
	//行1
	for(int i=0;i<chessshift-2;++i)
		cout<<" ";
	whichpic(drawch,0,0,0);
	cout<<"0 "<<drawch;
	for(int i=1;i<15;++i)
	{
		whichpic(drawch,1,0,i);
		cout<<drawch;
	}
	whichpic(drawch,2,0,15);
	cout<<drawch<<endl;
	//行2~行15 
	for(int i=1;i<15;++i)
	{
		for(int j=0;j<chessshift-2;++j)
			cout<<" ";
		whichpic(drawch,3,i,0); 
		cout<<i%10<<" "<<drawch; 
		for(int j=1;j<15;++j)
		{
			whichpic(drawch,4,i,j);
			cout<<drawch;
		}
		whichpic(drawch,5,i,15);
		cout<<drawch<<endl; 
	}
	//行16
	for(int i=0;i<chessshift-2;++i)
		cout<<" ";
	whichpic(drawch,6,15,0);
	cout<<"5 "<<drawch;
	for(int i=1;i<15;++i)
	{
		whichpic(drawch,7,15,i);
		cout<<drawch;
	}
	whichpic(drawch,8,15,15);
	cout<<drawch<<endl; 
	cout<<"请落子，请输入x y【以空格分隔】或者输入[20]悔棋···"<<endl;
}

void Draw::draw_whowin()
{
	string c;
	switch(isover)
	{
		case 1:
			c="【黑子胜】";
			break;
		case 2:
			c="【白子胜】";
			break;
		case 3:
			c="【和棋】";
			break; 
	}
	cout<<c<<endl;
}


void Draw::draw_initpic()
{
	system("clear");
	cout<<"+ + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + +"<<endl; 
	cout<<"+			【名称】	五子棋					+"<<endl;
	cout<<"+			【选项】	人机对战【1】				+"<<endl;
	cout<<"+			【选项】	人人对战【2】				+"<<endl;
	cout<<"+			【选项】	各项说明【3】				+"<<endl;
	cout<<"+			【选项】	关于写手【4】				+"<<endl;
	cout<<"+ + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + +"<<endl; 
 	cout<<"请输入选项："; 
}

void Draw::draw_initpic2()
{
	system("clear");
	cout<<"+ + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + +"<<endl;
	cout<<"+【名称】【选机号】									    		      	    +"<<endl;
	cout<<"+【选项】【1】【评估函数：一个空子考虑人和机器下的综合评分；暴力搜索取第一个max】			   	    +"<<endl;
	cout<<"+【选项】【2】【评估函数：棋盘上所有白子估分-棋盘上所有黑子估分；max-min搜索n步内的最优解】			    +"<<endl;
	cout<<"+【选项】【3】【评估函数：棋盘上所有白子估分-棋盘上所有黑子估分：max-min-alpha-beta搜索最优解，剪枝后搜索能力更强】 +"<<endl; 
	cout<<"+【选项】【4】【只搜索杀棋，所以搜索的少，搜索深度更大，但这也放弃了一些有益分支】 				    +"<<endl; 
	cout<<"+ + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + +"<<endl;
	cout<<"请输入选项："; 
} 

void Draw::draw_author()
{
	system("clear");
	cout<<"+ + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + +"<<endl; 
	cout<<"+			【姓名】	罗磐					+"<<endl;
	cout<<"+		    【联系方式】	1535976313@qq.com			+"<<endl;
	cout<<"+		【新学期新愿望】	我想做游戏，求领路人带带我		+"<<endl;
	cout<<"+ + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + +"<<endl;
	cout<<"那个···这就是你的界面？？？？"<<endl; 
} 

void Draw::draw_info()
{
	system("clear");
	cout<<"+ + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + +"<<endl; 
	cout<<"+			【规则】	轮流下在空子处，先连成五子者胜		+"<<endl;
	cout<<"+ + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + +"<<endl; 
} 

void Draw::draw_backagain()
{
	cout<<"【已悔过棋】"; 
}
