#include <bits/stdc++.h>

using namespace std;

long n;
int m;

struct pos{
	int x;//横坐标 
	int y;//纵坐标 
	int v;//每个点所在每条直线的上下，1表示上，-1表示下 
	int type;//分类点，0表示A，1表示B 
}a[1001];


int main(){
	
	cin >> n >> m;
	int x,y;
	char c;
	
	for (int i = 0; i < n; i++) {
		cin >> x >> y >> c;
		a[i].x = x;
		a[i].y = y;
		if(c == 'A') {
			a[i].type = 0;
		}else if(c == 'B') {
			a[i].type = 1;
		}
	}
	
	int v1,v2,v3;//输入的直线的三个参数 
	vector<string> vec;//输出结果存储 
	
	for(int i = 0; i < m; i++){
		cin >> v1 >> v2 >> v3;
		for (int j = 0; j < n; j++) {
			int v = v1 + v2*a[j].x + v3*a[j].y;//计算结果 
			a[j].v = v/abs(v);	//将在直线上面还是下面填入 
		}
		
		// c,d表示A，B现有的总数
		// c1，d1表示在直线上或者下面的总和 
		//当A、B分类符合题目要求，则c与c1的绝对值相等，d与d1的绝对值相等 
		int c = 0,c1 = 0; 
		int d = 0,d1 = 0;
		
		for(int j = 0; j < n; j++) {
			if(a[j].type == 0) {
				c1++;
				c += a[j].v;
			} else if(a[j].type == 1) {
				d1++;
				d += a[j].v;
			}
		}
		
		//最后的判断条件 
		if(abs(c) == c1 && abs(d) == d1) {
			vec.push_back("Yes");
		} else {
			vec.push_back("No");
		}
	}
	
	// 输出结果 
	for(int i = 0; i < vec.size(); i++) {
		cout << vec[i] << endl;
	}
	
	return 0;
}

/*

题目信息见图1

样例1输入
9 3
1 1 A
1 0 A
1 -1 A
2 2 B
2 3 B
0 1 A
3 1 B
1 3 B
2 0 A
0 2 -3
-3 0 2
-3 1 1
 
样例1输出
No
No
Yes

*/
