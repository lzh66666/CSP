#include <bits/stdc++.h>

using namespace std;

/*
    只能达到70分，能力有限，啊啊啊啊啊啊啊！！！！！！！！！
*/
int n,m;

map<string,string> json;
vector<string> vet;

void trim(string &line){//此函数是将一个字符串的首尾空格删掉
	if(!line.empty()){
    	line.erase(0,line.find_first_not_of(" "));
    	line.erase(line.find_last_not_of(" ") + 1);
 	}
}

void clear (string &line){  //此函数是将反斜杠去除（题目要求）
	for (int i = 0; i < line.size(); ++i){
		if (line[i] == '\\'){
			line.erase(line.begin() + i);
		}
	}
}

void da_left(string &line){//此函数为format函数服务，处理左大括号{
	string line1 = line;
	int s1 = line1.find("{");
	line = "";
	while(s1 != string::npos){
		line1.insert(s1+1,",");
		line += line1.substr(0,s1+1);
		line1.erase(0,s1+1);
		s1 = line1.find("{");
	}
	line += line1;
}

void da_right(){//此函数为format函数服务，处理右大括号{，不知什么原因，用处理‘{’的方法处理‘}’会出错，所以换了一种方法
	if(vet[vet.size()-1].find("}") != string::npos){
		string s = vet[vet.size()-1];
		s = s.substr(0,s.size()-1);trim(s);
		vet[vet.size()-1] = s;
		da_right();
		vet.push_back("}");
	}
}

void format(string line){//将不规范的格式转化为标准的json格式，即题目中的美观模式
	trim(line);
	da_left(line);//对左大括号后面加逗号，以便和属性一样处理
	while(line.find(",") != string::npos){
		int start = line.find(",");
		string s = line.substr(0,start);
		trim(s);vet.push_back(s);
		da_right();//可能是对象的最后一个，所以进行去除右大括号操作
		line.erase(0,start+1);trim(line);
	}
	if(line.size() > 0 && line.find(",") == string::npos){//对象最后一个没有逗号，将最后的值存储
		trim(line);vet.push_back(line);
	}
	da_right();//最后一个存储的时候多了一个右大括号}，去除
}

void deal(){    //将合格的json存储到map中
	for(int i = 0; i < vet.size(); i++){
		if(vet[i] != "" && vet[i] != "{" && vet[i] != "}" && vet[i] != "},"){
			string s = vet[i];
			int split = s.find(":");
			if(split != string::npos){
				string key = s.substr(0,split);trim(key);//截取属性
				key = key.substr(1,key.size()-2);//处理key的双引号

				string value = s.substr(split+1);trim(value);   //截取属性值
				if(value.find("{") == string::npos){    //如果不出对象，则进行
					value = value.substr(1,value.size()-2);//处理value的双引号
				}
				json[key] = value;//存储到map中
			}
		}
	}
}



int main(){
	cin >> n >> m;
	cin.get();
	
	string jsonString;
	while(n){//先将字符串拼成一行，再利用format分开，可能有多个空行的问题
		string line;
		getline(cin,line);trim(line);
		if(line != ""){
			jsonString += line;
		}
		n--;
	}
	clear(jsonString);//清除转义字符
	format(jsonString); //将一行字符美化成正常格式
	deal();         //将字符对匹配存到map中，一一对应


	//测试格式化之后是否正确
	for(int i = 0; i < vet.size(); i++){
		cout << vet[i] << endl;
	}
/*	//测试属性和属性值存储之后是否正确
	for (map<string,string>::iterator iter = json.begin();iter != json.end(); iter++){
        cout << iter->first << "->" << iter->second << endl;
    }
*/
	vector<string> vec;//为了输出整齐，存储到vec中
	while(m){
		string s;
		cin >> s;
		
		if(s.find(".") != string::npos){
			string t;
			while(s.find(".") != string::npos){//对象处理
				int start = s.find(".");
				t = s.substr(0,start);
				if(json.find(t) != json.end()){
					s.erase(0,start+1);//如果都符合，则只留下最后一层
				}else{
					s = t;//有不正确的字符退出，并将其赋给s;
					break;
				}
			}
			//处理完成，退出之后利用下面的字符串处理，存储
		}
		
		if(json.find(s) != json.end()){//字符串处理，存储到vector中,最后输出
			if(json[s] == "{"){ //对象
				vec.push_back("OBJECT");
			}else{  //字符串
				vec.push_back("STRING " + json[s]);
			}
		}else{  //不存在
			vec.push_back("NOTEXIST");
		}
		m--;
	}
	
	for(int i = 0; i < vec.size(); i++){
		cout << vec[i] << endl;
	}
	return 0;
}

