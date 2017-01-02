#ifndef CHESS_H
#define CHESS_H

extern int pos[17][17];
extern int isover;
extern int myturn; 
extern int prex,prey;
extern int backnum,whitenum; 

class Draw
{
public:
	void draw_chesspoint();
	void draw_initpic();
	void draw_whowin();
	void draw_author();
	void draw_info();
	void draw_initpic2(); 
	void draw_backagain();
};

class Chess
{
public:
	void chess_isover(int x,int y,int turn);
	void chess_ai_naive(int &x,int &y); 
	void chess_ai_minmax_noalphabeta(int &x,int &y,int depth);
	void chess_ai_minmax_alphabeta(int &x,int &y,int depth); 
	void chess_ai_killcount(int &x,int &y,int depth);
};

#endif
