#include <bits/stdc++.h>

using namespace std;

int n,a,b;
long long sum;

vector<pair<int, int> > u, v;

int main(){
	
	cin >> n >> a >> b;
	
	for(int i = 0; i < a; i++) {
		int x,y;
		cin >> x >> y;
		u.push_back({x,y});
	}
	
	for(int i = 0; i < b; i++) {
		int x,y;
		cin >> x >> y;
		v.push_back({x,y});
	}
	
	int i = 0, j = 0;
	
	while(i < a && j < b) {
		if(u[i].first == v[j].first) {
			sum += u[i++].second*v[j++].second;
		}else if(u[i].first > v[j].first) {
			j++;
		}else {
			i++;
		}
	}
	
	cout << sum << endl;
	
	return 0;
}

/*=================================================================
 
 题目见图 
 
样例输入
10 3 4
4 5
7 -3
10 1
1 10
4 20
5 30
7 40


样例输出
-20 
=================================================================*/
