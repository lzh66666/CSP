#include <bits/stdc++.h>

using namespace std;

int n;
string str[101];

int main(){
	string s1;
	int z;
	cin >> s1 >> z >> n;
	if(z == 0){
		transform(s1.begin(),s1.end(),s1.begin(),::tolower);        //��ѧ�ķ�������ĸȫתΪСд
	}
	int j = 0;
	for(int i = 0; i < n; i++){
		string s2,s3;
		cin >> s2;
		s3 = s2;
		if(z == 0){
			transform(s3.begin(),s3.end(),s3.begin(),::tolower);
		}
		string::size_type idx;
		idx=s3.find(s1);                        //��ѧ�ķ�����string�ַ����������Ӵ�������������򷵻�string::npos����������򷵻�����λ��
		if(idx != string::npos ){
			str[j++] = s2;
		}
	}
	for(int i = 0; i < j; i++){
		cout << str[i] << "\n";
	}
	return 0;
}

/*=================================================================
����
Hello
0
5
HelloWorld
HiHiHelloHiHi
GrepIsAGreatTool
HELLO
HELLOisNOTHello
���
HelloWorld
HiHiHelloHiHi
HELLOisNOTHello
=================================================================*/
/*
��������
��������һ���ַ����Ͷ������֣�����Щ�������ҵ��ַ������ֵ���Щ�С���ĳ�����֧�ִ�Сд����ѡ���ѡ���ʱ��
��ʾͬһ����ĸ�Ĵ�д��Сд������ͬ���ַ�����ѡ��ر�ʱ����ʾͬһ����ĸ�Ĵ�д��Сд������ͬ���ַ���
�����ʽ
��������ĵ�һ�а���һ���ַ���S���ɴ�СдӢ����ĸ��ɡ�
�����ڶ��а���һ�����֣���ʾ��Сд���е�ѡ�������Ϊ0ʱ��ʾ��Сд�����У�������Ϊ1ʱ��ʾ��Сд���С�
���������а���һ������n����ʾ���������ֵ�������
����������n�У�ÿ�а���һ���ַ������ַ����ɴ�СдӢ����ĸ��ɣ������ո�������ַ���
�����ʽ
����������У�ÿ�а���һ���ַ����������ֵ�˳�����θ�����Щ�������ַ���S���С�
��������
Hello
1
5
HelloWorld
HiHiHelloHiHi
GrepIsAGreatTool
HELLO
HELLOisNOTHello
�������
HelloWorld
HiHiHelloHiHi
HELLOisNOTHello
����˵��
����������������У����ĸ��ַ�����ȻҲ��Hello�����Ǵ�Сд����ȷ�����������ĵڶ��и�Ϊ0������ĸ��ַ���Ӧ�������
����������ģ��Լ��
����1<=n<=100��ÿ���ַ����ĳ��Ȳ�����100��
*/
