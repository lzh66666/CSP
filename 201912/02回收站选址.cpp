#include <bits/stdc++.h>

using namespace std;

int n,coun=0;
int a[1001][2];
int c[6];

bool isExist(int ax,int ay){
	for(int i = 0; i < n; i++){
		if(a[i][0] == ax && a[i][1] == ay){
			return true;
		}
	}
	return false;
}

int main(){
    cin >> n;
    
    for(int i = 0; i < n; i++){
		cin >> a[i][0] >> a[i][1];
	}
	
	for(int i = 0; i < n; i++){
		if( isExist(a[i][0]+1,a[i][1]) && isExist(a[i][0]-1,a[i][1]) && isExist(a[i][0],a[i][1]+1) && isExist(a[i][0],a[i][1]-1) ){
			coun = 0;
			if(isExist(a[i][0]+1,a[i][1]+1)){
				coun++;
			}
			if(isExist(a[i][0]+1,a[i][1]-1)){
				coun++;
			}
			if(isExist(a[i][0]-1,a[i][1]+1)){
				coun++;
			}
			if(isExist(a[i][0]-1,a[i][1]-1)){
				coun++;
			}
			c[coun]++;
		}
	}
	
	for(int i = 0; i < 5; i++){
		cout << c[i] << endl;
	}
    return 0;
}

/*
[题目背景]
开学了，可是校园里堆积了不少垃圾杂物。
热心的同学们纷纷自发前来清理，为学校注入正能量

[题目描述]
通过无人机航拍我们已经知晓了n处尚待清理的垃圾位置，其中第i (1≤i≤n)处的坐标为(x,y)，保证所有的坐标均为整数。
我们希望在垃圾集中的地方建立些回收站。具体来说，对于一个位置(x,y) 是否适合建立回收站，我们主要考虑以下几点:
●(x,y) 必须是整数坐标，且该处存在垃圾;
●上下左右四个邻居位置，即(x,y+ 1)、 (x,y-1)、 (x+ 1,y)和(x- 1,y)处，必须全部存在垃圾;
●进一步地，我们会对满足上述两个条件的选址进行评分，分数为不大于4的自然数，表示在(x土1,y土1)四个对角位置中有几处存在垃圾。
现在，请你统计一- 下每种得分的选址个数。

[输入格式]
从标准输入读入数据。
输入总共有n+ 1行。
第1行包含-一个正整数n,表示已查明的垃圾点个数。
第1+i行(1≤i≤n)包含由一个空格分隔的两个整数x;和yi，表示第i处垃圾的坐标。
保证输入的n个坐标互不相同。

[输出格式]
输出到标准输出。
输出共五行，每行一个整数，依次表示得分为0、1、2、3和4的回收站选址个数。
[样例1输入]
7
1 2
2 1
0 0
1 1
1 0
2 0
0 1
[样例1输出]
0
0
1
0
0
[样例1解释]
如图02.jpg所示，仅有(1,1)可选为回收站地址，评分为2。

[样例2输入]
2
0 0
- 100000 10

[样例2输出]
0
0
0
0
0

[样例2解释]
不存在可选地址。

[样例3输入]
11
9 10
10 10
11 10
12 10
13 10
11 9
11 8
12 9
10 9
10 11
12 11

[样例3输出]
0
2
1
0
0
[样例3解释]
1分选址: (10, 10)和(12, 10);
2分选址: (11,9)。
[子任务]
●测试点1和2，保证对于任意的i皆满足0≤xiy;≤2;
●测试点3、4和5，保证对于任意的i皆满足0≤x,y;≤500;
●测试点6、7和8，保证对于任意的i皆满足0≤xiy;≤109;
●测试占9和10.保证对干任音的;皆满足IrLlv|<109.即坐标可以是负数。
所有的测试点保证1 ≤n≤103。

[提示]
本题中所涉及的坐标皆为整数，且保证输入的坐标两两不同。


*/
