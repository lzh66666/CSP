#include <iostream>

using namespace std;

int a[1005];    //a[i]=-1表示被淘汰，a[i]=0表示未报数，a[i]>0表示还在继续游戏的人
int n;
int k;
int i = 1;      //每个人的报数
int j = 1;      //每个人的编号

int main(){
	cin >> n >> k;
	int m = n;
	
	while(true){
		if(m == 1){     //剩下一个人，胜利，退出
			break;
		}
		if(i%k == 0 || i%10 == k){
			m--;            //不符合的人数,减一
			a[j] = -1;       //淘汰
		}else{
			a[j]++;
		}
	
		j = j==n ? 1 : j+1;
		
		while(a[j] == -1){			//淘汰的直接过滤
			j = j==n ? 1 : j+1;     //此处忘记判断，一直得0分，啊啊啊啊啊啊啊！！！！！！！！！
		}
		i++;
	}
	if(n == 1){
		cout << j;
	}else if(k == 1){
		cout << n;      //一定不能忘，否则会扣10分，啊啊啊啊啊啊啊啊！！！！！！！！！！
	}else{
	 	for(j = 1; j <= n; j++){
	 		if(a[j] > 0){
	 			cout << j;
			}
		}
	}
 	
	return 0;
}


/*别人的代码，用到队列，又学到了新知识

#include<bits/stdc++.h>

using namespace std;

int n,k;

int main(){
	cin >> n >> k;
	queue<int>q;
	
	for(int i=1;i<=n;++i){		//将所有人编号压入队列
		q.push(i);
	}
	int num=1;					//当前的报数
	while(q.size()>1){
		int t=q.front();		//获取当前报数的人的编号
		q.pop();
		if(!(num%k==0||num%10==k))	//如果既不是K的倍数，末位也不为K
			q.push(t);			//将这个人编号加入队列中 ，表示没有被淘汰
		++num;					//递增当前报数
	}
	cout << q.front();
}

*/

/*=================================================================
输入
5 2
输出
3
输入
7 3
输出
4
=================================================================*/
/*

问题描述
有个小朋友围成一圈玩游戏， 小朋友从1至偏号，2号小朋友坐在1号小朋友的顺时针方向, 3号小朋友坐在2号小朋
友的顺时针方向，....， 1号小朋友坐在号小朋友的顺时针方向。
游戏开始，从1号小朋友开始顺时针报数，接下来每个小朋友的报数是_上一个小朋友报的数加1。若一个小朋友报的数
为的倍数或其末位数(即数的个位)为k,则该小朋友被淘汰出局，不再参加以后的报数。当游戏中只剩下一个小朋友
时，该小朋友获胜。
例如，当n=5，k=2时 :
1号小朋友报数1;
2号小朋友报数2淘汰;
3号小朋友报数3;
4号小朋友报数4淘汰;
5号小朋友报数5 ;
1号小朋友报数6淘汰;
3号小朋友报数7;
5号小朋友报数8淘汰;
3号小朋友获胜。
给定n和k,请问最后获胜的小朋友编号为多少?

输入格式
输入一行，包括两个整数x和k,意义如题目所述。

输出格式
输出- -行，包含- -个整数，表示获胜的小朋友编号。

样例输入
5 2

样例输出
3

样例输入
7 3

样例输出
4

数据规模和约定
对于所有评测用例，1≤n≤1000,1≤k≤9。

*/
