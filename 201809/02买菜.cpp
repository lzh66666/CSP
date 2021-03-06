#include <iostream>

using namespace std;

int n;
int coun = 0;
int a[2005];
int b[2005];
int c[2005];
int d[2005];

int main(){
	cin >> n;
	for(int i = 0; i < n; i++){
		cin >> a[i] >> b[i];
	}
	
	for(int i = 0; i < n; i++){
		cin >> c[i] >> d[i];
	}
	
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			int min = b[i] < d[j] ? b[i] : d[j];
			if( (c[j] >= a[i]) && (c[j] <= b[i]) ){
				coun += (min - c[j]);
			}else if( (a[i] >= c[j]) && (a[i] <= d[j]) ){
				coun += (min - a[i]);
			}
		}
	}
	
	cout << coun;
}

/*=================================================================
输入
4
1  3
5  6
9  13
14 15
2  4
5  7
10 11
13 14
输出
3
=================================================================*/
/*
问题描述
小啾小来到了一条街上，两人分开买菜，他们买菜的过程可以描述为，去店里买一些菜然后去旁边的一个广场把菜
装上车，两人都要买n种菜，所以也都要装n次车。具体的，对于小来说有n个不相交的时间段[a1, b1], [a2, b2]...
[an, bn]在装车，对于小来说有n个不相交的时间段[c1, d1], [c2, d2]..[cn dn]在装车。其中，一个时间段[s，t]表示的
是从时刻s到时刻t这段时间，时长为ts。
由于他们是好朋友，他们都在广场上装车的时候会聊天,他们]想知道他们可以聊多长时间。

输入格式.
输入的第- -行包含一个正整数n，表示时间段的数量。
接下来n行每行两个数a;, bi,描述小H的各个装车的时间段。
接下来n行每行两个数ci，di， 描述小的各个装车的时间段。

输出格式
输出一行，一个正整数，表示两人可以聊多长时间。

样例输入
4
1  3
5  6
9  13
14 15
2  4
5  7
10 11
13 14
样例输出
3
数据规模和约定

*/
