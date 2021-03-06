#include <bits/stdc++.h>

using namespace std;

int n;

int main(){
	vector<int> a;
	
	cin >> n;
	for (int i=0;i < n; i++){
		int x;
		cin >> x;
		a.push_back(x);
	}
	
	int ans = 0;
	
	for (int i = 0; i < n; i++){
		int h = a[i];
		for (int j = i;j < n; j++){
			if(a[j] < h){
				h = a[j];
			}
			
			int s = (j - i + 1) * h;
			
			if(ans < s){
				ans = s;
			}
		}
	}
	
	cout << ans << endl;
	return 0;
}

/*=================================================================
输入
6
3 1 6 5 2 3
输出
10
=================================================================*/
/*
问题描述
　　在横轴上放了n个相邻的矩形，每个矩形的宽度是1，而第i（1 ≤ i ≤ n）个矩形的高度是hi。这n个矩形构成了一个直方图。
例如，03(1).jpg中六个矩形的高度就分别是3, 1, 6, 5, 2, 3。
	请找出能放在给定直方图里面积最大的矩形，它的边要与坐标轴平行。对于上面给出的例子，最大矩形如图03(2).jpg所示的阴影部分，面积是10。
	输入格式
　　第一行包含一个整数n，即矩形的数量(1 ≤ n ≤ 1000)。
　　第二行包含n 个整数h1, h2, … , hn，相邻的数之间由空格分隔。(1 ≤ hi ≤ 10000)。hi是第i个矩形的高度。
输出格式
　　输出一行，包含一个整数，即给定直方图内的最大矩形的面积。
样例输入
6
3 1 6 5 2 3
样例输出
10
*/
