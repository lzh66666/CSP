//�Ż�����=======ʹ��ջʵ��======�ο�����
#include <iostream>
using namespace std;

int main(){
	int n, num[5], temp;//���� - num[ջ����--]
	char op[5]; 	//�����
	num[0] = 0;		//��ʼ��������ջ
	op[0] = 0;		//��ʼ�������ջ
	cin>>n;
	int result[n];
	for(int i=0; i<n; ++i){
		for(int j=0; j<7; ++j){
			if(j%2 == 0){	//��������ջ
				cin>>num[++num[0]];
				if (op[op[0]] == '-')	//��������ջ��Ϊ - �򽫲�����ת�� +��-x��
					num[num[0]] *= -1;
				else if (op[op[0]] == 'x'){	//��Ҫx����
					temp = num[num[0]] * num[num[0]-1];
					num[--num[0]] = temp;
					--op[0];
				}
				else if(op[op[0]] == '/'){	//��Ҫ/����
					temp = num[num[0]-1] / num[num[0]];
					num[--num[0]] = temp;
					--op[0];
				}
			}
			else{			//�������ջ
				cin>>op[++op[0]];
			}
		}
		while(op[0] > 0){	//��ʣ��+��������
				temp = num[num[0]] + num[num[0]-1];
				num[--num[0]] = temp;
				--op[0];
		}
		if(num[1] == 24)	//�ж����
			result[i] = 1;
		else
			result[i] = 0;
		num[0] = 0;			//��ʼ��������ջ
	}
	
	for(int i=0; i<n; ++i){	//��ӡ���
		if(result[i] == 1)
			cout<<"Yes\n";
		else
			cout<<"No\n";
	}
	return 0;
}


/*�����ƽ�============�Լ�����


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
	if(coun == 3 || coun == 0){ //��1+2+3+4  1*2*3*4  1/2/3/4
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
			if(j == 1){			//��1*2+3-4
				result = call(result,str[4]-'0',str[3]);
				result = call(result,str[6]-'0',str[5]);
			}else if(j == 3){   //��1+2*3-4
				result = call(str[0]-'0',result,str[1]);
				result = call(result,str[6]-'0',str[5]);
			}else{              //��1+2+3*4
				int res = call(str[0]-'0',str[2]-'0',str[1]);
				result = call(res,result,str[3]);
			}
		}else{
			for(int i = 1; i < 6; i+=2){
				if(c[i-1] == '0'){
					j = i;
				}
			}
			if(j == 1){     //�� 1+2*3/4
				result = call(str[2]-'0',str[4]-'0',str[3]);
				result = call(result,str[6]-'0',str[5]);
				result = call(str[0]-'0',result,str[1]);
			}else if(j == 3){       //�� 1*2+3*4
				int res = call(str[0]-'0',str[2]-'0',str[1]);
				result = call(str[4]-'0',str[6]-'0',str[5]);
				result = call(res,result,str[3]);
			}else{              //�� 1*2*3-4
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
����
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
���
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
[��Ŀ����]
��ʮ�ĵ���һ��������ֽ����Ϸ������Ϸ��Ŀ����ʹ��3���Ӽ��˳�����ʹ��4.��ֽ��.�����ֵ�������Ϊ24��

[��Ŀ����]
����ÿһһ����Ϸ��4����1-9�����ֺ�3�������������ɣ���֤�����������
�����������������������ź������ַ�������˳������������˳����С����мӷ���
����+��ʾ�������÷��Ŷ���ʾ���˷���Сд��ĸx��ʾ�������÷���L��ʾ������
Ϸ�����Ϊ����������2 /3=0��3/2=1,4/2=2��
��ʦ������n����Ϸ�Ľ⣬�����д������֤ÿ����Ϸ�Ľ���Ƿ�Ϊ24��

[�����ʽ]
�ӱ�׼����������ݡ�
��һ������-һ������n���ӵ�2�п�ʼ����n+1���У�ÿһ-�а���-һ������Ϊ7���ַ�����Ϊ������24����Ϸ����֤���ݸ�ʽ�Ϸ���

[�����ʽ]
�������׼�����
����n�У�����ÿ-һ����Ϸ���������Ϊ24������ַ���Yes,��������ַ���No��

[����1����]
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
[����1���]
Yes
No
No
Yes
Yes
No
No
Yes
Yes

[����1����]
9+3+4x3= 24.
5+4x5x5= 105
7-9-9+8=-3
5x6/5x4= 24
3+5+7+9= 24
1X1ʮ9-9=1
1 x9-5/9= 9
8/5+ 6x9= 55
6x7 -3x6= 24
6x4 +4/5 = 24
[������]
��ͼ02.jpg
*/