/*=================================================================
1 5
{"firstName": "John","lastName": "Smith","address": {"streetAddress": "2ndStreet","city": {"ddd":""},"state":"NY"},"esc\\aped": "\"hello\""}
firstName
address
address.city.ddd
address.postal
esc\aped
输入
11 5
{
"firstName": "John",
"lastName": "Smith",
"address":
{
"streetAddress": "2ndStreet",
"city": "NewYork",
"state": "NY"
},
"esc\\aped": "\"hello\""
}
firstName
address
address.state
address.postal
esc\aped
输出
STRING John
OBJECT
STRING NewYork
NOTEXIST
STRING "hello"
=================================================================*/
/*
问题描述
　　JSON (JavaScript Object Notation) 是一种轻量级的数据交换格式，可以用来描述半结构化的数据。
JSON 格式中的基本单元是值 (value)，出于简化的目的本题只涉及 2 种类型的值：
　　* 字符串 (string)：字符串是由双引号 " 括起来的一组字符（可以为空）。如果字符串的内容中出
现双引号 "，在双引号前面加反斜杠，也就是用 \" 表示；如果出现反斜杠 \，则用两个反斜杠 \\ 表示。
反斜杠后面不能出现 " 和 \ 以外的字符。例如：""、"hello"、"\"\\"。
　　* 对象 (object)：对象是一组键值对的无序集合（可以为空）。键值对表示对象的属性，键是属性名，
值是属性的内容。对象以左花括号 { 开始，右花括号 } 结束，键值对之间以逗号 , 分隔。一个键值对的键
和值之间以冒号 : 分隔。键必须是字符串，同一个对象所有键值对的键必须两两都不相同；值可以是字符串，
也可以是另一个对象。例如：{}、{"foo": "bar"}、{"Mon": "weekday", "Tue": "weekday", "Sun": "weekend"}。
　　除了字符串内部的位置，其他位置都可以插入一个或多个空格使得 JSON 的呈现更加美观，也可以在一些
地方换行，不会影响所表示的数据内容。例如，上面举例的最后一个 JSON 数据也可以写成如下形式。
　　{
　　"Mon": "weekday",
　　"Tue": "weekday",
　　"Sun": "weekend"
　　}
　　给出一个 JSON 格式描述的数据，以及若干查询，编程返回这些查询的结果。
输入格式
　　第一行是两个正整数 n 和 m，分别表示 JSON 数据的行数和查询的个数。
　　接下来 n 行，描述一个 JSON 数据，保证输入是一个合法的 JSON 对象。
　　接下来 m 行，每行描述一个查询。给出要查询的属性名，要求返回对应属性的内容。需要支持多层查询，各层
的属性名之间用小数点 . 连接。保证查询的格式都是合法的。
输出格式
　　对于输入的每一个查询，按顺序输出查询结果，每个结果占一行。
　　如果查询结果是一个字符串，则输出 STRING <string>，其中 <string> 是字符串的值，中间用一个空格分隔。
　　如果查询结果是一个对象，则输出 OBJECT，不需要输出对象的内容。
　　如果查询结果不存在，则输出 NOTEXIST。
样例输入
10 5
{
"firstName": "John",
"lastName": "Smith",
"address": {
"streetAddress": "2ndStreet",
"city": "NewYork",
"state": "NY"
},
"esc\\aped": "\"hello\""
}
firstName
address
address.city
address.postal
esc\aped
样例输出
STRING John
OBJECT
STRING NewYork
NOTEXIST
STRING "hello"
评测用例规模与约定
　　n ≤ 100，每行不超过 80 个字符。
　　m ≤ 100，每个查询的长度不超过 80 个字符。
　　字符串中的字符均为 ASCII 码 33-126 的可打印字符，不会出现空格。所有字符串都不是空串。
　　所有作为键的字符串不会包含小数点 .。查询时键的大小写敏感。
　　50%的评测用例输入的对象只有 1 层结构，80%的评测用例输入的对象结构层数不超过 2 层。举例来说，{"a": "b"}
是一层结构的对象，{"a": {"b": "c"}} 是二层结构的对象，以此类推。
*/
