#include <bits/stdc++.h>

using namespace std;

int daysOfMonth[12] = {31,28,31,30,31,30,31,31,30,31,30,31};

// y年是否是闰年
bool isLeap(int y) {
    return y%4==0 && y%100!=0 || y%400==0;
}

// 0001年到y年（包括）有多少个闰年,牛牛牛牛牛
int numLeapYear(int y) {
    return y/4 - y/100 + y/400;
}

// y/m/d离0001/01/01有多少天
// 0001/01/01星期一
int numDays(int y, int m, int d) {
    int days = 365 * (y-1);
    days += numLeapYear(y-1);
    int i = 0;
    while(i < m) {
        days += daysOfMonth[i];
        i++;
    }
    days += d;
    return days;
}

// y/m/d 星期几
int weekday(int y, int m, int d) {
    int days = numDays(y, m, d);
    int weekd = 0;
    weekd = (weekd + days) % 7;
    return weekd;
}

int main() {
    int a, b, c, y1, y2;
    cin >> a >> b >> c >> y1 >> y2;
    a--, b--, c--; // 月份，日期默认从0开始计数

    for(int y = y1; y <= y2; y++) {
        if(isLeap(y)){
        	daysOfMonth[1] = 29;
		}else{
			daysOfMonth[1] = 28;
		}
        int weekd = weekday(y, a, 0); // y年a月1日星期几
        int day = (c-weekd+7)%7 + b*7;
        if(day >= daysOfMonth[a]){
        	printf("none\n");
		}else{
			printf("%04d/%02d/%02d\n", y, a+1, day+1);
		} 
    }
    return 0;
}

/*=================================================================
输入
5 2 7 2014 2015
输出
2014/05/11
2015/05/10
=================================================================*/
/*
问题描述
　　有一类节日的日期并不是固定的，而是以“a月的第b个星期c”的形式定下来的，比如说母亲节就定为每年的五月的第二个星期日。
　　现在，给你a，b，c和y1, y2(1850 ≤ y1, y2 ≤ 2050)，希望你输出从公元y1年到公元y2年间的每年的a月的第b个星期c的日期。
　　提示：关于闰年的规则：年份是400的整数倍时是闰年，否则年份是4的倍数并且不是100的倍数时是闰年，其他年份都不是闰年。
例如1900年就不是闰年，而2000年是闰年。
　　为了方便你推算，已知1850年1月1日是星期二。
输入格式
　　输入包含恰好一行，有五个整数a, b, c, y1, y2。其中c=1, 2, ……, 6, 7分别表示星期一、二、……、六、日。
输出格式
　　对于y1和y2之间的每一个年份，包括y1和y2，按照年份从小到大的顺序输出一行。
　　如果该年的a月第b个星期c确实存在，则以"yyyy/mm/dd"的格式输出，即输出四位数的年份，两位数的月份，两位数的日期，中间
用斜杠“/”分隔，位数不足时前补零。
　　如果该年的a月第b个星期c并不存在，则输出"none"（不包含双引号)。
样例输入
5 2 7 2014 2015
样例输出
2014/05/11
2015/05/10
评测用例规模与约定
　　所有评测用例都满足：1 ≤ a ≤ 12，1 ≤ b ≤ 5，1 ≤ c ≤ 7，1850 ≤ y1, y2 ≤ 2050。
*/
