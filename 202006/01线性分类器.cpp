#include <bits/stdc++.h>

using namespace std;

long n;
int m;

struct pos{
	int x;//������ 
	int y;//������ 
	int v;//ÿ��������ÿ��ֱ�ߵ����£�1��ʾ�ϣ�-1��ʾ�� 
	int type;//����㣬0��ʾA��1��ʾB 
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
	
	int v1,v2,v3;//�����ֱ�ߵ��������� 
	vector<string> vec;//�������洢 
	
	for(int i = 0; i < m; i++){
		cin >> v1 >> v2 >> v3;
		for (int j = 0; j < n; j++) {
			int v = v1 + v2*a[j].x + v3*a[j].y;//������ 
			a[j].v = v/abs(v);	//����ֱ�����滹���������� 
		}
		
		// c,d��ʾA��B���е�����
		// c1��d1��ʾ��ֱ���ϻ���������ܺ� 
		//��A��B���������ĿҪ����c��c1�ľ���ֵ��ȣ�d��d1�ľ���ֵ��� 
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
		
		//�����ж����� 
		if(abs(c) == c1 && abs(d) == d1) {
			vec.push_back("Yes");
		} else {
			vec.push_back("No");
		}
	}
	
	// ������ 
	for(int i = 0; i < vec.size(); i++) {
		cout << vec[i] << endl;
	}
	
	return 0;
}

/*

��Ŀ��Ϣ��ͼ1

����1����
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
 
����1���
No
No
Yes

*/
