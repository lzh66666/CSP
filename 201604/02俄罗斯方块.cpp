#include <bits/stdc++.h>

using namespace std;

int a[20][10];      //专门多加了五行，防止掉调到最后一行无法判断，刚开始没有意识到，啊啊啊啊啊啊啊啊！！！！！！！！！！！
int b[4][4];

int main(){
	for(int i = 0; i < 15; i++){
		for(int j = 0; j < 10; j++){
			cin >> a[i][j];
		}
	}
	
	//多加一行，15行的下一行为墙壁，都设置为1，刚开始忘了加了，啊啊啊啊啊啊啊啊啊啊啊！！！！！！！！！！
	for(int j = 0; j < 10; j++){
		a[15][j] = 1;
	}
	/*
		b[i]为要加入的方块
	*/
	for(int i = 0; i < 4; i++){
		for(int j = 0; j < 4; j++){
			cin >> b[i][j];
		}
	}
	int s;
	cin >> s;
	
	/*
        以下查找第一个可能出现问题的行数，记录存储4*4方块的第一行
	*/
	int k = 0;
	for(int i = 4; i < 15; i++){
		for(int j = s-1; j < s+3; j++){
			if(a[i][j] == 1){
				k = i-3;    //出现问题的第一行
				break;
			}
		}
		if(k){          //防止再次判断，直接退出
			break;
		}
	}
	
	/*
        找到目标4*4的方块在整体范围内，并记录第一行
	*/
	int ju = 0;
	for(int i = k; i < 20; i++){
		for(int j = s-1; j < s+3; j++){     //目标的列数
			if(a[i][j] == 1 && b[i-k][j-s+1] == 1){
				ju = k-1;	//i-(i-k+1)===========i为当前行，i-k为b[4][4]数组中的行数，因为下标从0开始，i-k+1为i当前要回退的行数
			}
		}
		/*
            当ju≠0时说明已经记录，直接退出
		*/
		if(ju){
			break;
		}
		/*
			说明一个4*4方块检查完毕，没有问题，从k+1行重新开始遍历,i-3回退到k+1行，k++到达k+1行
		*/
		if(i-k == 3){       
			k++;
			i -= 3;
		}
	}
	
	/*
        将要改变的行用b[4][4]改变
	*/
	for(int i = ju; i < ju+4; i++){
		for(int j = s-1; j < s+3; j++){
			if(a[i][j] == 0){
				a[i][j] = b[i-ju][j-s+1];
			}
		}
	}
	/*
        输出最后的结果，大功告成
	*/
	for(int i = 0; i < 15; i++){
		for(int j = 0; j < 10; j++){
			cout << a[i][j] << " ";
		}
		cout << "\n";
	}
	return 0;
}
/*

0 0 0 0
0 0 0 0
0 0 0 0
0 0 0 0
0 0 0 0
0 0 0 0
0 0 0 0
0 0 0 0
0 0 0 0
0 0 0 0

0 0 0 0
0 0 0 0
0 0 0 0
1 0 0 0

0 0 1 0
*/
/*=================================================================
输入
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 1 0 0
0 0 0 0 0 0 1 0 0 0
0 0 0 0 0 0 1 0 0 0
1 1 1 0 0 0 1 1 1 1
0 0 0 0 1 0 0 0 0 0
0 0 0 0
0 1 1 1
0 0 0 1
0 0 0 0
3
输出
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 1 0 0
0 0 0 0 0 0 1 0 0 0
0 0 0 0 0 0 1 0 0 0
1 1 1 1 1 1 1 1 1 1
0 0 0 0 1 1 0 0 0 0
=================================================================*/
/*
问题描述
俄罗斯方块是俄罗斯人阿列克谢.帕基特诺夫发明的一款休闲游戏。
游戏在一个15行10列的方格图上进行，方格图上的每一个格子可能已经放置了方块，或者没有放置方块。每一轮，都
会有一个新的由4个小方块组成的板块从方格图的上方落下，玩家可以操作板块左右移动放到合适的位置，当板块中某一
个万块的下边缘与方格图上的万块上边缘重合或者达到下边界时，板块不再移动，如果此时方格图的某-行全放满了方
块，则该行被消除并得分。
在这个问题中，你需要写- -个程序来模拟板块下落,你不需要处理玩家的操作，也不需要处理消行和得分。
具体的，给定一个初始的方格图，以及一个板块的形状和它下落的初始位置，你要给出最终的方格图。

输入格式
输入的前15行包含初始的方格图，每行包含10个数字，相邻的数字用空格分隔。如果一个数字是0, 表示对应的方格
中没有方块，如果数字是1,则表示初始的时候有方块。输入保证前4行中的数字都是0。
输入的第16至第19行包含新加入的板块的形状，每行包含4个数字，组成了板块图案，同样0表示没方块，1表示有方
块。输入保证板块的图案中正好包含4个方块，且4个方块是连在一起的(准确的说，4个方块是四连通的，即给定的板块
是俄罗斯方块的标准板块)。
第20行包含一 个1到7之间的整数，表示板块图案最左边开始的时候是在方格图的哪一-列中。注意,这里的板块图案指
的是16至19行所输入的板块图案,如果板块图案的最左边一-列全是0,则它的左边和实际所表示的板块的左边是不一致的(见样例)

输出格式
输出15行，每行10个数字,相邻的数字之间用-一个空格分隔，表示板块下落后的方格图。注意，你不需要处理最终的
消行。

样例输入
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 1 0 0
0 0 0 0 0 0 1 0 0 0
0 0 0 0 0 0 1 0 0 0
1 1 1 0 0 0 1 1 1 1
0 0 0 0 1 0 0 0 0 0
0 0 0 0
0 1 1 1
0 0 0 1
0 0 0 0
3

样例输出
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 1 0 0
0 0 0 0 0 0 1 0 0 0
0 0 0 0 0 0 1 0 0 0
1 1 1 1 1 1 1 1 1 1
0 0 0 0 1 1 0 0 0 0

*/
