		目标：	五子棋人机版
		AI：
			【1】评价函数：一个空子评分考虑人和机器下的综合评分。空子选择方法：暴力搜索第一个评分最高的空子。
			【2】评价函数：棋盘上所有白子估分-棋盘上所有黑子估分。空子选择方法：极大极小搜索n步内最优解（即n步后，所选哪种走法后棋盘上评估函数值最高就选择哪种走法）（认为人和机器都会选择最好的步骤）
			【3】评价函数：棋盘上所有白子估分-棋盘上所有黑子估分。空子选择方法：极大极小alpha-beta剪枝
![image](https://github.com/tangsancai/chess/blob/master/2.png)
![image](https://github.com/tangsancai/chess/blob/master/3.png)
