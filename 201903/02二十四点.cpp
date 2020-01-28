//优化代码=======使用栈实现======参考代码
#include <iostream>
using namespace std;

int main(){
	int n, num[5], temp;//行数 - num[栈顶，--]
	char op[5]; 	//运算符
	num[0] = 0;		//初始化操作数栈
	op[0] = 0;		//初始化运算符栈
	cin>>n;
	int result[n];
	for(int i=0; i<n; ++i){
		for(int j=0; j<7; ++j){
			if(j%2 == 0){	//操作数进栈
				cin>>num[++num[0]];
				if (op[op[0]] == '-')	//如果运算符栈顶为 - 则将操作数转换 +（-x）
					num[num[0]] *= -1;
				else if (op[op[0]] == 'x'){	//需要x运算
					temp = num[num[0]] * num[num[0]-1];
					num[--num[0]] = temp;
					--op[0];
				}
				else if(op[op[0]] == '/'){	//需要/运算
					temp = num[num[0]-1] / num[num[0]];
					num[--num[0]] = temp;
					--op[0];
				}
			}
			else{			//运算符进栈
				cin>>op[++op[0]];
			}
		}
		while(op[0] > 0){	//将剩余+号运算完
				temp = num[num[0]] + num[num[0]-1];
				num[--num[0]] = temp;
				--op[0];
		}
		if(num[1] == 24)	//判定结果
			result[i] = 1;
		else
			result[i] = 0;
		num[0] = 0;			//初始化操作数栈
	}
	
	for(int i=0; i<n; ++i){	//打印结果
		if(result[i] == 1)
			cout<<"Yes\n";
		else
			cout<<"No\n";
	}
	return 0;
}


/*暴力破解============自己代码


#include <bits/stdc++.h>

using namespace std;

int n;
int result = 0;
bool judge[102];
string str;

int call(int a,int b,char c){
	int res;
	switch(c){
		case 'x':
			res=a*b;
			break;
		case '/':
			res=a/b;
			break;
		case '+':
			res=a+b;
			break;
		case '-':
			res=a-b;
			break;
	}
	return res;
}

bool cal(){
	char c[6];
	int coun = 0;
	int j = -1;
	c[1]=str[1];c[3]=str[3];c[5]=str[5];
	for(int i = 1; i < 6; i+=2){
		if(c[i]=='x' || c[i]=='/'){
			c[i-1] = '1';
			coun++;
		}else{
			c[i-1] = '0';
		}
	}
	if(coun == 3 || coun == 0){ //例1+2+3+4  1*2*3*4  1/2/3/4
		result = call(str[0]-'0',str[2]-'0',str[1]);
		result = call(result,str[4]-'0',str[3]);
		result = call(result,str[6]-'0',str[5]);
	}else{
		if(coun == 1){
			for(int i = 1; i < 6; i+=2){
				if(c[i-1] == '1'){
					result = call(str[i-1]-'0',str[i+1]-'0',str[i]);
					j = i;
				}
			}
			if(j == 1){			//例1*2+3-4
				result = call(result,str[4]-'0',str[3]);
				result = call(result,str[6]-'0',str[5]);
			}else if(j == 3){   //例1+2*3-4
				result = call(str[0]-'0',result,str[1]);
				result = call(result,str[6]-'0',str[5]);
			}else{              //例1+2+3*4
				int res = call(str[0]-'0',str[2]-'0',str[1]);
				result = call(res,result,str[3]);
			}
		}else{
			for(int i = 1; i < 6; i+=2){
				if(c[i-1] == '0'){
					j = i;
				}
			}
			if(j == 1){     //例 1+2*3/4
				result = call(str[2]-'0',str[4]-'0',str[3]);
				result = call(result,str[6]-'0',str[5]);
				result = call(str[0]-'0',result,str[1]);
			}else if(j == 3){       //例 1*2+3*4
				int res = call(str[0]-'0',str[2]-'0',str[1]);
				result = call(str[4]-'0',str[6]-'0',str[5]);
				result = call(res,result,str[3]);
			}else{              //例 1*2*3-4
				result = call(str[0]-'0',str[2]-'0',str[1]);
				result = call(result,str[4]-'0',str[3]);
				result = call(result,str[6]-'0',str[5]);
			}
		}
	}
	if(result == 24){
		return true;
	}
	return false;
}

int main(){
    cin >> n;
    for(int i = 0 ; i < n; i++){
		cin >> str;
		if(cal()){
			judge[i] = true;
		}
	}
	
	for(int i = 0; i < n; i++){
		if(judge[i]){
			cout << "Yes\n";
		}else{
			cout << "No\n";
		}
	}
	
    return 0;
}
*/
/*=================================================================
输入
10
9+3+4x3
5+4x5x5
7-9-9+8
5x6/5x4
3+5+7+9
1x1+9-9
1x9-5/9
8/5+6x9
6x7-3x6
6x4+4/5
输出
Yes
No
No
Yes
Yes
No
No
No
Yes
Yes
=================================================================*/
/*
[题目背景]
二十四点是一款著名的纸牌游戏，其游戏的目标是使用3个加减乘除运算使得4.张纸牌.上数字的运算结果为24。

[题目描述]
定义每一一个游戏由4个从1-9的数字和3个四则运算符组成，保证四则运算符将
数字两两隔开，不存在括号和其他字符，运算顺序按照四则运算顺序进行。其中加法用
符号+表示，减法用符号二表示，乘法用小写字母x表示，除法用符号L表示。在游
戏里除法为整除，例如2 /3=0，3/2=1,4/2=2。
老师给了你n个游戏的解，请你编写程序验证每个游戏的结果是否为24。

[输入格式]
从标准输入读入数据。
第一行输入-一个整数n，从第2行开始到第n+1行中，每一-行包含-一个长度为7的字符串，为上述的24点游戏，保证数据格式合法。

[输出格式]
输出到标准输出。
包含n行，对于每-一个游戏，如果其结果为24则输出字符串Yes,否则输出字符串No。

[样例1输入]
10
9+3+4x3
5+4x5x5
7-9-9+8
5x6/5x4
3+5+7+9
1x1+9-9
1x9-5/9
8/5+6x9
6x7-3x6
6x4+4/5
[样例1输出]
Yes
No
No
Yes
Yes
No
No
Yes
Yes

[样例1解释]
9+3+4x3= 24.
5+4x5x5= 105
7-9-9+8=-3
5x6/5x4= 24
3+5+7+9= 24
1X1十9-9=1
1 x9-5/9= 9
8/5+ 6x9= 55
6x7 -3x6= 24
6x4 +4/5 = 24
[子任务]
见图02.jpg
*/
