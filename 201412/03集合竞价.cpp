#include <bits/stdc++.h>

using namespace std;

#define MAX 5005

struct node{
    double price;
    long long num;
    int type;		//1表示buy,0表示sell
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
        为了与下面的pbuy和配色来对应，buy和sell的坐标从1开始
	*/
	
    int a = 1;      //buy的坐标
    int b = 1;      //sell的坐标

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
		三个数组,sell从小到大，buy从大到小排序,record从大到小，然后得出竞价较小股数和对应的价格。
	*/
    sort(buy+1,buy+a,cmp1);
    sort(sell+1,sell+b,cmp2);
    sort(record,record+c,cmp1);

	/*
        为了下面可以直接调用max和min函数，下标从1开始，下标0存储数字0，暂时表示最小值
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
	int k = 1;//k必须在这初始化，只能一次，啊啊啊啊啊啊啊啊啊啊啊！！！！！！！！！！！
	
    for(int i = 0;i < c;i++){
        if(record[i].cancel == 0){
	        for(; k < a; k++){
	        	//找到可以买的最高价格，也就是第一个buy<record的上一个
	            if(buy[k].price < record[i].price){
	            	break;
				}
	        }
	        for(j = 1; j < b; j++){
	        	//找到可以卖的最低价格，也就是第一个sell<record的上一个
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
输入
buy 9.25 100
buy 8.88 175
sell 9.00 1000
buy 9.00 400
sell 8.92 400
cancel 1
buy 100.00 50
输出
9.00 450
=================================================================*/
/*
问题描述
　　某股票交易所请你编写一个程序，根据开盘前客户提交的订单来确定某特定股票的开盘价和开盘成交量。
　　该程序的输入由很多行构成，每一行为一条记录，记录可能有以下几种：
　　1. buy p s 表示一个购买股票的买单，每手出价为p，购买股数为s。
　　2. sell p s 表示一个出售股票的卖单，每手出价为p，出售股数为s。
　　3. cancel i表示撤销第i行的记录。
　　如果开盘价为p0，则系统可以将所有出价至少为p0的买单和所有出价至多为p0的卖单进行匹配。因此，此
时的开盘成交量为出价至少为p0的买单的总股数和所有出价至多为p0的卖单的总股数之间的较小值。
　　你的程序需要确定一个开盘价，使得开盘成交量尽可能地大。如果有多个符合条件的开盘价，你的程序应
当输出最高的那一个。
输入格式
　　输入数据有任意多行，每一行是一条记录。保证输入合法。股数为不超过108的正整数，出价为精确到恰好
小数点后两位的正实数，且不超过10000.00。
输出格式
　　你需要输出一行，包含两个数，以一个空格分隔。第一个数是开盘价，第二个是此开盘价下的成交量。开
盘价需要精确到小数点后恰好两位。
样例输入
buy 9.25 100
buy 8.88 175
sell 9.00 1000
buy 9.00 400
sell 8.92 400
cancel 1
buy 100.00 50
样例输出
9.00 450
评测用例规模与约定
　　对于100%的数据，输入的行数不超过5000。
*/
