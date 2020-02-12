#include <bits/stdc++.h>

using namespace std;

#define MAX 5005

struct node{
    double price;
    long long num;
    int type;		//1��ʾbuy,0��ʾsell
    int cancel;
}buy[MAX],sell[MAX],record[MAX];

bool cmp1(node a,node b){
    return a.price > b.price;
}

bool cmp2(node a,node b){
    return a.price < b.price;
}

long long pbuy[MAX];
long long psell[MAX];

int main(){
    int c = 0;
    string str;
    
    while(cin >> str){
        if(str ==  "buy"){
            cin >> record[c].price >> record[c].num;
            record[c].type = 1;
            record[c].cancel = 0;
            c++;
        }else if(str == "sell"){
            cin >> record[c].price >> record[c].num;
            record[c].type = 0;
            record[c].cancel = 0;
            c++;
        }else if(str == "cancel"){
            int id;
            cin >> id;
            record[id-1].cancel = 1;
            record[c].cancel = 1;
            c++;
        }else{
        	break;
		}
    }
    
    /*
        Ϊ���������pbuy����ɫ����Ӧ��buy��sell�������1��ʼ
	*/
	
    int a = 1;      //buy������
    int b = 1;      //sell������

    for(int i = 0;i < c; i++){
	 if(record[i].cancel == 0){
	    	if(record[i].type == 1){
	            buy[a++] = record[i];
	        }else{
	        	sell[b++] = record[i];
			}
		}
    }

	/*
		��������,sell��С����buy�Ӵ�С����,record�Ӵ�С��Ȼ��ó����۽�С�����Ͷ�Ӧ�ļ۸�
	*/
    sort(buy+1,buy+a,cmp1);
    sort(sell+1,sell+b,cmp2);
    sort(record,record+c,cmp1);

	/*
        Ϊ���������ֱ�ӵ���max��min�������±��1��ʼ���±�0�洢����0����ʱ��ʾ��Сֵ
	*/
	
    pbuy[0] = 0;
    psell[0] = 0;
    
    pbuy[1] = buy[1].num;
    psell[1] = sell[1].num;

    for(int i = 2;i < a || i < b; i++){
        if(i < a){
        	pbuy[i] = pbuy[i-1]+buy[i].num;
		}
        if(i < b){
        	psell[i] = psell[i-1]+sell[i].num;
		}
    }
    
    double ansp = 0;
    long long ansn = 0;
    
    int j;
	int k = 1;//k���������ʼ����ֻ��һ�Σ���������������������������������������������
	
    for(int i = 0;i < c;i++){
        if(record[i].cancel == 0){
	        for(; k < a; k++){
	        	//�ҵ����������߼۸�Ҳ���ǵ�һ��buy<record����һ��
	            if(buy[k].price < record[i].price){
	            	break;
				}
	        }
	        for(j = 1; j < b; j++){
	        	//�ҵ�����������ͼ۸�Ҳ���ǵ�һ��sell<record����һ��
	            if(sell[j].price > record[i].price){
	            	break;
				}
	        }
	        long long res = min(psell[j-1],pbuy[k-1]);
	        if(res > ansn){
	            ansn = res;
	            ansp = record[i].price;
	        }else if(res == ansn){
	            ansp = max(record[i].price,ansp);
	        }
		}
    }
    
    printf("%.2f %lld\n",ansp,ansn);

	return 0;
}

/*=================================================================
����
buy 9.25 100
buy 8.88 175
sell 9.00 1000
buy 9.00 400
sell 8.92 400
cancel 1
buy 100.00 50
���
9.00 450
=================================================================*/
/*
��������
����ĳ��Ʊ�����������дһ�����򣬸��ݿ���ǰ�ͻ��ύ�Ķ�����ȷ��ĳ�ض���Ʊ�Ŀ��̼ۺͿ��̳ɽ�����
�����ó���������ɺܶ��й��ɣ�ÿһ��Ϊһ����¼����¼���������¼��֣�
����1. buy p s ��ʾһ�������Ʊ���򵥣�ÿ�ֳ���Ϊp���������Ϊs��
����2. sell p s ��ʾһ�����۹�Ʊ��������ÿ�ֳ���Ϊp�����۹���Ϊs��
����3. cancel i��ʾ������i�еļ�¼��
����������̼�Ϊp0����ϵͳ���Խ����г�������Ϊp0���򵥺����г�������Ϊp0����������ƥ�䡣��ˣ���
ʱ�Ŀ��̳ɽ���Ϊ��������Ϊp0���򵥵��ܹ��������г�������Ϊp0���������ܹ���֮��Ľ�Сֵ��
������ĳ�����Ҫȷ��һ�����̼ۣ�ʹ�ÿ��̳ɽ��������ܵش�����ж�����������Ŀ��̼ۣ���ĳ���Ӧ
�������ߵ���һ����
�����ʽ
��������������������У�ÿһ����һ����¼����֤����Ϸ�������Ϊ������108��������������Ϊ��ȷ��ǡ��
С�������λ����ʵ�����Ҳ�����10000.00��
�����ʽ
��������Ҫ���һ�У���������������һ���ո�ָ�����һ�����ǿ��̼ۣ��ڶ����Ǵ˿��̼��µĳɽ�������
�̼���Ҫ��ȷ��С�����ǡ����λ��
��������
buy 9.25 100
buy 8.88 175
sell 9.00 1000
buy 9.00 400
sell 8.92 400
cancel 1
buy 100.00 50
�������
9.00 450
����������ģ��Լ��
��������100%�����ݣ����������������5000��
*/
