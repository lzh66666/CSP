#include <bits/stdc++.h>

using namespace std;

int monthDay[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

//�ж��Ƿ�������
bool isLunarYear(int year){
    return (year%4 == 0 && year%100 ) || (year%400 == 0);
}

//�ַ���ת��Ϊ����
int string_to_num(string str){
	int num;stringstream ss;
    ss << str;ss >> num;
	return num;
}

//����ת��Ϊ�ַ���
string num_to_string(int num){
	string str;stringstream ss;
    ss << num;ss >> str;
	return str;
}
//��������ĸת��ΪСд
void string_to_lower(string &str){
	transform(str.begin(), str.end(), str.begin(), ::tolower);
}

//���·ݻ�����ת��Ϊ���ַ������
void mw_to_num(string &str) {
	string_to_lower(str);int num=-1;
 	string month[12] = { "jan","feb","mar","apr","may","jun","jul",
						"aug","sep","oct","nov","dec" };//12����
	string week[7] = { "sun","mon","tue","wed","thu","fri","sat" };//һ������
	for (int i = 0; i < str.length(); i++) {
		if (str[i] >= 'a' && str[i] <= 'z') {
			string mon_or_week = str.substr(i, 3);
			for (int j = 0; j < 12; j++)
				if (mon_or_week == month[j])
					num = j + 1;
			for (int j = 0; j < 7; j++)
				if (mon_or_week == week[j])
					num = j;
            if(num != -1){
            	string s = num_to_string(num);
				str.replace(i, 3, s);
			}
			num = -1;
		}
	}
}

//�ж�ĳ��ĳ��ĳ�������ڼ�
int getDayOfWeek(int year, int month, int day){
    int nowDay = 0;
    for (int i = 1970; i <= year - 1; i++){
        if (isLunarYear(i)){
        	nowDay += 366;
		}
        else{
        	nowDay += 365;
		}
    }
    for (int i = 0; i < month-1; i++){
        if (isLunarYear(year) && i == 1){
        	nowDay += 29;
		}
        else{
        	nowDay += monthDay[i];
		}
    }
    nowDay += day;
    nowDay = nowDay % 7;//����˵��ʱӦ�þͿ��ԣ�������Ŀ��˵1970.1.1�������ģ�������Ӧ���ټ���һ��
    nowDay = (nowDay + 3) % 7;
    return nowDay;
}

//����'*'�ַ�
void deal1(string &str,string name){
	if(str == "*"){
		if(name == "minute"){
			str = "0-59";
		}else if(name == "hour"){
			str = "0-23";
		}else if(name == "day"){
			str = "1-31";
		}else if(name == "month"){
			str = "1-12";
		}else if(name == "week"){
			str = "0-6";
		}
	}
}

//����'-'�ַ�
void deal2(string &str){

	int pos = str.find("-");
	while(pos != string::npos){
		int i = pos+1;
		while(str[i]>='0' && str[i]<= '9'){
			i++;
			if(str[i] == ','){
				i--;
				break;
			}
		}
		string ss = str.substr(pos+1,i-pos);
		int maxx = string_to_num(ss);

		i = pos-1;
		while(str[i]>='0' && str[i]<= '9'){
			i--;
			if(i<0){
				i = 0;
				break;
			}
			if(str[i] == ','){
				i++;
				break;
			}
		}
		ss = str.substr(i,pos-i);
		int minn = string_to_num(ss);

		pos = str.find("-");
		str.erase(pos,1);
		i = 0;
		for(int j = minn+1; j < maxx;j++){
			string s = ","+num_to_string(j);
			str.insert(pos+i,s);
			i += s.size();
		}
		str.insert(pos+i,",");
		pos = str.find("-");
	}
}

//����','�������з��ϵĴ浽vec��
void deal3(string str,vector<string> & vec){
	string s;
	str += ",";
	for(int i = 0; i < str.size(); i++){
		if(str[i] == ','){
			vec.push_back(s);
			s = "";
		}else{
			s += str[i];
		}
	}
}

//�ж�ĳ�������ڼ��Ƿ���ڣ���vector�Ƿ����ĳԪ���Ƿ����
bool judge(string str,vector<string> vec){
	vector<string>::iterator iter = find(vec.begin(), vec.end(), str);
	if(iter != vec.end()){
		return true;
	}
	return false;
}

//��������
struct node{//Ϊ�˽��ʱ��һ��ʱ��˳�������԰�key���һ���ṹ��
	string key;
	int i;
	bool operator < (const node &n) const{
		return key < n.key;
	}
};
typedef pair<node, vector<string> > PAIR;
bool cmp(const PAIR& x, const PAIR& y){
	if(x.first.key == y.first.key){//����һ��ʱ���ʱ����˳����
		x.first.i < y.first.i;
	}
	return x.first.key < y.first.key;//����Ļ���С������һ��
}


int main(){
	string str,s,t;int n;
	cin >> n >> s >> t;cin.get();

	string year1=s.substr(0,4);
    string year2=t.substr(0,4);

    map<node,vector<string> > mResult;
	for(int i = 0; i < n; i++){
		int y1=string_to_num(year1);int y2=string_to_num(year2);
		string minute,hour,day,month,week,command;
		vector<string> vMM,vHH,vdd,vmm,vww;

		getline(cin,str);
		istringstream line(str);
		line >> minute >> hour >> day >> month >> week >> command;

		deal1(minute,"minute");deal1(hour,"hour");deal1(day,"day");deal1(month,"month");deal1(week,"week");
		mw_to_num(month);mw_to_num(week);
		deal2(minute);deal2(hour);deal2(day);deal2(month);deal2(week);
		deal3(minute,vMM);deal3(hour,vHH);deal3(day,vdd);deal3(month,vmm);deal3(week,vww);
		node nod;nod.i = i;
		while(y1 <= y2){
			if(isLunarYear(y1)){
				monthDay[1] = 29;
			}else{
				monthDay[1] = 28;
			}
			for(int i = 0; i < vmm.size(); i++){
				string mon = vmm[i];//���·�
				for(int j = 0; j < vdd.size(); j++){
					string dd = vdd[j];//����
					string ww = num_to_string(getDayOfWeek(y1,string_to_num(mon),string_to_num(dd)));//���ڼ�
					if(judge(ww,vww) && string_to_num(dd) <= monthDay[string_to_num(mon)-1]){//��������жϣ���Ȼֻ��30�֣������С�ڵ�������
                        for(int k = 0; k < vHH.size(); k++){
                        	for(int m = 0; m < vMM.size(); m++){
                        		if(mon.size()==1)mon = "0"+mon;//һ�Ѳ�0����
                        		if(dd.size()==1)dd = "0"+dd;
                        		if(vHH[k].size()==1)vHH[k]="0"+vHH[k];
                        		if(vMM[m].size()==1)vMM[m]="0"+vMM[m];
                        		string alltime = num_to_string(y1)+mon+dd+vHH[k]+vMM[m];
                        		if(alltime>=s && alltime<t){//����ҿ������������������������������˴�һֱ��70�֣���ס
									nod.key = alltime;
									mResult[nod].push_back(command);
								}
							}
						}
					}
				}
			}
			y1++;
		}
	}

	vector<PAIR> vec(mResult.begin(),mResult.end());
	sort(vec.begin(), vec.end(), cmp);
	for (int i = 0; i < vec.size(); i++) {
		for(int j = 0; j < vec[i].second.size(); j++){
			cout << vec[i].first.key <<" "<<vec[i].second[j] << endl;
		}
  	}
	return 0;
}

/*=================================================================
����
3 201711170032 201711222352
0 7 * * 1,3-5 get_up
30 23 * * Sat,Sun go_to_bed
15 12,18 * * * have_dinner
���
201711170700 get_up
201711171215 have_dinner
201711171815 have_dinner
201711181215 have_dinner
201711181815 have_dinner
201711182330 go_to_bed
201711191215 have_dinner
201711191815 have_dinner
201711192330 go_to_bed
201711200700 get_up
201711201215 have_dinner
201711201815 have_dinner
201711211215 have_dinner
201711211815 have_dinner
201711220700 get_up
201711221215 have_dinner
201711221815 have_dinner
=================================================================*/
/*
��Ŀ��03.png
*/
